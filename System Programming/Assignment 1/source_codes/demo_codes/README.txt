systemcall_demo.c
	This is the program to test our system call set_myFlag. It asks user to give 2 inputs:
	-Process id. (To change the flag of the current process -1 must be given.)
	-Flag value.
	Program tries to set the flag of given process to given id. It will give propper error or successful
	message  as a output.
	Note that this program requires root privileges to run.

fork_demo.c
	This program tests the  fork function. It asks user to give 3 inputs.
	-Process id. (To change the flag of the current process -1 must be given.)
	-Flag value.
	-Nice value.
	It sets flag value and the priority of the given process. 
 	After that, it uses fork function to create a child process.
	Behaviour of the program changes with given input values. Returned values of the fork and set_myFlag 
	functions will given to user a run time.

exit_demo.c
	This is program to test exit function. It requires 1 input value: flag value to be set.
	After the input, it creates 5 child process and make parent process to wait them.
	All child process will be idle for 5 seconds except 3rd child. 
	The program will send terminate signal to 3rd child. 
	At normal conditions (flag value is 0) parent process has to wait all other childs for 5 seconds.
	If the flag set to 1, parent and all child will terminate immediately. 
	Note that we used signal.h library to send terminate signal.
	