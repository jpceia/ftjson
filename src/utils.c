#include "ftjson.h"
#include <stdlib.h>

void string_array_free(char **array, int size)
{
    for (int i = 0; i < size; ++i)
        free(array[i]);
    free(array);
}

void json_move_whitespace(char **str)
{
    while (**str == ' ' || **str == '\t' || **str == '\n' || **str == '\r')
        ++*str;
}

void *realloc_free_on_fail(void *ptr, size_t size)
{
    void *new_ptr = realloc(ptr, size);
    
    if (new_ptr == NULL)
        free(ptr);
    return new_ptr;
}