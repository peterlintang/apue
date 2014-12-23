

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
TARGETS=$(patsubst %.o, %, $(OBJS))
MAKEFLAGS=--print-directory --Wall

export SRCS OBJS TARGETS
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
	gcc -o $@ $<

$(OBJS):$(SRCS)
	gcc -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY:help all $(TARGET) $(OBJS) clean
