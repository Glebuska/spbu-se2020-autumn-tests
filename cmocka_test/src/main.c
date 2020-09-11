#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sort.h"

///* If this is being built for a unit test. */
//#ifdef UNIT_TESTING
///* Redirect printf to a function in the test application so it's possible to
// * test the standard output. */
//#ifdef printf
//#undef printf
//#endif /* printf */s
//extern int __wrap_printf(const char *format, ...);
//#define printf __wrap_printf
//
//#ifdef scanf
//#undef scanf
//#endif /* scanf */
//extern int example_test_scanf(const char *format, ...);
//#define scanf example_test_scanf
//
//
///* Redirect fprintf to a function in the test application so it's possible to
// * test error messages. */
//#ifdef fprintf
//#undef fprintf
//#endif /* fprintf */
//#define fprintf example_test_fprintf
//extern int example_test_fprintf(FILE * const file, const char *format, ...);
//
//int example_main(int argc, char *argv[]);
///* main is defined in the unit test so redefine name of the the main function
// * here. */
//#define main example_main
//
///* All functions in this object need to be exposed to the test application,
// * so redefine static to nothing. */
//#define static
//
//
//#endif /* UNIT_TESTING */
/**  Bubble sort

int sort(int *arr, int size) {
    int copy[100], transposCount = 0;
    for (int i = 0; i < size; ++i)
        copy[i] = arr[i];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        if (arr[size - i - 1] != copy[size - i - 1])
            transposCount++;
    }
    return transposCount;
}

*/

int to = 0, from = 0;
_Bool exist_to = 0, exist_from = 0;

static void parse(char *str) {
    int i = 0, cnt;
    char substr[4], number[1000];
    for ( ; i < strlen(str); ) {
        if (i < strlen(str) - 4)
            memcpy(substr, str + i, 4 * sizeof(char));
        else
            memcpy(substr, str + i, 2 * sizeof(char));
        if (substr[0] == 'f' && substr[1] == 'r' && substr[2] == 'o' && substr[3] == 'm') {
            i += 5;
            exist_from = 1;
            cnt = 0;
            memset(number, ' ', 1000 * sizeof(char));
            for ( ; i < strlen(str) && '0' <= str[i] && str[i] <= '9'; ++i)
                number[cnt++] = str[i];
            from = atoi(number);
        }
        else if (substr[0] == 't' && substr[1] == 'o') {
            i += 3;
            exist_to = 1;
            cnt = 0;
            memset(number, ' ', 1000 * sizeof(char));
            for ( ; i < strlen(str) && '0' <= str[i] && str[i] <= '9'; ++i)
                number[cnt++] = str[i];
            to = atoi(number);
        }
        else {
            ++i;
        }
    }
}

int main(int argc, char *argv[]) {

    // Parsing argv
    char argv_concat[1000];
    // if no argument -> return -1
    if (argc == 1){
        return -1;
    }

    if (argc > 3){
        return -2;
    }

    for (int i = 1; i < argc; ++i)
        strcat(argv_concat, argv[i]);
    parse(argv_concat);

    // Reading numbers
    int arr[100], count = 0, arrSize = 0;
    int data[100];
    char space_symbol;
    space_symbol = ' ';
    while (space_symbol != '\n') {
        scanf("%d%c", &data[count], &space_symbol);
        if (exist_from && data[count] <= from) {
            fprintf(stdout, "%d ", data[count]);
        }
        else {
            if (exist_to && data[count] >= to)
                fprintf(stderr, "%d ", data[count]);
            else
                arr[arrSize++] = data[count];
        }
    }
    int ans = sort(arr, arrSize);
    printf("%d", ans);

    return 0;
}
