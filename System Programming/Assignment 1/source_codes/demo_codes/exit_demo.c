#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/resource.h>
#include <signal.h>

#define set_myFlag 355

extern int errno;

int main(){
	
	int pid = getpid();
	printf("I am parent process, pid: %d\n",pid);
	int i;
	int f;
	int wpid = 1,status = 0;
	int flag_val = 0;
	int which = PRIO_PROCESS;
	
	printf("The program is going to set myFlag of the 3rd child.\nEnter the value of the flag: ");
	scanf("%d",&flag_val);
	
	
	
	for(i = 0; i < 5; i++){
		f = fork();
		if(f == 0)
			break;
		else if(f < 0){
			printf("Error on fork!\n");
			break;
		} 
	}
	if(f > 0){
		printf("Parent waits for each children to finish\n");
		while(wpid > 0)
			wpid = wait(&status);
		printf("All child are finished\n");
	}
	else if(f == 0 && i != 3){
		sleep(5);
		printf("I am the %d.child with process id: %d, my parent is: %d\n", i,getpid(), getppid());
	}
	else if(f == 0 && i == 3){
		printf("I am the %d.child with process id: %d, my parent is: %d\n",i, getpid(), getppid());
		printf("Setting the flag to 1 of the child 3 with the process id %d\n",getpid());
		
		int nice_val = 17;
		int ret_val = syscall(set_myFlag,getpid(),flag_val);
		int errnum = errno;
		
		if(ret_val == 0){
			printf("Set priority of the children with the pid %d\n",getpid());
			setpriority(which,getpid(),nice_val);
			printf("Flag changed!\nSend signal to kill %d\n",getpid()); 
			kill(getpid(),SIGKILL);
		}
		else 
			printf("Error! %s\n",strerror(errnum));
	}
	
	return 0;
}
