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

/**
 * @brief   Checks if a character is a whitespace.
 * 
 * @param   c   the character to check.
 * @return  int 1 if the character is a whitespace, 0 otherwise.
 */
int is_whitespace(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

/**
 * @brief   Moves the cursor to the next non-whitespace character.
 * 
 * @param   str the cursor to move. 
 */
void json_move_whitespace(char **cursor)
{
    while (is_whitespace(**cursor))
        ++*cursor;
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
 * @brief  Compares two strings, ignoring the whitespaces outside double quotes.
 * 
 * @param   str1    the first string.
 * @param   str2    the second string.
 * @return  int     1 if the strings are equal, 0 otherwise.
 */
int json_strcmp(char *str1, char *str2)
{
    int inside_quotes;
    char prev_char = 0;

    json_move_whitespace(&str1);
    json_move_whitespace(&str2);
    inside_quotes = *str1 == '"';
    while (*str1 && *str1 == *str2)
    {
        prev_char = *str1;
        ++str1;
        ++str2;
        if (inside_quotes)
        {
            if (*str1 == '"' && prev_char != '\\')
                inside_quotes = 0;
        }
        else
        {
            json_move_whitespace(&str1);
            json_move_whitespace(&str2);
            if (*str1 == '"')
                inside_quotes = 1;
        }
    }
    return ((int)*str1) - ((int)*str2);
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
        str = (char *)malloc(length);
        if (str)
            (void)!fread(str, 1, length, fp);
        fclose (fp);
    }
    return str;
}
