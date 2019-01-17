#include <linux/syscalls.h>
#include <linux/kernel.h>

asmlinkage long sys_setmyFlag(pid_t  pid, int flag){
	
	if(capable(CAP_SYS_ADMIN)){
		
		struct task_struct *currentProc = find_task_by_vpid(pid);	
		
		if (!currentProc)
			return -ESRCH;
		
		if(flag != 0 && flag != 1)
			return -EINVAL;
		
		currentProc->myFlag = flag; 
		return 0;
	}
	 
	return -EACCES;

}
