#ifndef LIST_H_
#define LIST_H_
#include "utils.h"

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
bool search(char *word,LinkedList *linkedList);
bool find(char *key,LinkedList *linkedList);
void deleteFromList(char *key,LinkedList *linkedList);
void freeList(LinkedList **linkedList);
void deleteList(LinkedList* list);
void deleteNode(Node *node);
void add_into(LinkedList *linkedList, char *key, char *value);

#endif