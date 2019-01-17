#ifndef __QUEUE_H
#define __QUEUE_H
#include <linux/ioctl.h>


struct Node{
    char *data;
    int size;
    struct Node * next;
};

#define QUEUE_IO_MAGIC 'k'
#define QUEUE_IOPOP _IOR(QUEUE_IO_MAGIC, 0, struct Node *)
#define QUEUE_IOC_MAXNR 0



#endif