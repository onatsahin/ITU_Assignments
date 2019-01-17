#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>	/* printk() */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/types.h>	/* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h>	/* O_ACCMODE */
#include <linux/seq_file.h>
#include <linux/cdev.h>

#include <asm/switch_to.h>		/* cli(), *_flags */
#include <asm/uaccess.h>	/* copy_*_user */

#include "queue_ioctl.h"
#include "queue.h"
MODULE_LICENSE("Dual BSD/GPL");

int queue_major = QUEUE_MAJOR;
int queue_minor = 0;
int queue_nr_devs = QUEUE_NR_DEVS;

// Set the permision and the type of the parameters.
module_param(queue_major, int, S_IRUGO);
module_param(queue_minor, int, S_IRUGO);
module_param(queue_nr_devs, int, S_IRUGO);

struct queue_dev *queue_devices;

int queue_trim(struct queue_dev *dev){
    struct Node *trav;
    while(dev->head){
        trav = dev->head;
        dev->head = dev->head->next;
        kfree(trav);
    }
    dev->head = NULL;
    return 0;
}

int queue_open(struct inode *inode, struct file *filp){

    struct queue_dev *dev;

    dev = container_of(inode->i_cdev, struct queue_dev, cdev);
    filp->private_data = dev;

    return 0;
}

int queue_release(struct inode *inode, struct file *filp){
    return 0;
}

ssize_t queue_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos){
    
    struct queue_dev *dev = filp->private_data;
    struct Node * trav  = dev->head;
    struct Node * tempTrav = trav;
    char *concatanatedStr = NULL;
    int toRetIndex = 0;
    int i = 0;
    int tempCount = 0;
    int length = 0;
    int read_start = *f_pos;
    ssize_t retVal = 0;

    // Check whether 0th device is read.
    if ( iminor(filp->f_path.dentry->d_inode ) == 0 )
        return -EPERM; 
    
    if(down_interruptible(&dev->sem))
        return -ERESTARTSYS;


    // Move to the file position.
    trav  = dev->head;
    while(trav && read_start > trav->size){
        read_start -= trav->size;
        trav = trav->next;
    }

    tempTrav = trav;
    // Calculate the size of to be concatanated string.
    while(tempTrav){
        length += strlen(tempTrav->data);
        tempTrav = tempTrav->next;
    }
    
    // Reached to the end of the file.
    if (*f_pos >= length * sizeof(char) )
        goto out;
        

    // Read whole queue.
    if (count >= length)
        count = length;
    

    concatanatedStr = kmalloc(count * sizeof(char), GFP_KERNEL);
    
    // Cannot allocate memory.
    if (!concatanatedStr){
        retVal = -ENOMEM;
        goto out;
    }   
    tempCount  = count;
    // Copy strings to return value.
    
    while(trav && tempCount > 0){
        for(i = 0 ; ( i + read_start < (strlen(trav->data) * sizeof(char)) ) && ( tempCount > 0 ) ; i++, toRetIndex++,tempCount-- )
            concatanatedStr[toRetIndex] = trav->data[i + read_start];
        trav = trav->next;
        read_start = 0; // Start from the middle only in the first node which is read.
        
    }
        
    if (copy_to_user(buf, concatanatedStr, count * sizeof(char) )) {
        retVal = -EFAULT;
        goto out;
    }

    retVal = count;
    *f_pos += (count * sizeof(char) ) ;
        
    // free concatanatedStr
    kfree(concatanatedStr);
    
    out:
        up(&dev->sem);
        return retVal;
}

ssize_t queue_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos){
    
    struct queue_dev *dev = filp->private_data;
    ssize_t retVal = -ENOMEM;
    struct Node *newnode = NULL;
    struct Node *trav = NULL;

    // Check whether 0th device is read.
    if ( iminor(filp->f_path.dentry->d_inode ) == 0 )
        return -EPERM; 
    
    if (down_interruptible(&dev->sem))
        return -ERESTARTSYS;
    
    //Allocate space for node.
    newnode = kmalloc(sizeof(struct Node) , GFP_KERNEL);
    if (!newnode)
        goto out;
    
    // Allocate space for char array.
    newnode->data = kmalloc( ( sizeof(char) * count )  , GFP_KERNEL);
    
    
    if(!newnode->data){
        kfree(newnode);
        goto out;
    }
    newnode->next = NULL;
    if(copy_from_user(newnode->data, buf , count)){
        retVal = -EFAULT;
        goto out;    
    }
    newnode->data[count-1] = 0;
    newnode->size = ( count * sizeof(char) );
    // Add to queue
    trav = dev->head;
    
    // Head is null. Add as first element.
    if( !dev->head ){
        dev->head = newnode;
    }
        
    else{
        // Move to the end of the list.
        while(trav->next){
            trav = trav->next;
        }
        // Add as last element.
        trav->next = newnode;
    }
    retVal = count;
    dev->size += sizeof(newnode->data);   
    
    out:
        up(&dev->sem);
        return retVal;
}

long queue_ioctl(struct file *flip, unsigned int cmd, unsigned long arg){
    
    int err = 0;
    int retval = 0;
    int i;
    int copyLenght = 0;
    struct queue_dev *dev;
    struct Node *toPop;

    // ENOTY: Inappropriate I/O control operation
    if( _IOC_TYPE(cmd) != QUEUE_IO_MAGIC) return -ENOTTY;
    if(_IOC_NR(cmd) > QUEUE_IOC_MAXNR ) return -ENOTTY;
    
    /*
        Read and write are reversed because, type and access_ok are oriented 
        differently.
    */
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	if (err) return -EFAULT;

    switch(cmd){
        case QUEUE_IOPOP:
            dev = flip->private_data;

            // Request to pop from 0th device.
            if( iminor(flip->f_path.dentry->d_inode ) == 0 ){
                for(i = 1;  i < queue_nr_devs; i++){
                    dev = &queue_devices[i];
                    if(dev->head)
                        break;
                }
            }
            toPop = dev->head;
            if(!toPop){
                retval = -EINVAL;
            }
            else{     
                dev->head = dev->head->next;
                toPop->next = NULL;

                // User may have send the size less than the actual size of the data in the Node.
                copyLenght = ((struct Node __user *)arg)->size > toPop->size  ? toPop->size :((struct Node __user *)arg)->size;
        
                retval = copy_to_user( ((struct Node __user *)arg)->data, toPop->data, copyLenght * sizeof(char) );

                dev->size -=  sizeof(toPop->data); 
                kfree(toPop->data);
                kfree(toPop);
            }
            break;
        default:
            return -ENOTTY;
    }
    return retval;

}



struct file_operations queue_fops = {
    .owner = THIS_MODULE,
    .read =     queue_read,
    .write =    queue_write,
    .unlocked_ioctl =  queue_ioctl,
    .open =     queue_open,
    .release =  queue_release,
};


void queue_cleanup_module(void){
    int i;
    dev_t devno = MKDEV(queue_major, queue_minor);

    if(queue_devices){
        for(i = 0 ;i < queue_nr_devs ;i++){
            queue_trim(queue_devices + i);
            cdev_del(&queue_devices[i].cdev);
        }
        kfree(queue_devices);
    }
    unregister_chrdev_region(devno, queue_nr_devs);
}


int queue_init_module(void){
    int result,i;
    int err;
    dev_t devno;
    struct queue_dev *dev;

    if(queue_major){
        // Get the device number
        devno = MKDEV(queue_major,queue_minor);
        // Get a region from system
        result = register_chrdev_region(devno, queue_nr_devs, "queue");   
    } else{
        // Allocate space and change the devno
        result = alloc_chrdev_region(&devno, queue_minor, queue_nr_devs, "queue");
        queue_major = MAJOR(devno);  // Keep that devno
    }
    if (result < 0){
        printk(KERN_WARNING "queue: cannot get major %d\n", queue_major);        
        return result;
    }

    queue_devices = kmalloc( queue_nr_devs * sizeof( struct queue_dev), GFP_KERNEL);

    if(!queue_devices){
        result = -ENOMEM; // Not enough space.
        goto fail;
    }
    
    memset(queue_devices, 0, queue_nr_devs  * sizeof(struct queue_dev));

    // Initialize devices
    for(i = 0 ; i < queue_nr_devs; i++){
        dev = &queue_devices[i];
        dev->head = NULL;
        dev->size = 0;
        sema_init(&dev->sem,1);
        devno = MKDEV(queue_major, queue_minor + i);
        cdev_init(&dev->cdev, &queue_fops);
        dev->cdev.owner = THIS_MODULE;
        dev->cdev.ops = &queue_fops;
        err = cdev_add(&dev->cdev, devno, 1);
        if(err)
        printk(KERN_NOTICE "Error %d adding queue%d", err, i);
    }

    //Successfull
    return 0;

    //Failed
    fail:
        queue_cleanup_module();
        return result;

}


module_init(queue_init_module);
module_exit(queue_cleanup_module);