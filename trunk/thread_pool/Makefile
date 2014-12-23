################OPTION###################
CCOMPILE = gcc
CPPCOMPILE = g++
INCLUDEDIR = -I.
LINK = g++


OBJS = thread_pool.o test_thread_pool.o

COMPILEOPTION += -O3 
LINKOPTION = -o test-thread-pool -Wl
OUTPUT = test-thread-pool

SHAREDLIB += -lrt -lpthread

$(OUTPUT): $(OBJS)
	$(LINK) $(LINKOPTION) $(OBJS) $(SHAREDLIB)

clean: 
	rm -f $(OBJS)
	rm -f $(OUTPUT)
	rm -rf .test_thread_pool*
	rm -rf .test_thread_pool*
	rm -rf .thread_pool*
all: clean $(OUTPUT)
.PRECIOUS:%.cpp %.c %.C
.SUFFIXES:
.SUFFIXES:  .c .o .cpp .ecpp .pc .ec .C .cc .cxx

.cpp.o:
	$(CPPCOMPILE) -c -o $*.o $(COMPILEOPTION) $(INCLUDEDIR)  $*.cpp
	
.cc.o:
	$(CCOMPILE) -c -o $*.o $(COMPILEOPTION) $(INCLUDEDIR)  $*.cx

.cxx.o:
	$(CPPCOMPILE) -c -o $*.o $(COMPILEOPTION) $(INCLUDEDIR)  $*.cxx

.c.o:
	$(CCOMPILE) -c -o $*.o $(COMPILEOPTION) $(INCLUDEDIR) $*.c

.C.o:
	$(CPPCOMPILE) -c -o $*.o $(COMPILEOPTION) $(INCLUDEDIR) $*.C	

.ecpp.C:
	$(ESQL) -e $(ESQL_OPTION) $(INCLUDEDIR) $*.ecpp 
	
.ec.c:
	$(ESQL) -e $(ESQL_OPTION) $(INCLUDEDIR) $*.ec
	
.pc.cpp:
	$(PROC)  CPP_SUFFIX=cpp $(PROC_OPTION)  $*.pc
