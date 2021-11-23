#include "ftjson.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <check.h>

/*
 * Parses a JSON empty object
 */
START_TEST (parse_object_empty)
{
    char *str = "{}";
    t_json json = json_parse(str);

    ck_assert_uint_eq(json.type, JSON_OBJECT);
    ck_assert_ptr_eq(json.object, NULL);
    // compare strings
    char *s = json_stringify(json);
    ck_assert_int_eq(json_strcmp(s, str), 0);
    free(s);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON object with one pair
 */
START_TEST (parse_object_one_pair)
{
    char *str = "{\"key\"   :   \"value\"}";
    t_json json = json_parse(str);

    ck_assert_uint_eq(json.type, JSON_OBJECT);
    ck_assert_uint_eq(json_object_size(json.object), 1);
    // compare strings
    char *s = json_stringify(json);
    ck_assert_int_eq(json_strcmp(s, str), 0);
    free(s);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON object with two pairs
 */
START_TEST (parse_object_two_pairs)
{
    char *str = "  {\"key1\"   : \"value1\", \
        \"key2\": \"value2\"}  ";
    t_json json = json_parse(str);

    ck_assert_uint_eq(json.type, JSON_OBJECT);
    ck_assert_uint_eq(json_object_size(json.object), 2);
    // compare strings
    char *s = json_stringify(json);
    ck_assert_int_eq(json_strcmp(s, str), 0);
    free(s);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON object with invalid key (unquoted string)
 */
START_TEST (parse_object_invalid_key)
{
    char *str = "{\"key\":\"value\", a:\"value\"}";
    t_json json = json_parse(str);

    ck_assert_uint_eq(json.type, JSON_ERROR);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON object with invalid value
 */
START_TEST (parse_object_invalid_value)
{
    char *str = "{\"key\":\"value\",\"a\":fALSE}";
    t_json json = json_parse(str);

    ck_assert_uint_eq(json.type, JSON_ERROR);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON object with a trailing comma
 */
START_TEST (parse_object_trailing_comma)
{
    char *str = "{\"key\":\"value\",}";
    t_json json = json_parse(str);

    ck_assert_uint_eq(json.type, JSON_ERROR);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON unclosed object
 */
START_TEST (parse_object_unclosed)
{
    char *str = "{\"key\": \"value\"";
    t_json json = json_parse(str);

    ck_assert_uint_eq(json.type, JSON_ERROR);
    json_free(json);
}
END_TEST


TCase *json_object_test_case(void)
{
    TCase *tc = tcase_create("JSON_Object");

    tcase_add_test(tc, parse_object_empty);
    tcase_add_test(tc, parse_object_one_pair);
    tcase_add_test(tc, parse_object_two_pairs);
    tcase_add_test(tc, parse_object_invalid_key);
    tcase_add_test(tc, parse_object_invalid_value);
    tcase_add_test(tc, parse_object_trailing_comma);
    tcase_add_test(tc, parse_object_unclosed);
    return tc;
}
