

all:showexit

showexit:showexit.c ../src/err.c ../src/pr_exit.c
	gcc -I../include -o showexit showexit.c ../src/err.c ../src/pr_exit.c
clean: 
	rm -f showexit
.PHONY: clean showexit all
