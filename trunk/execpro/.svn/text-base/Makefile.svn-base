

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
TARGETS=$(patsubst %.o, %, $(OBJS))
MAKEFLAGS=--print-directory --Wall

help:
	@echo -----------------------------------------
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(TARGETS)
	@echo make all
	@echo 
	@echo -----------------------------------------
	
#%.o:%.c
#	gcc -c $< -o $@
all:$(TARGETS)

$(TARGETS):$(OBJS)
	gcc -o $@ $(OBJS)

$(OBJS):%.o:%.c
	gcc -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY:help all $(TARGET) $(OBJS) clean
