CC = gcc
CFLAGS = $(CF) -Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline
DEP = Terminal.h
SRC = terminalMain.c Terminal.c

all: $(DEP)
	$(CC) $(CFLAGS) -o terminalMain $(SRC)

debug: CFLAGS += -g
debug: all

clean:
	-@rm -rf *.o
	-@rm -rf terminalMain

