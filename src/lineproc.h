#ifndef LINE_PROCESSING_H
#define LINE_PROCESSING_H
#include "list.h"
#include "utils.h"

int find_offset_for(char *line);
void prepare(char *line, LinkedList *linkedList);
void replace(char *line, char *key, char *value);


#endif