#include "ftjson.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <check.h>

/*
 * Parse a JSON null
 */
START_TEST (parse_null)
{
    char *str = "null";
    char *p = str;
    t_json json = json_parse(&p);
    ck_assert_uint_eq(json.type, JSON_NULL);
    // compare strings
    char *s = json_stringify(json);
    ck_assert_str_eq(s, str);
    free(s);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON null with whitespaces around
 */
START_TEST (parse_null_ws)
{
    char *str = "   null   ";
    char *p = str;
    t_json json = json_parse(&p);
    ck_assert_uint_eq(json.type, JSON_NULL);
    // compare strings
    char *s = json_stringify(json);
    ck_assert_str_eq(s, "null");
    free(s);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON an invalid null
 * starts with 'n'
 */
START_TEST (parse_null_invalid_1)
{
    char *str = "none";
    char *p = str;
    t_json json = json_parse(&p);
    ck_assert_uint_eq(json.type, JSON_ERROR);
    json_free(json);
}
END_TEST


TCase *json_null_test_case(void)
{
    TCase *tc = tcase_create("JSON_Null");

    tcase_add_test(tc, parse_null);
    tcase_add_test(tc, parse_null_ws);
    tcase_add_test(tc, parse_null_invalid_1);
    return tc;
}
