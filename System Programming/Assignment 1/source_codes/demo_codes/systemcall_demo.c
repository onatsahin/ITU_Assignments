#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#define set_myFlag 355

extern int errno;

int main(){
	
	int ret_val;
	
	int pid;
	int flag_val;
	
	printf("Enter the process id: (Enter -1 to change flag of the current process)");
	scanf("%d",&pid);
	
	printf("Enter the flag value : ");
	scanf("%d",&flag_val);
	
	if(pid == -1)
		pid = getpid();
		
	ret_val = syscall(set_myFlag,pid,flag_val);
	
	int errnum = errno;

	if(ret_val == 0)
		printf("Flag changed!\n"); 
	else 
		printf("Error! %s\n",strerror(errnum));

	
	return 0;
}
