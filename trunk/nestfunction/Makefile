
SRCS=nestfunction.c
OBJS=nestfunction.o my_index.o
TARGET=nestfunction
WARN=-Wall -Winline 
MAKEFLAGS=--print-directory -Wall 


help:
	@echo ---------------------------------------------
	@echo 
	@echo input make all --- make the executable  file
	@echo 
	@echo ---------------------------------------------
$(OBJS):%.o:%.c
	gcc $(WARN) -c $< -o $@
#$(OBJS):$(SRCS)
#	echo generating objs
#	gcc $(WARN) -c $< -o $@
	
$(TARGET): $(OBJS)
	@echo generating target
	gcc $(WARN) -o $@ $(OBJS)
	
all: $(TARGET)

.PHONY: all $(TARGET) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
	
.PHONY: clean
