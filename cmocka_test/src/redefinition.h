#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sort.h"

/* If this is being built for a unit test. */
#ifdef UNIT_TESTING
/* Redirect printf to a function in the test application so it's possible to
 * test the standard output. */
#ifdef printf
#undef printf
#endif /* printf */
extern int example_test_printf(const char *format, ...);
#define printf example_test_printf

#ifdef scanf
#undef scanf
#endif /* scanf */
extern int example_test_scanf(const char *format, ...);
#define scanf example_test_scanf


/* Redirect fprintf to a function in the test application so it's possible to
 * test error messages. */
#ifdef fprintf
#undef fprintf
#endif /* fprintf */
#define fprintf example_test_fprintf
extern int example_test_fprintf(FILE * const file, const char *format, ...);

int example_main(int argc, char *argv[]);
/* main is defined in the unit test so redefine name of the the main function
 * here. */
#define main example_main

/* All functions in this object need to be exposed to the test application,
 * so redefine static to nothing. */
#define static


#endif /* UNIT_TESTING */

