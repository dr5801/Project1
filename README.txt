Project 1  : Unixshell
Programmer : Drew Rife
Course     : CMPE 320
Section    : 2 (11-12:50)
Instructor : S. Lee

CONTENTS OF THIS FILE
----------------------
(1) : Introduction
(2) : Configuration
(3) : Bugs



INTRODUCTION
-------------
This is a basic C program that mimics a UNIX Shell.  The user will be allowed to enter any UNIX command they wish and should execute properly.  Commands like "history" will display the history of the latest 10 commands.  The command "!!" will execute the last command entered and "!#" will execute that specific command in history index that the user previously entered.


CONFIGURATION
--------------
The following files are CRUCIAL for this program to work:
	CSHELL.c
	CSHELL.h
	BuildAndExecute.c
	BuildAndExecute.h
	ShellHistory.c
	ShellHistory.h
	makefile
Should any of these files not exist within the package will result in the program not working.  It is crucial to not delete any contents within the package.

To run the UnixShell program you first must make sure that the package is clean.  

To do this the user shall enter in the following command:
	make clean

For the program to be compiled the user shall enter the following command:
	make

For the user to be able to run the program they shall enter the following command:
	./terminal

From there the program will run and the UnixShell program will run and then the user has free choice of what they want to do with it.

When the user is done with the program, they shall enter "exit" for the program to finish.



BUGS
-----
For executing the latest command "!!" the user must enter it exactly as the quoted message.  If it is different in any way then the program will think that it is a new command.

The same is with "!#" as well ^