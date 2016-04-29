/**
 * Project 1  : Unixshell
 * Programmer : Drew Rife
 * Course     : CMPE 320
 * Section	  : 2 (11-12:50pm)
 * Instructor : S. Lee
 */

#ifndef SHELLHISTORY_H
#define SHELLHISTORY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "BuildAndExecute.h"
#include "CSHELL.h"

/* History is the library that stores the user's commands */
typedef struct History{
	char *Commands;
	struct History *next;
	struct History *prev;
}History;

/* A List that links to the History library */
typedef struct ListHistory{
	struct History *topOfHistory;
	struct History *bottomOfHistory;
}ListHistory;

/* initialize the list from main (Constructor) */
void initializeList(ListHistory *list);

/* adds the command to the History library */
void addHistory(char *commandLine, ListHistory * list);

/* display the history of the user's commands */
void displayHistory(ListHistory *list);

/* execute specific command in history */
void executeCommandFromHistory(unsigned long long int index, ListHistory * list);

/* a deconstructor that frees the History library */
void deconstructList(ListHistory *list);

int numberOfCommands;  // the number of commands that have been entered

#endif // SHELLHISTORY_H