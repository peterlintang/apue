SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRC))
TARGETS=foo bar
ifndef GCC
GCC:=gcc
endif

G++:=$(subst cc,++, $(GCC))
all: $(TARGETS)
	@echo $(GCC)
	@echo $(G++)
foo:$(OBJS)
	@echo fooing...
bar:$(OBJS)
	@echo baring...
$(OBJS):$(SRCS)
	@echo objsing...
#	gcc -o $@ $<
clean:
	@echo cleaning...
.PHONY:all $(TARGETS) $(OBJS) clean
