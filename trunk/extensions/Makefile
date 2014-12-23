###we use these to test the c program.
###modify these ? oh do it.
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
TARGETS=$(patsubst %.o, %, $(OBJS))
MAKEFLAGS=--print-directory --Wall 

help:
	@echo -----------------------------------------
	@echo your sources   objs    targets
	@echo      $(SRCS)   $(OBJS) $(TARGETS)
	@echo enter "make all" to make the program
	@echo 
	@echo -----------------------------------------
	
#%.o:%.c
#	gcc -c $< -o $@
all:$(TARGETS)

$(TARGETS):$(OBJS)
	gcc -o $@ $<

$(OBJS):$(SRCS)
	gcc -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY:help all $(TARGET) $(OBJS) clean
