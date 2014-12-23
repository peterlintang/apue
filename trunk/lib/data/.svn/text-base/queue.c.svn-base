/*
 * implement queue interface
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int _grow_cqueue(cqueue_t *q)
{
	if (q->num_chunks != q->max_chunks) {
		uint16_t grow_by = q->chunk_size;
		queue_item_t *chunk = \
			(queue_item_t *)calloc(grow_by, sizeof(queue_item_t));
		queue_item_t *ptr = chunk;
		if (chunk) {
			if (q->putpos && q->getpos) {
				ptr = chunk + (grow_by -1);
				ptr->next = q->putpos->next;
				q->putpos->next = chunk;
			} else {
				ptr = chunk + (grow_by -1);
				ptr->next = chunk;
				q->putpos = q->getpos = chunk;
			}
			while (--grow_by) {
				ptr = chunk + (grow_by -1);
				ptr->next = chunk + grow_by;
			}
			q->chunks[q->num_chunks] = chunk;
			q->num_chunks++;
			return 1;
		}
	}
	return 0;
}

/* 
 * save @q->num_chunks chunk as the first
 * int @q->chunks and destroy others
 *
 */
void _shrink_cqueue(cqueue_t *q)
{
	if (q->num_chunks > 1) {
		queue_item_t *save = q->chunks[q->num_chunks - 1];
		queue_item_t *ptr = save + (q->chunk_size - 1);
		ptr->next = save;

		while (--q->num_chunks) {
			free(q->chunks[q->num_chunks - 1]);
		}

		q->chunks[0] = save;
		q->num_chunks = 1;
		q->putpos = q->getpos = save;
	}
}

cqueue_t *_new_cqueue(uint32_t chunk_size, unsigned char max_chunks)
{
	cqueue_t *cqueue = calloc(1, sizeof(cqueue_t));
	if (cqueue) {
		cqueue->chunk_size = (chunk_size > QUEUE_CHUNK_SIZE) ? \
				chunk_size : QUEUE_CHUNK_SIZE;
		cqueue->max_chunks = (max_chunks > 0) ? \
				max_chunks : 1;
		pthread_mutex_init(&cqueue->lock, NULL);
		pthread_cond_init(&cqueue->wait, NULL);
		
		if (!_grow_cqueue(cqueue)) {
			free(cqueue);
			return NULL;
		}
	}
	return cqueue;
}

void _destroy_cqueue(cqueue_t **queue_ptr)
{
	if (queue_ptr) {
		cqueue_t *queue = *queue_ptr;
		if (queue) {
			while (queue->getpos != queue->putpos) {
				free(queue->getpos->node);
				queue->getpos = queue->getpos->next;
			}
			/* empty queue now */
			while (queue->num_chunks) {
				free(queue->chunks[queue->num_chunks - 1]);
				queue->num_chunks--;
			}
			free(queue);
			*queue_ptr = NULL;
		}
	}
}

int _put_cqueue(cqueue_t *queue, void *in)
{
	if (queue && !queue->disabled) {
		if (!in) {
			fprintf(stdout, "NULL data requested \
					to be placed into the queue");
			return 1;
		}

		pthread_mutex_lock(&queue->lock);

		if (queue->putpos->next == queue->getpos) {
			if (!_grow_cqueue(queue)) {
				pthread_mutex_unlock(&queue->lock);
				return 0;
			}
		}
		queue->putpos->node = in;
		queue->putpos = queue->putpos->next;
		queue->pending++;

		if (queue->blocking || queue->timeout > 0)
			pthread_cond_signal(&queue->wait);	
		pthread_mutex_unlock(&queue->lock);
		return 1;
	}
	return 0;
}

/* should be called with @q->lock locked, inner use */
void __get_data_timeout_block(cqueue_t *q, void **data_ptr)
{
	if (q->blocking) {
		if (!pthread_cond_wait(&q->wait, &q->lock) &&
			q->getpos->node) {
			*data_ptr = q->getpos->node;
			q->getpos->node = NULL;
			q->getpos = q->getpos->next;
			q->pending--;
		}
	} else if (q->timeout > 0) {
		struct timeval now;
		struct timespec to;
		gettimeofday(&now, NULL);

		to.tv_sec = now.tv_sec + q->timeout / 1000;
		to.tv_nsec = (now.tv_usec * 1000) + (q->timeout % 1000 * 1000000);
		if (to.tv_nsec >= 1000000000) {
			to.tv_sec += 1;
			to.tv_nsec %= 1000000000;
		}

		if (!pthread_cond_timeout(&q->wait, 
				&q->lock, 
				(const struct timespec *)(&to)) &&
			q->getpos->node) {
			*data_ptr = q->getpos->node;
			q->getpos->node = NULL;
			q->getpos = q->getpos->next;
			q->pending--;
		} else {
			fprintf(stdout, "timeout or no data\n");
		}
	}
}

void *_get_cqueue(cqueue_t *queue)
{
	void *data = NULL;
	if (queue) {
		pthread_mutex_lock(&queue->lock);
		if (queue->getpos == queue->putpos) _shrink_cqueue(queue);

		if (queue->getpos->node) {
			data = queue->getpos->node;
			queue->getpos->node = NULL;
			queue->getpos = queue->getpos->next;
			queue->pending--;
		} else if (!queue->disabled) {
			__get_data_timeout_block(queue, &data);
		}
	pthread_mutex_unlock(&queue->lock);
	}
	return data;
}

void *_drop_cqueue(cqueue_t *queue)
{
	if (queue) {
		void *data = _get_cqueue(queue);
		if (data)
			queue->drops++;
		return data;
	}
	return NULL;
}


/* toggle 0 or 1 , it is a boolean_t */
void _set_blocking_cqueue(cqueue_t *queue, int toggle)
{
	if (queue)
		queue->blocking = toggle;
}

void _set_timeout_cqueue(cqueue_t *queue, uint32_t timeout_ms)
{
	if (queue)
		queue->timeout = timeout_ms;
}

void _disable_cqueue(cqueue_t *queue)
{
	if (queue)
		queue->disabled = 1;
}

