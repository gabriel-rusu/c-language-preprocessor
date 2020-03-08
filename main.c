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


void process_input(char *line,FILE *file_out,LinkedList * linkedList);
void verify_write_for(char *line){
    printf("Mesaj: %s\n",line);
}

int create_new(LinkedList ** linkedList);
int process_arguments(char **arguments,int argument_count,LinkedList *linkedList,FILE **file_in,FILE **file_out);
bool is_invalid_flag(char *argument);
bool is_symbol(char *argument);
void freeList(LinkedList **linkedList);
void addSymbol(char **arguments,int *index, LinkedList* linkedList,int argc);

bool is_file(char * name,char * extension);
void verify(void *pointer,int line_number);
int process(FILE *file_in,FILE *file_out,LinkedList *linkedList);
int find_offset_for(char *line);
void add_into(LinkedList * linkedList,char *key,char *value);
bool search(char *word,LinkedList *linkedList);
char * getValueOf(char *key,LinkedList *linkedList);
void delete(Node *node);
void freeList(LinkedList **linkedList);
void deleteList(LinkedList* list);


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

int find_offset_for(char *line){
    char *pos;
    int index = 0;
    if((pos = strchr(line,'\"'))!=NULL){
        index = pos - line;
        return ((strchr(line+index+1,'\"') - line) + 1);
    }
    return 0;
}

void replace(char *line,char *key,char *value)
{
    char temp[BUFFER_SIZE];
    int index = 0;
    int offset = find_offset_for(line);
    int length_of_key = strlen(key);
    char *position;
    while((position = strstr(line+offset,key))!=NULL){
        strcpy(temp,line);
        index = position - line;
        line[index] = '\0';
        strcat(line,value);
        strcat(line,temp+index+length_of_key);
    }

}

void prepare(char *line,LinkedList *linkedList)
{
    Node *head = linkedList->head;
    while(head){
        if(strstr(line,head->key))
            replace(line,head->key,head->value);
        head = head->address;
    }
}

void process_input(char *line,FILE *file_out,LinkedList * linkedList){
    char temp[BUFFER_SIZE];
    char delimiters[] = " \n";
    char *word=NULL,*key=NULL,*value=NULL;
   
    strcpy(temp,line);
    if(strchr(line,'#')){
        if(strstr(line,"#define")){
            word = strtok(temp,delimiters);
            if(word)
                key = strtok(NULL,delimiters);
            if(key){
                value = strtok(NULL,delimiters);
                if(!value)
                    value = "";
            }
            add_into(linkedList,key,value);
        }else if(strstr(line,"#include")){
            
        }else if(strstr(line,"#undef")){
            //TODO: delete the node with key after undef
        }
    }else{
        prepare(line,linkedList);
        if(strlen(line)!=1)
        fprintf(file_out,"%s",line);
    }
}


int process(FILE *file_in,FILE *file_out,LinkedList *linkedList){
    char line[BUFFER_SIZE];
    char prev_line[BUFFER_SIZE] = "";
    while (fgets(line,BUFFER_SIZE,file_in)!=NULL)
    {
        if(strcmp(line,prev_line)==0){
            printf("S-a bulit fisierul ?");
            break;
        }
        strcpy(prev_line,line);
        process_input(line,file_out,linkedList);
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
            addSymbol(arguments,&index,linkedList,argument_count);
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

void addSymbol(char **arguments,int* index, LinkedList* linkedList,int argc){
    if(strstr(arguments[*index],SYMBOL_FLAG)&&strlen(arguments[*index])>2)
        {
            char temp[55];
            memcpy(temp,&(arguments[*index][1]),strlen(&(arguments[*index][1]))+1);
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
            char temp[55];
            memcpy(temp,arguments[*index+1],strlen(arguments[*index+1])+1);
            char *key,*value;
            key = strtok(temp,"=");
            if(key!=NULL){
                value = strtok(NULL,"=");
                if(!value)
                    value = "";
            }else value="";
            printf("key: %s\nvalue: %s\n",key,value);
            add_into(linkedList,key,value);
            (*index)++;
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

void add_into(LinkedList * linkedList,char *key,char *value){
    (linkedList->size)++;
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

bool search(char *word,LinkedList *linkedList){
    Node *head = linkedList->head;
    while(head){
        if(strcmp(head->key,word)==0)
            return true;
    }
    return false;
}

char * getValueOf(char *key,LinkedList *linkedList){
    Node *head = linkedList->head;
    while(head){
        if(strcmp(head->key,key)==0)
            return head->value;
    }
    return "";
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