/**
 * Project 1  : Unixshell
 * Programmer : Drew Rife
 * Course     : CMPE 320
 * Section	  : 2 (11-12:50pm)
 * Instructor : S. Lee
 */
 
#include "ShellHistory.h"

/**
 * initialize the list that was declared in main 
 */
void initializeList(ListHistory *list) {
	list->topOfHistory = list->bottomOfHistory = NULL;	
}

/**
 * adds the command to the history library 
 */
void addHistory(char  *commandLine, ListHistory * list) {	
	/* if top and bottom of history is NULL then the user has entered their first command */
	if(list->topOfHistory == NULL && list->bottomOfHistory == NULL) {	
		/* allocate memory as we need it */	
		History *history = malloc(sizeof(*history));
		if(history == NULL) {
			printf("\n\nError: out of memory!");
		}
		else {
			history->Commands = (char *)malloc((strlen(commandLine) + 1) * sizeof(char));
			strcpy(history->Commands, commandLine);
			history->prev = history->next = NULL;

			list->topOfHistory = list->bottomOfHistory = history;
		}
	}
	/* this should never happen - if it does, something went horribly wrong */
	else if(list->topOfHistory == NULL || list->bottomOfHistory == NULL) {
		printf("\n\nError: something really bad happened");
	}
	/* the user has already entered 1 command so top and bottom of history should not be null */
	else {
		/* allocate memory as we need it */
		History *history = malloc(sizeof(*history));
		history->Commands = (char *)malloc((strlen(commandLine) + 1) * sizeof(char));
		strcpy(history->Commands, commandLine);
		history->prev = history->next = NULL;

		list->bottomOfHistory->next = history;
		history->prev = list->bottomOfHistory;
		list->bottomOfHistory = history;
	}
	numberOfCommands++;
}

/**
 * execute a specific command from history
 */
void executeCommandFromHistory(unsigned long long int index, ListHistory * list) {
	if(index <= numberOfCommands) {
		int i = numberOfCommands;
		History *history = list->bottomOfHistory;
		while(i != index) {
			history = history->prev;
			i--;
		}
		buildCommandLine(history->Commands);
		addHistory(history->Commands, list);
	}
	else {
		printf("\nYour specified index (%llu) is greater than the number of commands you entered\n", index);
	}
}

/**
 * display the history from the History library 
 */
void displayHistory(ListHistory *list) {
	/* if topOfHistory or bottomOfHistory is NULL than no command was entered */
	if(list->topOfHistory == NULL && list->bottomOfHistory == NULL) {
		printf("\n\nYou haven't entered in anything");
	}
	/* if this condition is true then something really bad happened */
	else if(list->topOfHistory == NULL || list->bottomOfHistory == NULL) {
		printf("\n\nYOU SHOULD NEVER SEE THIS ;)");
	}
	else {
		int i = numberOfCommands;

		/* set history pointer to bottom of history */
		History *latest = list->bottomOfHistory;
		printf("\n\nHistory:\n");
		while(latest && i != numberOfCommands-10) {
			/* iterate through the commands */
			printf("(%d) %s\n",i, latest->Commands);
			latest = latest->prev;
			i--;
		}
	}
}

/**
 * frees the pointers in History library 
 */
void deconstructList(ListHistory *list) {
		History *freeBottom = list->bottomOfHistory;
		while(freeBottom) {
			free(freeBottom->Commands);
			freeBottom = freeBottom->prev;
		}
		free(list->topOfHistory);
}