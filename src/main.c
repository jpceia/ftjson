
#include "ftjson.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    t_json json;
    t_json_array *array = NULL;
    t_json_array *array2 = NULL;
    t_json_object *object = NULL;

    json_array_pushback(&array, json_from_string("Hello"));
    json_array_pushback(&array, json_from_number(42));
    json_array_pushback(&array, json_from_number(32));

    json_array_pushback(&array2, json_from_string("World"));
    json_array_pushback(&array2, json_from_number(1));
    json_array_pushback(&array2, json_from_number(2));
    json_object_pushback(&object, "key1", json_from_array(array));
    json_object_pushback(&object, "key2", json_from_number(42));
    json_object_pushback(&object, "key3", json_from_array(array2));
    // json = json_from_array(array);
    json = json_from_object(object);
    char *s = json_stringify(json);
    puts(s);
    free(s);
    json_free(json);
    return 0;
}
