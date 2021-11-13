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
    free(object->key);
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

// addback json object
t_json_object *json_object_append(t_json_object **object, t_json_object *new)
{
    t_json_object *node = *object;

    if (node == NULL)
    {
        *object = new;
        return new;
    }
    while (node->next != NULL)
        node = node->next;
    node->next = new;
    return new;
}

// pushback json object
t_json_object *json_object_pushback(t_json_object **object, char *key, t_json value)
{
    t_json_object *new = json_object_new(key, value);

    if (new == NULL)
        return (NULL);
    return json_object_append(object, new);
}

// pushfront json object
t_json_object *json_object_pushfront(t_json_object **object, char *key, t_json value)
{
    t_json_object *new = json_object_new(key, value);

    if (new == NULL)
        return (NULL);
    new->next = *object;
    *object = new;
    return (new);
}

// Converts a key value pair to a string
static char *json_object_stringify_key_value(t_json_object* object)
{
    char *text = NULL;
    char *key = object->key;
    char *value_str = json_stringify(object->value);

    if (value_str == NULL)
        return (NULL);
    text = malloc(strlen(key) + strlen(value_str) + 5);
    if (text == NULL)
    {
        free(value_str);
        return (NULL);
    }
    strcpy(text, "\"");
    strcat(text, key);
    strcat(text, "\": ");
    strcat(text, value_str);
    free(value_str);
    return (text);
}

// Converts a t_json_object to a string
char *json_object_stringify(t_json_object *object)
{
    char *text = NULL;
    char **arr = NULL;
    int size = 0;
    int arr_size = json_object_size(object);
    
    arr = malloc(sizeof(char *) * arr_size);
    if (arr == NULL)
        return (NULL);
    for (int i = 0; i < arr_size; ++i)
    {
        arr[i] = json_object_stringify_key_value(object);
        if (arr[i] == NULL)
        {
            string_array_free(arr, i);
            return (NULL);
        }
        size += strlen(arr[i]) + 2;
        object = object->next;
    }
    text = malloc(size + 1);
    if (text != NULL)
    {
        text[0] = '\0';
        strcat(text, "{");
        if (arr_size > 0)
        {
            strcat(text, arr[0]);
            for (int i = 1; i < arr_size; ++i)
            {
                strcat(text, ", ");
                strcat(text, arr[i]);
            }
        }
        strcat(text, "}");
    }
    string_array_free(arr, arr_size);
    return (text);
}

t_json_object *json_key_value_parse(char **str)
{
    char *key = NULL;
    t_json value;

    if (*str == NULL)
        return (NULL);
    json_move_whitespace(str);
    key = json_string_parse(str);
    if (key == NULL)
        return (NULL);
    if (**str != ':')
    {
        fprintf(stderr, "Expected ':'\n");
        free(key);
        return (NULL);
    }
    ++*str;
    value = json_parse(str);
    if (value.type == JSON_ERROR)
    {
        free(key);
        return (NULL);
    }
    json_move_whitespace(str);
    return json_object_new(key, value);
}

// Parsers a t_json_object from a string
t_json_object *json_object_parse(char **str)
{
    t_json_object *object = NULL;
    t_json_object *last = NULL;

    if (*str == NULL)
        return NULL;
    if (**str != '{')
    {
        perror("Expected '{'");
        return NULL;
    }
    ++*str;
    if (**str != '}')
    {
        while (1)
        {
            last = json_key_value_parse(str);
            if (last == NULL)
            {
                json_object_free(object);
                return NULL;
            }
            object = json_object_append(&object, last);
            if (**str == '}')
                break;
            if (**str != ',')
            {
                fprintf(stderr, "Expected ',' or '}'\n");
                json_object_free(object);
                return NULL;
            }
            ++*str;
        }
    }
    ++*str;
    return object;
}
