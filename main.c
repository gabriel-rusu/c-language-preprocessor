#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 257
#define FAILED 2
#define SYMBOL_FLAG "-D"
#define FLAG_CHAR '-'


typedef struct Node{
    char *key;
    char *value;
    struct Node *address;
}Node;

typedef struct HashMap{
    int size;
    Node **array;
}HashMap;

int create_new(HashMap ** hashMap,int size);
int process_arguments(char **arguments,int argument_count,HashMap *hashMap);
bool is_invalid_flag(char *argument);
bool is_symbol(char *argument);
void freeMap(HashMap **hashMap);
void addSymbol(char **arguments,int index, HashMap* hashMap);

int main(int argc ,char **argv)
{
    HashMap *hashMap = NULL;
    create_new(&hashMap,argc);
    if(process_arguments(argv,argc,hashMap) == FAILED)
        exit(EXIT_FAILURE);
    freeMap(&hashMap);
}

void freeMap(HashMap **hashMap){
    free((*hashMap)->array);
    free(*hashMap);
}

int create_new(HashMap ** hashMap,int size){
    if(size<=0)
        return 0;
    *hashMap = malloc(sizeof(HashMap));
    (*hashMap)->size = size;
    (*hashMap)->array = malloc(sizeof(Node)*size);
}

int process_arguments(char **arguments,int argument_count,HashMap *hashMap){
    int index = 0;
    while(index < argument_count){
        if(is_symbol(arguments[index])){
            addSymbol(arguments,index,hashMap);
        }
        else if(is_invalid_flag(arguments[index]))
            return FAILED;
        index++;
    }
}

void addSymbol(char **arguments,int index, HashMap* hashMap){
    return;
}

bool is_symbol(char *argument){
    if(strlen(argument)>=2)
        return strcmp(argument,SYMBOL_FLAG) == 0 ? true : (argument[0] == '-' && argument[1] == 'D');
    else return false;
}

bool is_invalid_flag(char *argument){
    if(strlen(argument) >= 2)
        return argument[0] == FLAG_CHAR;
    return false;
}