CC = gcc
FLAGS = -Wall -g -o2 -o
PATH_TO_SOURCES = ./src/
PATH_TO_TEST = ./test/
PATH_FOR_TESTS = ./_test/inputs/
SOURCES = $(PATH_TO_SOURCES)main.c $(PATH_TO_SOURCES)list.c $(PATH_TO_SOURCES)utils.c $(PATH_TO_SOURCES)fileproc.c $(PATH_TO_SOURCES)lineproc.c
EXECUTABLE_PATH = ./test/so-cpp
EXECUTABLE = so-cpp
TEST_IN = test38.in
TEST_OUT = test.out
TEST_PARAM = -D DEBUG=1 -D CUSTOM_DBG=custom-debugging -I _test/inputs/test38.dir


move: build
	cd $(PATH_TO_TEST);\
	make -f Makefile.checker > result.out
build: 
	$(CC) $(SOURCES) $(FLAGS) $(EXECUTABLE_PATH)
	
test: build
	cd $(PATH_TO_TEST);\
	./$(EXECUTABLE) $(TEST_PARAM) < $(PATH_FOR_TESTS)$(TEST_IN) > $(TEST_OUT);\
	# rm -f $(EXECUTABLE);

local_build:
	$(CC) $(SOURCE) $(FLAGS) $(EXECUTABLE)

test_one: build
	@read -p "Enter test name:" test; \  
    $(TEST_IN)=$(PATH_FOR_INPUT_TESTS)$$test; \
    mkdir -p $$module_dir/build




