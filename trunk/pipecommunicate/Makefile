

SRCS=pipecom.c ../src/err.c
OBJS=pipecom.o err.o
TARGETS=pipecom
MAKEFLAGS=--print-directory --Wall
CFLAGS=-I../include

help:
	@echo -----------------------------------------
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(TARGETS)
	@echo make all to make the program
	@echo 
	@echo -----------------------------------------
	
#%.o:%.c
#	gcc -c $< -o $@
all:$(TARGETS)

$(TARGETS):$(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

pipecom.o: pipecom.c
	gcc -I../include -c pipecom.c
err.o:../src/err.c
	gcc -I../include -c ../src/err.c
#$(OBJS):$(SRCS) 
#	gcc $(CFLAGS) -c $< -o $@
#COPY:
#	mv ../src/pr_mask.o ./
clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY:help all $(TARGET) $(OBJS) clean
