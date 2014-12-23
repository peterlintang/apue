

SRCS=mysleep.c mysleep2.c
OBJS=mysleep.o mysleep2.o
TARGETS=mysleep mysleep2
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

mysleep:mysleep.c
	gcc ${CFLAGS} -o mysleep mysleep.c
mysleep2:mysleep2.c
	gcc ${CFLAGS} -o mysleep2 mysleep2.c ../src/sleep2.c
clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY:help all $(TARGET) $(OBJS) clean
