#include<stdio.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<errno.h>

#include "queue_ioctl.h"
#define NODE_DATA_SIZE 20

extern int errno;

int main(){
    int ioctl_mode = QUEUE_IOPOP;
    
    int fd = open("/dev/queue0",O_RDWR);
    
    int errnum = errno;
    int retVal;
    struct Node * node;
    
    node = malloc(sizeof(struct Node));
    node->data = malloc(sizeof(char) * NODE_DATA_SIZE);
    node->size = NODE_DATA_SIZE;

    if (fd > 0){
        retVal = ioctl(fd,ioctl_mode,node);
        if( retVal < 0 ){
            errnum = errno;
            printf("Error! %s\n",strerror(errnum));
        }
        else{
            printf("Value of the node: %s\n",node->data);
        }
        close(fd);
    }
    else{
        printf("error:%d\n",fd);
    }
    free(node->data);
    free(node);
    
    return 0;
}
