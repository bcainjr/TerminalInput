#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>
#include <stdlib.h>

#define ISDIGIT 1
#define ISALPHA 2

#define ESC "\033"
#define ANSIESC      ESC        "["
#define DELETELINE   ANSIESC    "K"

#define ENTER        '\012'
#define BACKSPACE    '\010'
#define DEL          '\177'

void captureCurrentTerminal(struct termios *originalTerm);
void resetInputMode(struct termios *originalTerm);
void setInputMode(void);
char *getUserInput(char *prompt, int numOfChar, int flags);
#endif
