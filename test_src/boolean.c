#include "ftjson.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <check.h>

/*
 * Parse a JSON boolean true
 */
START_TEST (parse_true)
{
    char *str = "true";
    t_json json = json_parse(str);

    ck_assert_uint_eq(json.type, JSON_BOOLEAN);
    ck_assert_uint_eq(json.boolean, 1);
    // compare strings
    char *s = json_stringify(json);
    ck_assert_str_eq(s, str);
    free(s);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON boolean false
 */ 
START_TEST (parse_false)
{
    char *str = "false";
    t_json json = json_parse(str);

    ck_assert_uint_eq(json.type, JSON_BOOLEAN);
    ck_assert_uint_eq(json.boolean, 0);
    // compare strings
    char *s = json_stringify(json);
    ck_assert_str_eq(s, str);
    free(s);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON boolean 'true' with whitespaces around
 */
START_TEST (parse_true_ws)
{
    char *str = "   true   ";
    t_json json = json_parse(str);

    ck_assert_uint_eq(json.type, JSON_BOOLEAN);
    ck_assert_int_eq(json.boolean, 1);
    // compare strings
    char *s = json_stringify(json);
    ck_assert_int_eq(json_strcmp(s, str), 0);
    free(s);
    json_free(json);
}
END_TEST


/*
 * Parse a JSON boolean 'false' with whitespaces around
 */
START_TEST (parse_false_ws)
{
    char *str = "    false   ";
    t_json json = json_parse(str);

    ck_assert_uint_eq(json.type, JSON_BOOLEAN);
    ck_assert_int_eq(json.boolean, 0);
    // compare strings
    char *s = json_stringify(json);
    ck_assert_int_eq(json_strcmp(s, str), 0);
    free(s);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON an invalid false
 * starts with 'f'
 */
START_TEST (parse_false_invalid_1)
{
    char *str = "fOoollse";
    t_json json = json_parse(str);

    ck_assert_uint_eq(json.type, JSON_ERROR);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON an invalid null
 * starts with 'false' but the string is longer
 */
START_TEST (parse_false_invalid_2)
{
    char *str = "falseeee";
    t_json json = json_parse(str);

    ck_assert_uint_eq(json.type, JSON_ERROR);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON an invalid true
 * starts with 't'
 */
START_TEST (parse_true_invalid_1)
{
    char *str = "TrOe";
    t_json json = json_parse(str);

    ck_assert_uint_eq(json.type, JSON_ERROR);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON an invalid null
 * starts with 'true' but the string is longer
 */
START_TEST (parse_true_invalid_2)
{
    char *str = "trueeeee";
    t_json json = json_parse(str);

    ck_assert_uint_eq(json.type, JSON_ERROR);
    json_free(json);
}
END_TEST


TCase *json_boolean_test_case(void)
{
    TCase *tc = tcase_create("JSON_Boolean");

    tcase_add_test(tc, parse_true);
    tcase_add_test(tc, parse_false);
    tcase_add_test(tc, parse_true_ws);
    tcase_add_test(tc, parse_false_ws);
    tcase_add_test(tc, parse_true_invalid_1);
    tcase_add_test(tc, parse_false_invalid_1);
    tcase_add_test(tc, parse_true_invalid_2);
    tcase_add_test(tc, parse_false_invalid_2);
    return tc;
}
