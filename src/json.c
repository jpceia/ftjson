#include "ftjson.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// free the json contents
void json_free(t_json json)
{
    switch (json.type)
    {
    case JSON_OBJECT:
        json_object_free(json.object);
        break ;
    case JSON_ARRAY:
        json_array_free(json.array);
        break ;
    case JSON_STRING:
        free(json.string);
        break ;
    default:
        break ;
    }
}

// Json error
t_json json_error(void)
{
    t_json json;

    json.type = JSON_ERROR;
    return (json);
}

// convert a json to a string
char *json_stringify(t_json json)
{
    switch (json.type)
    {
    case JSON_OBJECT:
        return json_object_stringify(json.object);
    case JSON_ARRAY:
        return json_array_stringify(json.array);
    case JSON_STRING:
        return json_string_stringify(json.string);
    case JSON_NUMBER:
        return json_number_stringify(json.number);
    case JSON_BOOLEAN:
        return json_boolean_stringify(json.boolean);
    case JSON_NULL:
    default:
        return json_null_stringify();
    }
}

// JSON Parse
t_json json_parse(char *str)
{
    t_json json = json_parse_next(&str);
    if (str == NULL)
        return (json);
    if (*str != '\0')
    {
        fprintf(stderr, "Parsing failled, the string is not null terminated: %s\n", str);
        json_free(json);
        return json_error();
    }
    return json;
}


t_json json_parse_next(char **str)
{
    t_json json;

    if (*str == NULL)
    {
        json.type = JSON_ERROR;
        return json;
    }
    json_move_whitespace(str);
    switch (**str)
    {
        case '{':
            json.type = JSON_OBJECT;
            json.object = json_object_parse(str);
            if (*str == NULL)
                return json_error();
            break ;
        case '[':
            json.type = JSON_ARRAY;
            json.array = json_array_parse(str);
            if (*str == NULL)
                return json_error();
            break ;
        case '"':
            json.type = JSON_STRING;
            json.string = json_string_parse(str);
            if (json.string == NULL || *str == NULL)
                return json_error();
            break ;
        case 't':
        case 'f':
            json.type = JSON_BOOLEAN;
            json.boolean = json_boolean_parse(str);
            if (*str == NULL)
                return json_error();
            break ;
        case 'n':
            json.type = JSON_NULL;
            json_null_parse(str);
            if (*str == NULL)
                return json_error();
            break ;
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            json.type = JSON_NUMBER;
            json.number = json_number_parse(str);
            if (*str == NULL)
                return json_error();
            break ;
        default:
            return json_error();
    }
    json_move_whitespace(str);
    return json;
}
