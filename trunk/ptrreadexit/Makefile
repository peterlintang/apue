

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
TARGETS=$(patsubst %.o, %, $(OBJS))
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
	gcc $(CFLAGS) -o $@ $< /usr/lib/libpthread.so

$(OBJS):$(SRCS)
	gcc $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY:help all $(TARGET) $(OBJS) clean
