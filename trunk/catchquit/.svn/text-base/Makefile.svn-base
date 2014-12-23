

SRCS=catchquit.c ../src/pr_mask.c
OBJS=catchquit.o pr_mask.o
TARGETS=catchquit
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

catchquit.o: catchquit.c
	gcc -I../include -c catchquit.c
pr_mask.o:../src/pr_mask.c
	gcc -I../include -c ../src/pr_mask.c
#$(OBJS):$(SRCS) 
#	gcc $(CFLAGS) -c $< -o $@
#COPY:
#	mv ../src/pr_mask.o ./
clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY:help all $(TARGET) $(OBJS) clean
