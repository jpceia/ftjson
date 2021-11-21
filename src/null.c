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
    if (strncmp(*str, "null", 4) != 0)
    {
        fprintf(stderr, "Invalid name\n");
        *str = NULL;
        return ;
    }
    *str += 4;
}
