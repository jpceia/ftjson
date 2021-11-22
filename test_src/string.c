#include "ftjson.h"
#include <stdlib.h>
#include <stdio.h>
#include <check.h>


char *quote_string(const char *str)
{
    char *ret = malloc(strlen(str) + 3);

    if (ret == NULL)
        return NULL;
    ret[0] = '\0';
    strcat(ret, "\"");
    strcat(ret, str);
    strcat(ret, "\"");
    return ret;
}

/*
 * Parse a JSON with a (quoted) string and stringify it again.
 * checks if the string is the same.
 */
START_TEST (parse_string1)
{
    char *str = "name";
    char *s1, *s2;

    s1 = quote_string(str);
    if (s1 == NULL)
        fail();

    t_json json = json_parse(s1);
    ck_assert_uint_eq(json.type, JSON_STRING);
    ck_assert_str_eq(json.string, str);
    s2 = json_stringify(json);
    ck_assert_str_eq(s1, s2);
    free(s1);
    free(s2);
    json_free(json);
}
END_TEST


/*
 * Same as the parse_string1 test, with a longer string characters.
 */
START_TEST (parse_string2)
{
    char *str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed";
    char *s1, *s2;

    s1 = quote_string(str);
    if (s1 == NULL)
        fail();

    t_json json = json_parse(s1);
    ck_assert_uint_eq(json.type, JSON_STRING);
    ck_assert_str_eq(json.string, str);
    s2 = json_stringify(json);
    ck_assert_str_eq(s1, s2);
    free(s1);
    free(s2);
    json_free(json);
}
END_TEST


/*
 * Parse a JSON with an unquoted string at the end.
 * Must return a JSON with type JSON_ERROR
 */
START_TEST (parse_string_error1)
{
    char *str = "test";
    char *s;

    s = malloc(strlen(str) + 2);
    s[0] = '\0';
    strcat(s, "\"");
    strcat(s, str);

    t_json json = json_parse(s);
    ck_assert_uint_eq(json.type, JSON_ERROR);
    // ck_assert_ptr_eq(json.string, NULL); -> not necessarily NULL
    free(s);
}
END_TEST


/*
 * Parse a JSON with an unquoted string in the beginning.
 * Must return a JSON with type JSON_ERROR
 */
START_TEST (parse_string_error2)
{
    char *str = "test";
    char *s;

    s = malloc(strlen(str) + 2);
    s[0] = '\0';
    strcat(s, str);
    strcat(s, "\"");

    t_json json = json_parse(s);
    ck_assert_uint_eq(json.type, JSON_ERROR);
    // ck_assert_ptr_eq(json.string, NULL); -> not necessarily NULL
    free(s);
}
END_TEST


TCase *json_string_test_case(void)
{
    TCase *tc = tcase_create("JSON_String");

    tcase_add_test(tc, parse_string1);
    tcase_add_test(tc, parse_string2);
    tcase_add_test(tc, parse_string_error1);
    tcase_add_test(tc, parse_string_error2);

    return tc;
}
