#include "ftjson.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


t_json json_from_number(double number)
{
    t_json json;
    
    json.type = JSON_NUMBER;
    json.number = number;
    return json;
}

char *json_number_stringify(double number)
{
    char *str = (char *)malloc(32);
    
    if (str == NULL)
        return NULL;
    sprintf(str, "%g", number);
    return str;
}

double json_number_parse(char **str)
{
    double number;
    char *endptr;
    
    number = strtod(*str, &endptr);
    if (endptr == *str)
    {
        *str = NULL;
        return 0;
    }
    *str = endptr;
    return number;
}
