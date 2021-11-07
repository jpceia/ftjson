#include "ftjson.h"
#include <stdlib.h>

void string_array_free(char **array, int size)
{
    for (int i = 0; i < size; ++i)
        free(array[i]);
    free(array);
}
