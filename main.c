#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 257

int main(int argc ,char **argv)
{
    char buffer[BUFFER_SIZE];
    
    scanf("%[^\n]s",buffer);
    printf("%s\n",buffer);

    return 0;
}
