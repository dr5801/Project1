/**
 * Project 1  : Unixshell
 * Programmer : Drew Rife
 * Course     : CMPE 320
 * Section	  : 2 (11-12:50pm)
 * Instructor : S. Lee
 */
 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdbool.h>

#include "CSHELL.h"

/* builds the command line to execute */
void buildCommandLine(char  *  commandLine);

/* cound the number of arguments */
int countArguments(char * args);

/* create the process */
void createFork(char  ** commandLine);

/* execute the command */
void execute(char ** commandLine);

void runLastCommand();

/* a deconstructor to free argument pointer */
void deconstructArguments(char ** argument, int numArguments);