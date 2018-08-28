#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>
#include <stdlib.h>
#include <stdint.h>

#define ISDIGIT  1
#define ISALPHA  2
#define HASTOBE  128

#define ESC "\033"
#define CSI          ESC        "["
#define DELETELINE   CSI        "K"

#define CURSORLEFT   CSI        "%D"

#define ENTER        '\012'
#define BACKSPACE    '\010'
#define DEL          '\177'

void captureCurrentTerminal(struct termios *originalTerm);
void resetInputMode(struct termios *originalTerm);
void setInputMode(void);
char *getUserInput(char const *prompt, uint32_t numOfChar, uint8_t flags);
#endif
