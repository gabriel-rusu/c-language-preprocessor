
#include "utils.h"
#include "list.h"

void replace(char *line, char *key, char *value)
{
    char temp[BUFFER_SIZE];
    int index = 0;
    int offset = find_offset_for(line);
    int length_of_key = strlen(key);
    char *position;
    while ((position = strstr(line + offset, key)) != NULL)
    {
        strcpy(temp, line);
        index = position - line;
        line[index] = '\0';
        strcat(line, value);
        strcat(line, temp + index + length_of_key);
    }
    int first_escape = (strstr(line, key) - line) + 1;
    position = NULL;
    while (position = strstr(line, key))
    {
        strcpy(temp, line);
        index = position - line;
        if (index > first_escape)
            break;
        line[index] = '\0';
        strcat(line, value);
        strcat(line, temp + index + length_of_key);
    }
}


int find_offset_for(char *line)
{
    char *pos;
    int index = 0;
    if ((pos = strchr(line, '\"')) != NULL)
    {
        index = pos - line;
        return ((strchr(line + index + 1, '\"') - line) + 1);
    }
    return 0;
}


void prepare(char *line, LinkedList *linkedList)
{
    Node *head = linkedList->head;
    while (head)
    {
        if (strstr(line, head->key))
            replace(line, head->key, head->value);
        head = head->address;
    }
}
