/**
 * Project 1  : Unixshell
 * Programmer : Drew Rife
 * Course     : CMPE 320
 * Section	  : 2 (11-12:50pm)
 * Instructor : S. Lee
 */

 #include "CSHELL.h"

/**
 * mimic a standard UNIX terminal
 */
int main(void) {
	ListHistory list;
	initializeList(&list);

	char args[MAX_LINE/2 + 1];  // user inputted string
	char previousCommand[MAX_LINE/2 + 1];

	bool should_run = true; // flag to indicate if the user entered "exit"

	/* run until user enters "exit" */
	while(should_run) {
		printf("\nosh> ");
		fflush(stdout);
		fgets(args, (MAX_LINE/2 + 1), stdin);

		/* check to see if the user entered a command,
		   fgets adds a newline character once the user presses enter
		   so if the user enters in a command the newline character
		   should not be at the first position */
		if(args[0] != '\n') {
			int i = 0;
			char *token;
			strtok_r(args, "\n", &token);

			/* check if user enters "exit" */
			if(strcasecmp(args, "exit") == 0) {
				should_run = false;
			}
			/* the user wants a specific command in history executed */
			else if(args[0] == '!' && isdigit(args[1])) {
				/* make sure the user actually entered a command first */
				if(list.bottomOfHistory != NULL && list.topOfHistory != NULL) {
					int digit;
					unsigned long long int index;
					int length = strlen(args)-1;
					int number[length];

					/* parse the string array for the individual digits entered */
					for(digit = 1; isdigit(args[digit]); digit++) {
						number[i++] = (args[digit] - '0');
					}					
					
					/* save the array of ints as a whole number */
					switch(length) {
						case 1:
							index = number[0];
							break;
						case 2:
							index = (10 * number[0]) + number[1];
							break;
						case 3:
							index = (100 * number[0]) + ((10 * number[1]) + number[2]);
							break;
						case 4:
							index = (1000 * number[0]) + (100 * number[1] + ((10 * number[2]) + number[3]));
							break; 
					}

					/* execute the specified indexed command from history */
					executeCommandFromHistory(index, &list);
				}
				/* the user has entered no commands */
				else {
					printf("\nError: no commands in history - you need to enter a command!\n");
				}
			}
			/* if the user doesn't enter history (or exit or !! or !#) then it is a command */
			else if(strcasecmp(args, "history") != 0 && strcasecmp(args,"!!") != 0) {
					strncpy(previousCommand, args, strlen(args) + 1);
					addHistory(args, &list);
					buildCommandLine(args);
			}
			/* the user wants the last command executed */
			else if(strcasecmp(args, "!!") == 0) {
					if(list.bottomOfHistory != NULL && list.topOfHistory != NULL) {
						History *p = list.bottomOfHistory;
						addHistory(p->Commands, &list);
						buildCommandLine(p->Commands);						
					}
					else {
						printf("\nError: no commands in history - you need to enter a command!\n");
					}
			}
			/* user entered history */
			else if(strcasecmp(args, "history") == 0) {
				displayHistory(&list);
			}
		}
		/* the user didn't enter a command */
		else {
			printf("You didn't enter in a command!");
		}
	}

	/* free pointers from list once user is done with terminal */
	deconstructList(&list);
	return 0;
}