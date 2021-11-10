#include "ftjson.h"
#include <stdlib.h>
#include <string.h>

// free the json contents
void json_free(t_json json)
{
    switch (json.type)
    {
    case JSON_OBJECT:
        json_object_free(json.object);
        break;
    case JSON_ARRAY:
        json_array_free(json.array);
        break;
    case JSON_STRING:
        free(json.string);
        break;
    default:
        break;
    }
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
t_json json_parse(char **str)
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
            json.object = NULL; // Work in progress
            break ;
        case '[':
            // Work in progress
            json.type = JSON_ARRAY;
            json.array = NULL; // Work in progress
            break ;
        case '"':
            json.type = JSON_STRING;
            json.string = json_string_parse(str);
            if (json.string == NULL || *str == NULL)
                json.type = JSON_ERROR;
            break ;
        case 't':
        case 'f':
            json.type = JSON_BOOLEAN;
            json.boolean = json_boolean_parse(str);
            if (json.boolean < 0 || *str == NULL)
                json.type = JSON_ERROR;
            break ;
        case 'n':
            json.type = JSON_NULL;
            json_null_parse(str);
            if (*str == NULL)
                json.type = JSON_ERROR;
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
                json.type = JSON_ERROR;
            break ;
        default:
            json.type = JSON_ERROR;
    }
    if (json.type == JSON_ERROR)
        json_free(json);
    else
        json_move_whitespace(str);
    return json;
}
