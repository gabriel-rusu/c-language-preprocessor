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
#define PATH_TO_INPUT "_test/inputs/"
#define INCLUDE_FLAG "-I"


typedef struct Node{
    char *key;
    char *value;
    struct Node *address;
}Node;

typedef struct LinkedList{
    int size;
    Node *head;
}LinkedList;


void process_input(char *line,FILE *file_out,LinkedList * linkedList,LinkedList *include_paths);
void verify_write_for(char *line){
    printf("Mesaj: %s\n",line);
}
int process(FILE *file_in,FILE *file_out,LinkedList *linkedList,LinkedList *include_paths);
void addInclude(char **argument,int *index,LinkedList *include_list,int argument_count);
void deleteFromList(char *key,LinkedList *linkedList);
int create_new(LinkedList ** linkedList);
int process_arguments(char **arguments,int argument_count,LinkedList *linkedList,LinkedList *include_list,FILE **file_in,FILE **file_out);
bool is_invalid_flag(char *argument);
bool is_symbol(char *argument);
void freeList(LinkedList **linkedList);
void addSymbol(char **arguments,int *index, LinkedList* linkedList,int argc);
bool is_include(char *argument);
FILE *try_to_open(char *file_name,LinkedList *include_paths);
bool is_file(char * name,char * extension);
void verify(void *pointer,int line_number);
int process(FILE *file_in,FILE *file_out,LinkedList *linkedList,LinkedList *include_paths);
int find_offset_for(char *line);
void add_into(LinkedList * linkedList,char *key,char *value);
bool search(char *word,LinkedList *linkedList);
char * getValueOf(char *key,LinkedList *linkedList);
void delete(Node *node);
void freeList(LinkedList **linkedList);
void deleteList(LinkedList* list);
bool find(char *key,LinkedList *linkedList);


int main(int argc ,char **argv)
{
    LinkedList *linkedList = NULL,*file_list =NULL;
    FILE *file_in = stdin,*file_out = stdout;
    create_new(&linkedList);
    create_new(&file_list);
    if(process_arguments(argv,argc,linkedList,file_list,&file_in,&file_out) == FAILED){
        printf("ARGUMENT PROCESSING FAILED\n");
        exit(EXIT_FAILURE);
    }
    FILE *temp = fopen("temp.out","w");
    FILE *temp1 = fopen("temp1.out","w");
    process(file_in,temp,linkedList,file_list);
    fclose(temp);
    
    temp = fopen("temp.out","r");
    process(temp,temp1,linkedList,file_list);
    fclose(temp1);
    fclose(temp);

    temp1 = fopen("temp1.out","r");
    process(temp1,file_out,linkedList,file_list);
    fclose(temp1);

    freeList(&linkedList);
    freeList(&file_list);
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
    int first_escape = (strstr(line,key) - line)+1;
    position = NULL;
    while(position = strstr(line,key)){
        strcpy(temp,line);
        index = position - line;
        if(index > first_escape)
            break;
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

void process_input(char *line,FILE *file_out,LinkedList * linkedList,LinkedList *include_paths){
    char temp[BUFFER_SIZE];
    char delimiters[] = " \n";
    char *word=NULL,*key=NULL,*value=NULL;
    static bool write = true;
   //TODO: verify how you free the memory for test 9
    
    if(strchr(line,'#')&&(strstr(line,"\"#define")==NULL)){
        if(strstr(line,"#define")){
            prepare(line,linkedList);
            strcpy(temp,line);
            word = strtok(temp,delimiters);
            if(word)
                key = strtok(NULL,delimiters);
            if(key){
                value = strtok(NULL,"\n");
                if(!value)
                    value = "";
            }
            add_into(linkedList,key,value);
        }else if(strstr(line,"#ifdef")){
            strcpy(temp,line);
            word = strtok(temp,delimiters);
            if(word)
                key = strtok(NULL,delimiters);
            if(find(key,linkedList))
                write = true;
            else write = false;
        }else if(strstr(line,"#ifndef")){
            strcpy(temp,line);
            word = strtok(temp,delimiters);
            if(word)
                key = strtok(NULL,delimiters);
            if(find(key,linkedList))
                write = false;
            else write = true;
        }else if(strstr(line,"#include")){
            strcpy(temp,line);
            char *file_name,full_path[256] = "";
            strcat(full_path,PATH_TO_INPUT);
            word = strtok(temp,"\" \n");
            if(word)
                file_name = strtok(NULL,"\" ");
            strcat(full_path,file_name);
            
            FILE *include_file;
           if((include_file = fopen(full_path,"r"))==NULL){
               include_file = try_to_open(file_name,include_paths);
               verify(include_file,__LINE__);
           }

            while(fgets(line,BUFFER_SIZE,include_file)!=NULL){
                prepare(line,linkedList);
                fprintf(file_out,"%s",line);
            }
            fclose(include_file);
        }else if(strstr(line,"#if")){
            prepare(line,linkedList);
            strcpy(temp,line);
            word = strtok(temp,delimiters);
            if(word)
                write = atoi(strtok(NULL,delimiters));
        }else if(strstr(line,"#elif")&&write==false){
            prepare(line,linkedList);
            strcpy(temp,line);
            word = strtok(temp,delimiters);
            if(word)
                write = atoi(strtok(NULL,delimiters));
        }else if(strstr(line,"#elif")&&write==true){
            write=false;
        }else if(strstr(line,"#else")){
            write=!write;
        }else if(strstr(line,"#endif")){
            write=true;
        }else if(strstr(line,"#undef")){
            strcpy(temp,line);
            word = strtok(temp,delimiters);
            if(word)
                key = strtok(NULL,delimiters);
            deleteFromList(key,linkedList);
        }
    }else{
        if(write){
            prepare(line,linkedList);
            if(strlen(line)!=1)
            fprintf(file_out,"%s",line);
        }
    }
}

void deleteFromList(char *key,LinkedList *linkedList){
    Node *head = linkedList->head;
    Node *next = head->address;
    if(strcmp(head->key,key)==0){
        linkedList->head = head->address;
        free(head->key);
        free(head->value);
        return;
    }
    while(next){
        if(next!=NULL && strcmp(next->key,key)==0){
            head->address = next->address;
            free(next->key);
            free(next->value);
            return;
        }
    }
}

FILE *try_to_open(char *file_name,LinkedList *include_paths){
    Node *head = include_paths->head;
    FILE *temp;
    char buffer[BUFFER_SIZE];
    while(head){
        strcpy(buffer,"");
        strcat(buffer,head->value);
        strcat(buffer,"/");
        strcat(buffer,file_name);
        temp = fopen(buffer,"r");
        if(temp)
            return temp;
        head = head->address;
    }
    return NULL;
}


int process(FILE *file_in,FILE *file_out,LinkedList *linkedList,LinkedList *include_paths){
    char line[BUFFER_SIZE];
    while (fgets(line,BUFFER_SIZE,file_in)!=NULL)
        process_input(line,file_out,linkedList,include_paths);
    
    return SUCCESS;
}

bool is_file(char * name,char * extension){
    return strstr(name,extension)!=NULL;
}

bool find(char *key,LinkedList *linkedList){
    Node *head = linkedList->head;
    while(head){
        if(strcmp(head->key,key)==0)
            return true;
        head= head->address;
    }
    return false;
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

int process_arguments(char **arguments,int argument_count,LinkedList *linkedList,LinkedList *include_list,FILE **file_in,FILE **file_out){
    int index = 0;
    while(index < argument_count){
        if(is_symbol(arguments[index])){
            addSymbol(arguments,&index,linkedList,argument_count);
        }
        else if(is_file(arguments[index],INPUT_FILE_EXTENSION)){
            verify(*file_in = fopen(arguments[index],"r"),__LINE__);
        }else if(is_file(arguments[index],OUTPUT_FILE_EXTENSION)){
            verify(*file_out = fopen(arguments[index],"w"),__LINE__);
        }else if(is_include(arguments[index])){
            addInclude(arguments,&index,include_list,argument_count);
        
        }else if(is_file(arguments[index],INVALID_FILE_EXTENSION)&& (is_file(arguments[index],"./")==false))
            return FAILED;
        else if(is_invalid_flag(arguments[index]))
            return FAILED;
        index++;
    }
    return 0;
}

bool is_include(char *argument){
    if(strlen(argument)>=2)
        return strcmp(argument,INCLUDE_FLAG) == 0 ? true : strstr(argument,INCLUDE_FLAG)!=NULL;
    else return false;
}

void addInclude(char **argument,int *index,LinkedList *include_list,int argument_count){
    if(strstr(argument[*index],INCLUDE_FLAG)&&strlen(argument[*index])>2)
        {
            char path[70];
            strcpy(path,&(argument[*index][2]));
            add_into(include_list,path,path);
        }else{
            char path[70];
            strcpy(path,argument[*index+1]);
            add_into(include_list,path,path);
            (*index)++;
        }
    
        return;
}

void addSymbol(char **arguments,int* index, LinkedList* linkedList,int argc){
    if(strstr(arguments[*index],SYMBOL_FLAG)&&strlen(arguments[*index])>2)
        {
            char temp[55];
            strcpy(temp,&(arguments[*index][2]));
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