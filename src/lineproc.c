
#include "utils.h"
#include "list.h"

void replace(char *line, char *key, char *value)
{
    char temp[BUFFER_SIZE];
    char search[BUFFER_SIZE];
    int index = 0;
    char *word;
    int offset = find_offset_for(line);
    int length_of_key = strlen(key);
    char *position;
    int first_escape = 0;

    if (strchr(line, '"') != NULL)
    {
        first_escape = (strchr(line, '"') - line);
        word = strtok(search, ALL_DELIMITERS);

        while ((position = strstr(line, key))!=NULL && first_escape < strlen(line))
        {
            strcpy(temp, line);
            index = position - line;
            if (index >= first_escape)
                break;
            line[index] = '\0';
            strcat(line, value);
            strcat(line, temp + index + length_of_key);
        }
        return;
    }

    while ((position = strstr(line + offset, key)) != NULL)
    {
        strcpy(temp, line);
        index = position - line;
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
        return ((strchr(line + index + 1, '\"') - line));
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
