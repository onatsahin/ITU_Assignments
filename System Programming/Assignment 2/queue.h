#define QUEUE_MAJOR 0
#define QUEUE_NR_DEVS 4


struct queue_dev{
    struct Node* head;
    struct semaphore sem;
    struct cdev cdev;
    int size; // Keeps the size of the character arrays of the whole queue.
             // Instead of keeping the size of actual size of a Node. (next pointer + char data)
};

