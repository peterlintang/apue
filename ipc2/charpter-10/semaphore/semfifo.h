
typedef struct {
	int sem_fd[2];
	int sem_magic;
} Sem_t;

#define SEM_MAGIC	0x89674523

#ifdef SEM_FAILED
#undef SEM_FAILED
#define SEM_FAILED	((Sem_t *)(-1))
#else
#define SEM_FAILED	((Sem_t *)(-1))
#endif

