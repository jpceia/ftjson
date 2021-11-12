#include "ftjson.h"
#include <stdlib.h>
#include <check.h>


/*
 * Parse a JSON with a (quoted) string and stringify it again.
 * checks if the string is the same.
 */
START_TEST (parse_string1)
{
    char *str = "name";
    char *s1, *s2;

    s1 = malloc(strlen(str) + 3);
    s1[0] = '\0';
    strcat(s1, "\"");
    strcat(s1, str);
    strcat(s1, "\"");
    char *p = s1;
    t_json json = json_parse(&p);
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

    s1 = malloc(strlen(str) + 3);
    s1[0] = '\0';
    strcat(s1, "\"");
    strcat(s1, str);
    strcat(s1, "\"");
    char *p = s1;
    t_json json = json_parse(&p);
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
    char *p = s;
    t_json json = json_parse(&p);
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
    char *p = s;
    t_json json = json_parse(&p);
    ck_assert_uint_eq(json.type, JSON_ERROR);
    // ck_assert_ptr_eq(json.string, NULL); -> not necessarily NULL
    free(s);
}
END_TEST


Suite *json_string_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("JSON");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, parse_string1);
    tcase_add_test(tc_core, parse_string2);
    tcase_add_test(tc_core, parse_string_error1);
    tcase_add_test(tc_core, parse_string_error2);
    suite_add_tcase(s, tc_core);

    return s;
}
