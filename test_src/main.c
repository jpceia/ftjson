#include <check.h>
#include <stdlib.h>

TCase *json_string_test_case(void);
TCase *json_object_test_case(void);
TCase *json_array_test_case(void);
TCase *json_boolean_test_case(void);
TCase *json_null_test_case(void);

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = suite_create("JSON");;
    suite_add_tcase(s, json_string_test_case());
    suite_add_tcase(s, json_object_test_case());
    suite_add_tcase(s, json_array_test_case());
    suite_add_tcase(s, json_boolean_test_case());
    suite_add_tcase(s, json_null_test_case());
    
    sr = srunner_create(s);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    if (number_failed > 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
