CC = gcc
FLAGS = -Wall -g -o2 -o
SOURCE = main.c 
EXECUTABLE_PATH = ./checker/multi/so-cpp
EXECUTABLE = so-cpp
TEST_IN = ceva.txt
TEST_OUT = out.out



move: build
	cd ./checker/multi/; make -f Makefile.checker > result.out
build: 
	$(CC) $(SOURCE) $(FLAGS) $(EXECUTABLE_PATH)
	
local: build
	$(CC) $(SOURCE) $(FLAGS) $(EXECUTABLE)
run: local
	./$(EXECUTABLE) < $(TEST_IN) > $(TEST_OUT)


