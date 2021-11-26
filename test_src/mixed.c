#include "ftjson.h"
#include <stdio.h>
#include <stdlib.h>
#include <check.h>

/*
 * Parse a JSON from file
 */
START_TEST (parse_json_sample_web)
{
    char *s1 = file_to_string("data/adobesvg.json");
    t_json json = json_parse(s1);

    ck_assert_uint_eq(json.type, JSON_OBJECT);

    char *s2 = json_stringify(json);
    ck_assert_int_eq(json_strcmp(s1, s2), 0);
    
    free(s1);
    free(s2);
    json_free(json);
}
END_TEST


TCase *json_mixed_test_case(void)
{
    TCase *tc = tcase_create("JSON_mixed");

    tcase_add_test(tc, parse_json_sample_web);
    return tc;
}
