#include "config.h"
#include "string.h"

static char temporary_buffer[256];
static char temporary_buffer_stdout[256];
static char temporary_buffer_stderr[256];
static FILE *my_file;
static int num_of_test;
static int test1_input[] = {2, 4, 1, 5, 8, 4};
static int idx;

/* A mock fprintf function that checks the value of strings printed to the
 * standard error stream or output stream. */
int example_test_fprintf(FILE* const file, const char *format, ...) {
    int return_value;
    va_list args;
    assert_true(file == stdout || file == stderr);
    va_start(args, format);
    return_value = vsnprintf(temporary_buffer, sizeof(temporary_buffer),
                             format, args);

    if (file == stdout) {
        strcpy(temporary_buffer_stdout, temporary_buffer);
        check_expected_ptr(temporary_buffer_stdout);
    }
    else {
        strcpy(temporary_buffer_stderr, temporary_buffer);
        check_expected_ptr(temporary_buffer_stderr);
    }

    va_end(args);
    return return_value;
}

/* A mock printf function that checks the value of strings printed to the
 * standard output stream. */
int example_test_printf(const char *format, ...) {
    int return_value;
    va_list args;
    va_start(args, format);
    return_value = vsnprintf(temporary_buffer, sizeof(temporary_buffer),
                             format, args);
    check_expected_ptr(temporary_buffer);
    va_end(args);
    return return_value;
}

void example_test_scanf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    *va_arg(args, int*) = test1_input[idx++];
    if (array_length(test1_input) == idx) *va_arg(args, char*) = '\n';
    va_end(args);
}

//int example_test_scanf(const char *format, ...) {
//    int return_value;
//
//    va_list args;
//    va_start(args, format);
//
//    if (my_file == NULL) {
//        if ((my_file = fopen("test_1.txt", "r")) == NULL) {
//            printf("Cannot open file.\n");
//            exit(1);
//        }
//    }
//    return_value = vfscanf(my_file, format, args);
//    va_end(args);
//    return return_value;
//}

static void test_example_main_no_args(void **state) {
    const char *args[] = {
            "example",
    };

    (void) state; /* unused */

    assert_int_equal(example_main(array_length(args), (char **) args), -1);
}

static void test_example_main(void **state) {
    num_of_test = 1;
    idx = 0;
    const char *args[] = {
            "example", "--from=3",
    };

    (void) state; /* unused */

    expect_string(example_test_fprintf, temporary_buffer_stdout, "2 ");
    expect_string(example_test_fprintf, temporary_buffer_stdout, "1 ");
    expect_string(example_test_printf, temporary_buffer, "3");

    assert_int_equal(example_main(array_length(args), (char **) args), 0);
}

static void test_1_main(void **state){
    num_of_test = 2;
    const char *args[] = {
            "example", "--to=9", "--from=3"
    };

    (void) state; /* unused */

    expect_string(example_test_fprintf, temporary_buffer_stdout, "1");
    expect_string(example_test_fprintf, temporary_buffer_stderr, "10");
    expect_string(example_test_fprintf, temporary_buffer_stdout, "3");

    assert_int_equal(example_main(array_length(args), (char **) args), 0);
}

int main()
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_example_main_no_args),
            cmocka_unit_test(test_example_main),
    };

    //if (my_file != NULL) fclose(my_file);
    return cmocka_run_group_tests(tests, NULL, NULL);
}