
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
        return (NULL);
    if (*array == NULL)
        *array = new;
    else
    {
        t_json_array *node = *array;

        while (node->next != NULL)
            node = node->next;
        node->next = new;
    }
    return (*array);
}

// pushfront json array
t_json_array *json_array_pushfront(t_json_array **array, t_json value)
{
    t_json_array *new = json_array_new(value);

    if (new == NULL)
        return (NULL);
    new->next = *array;
    *array = new;
    return (*array);
}

// Converts a json array to a string
char *json_array_stringify(t_json_array *array)
{
    int size;
    int text_size;
    char *text;
    char **arr;

    size = json_array_size(array);
    arr = (char **)malloc(sizeof(char *) * (size + 1));
    if (arr == NULL)
        return (NULL);
    arr[size] = NULL;
    text_size = 2; // left and right brackets
    for (int i = 0; i < size; ++i)
    {
        arr[i] = json_stringify(array->value);
        if (arr[i] == NULL)
        {
            for (int j = 0; j < i; ++j)
                free(arr[j]);
            free(arr);
            return (NULL);
        }
        text_size += strlen(arr[i]) + 1; // +1 for the comma
        array = array->next;
    }
    text_size--; // remove the last comma
    text = (char *)malloc(sizeof(char) * (text_size + 1));
    if (text == NULL)
    {
        // free(arr);
        for (int i = 0; i < size; ++i)
            free(arr[i]);
        free(arr);
        return (NULL);
    }
    strcpy(text, "[");
    strcat(text, arr[0]);
    free(arr[0]);
    for (int i = 1; i < size; i++)
    {
        strcat(text, ",");
        strcat(text, arr[i]);
        free(arr[i]);
    }
    free(arr);
    strcat(text, "]");
    return (text);
}
