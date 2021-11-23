#include "ftjson.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <check.h>
#include <math.h>

/*
 * Parse a JSON with a positive integer
 */
START_TEST (parse_positive_int)
{
    int nb = 123;
    char s1[12];
    char *s2;

    sprintf(s1, "%d", nb);
    t_json json = json_parse(s1);

    ck_assert_uint_eq(json.type, JSON_NUMBER);

    // compare numbers
    s2 = json_stringify(json);
    ck_assert_str_eq(s1, s2);

    free(s2);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON with a negative integer
 */
START_TEST (parse_negative_int)
{
    int nb = -123;
    char s1[12];
    char *s2;

    sprintf(s1, "%d", nb);
    t_json json = json_parse(s1);

    ck_assert_uint_eq(json.type, JSON_NUMBER);
    
    // compare numbers
    s2 = json_stringify(json);
    ck_assert_str_eq(s1, s2);

    free(s2);
    json_free(json);
}
END_TEST

/*
 * Parse a JSON with a positive decimal
 */
START_TEST (parse_positive_float)
{
    float nb = 123.45;
    char s[12];

    sprintf(s, "%g", nb);
    t_json json = json_parse(s);

    ck_assert_uint_eq(json.type, JSON_NUMBER);
    ck_assert_uint_eq(fabs(json.number / nb - 1) < __FLT_EPSILON__, 1);

    json_free(json);
}
END_TEST

/*
 * Parse a JSON with a negative decimal
 */
START_TEST (parse_negative_float)
{
    float nb = -123.45;
    char s[__FLT_MAX_10_EXP__ + 1];

    sprintf(s, "%g", nb);
    t_json json = json_parse(s);

    ck_assert_uint_eq(json.type, JSON_NUMBER);
    ck_assert_uint_eq(fabs(json.number / nb - 1) < __FLT_EPSILON__, 1);

    json_free(json);
}
END_TEST

/*
 * Parse a JSON with a big float
 */
START_TEST (parse_big_float1)
{
    float nb = 123e23;
    char s[__FLT_MAX_EXP__ + 1];

    sprintf(s, "%g", nb);
    t_json json = json_parse(s);

    ck_assert_uint_eq(json.type, JSON_NUMBER);
    ck_assert_uint_eq(fabs(json.number / nb - 1) < __FLT_EPSILON__, 1);

    json_free(json);
}
END_TEST

/*
 * Parse a JSON with a big float with alternative notation (E)
 */
START_TEST (parse_big_float2)
{
    float nb = 123.456E23;
    char s[__FLT_MAX_EXP__ + 1];

    sprintf(s, "%g", nb);
    t_json json = json_parse(s);

    ck_assert_uint_eq(json.type, JSON_NUMBER);
    ck_assert_uint_eq(fabs(json.number / nb - 1) < __FLT_EPSILON__, 1);

    json_free(json);
}
END_TEST

/*
 * Parse a JSON with a small float.
 */
START_TEST (parse_small_float)
{
    double nb = 5E-33;
    char s[__FLT_MAX_EXP__ + 1];

    sprintf(s, "%g", nb);
    t_json json = json_parse(s);

    ck_assert_uint_eq(json.type, JSON_NUMBER);
    ck_assert_uint_eq(fabs(json.number / nb - 1) < __FLT_EPSILON__, 1);

    json_free(json);
}
END_TEST

/*
 * Parse a JSON with an invalid integer
 */
START_TEST (parse_invalid_char)
{
    char *s = "123a";
    t_json json = json_parse(s);

    ck_assert_uint_eq(json.type, JSON_ERROR);

    json_free(json);
}
END_TEST

/*
 * Parse a JSON with invalid float (two dots)
 */
START_TEST (parse_invalid_dot)
{
    char *s1 = "123..45";
    t_json json = json_parse(s1);

    ck_assert_uint_eq(json.type, JSON_ERROR);

    json_free(json);
}
END_TEST

/*
 * Parse a JSON with an invalid int (negative sign in the middle)
 */
START_TEST (parse_invalid_signal)
{
    char *s1 = "1-23";
    t_json json = json_parse(s1);

    ck_assert_uint_eq(json.type, JSON_ERROR);

    json_free(json);
}
END_TEST

/*
 * Parse a JSON with an invalid exponent
 */
START_TEST (parse_invalid_exponent)
{
    char *s1 = "1e-";
    t_json json = json_parse(s1);

    ck_assert_uint_eq(json.type, JSON_ERROR);

    json_free(json);
}
END_TEST

/*
 * Parse a JSON with an exponent declared twice
 */
START_TEST (parse_exponent_twice)
{
    char *s1 = "1e-23e-23";
    t_json json = json_parse(s1);

    ck_assert_uint_eq(json.type, JSON_ERROR);

    json_free(json);
}
END_TEST


TCase *json_number_test_case(void)
{
    TCase *tc = tcase_create("JSON_Number");

    tcase_add_test(tc, parse_positive_int);
    tcase_add_test(tc, parse_negative_int);
    tcase_add_test(tc, parse_positive_float);
    tcase_add_test(tc, parse_negative_float);
    tcase_add_test(tc, parse_big_float1);
    tcase_add_test(tc, parse_big_float2);
    tcase_add_test(tc, parse_small_float);
    tcase_add_test(tc, parse_invalid_char);
    tcase_add_test(tc, parse_invalid_dot);
    tcase_add_test(tc, parse_invalid_signal);
    tcase_add_test(tc, parse_invalid_exponent);
    tcase_add_test(tc, parse_exponent_twice);

    return tc;
}
