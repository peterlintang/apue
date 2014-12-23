

SRCS=recurisemutex.c ../src/makethread.c
OBJS=recurisemutex.o makethread.o
TARGETS=recurisemutex
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
	gcc -g $(CFLAGS) -o $@ $(OBJS) /usr/lib/libpthread.so

recurisemutex.o: recurisemutex.c
	gcc -g -I../include -c recurisemutex.c
makethread.o:../src/makethread.c
	gcc -g -I../include -c ../src/makethread.c
#$(OBJS):$(SRCS) 
#	gcc $(CFLAGS) -c $< -o $@
#COPY:
#	mv ../src/pr_mask.o ./
clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY:help all $(TARGET) $(OBJS) clean
