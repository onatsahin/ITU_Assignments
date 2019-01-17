#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/resource.h>
#define set_myFlag 355

extern int errno;

int main(){
	
	int ret_val;
	int flag_val;
	int pid;
	int which = PRIO_PROCESS;
	int nice_val;
	printf("Enter the process id (Enter -1 to change flag of the current process) ");
	scanf("%d",&pid);
	
	printf("Enter the flag value : ");
	scanf("%d",&flag_val);
	
	printf("Enter the nice value : ");
	scanf("%d",&nice_val);
	
	if(pid == -1)
		pid = getpid();
	
	printf("Setting the priority of the process %d to %d...\n",pid,nice_val);
	setpriority(which,pid,nice_val);

	printf("Setting the flag...\n");
	ret_val = syscall(set_myFlag,pid,flag_val);
	int errnum = errno;
	
	
	if(ret_val == 0){
		
		printf("Changed the flag to %d! \n",flag_val);
		int forkReturn = fork();
		errnum = errno;
		
		if(forkReturn > 0) {
			printf("I am parent with the pid: %d. Fork return as: %d\n",getpid(),forkReturn);
			wait(); 
		}
		else if(forkReturn < 0) 
			printf("Fork Error! %s\n",strerror(errnum));
		else 
			printf("I am a child with pid %d, my parent : %d\n",getpid(),getppid());
		
	}else 
		printf("Error while setting the flag! %s\n",strerror(errnum));
	
	return 0;
}
