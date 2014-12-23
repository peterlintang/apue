

SRCS=teststream.c ../src/err.c
OBJS=teststream.o err.o
TARGETS=teststream
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
	gcc $(CFLAGS) -o $@ $(OBJS)

teststream.o: teststream.c
	gcc -I../include -c teststream.c
err.o:../src/err.c
	gcc -I../include -c ../src/err.c
#$(OBJS):$(SRCS) 
#	gcc $(CFLAGS) -c $< -o $@
#COPY:
#	mv ../src/pr_mask.o ./
clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY:help all $(TARGET) $(OBJS) clean
