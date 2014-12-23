#include ./test.d

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o, $(SRCS))
TARGETS=$(patsubst %.o,%, $(OBJS))

all: $(TARGETS)

$(TARGETS):$(OBJS)
	gcc -o $@ $<

$(OBJS):$(SRCS)
	gcc -c $< -o $@	

#test.d:test.c
#	gcc -M $<> $@.$$$$; \
#	sed 's,\($*\).o[:]*,\1.o $@:,g' <$@.$$$$> $@;\
#	#rm -f $@.$$$$
clean:
	rm -f $(TARGETS) $(OBJS)
.PHONY: all
.PHONY: $(TARGETS) $(OBJS)
.PHONY: clean
