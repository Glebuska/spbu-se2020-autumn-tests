#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
/* Compatibility with the Windows standard C library. */
#define vsnprintf _vsnprintf
#endif /* _WIN32 */

#define array_length(x) (sizeof(x) / sizeof((x)[0]))

extern int example_main(int argc, char *argv[]);

int example_test_fprintf(FILE* const file, const char *format, ...) CMOCKA_PRINTF_ATTRIBUTE(2, 3);
int example_test_printf(const char *format, ...) CMOCKA_PRINTF_ATTRIBUTE(1, 2);

static char temporary_buffer[256];
static FILE *my_file;

/* A mock fprintf function that checks the value of strings printed to the
 * standard error stream or output stream. */
int example_test_fprintf(FILE* const file, const char *format, ...) {
    int return_value;
    va_list args;
    assert_true(file == stdout || file == stderr);
    va_start(args, format);
    return_value = vsnprintf(temporary_buffer, sizeof(temporary_buffer),
                             format, args);
    check_expected_ptr(temporary_buffer);
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

int example_test_scanf(const char *format, ...) {
    int return_value;
    va_list args;
    va_start(args, format);

    if (my_file == NULL) {
        if ((my_file = fopen("test_1.txt", "r")) == NULL) {
            printf("Cannot open file.\n");
            exit(1);
        }
    }
    return_value = vfscanf(my_file, format, args);
    va_end(args);
    return return_value;
}

static void test_example_main_no_args(void **state) {
    const char *args[] = {
            "example",
    };

    (void) state; /* unused */

    assert_int_equal(example_main(array_length(args), (char **) args), -1);
}

static void test_example_main(void **state) {
    const char *args[] = {
            "example", "--from=3",
    };

    (void) state; /* unused */

    expect_string(example_test_fprintf, temporary_buffer, "2 ");
    expect_string(example_test_fprintf, temporary_buffer, "1 ");
    expect_string(example_test_printf, temporary_buffer, "3");

    assert_int_equal(example_main(array_length(args), (char **) args), 0);
}

int main()
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_example_main_no_args),
            cmocka_unit_test(test_example_main),
    };

    if (my_file != NULL) fclose(my_file);
    return cmocka_run_group_tests(tests, NULL, NULL);
}