#include "list.h"
#include "utils.h"

int create_new(LinkedList ** linkedList){
    verify((*linkedList) = malloc(sizeof(LinkedList)),__LINE__);
    (*linkedList)->size = 0;
    (*linkedList)->head = NULL;
    return 0;
}

bool search(char *word,LinkedList *linkedList){
    Node *head = linkedList->head;
    while(head){
        if(strcmp(head->key,word)==0)
            return true;
    }
    return false;
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

void deleteList(LinkedList* list){
    Node *head = list->head;
    Node *next;
    while(head){
        next = head->address;
        deleteNode(head);
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

void deleteNode(Node *node){
    free(node->value);
    free(node->key);
    free(node);
}

void add_into(LinkedList *linkedList, char *key, char *value)
{
    (linkedList->size)++;
    if (!(linkedList->head))
    {
        linkedList->head = malloc(sizeof(Node));
        linkedList->head->key = strdup(key);
        linkedList->head->value = strdup(value);
        linkedList->head->address = NULL;
    }
    else
    {
        Node *oldHead = linkedList->head;
        linkedList->head = malloc(sizeof(Node));
        linkedList->head->key = strdup(key);
        linkedList->head->value = strdup(value);
        linkedList->head->address = oldHead;
    }
}