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
void verify(void *pointer,int line_numer){
    if(pointer==NULL)
    {
        printf("Allocation error on line %d!\n",line_numer);
        exit(EXIT_FAILURE);
    }
}
int main(int argc ,char **argv)
{
    HashMap *hashMap = NULL;
    create_new(&hashMap,argc);
    if(process_arguments(argv,argc,hashMap) == FAILED)
        exit(EXIT_FAILURE);
    freeMap(&hashMap);
    return 0;
}

void freeMap(HashMap **hashMap){
    if(*hashMap){
        free((*hashMap)->array);
        free(*hashMap);
    }
}

int create_new(HashMap ** hashMap,int size){
    if(size<=0)
        return 0;
    verify((*hashMap) = malloc(sizeof(HashMap)),__LINE__);
    (*hashMap)->size = size;
    verify((*hashMap)->array = malloc(sizeof(Node*)*size),__LINE__);
    return 0;
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
    return 0;
}

void addSymbol(char **arguments,int index, HashMap* hashMap){
    return;
}

bool is_symbol(char *argument){
    if(strlen(argument)>=2)
        return strcmp(argument,"-D") == 0 ? true : (argument[0] == '-' && argument[1] == 'D');
    else return false;
}

bool is_invalid_flag(char *argument){
    if(strlen(argument) >= 1)
        return argument[0] == FLAG_CHAR;
    return false;
}