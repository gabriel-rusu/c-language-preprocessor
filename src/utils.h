#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define FAILED 2
#define SUCCESS 1
#define FLAG_CHAR '-'
#define BUFFER_SIZE 256
#define SYMBOL_FLAG "-D"
#define INCLUDE_FLAG "-I"
#define INPUT_FILE_EXTENSION ".in"
#define OUTPUT_FILE_EXTENSION ".out"
#define INVALID_FILE_EXTENSION "."



#define PATH_TO_INPUT "_test/inputs/"
#define IFDEF_DIRECTIVE "#ifdef"
#define IFNDEF_DIRECTIVE "#ifndef"
#define INCLUDE_DIRECTIVE "#include"
#define DEFINE_DIRECTIVE "#define"




void verify(void *pointer, int line_number);

#endif