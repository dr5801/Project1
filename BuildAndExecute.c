/**
 * Project 1  : Unixshell
 * Programmer : Drew Rife
 * Course     : CMPE 320
 * Section	  : 2 (11-12:50pm)
 * Instructor : S. Lee
 */

#include "BuildAndExecute.h"

bool foundAmpersand = false;


/**
 * Split the string passed in 
 * and set a pointer to each 
 * command and argument 
 */
void buildCommandLine(char  *  commandLine) {
	

	int numArguments = countArguments(commandLine);  // saves the number of arguments 
	int i;
	int index;
	int tmp;	

	bool foundFirstLetter = false;  // flag to indicate that the first letter was found

	/* create a char pointer array that has char pointers to save each command and argument */
	char **argument = malloc((numArguments + 1) * sizeof(char *));		
		
	/* allocate each pointer for the number of arguments and add 1 for the NULL terminated array */
	for(i = 0; i < numArguments+1; i++) {
			argument[i] = malloc((strlen(commandLine) + 1) * sizeof(commandLine[i]));
	}

	tmp = 0;
	i = 0;
	/* split commandLine to save each argument to argument array pointer */
	for(index = 0; index <= strlen(commandLine); index++) {
		if(!foundFirstLetter) {
			if(isspace(commandLine[index]) || commandLine[index] == '\0') {
				continue;
			}
			else {
				foundFirstLetter = true;  // indicate that we found the first letter
				tmp = index;  // set temp to the index of the first letter
			}
		}
		/* first letter is found -> now we want to see where the word ends */
		else {
			if(isspace(commandLine[index]) || commandLine[index] == '\0') {
				strncpy(argument[i], commandLine+tmp, (index)-tmp);  // set the argument[i] pointer to the command or argument 
				i++;
				foundFirstLetter = false;
			}
		}
	}

	argument[numArguments] = NULL; // null terminate the array of pointers 

	/* create the process */
	createFork(argument);
		
	/* free argument after done using */
	deconstructArguments(argument, numArguments);
}

/**
 * Count the number of arguments 
 */
int countArguments(char * commandLine) {
	int index;
	int wordCount = 0;

	for(index = 0; index <= strlen(commandLine); index++) {
		if(isalnum(commandLine[index]) || ispunct(commandLine[index])) {
			continue;
		}
		else if(isspace(commandLine[index]) || (commandLine[index] == '\0')) {
			if(isalnum(commandLine[index-1]) || ispunct(commandLine[index-1])) {
				if(commandLine[index-1] != '&'){
					wordCount++;					
				}
				else {
					foundAmpersand = true;
					commandLine[index-1] = '\0';
				}
			}	
		}	
	}
	return wordCount;
}

/**
 * Create process/es to execute the command
 */
void createFork(char  ** argument) {
	
	/* pid returns -1, 0, or a positive integer */
	pid_t pid = fork();

	/* pid is negative? indicates an error */
	if(pid < 0) {
		perror("Error: fork failed.");
		exit(-1);
	}

	/* a new process was created if 0 */
	if(pid == 0) {
		/*execute the command */
		execute(argument);

		/* something bad happened */
		abort();
	}
	/* pid is not 0? then it is the pid of the child */
	else {
		/* if no ampersand is found make parent wait for child */
		if(!foundAmpersand) {
			int status;
			waitpid(pid, &status, 0);
		}	
	}
}

/**
 * execute the command 
 */
void execute(char ** argument) {
	/* should never be 0 */
	if(execvp(argument[0], argument) < 0) {
		printf("\nexecvp failed");  // bad command
		exit(1);
	}
}

/**
 * Free argument after done with it
 */
void deconstructArguments(char ** argument, int numArguments) {
	int i;
	for(i = numArguments; i >= 0; i--) {
		free(argument[i]);
	}
}