############################################################################
## Project 1  : Unixshell
## Programmer : Drew Rife
## Course     : CMPE 320
## Section	  : 2 (11-12:50pm)
## Instructor : S. Lee
############################################################################
CC = gcc
CFLAGS = -Wall -g
DEPS = CSHELL.h ShellHistory.h BuildAndExecute.h
OBJ = CSHELL.o BuildAndExecute.o ShellHistory.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

terminal: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) terminal