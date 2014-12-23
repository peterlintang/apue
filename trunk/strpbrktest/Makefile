

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
TARGET=strp
MAKEFLAGS=--print-directory -Wall
%.o:%.c
	gcc -c $< -o $@

all: $(OBJS)  $(TARGET)
#	gcc -o $@ $(OBJS)

$(TARGET): $(OBJS)
	gcc -o $@ $(OBJS)

clean:
	rm -f $(OBJS) all

.PHONY: all clean
	

