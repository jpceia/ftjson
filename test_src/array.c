#include "ftjson.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <check.h>


/*
 * Parse a JSON empty array
 */
START_TEST (parse_array_empty)
{
    char *str = "[]";
    char *p = str;
    t_json json = json_parse(&p);
    ck_assert_uint_eq(json.type, JSON_ARRAY);
    ck_assert_ptr_eq(json.array, NULL);
    // compare strings
    char *s = json_stringify(json);
    ck_assert_str_eq(s, str);
    free(s);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON array with one element
 */
START_TEST (parse_array_one_element)
{
    char *str = "[\"hello\"]";
    char *p = str;
    
    t_json json = json_parse(&p);
    ck_assert_uint_eq(json.type, JSON_ARRAY);
    ck_assert_uint_eq(json_array_size(json.array), 1);
    // compare strings
    char *s = json_stringify(json);
    ck_assert_str_eq(s, str);
    free(s);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON array with two elements
 */
START_TEST (parse_array_two_elements)
{
    char *str = "[\"hello\", \"world\"]";
    char *p = str;
    
    t_json json = json_parse(&p);
    ck_assert_uint_eq(json.type, JSON_ARRAY);
    ck_assert_uint_eq(json_array_size(json.array), 2);
    // compare strings
    char *s = json_stringify(json);
    ck_assert_str_eq(s, str);
    free(s);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON array with nested arrays
 */
START_TEST (parse_array_nested1)
{
    char *str = "[\"a\", [\"b\", [\"c\"]]]";
    char *p = str;
    
    t_json json = json_parse(&p);
    ck_assert_uint_eq(json.type, JSON_ARRAY);
    ck_assert_uint_eq(json_array_size(json.array), 2);
    ck_assert_uint_eq(json.array->next->value.type, JSON_ARRAY);
    // compare strings
    char *s = json_stringify(json);
    ck_assert_str_eq(s, str);
    free(s);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON array with nested arrays (test 2)
 */
START_TEST (parse_array_nested2)
{
    char *str = "[[[\"a\"], \"b\"], \"c\"]";
    char *p = str;
    
    t_json json = json_parse(&p);
    ck_assert_uint_eq(json.type, JSON_ARRAY);
    ck_assert_int_eq(json_array_size(json.array), 2);
    ck_assert_uint_eq(json.array->value.type, JSON_ARRAY);
    // compare strings
    char *s = json_stringify(json);
    ck_assert_str_eq(s, str);
    free(s);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON array with invalid element
 */
START_TEST (parse_array_invalid_element)
{
    char *str = "[a]";
    char *p = str;
    t_json json = json_parse(&p);
    ck_assert_uint_eq(json.type, JSON_ERROR);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON array with a trailing comma
 */
START_TEST (parse_array_trailing_comma)
{
    char *str = "[\"hello\",]";
    char *p = str;
    t_json json = json_parse(&p);
    ck_assert_uint_eq(json.type, JSON_ERROR);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON unclosed array
 */
START_TEST (parse_array_unclosed)
{
    char *str = "[\"hello\"";
    char *p = str;
    t_json json = json_parse(&p);
    ck_assert_uint_eq(json.type, JSON_ERROR);
    json_free(json);
}
END_TEST


TCase *json_array_test_case(void)
{
    TCase *tc = tcase_create("JSON_Array");

    tcase_add_test(tc, parse_array_empty);
    tcase_add_test(tc, parse_array_one_element);
    tcase_add_test(tc, parse_array_two_elements);
    tcase_add_test(tc, parse_array_nested1);
    tcase_add_test(tc, parse_array_nested2);
    tcase_add_test(tc, parse_array_invalid_element);
    tcase_add_test(tc, parse_array_trailing_comma);
    tcase_add_test(tc, parse_array_unclosed);
    return tc;
}
