

SRCS=showprtct.c ../src/pr_mask.c
OBJS=showprtct.o pr_mask.o
TARGETS=showprtct
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

showprtct.o: showprtct.c
	gcc -I../include -c showprtct.c
pr_mask.o:../src/pr_mask.c
	gcc -I../include -c ../src/pr_mask.c
#$(OBJS):$(SRCS) 
#	gcc $(CFLAGS) -c $< -o $@
#COPY:
#	mv ../src/pr_mask.o ./
clean:
	rm $(OBJS) $(TARGETS)

.PHONY:help all $(TARGET) $(OBJS) clean
