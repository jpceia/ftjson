


#include "ftjson.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Json from t_json_object
t_json json_from_object(t_json_object *object)
{
    t_json json;

    json.type = JSON_OBJECT;
    json.object = object;
    return json;
}

// Create json object
t_json_object *json_object_new(char *key, t_json value)
{
    t_json_object *object = malloc(sizeof(*object));

    if (object == NULL)
        return (NULL);
    object->key = key;
    object->value = value;
    object->next = NULL;
    return (object);
}

// Free json object
void json_object_free(t_json_object *object)
{
    if (object == NULL)
        return ;
    json_object_free(object->next);
    json_free(object->value);
    free(object);
}


// Get the t_json_object size
int json_object_size(t_json_object *object)
{
    int size = 0;
    while (object != NULL)
    {
        size++;
        object = object->next;
    }
    return (size);
}

// pushback json object
t_json_object *json_object_pushback(t_json_object **object, char *key, t_json value)
{
    t_json_object *new = json_object_new(key, value);

    if (new == NULL)
        return (NULL);
    if (*object == NULL)
        *object = new;
    else
    {
        t_json_object *node = *object;
        while (node->next != NULL)
            node = node->next;
        node->next = new;
    }
    return (*object);
}

// pushfront json object
t_json_object *json_object_pushfront(t_json_object **object, char *key, t_json value)
{
    t_json_object *new = json_object_new(key, value);

    if (new == NULL)
        return (NULL);
    new->next = *object;
    *object = new;
    return (*object);
}

// Converts a key value pair to a string
static char *json_object_stringify_key_value(t_json_object* object)
{
    char *str = NULL;
    char *key = object->key;
    char *value_str = json_stringify(object->value);

    if (value_str == NULL)
        return (NULL);
    str = malloc(strlen(key) + strlen(value_str) + 5);
    if (str == NULL)
    {
        free(value_str);
        return (NULL);
    }
    strcpy(str, "\"");
    strcat(str, key);
    strcat(str, "\": ");
    strcat(str, value_str);
    free(value_str);
    return (str);
}

// Converts a t_json_object to a string
char *json_object_stringify(t_json_object *object)
{
    char *text = NULL;
    char **arr = NULL;
    int size = 0;
    int arr_size = json_object_size(object);
    arr = malloc(sizeof(char *) * (arr_size + 1));
    if (arr == NULL)
        return (NULL);
    for (int i = 0; i < arr_size; ++i)
    {
        arr[i] = json_object_stringify_key_value(object);
        if (arr[i] == NULL)
        {
            for (int j = 0; j < i; ++j)
                free(arr[j]);
            free(arr);
            return (NULL);
        }
        size += strlen(arr[i]) + 2;
        object = object->next;
    }
    text = malloc(sizeof(char) * (size + 1));
    if (text == NULL)
    {
        for (int i = 0; i < arr_size; ++i)
            free(arr[i]);
        free(arr);
        return (NULL);
    }
    strcpy(text, "{");
    for (int i = 0; i < arr_size - 1; ++i)
    {
        strcat(text, arr[i]);
        strcat(text, ", ");
        free(arr[i]);
    }
    if (arr_size > 0)
    {
        strcat(text, arr[arr_size - 1]);
        free(arr[arr_size - 1]);
    }
    free(arr);
    strcat(text, "}");
    return (text);
}
