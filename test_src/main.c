#include <check.h>
#include <stdlib.h>

Suite *json_string_suite(void);
//Suite *json_number_suite(void);
//Suite *json_object_suite(void);
//Suite *json_array_suite(void);
//Suite *json_boolean_suite(void);
//Suite *json_null_suite(void);

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = json_string_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NOFORK);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    if (number_failed > 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
