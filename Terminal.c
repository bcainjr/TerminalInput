/*
* Bruce Cain
*
* Work out termios
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include "Terminal.h"

/* Use this variable to remember original terminal attributes. */

void resetInputMode(struct termios *originalTerm)
{
    tcsetattr(STDIN_FILENO, TCSANOW, originalTerm);
}

void captureCurrentTerminal(struct termios *originalTerm)
{
    /* Make sure stdin is a terminal. */
    if(!isatty(STDIN_FILENO))
    {
        fprintf(stderr, "Not a terminal.\n");
        exit(EXIT_FAILURE);
    }

    /* Save the terminal attributes so we can restore them later. */
    tcgetattr(STDIN_FILENO, originalTerm);

}

void setInputMode(void)
{
    struct termios tattr;
    char *name;

    /* Set the terminal modes. */
    tcgetattr(STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO and INTURRUPT. */
    tattr.c_cc[VMIN] = 1;
    tattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
}

char *getUserInput(char *prompt, int numOfChar, int flags)
{
    struct termios originalTerm;
    char c = '0', *input = NULL, *returnValue = NULL;
    size_t totalChar = 0;

    input = calloc(numOfChar, sizeof(char));

    captureCurrentTerminal(&originalTerm);
    setInputMode();

    write(STDIN_FILENO, prompt, strlen(prompt));

    while(c != ENTER || totalChar < numOfChar)
    {
        read(STDIN_FILENO, &c, 1);
        if(isdigit(c) && totalChar != numOfChar && (flags & ISDIGIT))
        {
            write(STDOUT_FILENO, &c, 1);
            input[totalChar++] = c;
        }
        else if(isalpha(c) && totalChar != numOfChar && (flags & ISALPHA))
        {
            write(STDOUT_FILENO, &c, 1);
            input[totalChar++] = c;
        }

        else if((c == DEL || c == BACKSPACE) && totalChar != 0)
        {
            write(STDOUT_FILENO, ANSIESC "1D" DELETELINE, 13);
            totalChar--;
        }
    }

    resetInputMode(&originalTerm);
    returnValue = input;
    free(input);
    return returnValue;
}
