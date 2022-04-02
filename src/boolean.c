#include "ftjson.h"
#include <string.h>


t_json json_from_boolean(int boolean)
{
    t_json json;
    
    json.type = JSON_BOOLEAN;
    json.boolean = boolean;
    return json;
}

char *json_boolean_stringify(int boolean)
{
    return strdup(boolean ? "true" : "false");
}

/**
 * @brief Parses a JSON boolean from a string
 * 
 * @param str 
 * @return int 
 */
int json_boolean_parse(char **str)
{
    if (!strncmp(*str, "true", 4))
    {
        *str += 4;
        return 1;
    }
    else if (!strncmp(*str, "false", 5))
    {
        *str += 5;
        return 0;
    }
    *str = NULL;
    return -1;
}
