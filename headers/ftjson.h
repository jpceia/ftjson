#ifndef FTJSON_H
# define FTJSON_H

# include <stddef.h>

typedef struct s_json           t_json;
typedef struct s_json_object    t_json_object;
typedef struct s_json_array     t_json_array;

typedef enum e_value_type
{
    JSON_ERROR = 0,
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_STRING,
    JSON_NUMBER,
    JSON_BOOLEAN,
    JSON_NULL
}   t_value_type;

typedef struct s_json
{
    union
    {
        t_json_object   *object;
        t_json_array    *array;
        char            *string;
        double          number;
        int             boolean;
    };
    t_value_type        type;
}   t_json;

typedef struct s_json_object
{
    char            *key;
    t_json          value;
    t_json_object   *next;
}   t_json_object;

typedef struct s_json_array
{
    t_json          value;
    t_json_array    *next;
}   t_json_array;

// -----------------------------------------------------------------------------
// JSON General Functions
// -----------------------------------------------------------------------------

void json_free(t_json json);
char *json_stringify(t_json json);
t_json json_parse(char **str);

// -----------------------------------------------------------------------------
// JSON Object Functions
// -----------------------------------------------------------------------------

t_json json_from_object(t_json_object *object);
t_json_object *json_object_new(char *key, t_json value);
void json_object_free(t_json_object *object);
int json_object_size(t_json_object *object);
t_json_object *json_object_append(t_json_object **object, t_json_object *new_object);
t_json_object *json_object_pushback(t_json_object **object, char *key, t_json value);
char *json_object_stringify(t_json_object *object);

// -----------------------------------------------------------------------------
// JSON Array Functions
// -----------------------------------------------------------------------------

t_json json_from_array(t_json_array *array);
t_json_array *json_array_new(t_json value);
void json_array_free(t_json_array *array);
int json_array_size(t_json_array *array);
t_json_array *json_array_pushback(t_json_array **array, t_json value);
t_json_array *json_array_pushfront(t_json_array **array, t_json value);
char *json_array_stringify(t_json_array *array);
t_json_array *json_array_parse(char **str);

// -----------------------------------------------------------------------------
// JSON String Functions
// -----------------------------------------------------------------------------

t_json json_from_string(char *string);
char *json_string_stringify(char *string);
char *json_string_parse(char **str);

// -----------------------------------------------------------------------------
// JSON Value Functions
// -----------------------------------------------------------------------------

// Number
t_json json_from_number(double number);
char *json_number_stringify(double number);
double json_number_parse(char **string);

// Boolean
t_json json_from_boolean(int boolean);
char *json_boolean_stringify(int boolean);
int json_boolean_parse(char **string);

/// Null
t_json json_from_null(void);
char *json_null_stringify(void);
void json_null_parse(char **str);

// -----------------------------------------------------------------------------
// Utility Functions
// -----------------------------------------------------------------------------
void string_array_free(char **array, int size);
void json_move_whitespace(char **str);
void *realloc_free_on_fail(void *ptr, size_t size);

#endif
