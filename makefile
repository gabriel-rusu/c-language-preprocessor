CC = gcc
FLAGS = -Wall -g -o2 -o
SOURCE = main.c 
EXECUTABLE_PATH = ./checker/multi/so-cpp
EXECUTABLE = so-cpp
TEST_IN = checker/multi/_test/inputs/test32.in
TEST_OUT = out.out
TEST_PARAM = checker/multi/_test/inputs/test28.param
PARAMS= -DDEBUG




move: build
	cd ./checker/; make -f Makefile.checker > result.out
build: 
	$(CC) $(SOURCE) $(FLAGS) $(EXECUTABLE_PATH)
	
test: local_build
	./$(EXECUTABLE) < $(TEST_IN) > $(TEST_OUT)
	# rm -f $(EXECUTABLE)

local_build:
	$(CC) $(SOURCE) $(FLAGS) $(EXECUTABLE)

test_p: local_build
	./$(EXECUTABLE) $(PARAMS) < $(TEST_IN) > $(TEST_OUT)
	# rm -f $(EXECUTABLE)



