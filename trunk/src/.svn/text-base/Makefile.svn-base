

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
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
all: $(OBJS)


$(OBJS):$(SRCS)
	gcc $(CFLAGS) -c $< -o $@
clean:
	rm $(OBJS) $(TARGETS)

.PHONY:help all  $(OBJS) clean
