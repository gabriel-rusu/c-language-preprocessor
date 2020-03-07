#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 257
#define FAILED 2
#define SYMBOL_FLAG "-D"
#define FLAG_CHAR '-'
#define INPUT_FILE_EXTENSION ".in"
#define OUTPUT_FILE_EXTENSION ".out"
#define INVALID_FILE_EXTENSION "."
#define SUCCESS 13


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
int process_arguments(char **arguments,int argument_count,HashMap *hashMap,FILE **file_in,FILE **file_out);
bool is_invalid_flag(char *argument);
bool is_symbol(char *argument);
void freeMap(HashMap **hashMap);
void addSymbol(char **arguments,int index, HashMap* hashMap);

bool is_file(char * name,char * extension);
void verify(void *pointer,int line_number);
int process(FILE *file_in,FILE *file_out,HashMap *hashMap);

int hash(char *key,int size){
    int sum = 0;
    for(int index = 0;key[index] != '\0';index++)
        sum+= key[index];
    return sum%size;
}

void add_at(Node *head,char *key,char *value){
    Node *newNode = malloc(sizeof(Node));
    if(head->address){
        Node *temp =  head->address;
        newNode->address = temp;
        head->address = newNode;
    }else{
        head->address = newNode;
    }
    newNode->key = strdup(key);
    newNode->value = strdup(value);
        
}

void add_into(HashMap * hashMap,char *key,char *value){
    add_at(hashMap->array[hash(key,hashMap->size)],key,value);
}

void delete(Node **node){
    free((*node)->value);
    free((*node)->key);
    free(&(*node));

}


int main(int argc ,char **argv)
{
    HashMap *hashMap = NULL;
    FILE *file_in = stdin,*file_out = stdout;
    create_new(&hashMap,argc+1);
    if(process_arguments(argv,argc,hashMap,&file_in,&file_out) == FAILED){
        printf("ARGUMENT PROCESSING FAILED");
        exit(EXIT_FAILURE);
    }
    process(file_in,file_out,hashMap);
    
    freeMap(&hashMap);
    fclose(file_out);
    fclose(file_in);
    return 0;
}

int process(FILE *file_in,FILE *file_out,HashMap *hashMap){
    char line[256];
    char prev_line[256] = "";
    while (fscanf(file_in,"%[^\n]s",line)!=EOF)
    {
        if(strcmp(line,prev_line)==0)
            break;
        memcpy(prev_line,line,256);
        fprintf(file_out,"%s\n",line);

    }
    return SUCCESS;
}

bool is_file(char * name,char * extension){
    return strstr(name,extension)!=NULL;
}

void freeMap(HashMap **hashMap){
    if(*hashMap){
        free((*hashMap)->array);
        free(*hashMap);
        *hashMap = NULL;
    }
}

void verify(void *pointer,int line_number){
    if(pointer==NULL)
    {
        printf("Allocation error on line %d!\n",line_number);
        exit(EXIT_FAILURE);
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

int process_arguments(char **arguments,int argument_count,HashMap *hashMap,FILE **file_in,FILE **file_out){
    int index = 0;
    while(index < argument_count){
        if(is_symbol(arguments[index])){
            addSymbol(arguments,index,hashMap);
        }
        else if(is_file(arguments[index],INPUT_FILE_EXTENSION)){
            verify(*file_in = fopen(arguments[index],"r"),__LINE__);
        }else if(is_file(arguments[index],OUTPUT_FILE_EXTENSION)){
            verify(*file_out = fopen(arguments[index],"w"),__LINE__);
        }else if(is_file(arguments[index],INVALID_FILE_EXTENSION)&& (is_file(arguments[index],"./")==false))
            return FAILED;
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