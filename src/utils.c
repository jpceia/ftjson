#include "ftjson.h"
#include <stdio.h>
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

// File to string conversion
char *file_to_string(const char *filename)
{
    FILE *fp = fopen (filename, "rb");
    char *str = 0;
    long length;

    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        str = malloc(length);
        if (str)
            (void)!fread(str, 1, length, fp);
        fclose (fp);
    }
    return str;
}
