CC = gcc
FLAGS = -Wall -g -o2 -o
SOURCE = main.c 
EXECUTABLE_PATH = ./checker/multi/so-cpp
EXECUTABLE = so-cpp
TEST_IN = checker/multi/_test/inputs/test7.in
TEST_OUT = out.out



move: build
	cd ./checker/multi/; make -f Makefile.checker > result.out
build: 
	$(CC) $(SOURCE) $(FLAGS) $(EXECUTABLE_PATH)
	
test: test_build
	./$(EXECUTABLE) < $(TEST_IN) > $(TEST_OUT)
	# rm -f $(EXECUTABLE)

test_build:
	$(CC) $(SOURCE) $(FLAGS) $(EXECUTABLE)
	



