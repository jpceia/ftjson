#include "ftjson.h"
#include <stdlib.h>

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
