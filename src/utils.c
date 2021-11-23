#include "ftjson.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief   Frees an array of strings.
 * 
 * @param   array the array to free.
 * @param   size  the size of the array.
 */
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

/**
 * @brief   Realloc with error handling.
 *          If the realloc fails, it clears the previous memory allocation.
 * 
 * @param   ptr     the pointer to the memory to reallocate.
 * @param   size    the new size of the memory.
 * @return  void*   the new pointer to the memory.
 */
void *realloc_free_on_fail(void *ptr, size_t size)
{
    void *new_ptr = realloc(ptr, size);

    if (new_ptr == NULL)
        free(ptr);
    return new_ptr;
}

/**
 * @brief   Gets the file content as a string.
 * 
 * @param   filename    the name of the file to convert.
 * @return  char*       the string containing the file content.
 */
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
