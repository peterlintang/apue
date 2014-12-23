
all:
	gcc -o parse-test parse_test.c ../data/parameter.c ../cmdparameters/parse_params.c -I../cmdparameters -I../data
	gcc -o stack_test stack_test.c ../data/simple_stack.c -I../data
	gcc -o queue_test queue_test.c ../data/simple_queue.c -I../data
	gcc -o quark_test quark_test.c ../sys/quark.c /usr/lib/libpthread.so -I../sys
	gcc -o cquark_test cquark_test.c ../sys/cquark.c ../sys/quark.c /usr/lib/libpthread.so -I../sys
	gcc -o tree_test tree_test.c ../data/simple_tree.c -I../data
	gcc -o parse-file parse-file.c ../inifile/inifile.c ../inifile/configuration.c ../inifile/category.c ../data/parameter.c ../data/str.c ../file/file.c -I../inifile -I../data -I../file
	gcc -o debug-test debug-test.c ../sys/debug.c -I../sys
clean:
	rm -rf stack_test queue_test quark_test cquark_test tree_test parse-file debug-test parse-test
