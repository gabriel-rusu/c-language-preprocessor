#include "utils.h"


void verify(void *pointer, int line_number)
{
    if (pointer == NULL)
    {
        printf("Allocation error on line %d!\n", line_number);
        exit(EXIT_FAILURE);
    }
}
