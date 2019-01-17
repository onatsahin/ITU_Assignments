#include<stdio.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<errno.h>

#include "queue_ioctl.h"
#define NODE_DATA_SIZE 20

extern int errno;

int main(){

    int ret;
    int fd = open("/dev/queue1",O_RDWR);
    char *str = malloc(sizeof(char) * 10);
    char *str2 = malloc(sizeof(char) * 6);
    
    printf("FD:  %d",fd);
    if (fd > 0){
        ret = read(fd,str,5);
        printf("ret: %d  Readed: %s\n",ret,str);
		ret = read(fd,str2,4);
		printf("second %d read:%s\n",ret,str2);
        close(fd);    
    }
    free(str);//886.930146
}
