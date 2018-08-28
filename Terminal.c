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

    /* Set the terminal modes. */
    tcgetattr(STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO and INTURRUPT. */
    tattr.c_cc[VMIN] = 1;
    tattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
}

char *getUserInput(char const *prompt, uint32_t numOfChar, uint8_t flags)
{
    struct termios originalTerm;
    char c = '0', *input = NULL;
    size_t totalChar = 0;

    input = calloc(numOfChar + 1, sizeof(char));

    captureCurrentTerminal(&originalTerm);
    setInputMode();

    write(STDOUT_FILENO, prompt, strlen(prompt));

    while(c != ENTER)
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
            write(STDOUT_FILENO, CSI "1D" DELETELINE, 8);
            input[--totalChar] = '\0';
        }
    }

    resetInputMode(&originalTerm);
    return input;
}
