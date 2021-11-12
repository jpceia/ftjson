#include "ftjson.h"
#include <stdio.h>
#include <string.h>


t_json json_from_null(void)
{
    t_json json;
    
    json.type = JSON_NULL;
    return json;
}

char *json_null_stringify(void)
{
    return strdup("null");
}

void json_null_parse(char **str)
{
    char *null_str = "null";

    if (strncmp(*str, null_str, 4) != 0)
    {
        perror("Invalid name");
        *str = NULL;
    }
    *str += 4;
}
