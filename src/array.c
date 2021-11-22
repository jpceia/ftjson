#include "ftjson.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Json from t_json_array
t_json json_from_array(t_json_array *array)
{
    t_json json;

    json.type = JSON_ARRAY;
    json.array = array;
    return (json);
}

// Create json array
t_json_array *json_array_new(t_json value)
{
    t_json_array *array = malloc(sizeof(t_json_array));
    
    if (array == NULL)
        return (NULL);
    array->value = value;
    array->next = NULL;
    return (array);
}

// free the json array
void json_array_free(t_json_array *array)
{
    if (array == NULL)
        return ;
    json_array_free(array->next);
    json_free(array->value);
    free(array);
}

// Gets the size of the json array
int json_array_size(t_json_array *array)
{
    int size = 0;

    while (array != NULL)
    {
        size++;
        array = array->next;
    }
    return (size);
}

// pushback json array
t_json_array *json_array_pushback(t_json_array **array, t_json value)
{
    t_json_array *new = json_array_new(value);

    if (new == NULL)
        return NULL;
    if (*array == NULL)
        *array = new;
    else
    {
        t_json_array *node = *array;

        while (node->next != NULL)
            node = node->next;
        node->next = new;
    }
    return (new);
}

// pushfront json array
t_json_array *json_array_pushfront(t_json_array **array, t_json value)
{
    t_json_array *new = json_array_new(value);

    if (new == NULL)
        return (NULL);
    new->next = *array;
    *array = new;
    return (new);
}

// Converts a json array to a string
char *json_array_stringify(t_json_array *array)
{
    int arr_size;
    int size;
    char *text;
    char **arr;

    arr_size = json_array_size(array);
    arr = (char **)malloc(sizeof(char *) * arr_size);
    if (arr == NULL)
        return (NULL);
    size = 2; // left and right brackets
    for (int i = 0; i < arr_size; ++i)
    {
        arr[i] = json_stringify(array->value);
        if (arr[i] == NULL)
        {
            string_array_free(arr, i);
            return (NULL);
        }
        size += strlen(arr[i]) + 2; // +2 for the comma
        array = array->next;
    }
    if (arr_size > 0)
        size -= 2; // -2 for the last comma
    text = malloc(size + 1);
    if (text != NULL)
    {
        text[0] = '\0';
        strcat(text, "[");
        if (arr_size > 0)
        {
            strcat(text, arr[0]);
            for (int i = 1; i < arr_size; ++i)
            {
                strcat(text, ", ");
                strcat(text, arr[i]);
            }
        }
        strcat(text, "]");
    }
    string_array_free(arr, arr_size);
    return (text);
}

// Parsers a JSON array from a string
t_json_array *json_array_parse(char **str)
{
    t_json_array *array = NULL;
    t_json value;

    if (*str == NULL)
        return NULL;
    if (**str != '[')
    {
        *str = NULL;
        fprintf(stderr, "Expected '['\n");
        return NULL;
    }
    ++*str;
    if (**str == ']')
        return NULL;
    while (1)
    {
        value = json_parse(str);
        if (value.type == JSON_ERROR)
        {
            json_array_free(array);
            *str = NULL;
            return NULL;
        }
        if (!json_array_pushback(&array, value))
        {
            json_array_free(array);
            *str = NULL;
            return NULL;
        }
        if (**str == ',')
            ++*str;
        else if (**str == ']')
            break ;
        else
        {
            fprintf(stderr, "Expected ',' or ']'\n");
            json_array_free(array);
            *str = NULL;
            return NULL;
        }
    }
    ++*str;
    return array;
}
