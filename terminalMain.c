/*
* Bruce Cain
*
*
*/

#include <stdio.h>
#include "Terminal.h"

int main(void)
{
    char *input = getUserInput("Enter a number: ", 5, ISDIGIT);

    printf("\nNumber entered: %ld\n", strtol(input, NULL, 10));
    return 0;
}

