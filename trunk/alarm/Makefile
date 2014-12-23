

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
#TARGETS=$(patsubst %.o, %, $(OBJS))
TARGETS=alarm alarm2
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

#$(TARGETS):$(OBJS)
#	gcc $(CFLAGS) $< -o $@

#$(OBJS):$(SRCS)
alarm: alarm.o
	gcc $(CFLAGS)  $< -o $@
alarm2: alarm2.o
	gcc $(CFLAGS)  $< -o $@
#%.o:%.c
#	gcc -c $(CFLAGS) $< -o $@
alarm.o: alarm.c
	gcc -c $(CFLAGS) $< -o $@
alarm2.o: alarm2.c
	gcc -c $(CFLAGS) $< -o $@
clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY:help all $(TARGETS) $(OBJS) clean
