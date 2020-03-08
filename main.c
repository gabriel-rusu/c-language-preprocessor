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

typedef struct LinkedList{
    int size;
    Node *head;
}LinkedList;

int create_new(LinkedList ** linkedList);
int process_arguments(char **arguments,int argument_count,LinkedList *linkedList,FILE **file_in,FILE **file_out);
bool is_invalid_flag(char *argument);
bool is_symbol(char *argument);
void freeList(LinkedList **linkedList);
void addSymbol(char **arguments,int index, LinkedList* linkedList);

bool is_file(char * name,char * extension);
void verify(void *pointer,int line_number);
int process(FILE *file_in,FILE *file_out,LinkedList *linkedList);


void add_into(LinkedList * linkedList,char *key,char *value){
    if(!(linkedList->head)){
        linkedList->head = malloc(sizeof(Node));
        linkedList->head->key = strdup(key);
        linkedList->head->value = strdup(value);
        linkedList->head->address = NULL;
    }else{
        Node *oldHead = linkedList->head;
        linkedList->head = malloc(sizeof(Node));
        linkedList->head->key = strdup(key);
        linkedList->head->value = strdup(value);
        linkedList->head->address = oldHead;
    }
}

void delete(Node *node){
    free(node->value);
    free(node->key);
    free(node);
}

void deleteList(LinkedList* list){
    Node *head = list->head;
    Node *next;
    while(head){
        next = head->address;
        delete(head);
        head = next;
    }
    list->head = NULL;
}

void freeList(LinkedList **linkedList){
    if(*linkedList){
        deleteList(*linkedList);
        free(*linkedList);
    }
}








int main(int argc ,char **argv)
{
    LinkedList *linkedList = NULL;
    FILE *file_in = stdin,*file_out = stdout;
    create_new(&linkedList);
    if(process_arguments(argv,argc,linkedList,&file_in,&file_out) == FAILED){
        printf("ARGUMENT PROCESSING FAILED\n");
        exit(EXIT_FAILURE);
    }
    process(file_in,file_out,linkedList);
    freeList(&linkedList);
    fclose(file_out);
    fclose(file_in);
    return 0;
}

int process(FILE *file_in,FILE *file_out,LinkedList *hashMap){
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



void verify(void *pointer,int line_number){
    if(pointer==NULL)
    {
        printf("Allocation error on line %d!\n",line_number);
        exit(EXIT_FAILURE);
    }
}

int create_new(LinkedList ** linkedList){
    verify((*linkedList) = malloc(sizeof(LinkedList)),__LINE__);
    (*linkedList)->size = 0;
    (*linkedList)->head = NULL;
    return 0;
}

int process_arguments(char **arguments,int argument_count,LinkedList *linkedList,FILE **file_in,FILE **file_out){
    int index = 0;
    while(index < argument_count){
        if(is_symbol(arguments[index])){
            addSymbol(arguments,index,linkedList);
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

void addSymbol(char **arguments,int index, LinkedList* linkedList){
    if(strstr(arguments[index],SYMBOL_FLAG)&&strlen(arguments[index])>2)
        {
            char temp[55];
            memcpy(temp,&(arguments[index][2]),strlen(&(arguments[index][2]))+1);
            char *key,*value;
            key = strtok(temp,"=");
            if(key!=NULL){
                value = strtok(NULL,temp);
                if(!value)
                    value = "";
            }
            else value="";
            add_into(linkedList,key,value);
        }else{
            printf("%s",arguments[index]);
            char temp[55];
            memcpy(temp,arguments,strlen(arguments[index])+1);
            char *key,*value;
            key = strtok(temp,"=");
            if(key!=NULL){
                value = strtok(NULL,"=");
                if(!value)
                    value = "";
            }else value="";
            printf("key: %s\nvalue: %s\n",key,value);
            add_into(linkedList,key,value);
        }
    
        return;
}

bool is_symbol(char *argument){
    if(strlen(argument)>=2)
        return strcmp(argument,SYMBOL_FLAG) == 0 ? true : strstr(argument,SYMBOL_FLAG)!=NULL;
    else return false;
}

bool is_invalid_flag(char *argument){
    if(strlen(argument) >= 1)
        return argument[0] == FLAG_CHAR;
    return false;
}