//
//  Name: Onat Şahin
//  ID: 150150129
//
#define _GNU_SOURCE
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define KEYSEM_SYNC 20
#define KEYSEM_MUTEX 21
#define KEYSEM_FILLER_SYNC 24
#define KEYSHM_WATER 22
#define KEYSHM_FILLER 23

void sem_signal(int semid, int val){ //Semaphore signal and wait functions
    struct sembuf semaphore;
    semaphore.sem_num = 0;
    semaphore.sem_op = val;
    semaphore.sem_flg = 1;
    semop(semid, &semaphore, 1);
}

void sem_wait(int semid, int val){
    struct sembuf semaphore;
    semaphore.sem_num = 0;
    semaphore.sem_op = (-1*val);
    semaphore.sem_flg = 1;
    semop(semid, &semaphore, 1);
}

void mysignal(int signum){} //Signal functions

void mysigset(int num){
    struct sigaction mysigaction;
    mysigaction.sa_handler = (void *)mysignal;
    mysigaction.sa_flags = 0;
    sigaction(num, &mysigaction, NULL);
}

int main(int argc, char *argv[]){
    setvbuf(stdout,(char*)NULL, _IONBF,0);
    mysigset(12);

    int shmid_water=0, shmid_filler=0, semid_sync=0, semid_mutex=0, semid_filler_sync=0;
    int *shmwater_ptr = NULL, *shmfiller_ptr = NULL; //Shared memory ptr
    int *sync_ptr = NULL, *mutex_ptr = NULL; //Semaphore ptr
    int filler = 0;
    int *empCoffee, *consumer;
    int employeeCount=0, maxWater=0, empOrder=0;
    int i,j,f,k;
    char temp;
    int coffeeTypeSize = 10, tempInt;

    empCoffee = malloc(sizeof(int) * 10); //Create a dynamic array for coffee types with the size of ten elements

    FILE *inputFile = fopen(argv[1], "r"); //Open the file
    if(!inputFile){
        printf("File could not be opened\n");
        return 0;
    }

    fscanf(inputFile, "%d", &maxWater); //Scan the first line and get the water capacity of the machine

    temp = getc(inputFile); //Handling the end of line
    if(temp == '\r')
        getc(inputFile);

    do{                                         // Reading the list of coffee types and putting them to the empCoffee dynamic array
        if(employeeCount == coffeeTypeSize){    // If the array is full, double its size
            coffeeTypeSize *= 2;
            empCoffee = realloc(empCoffee, sizeof(int) * coffeeTypeSize);
        }
        fscanf(inputFile, "%d", &tempInt); // Read the coffee type
        empCoffee[employeeCount] = tempInt; // Put the value in empCoffee
        employeeCount++;                    // Increment employee number
        temp = getc(inputFile);             // Read the character after the coffee type to temp
    }while(temp == ' ');                    // If temp is a space character, this means there are more coffee types, therefore the loop must continue

    fclose(inputFile);      // Close the file

    printf("Employee count = %d\n", employeeCount);

    consumer = malloc(sizeof(int) * employeeCount); // Allocate space for the consumer dynamic array which will hold the process ids of the employees

    printf("SIMULATION BEGINS\n");
    for(i=0; i<employeeCount+1; i++){ //Creating child processes.
        f = fork();
        if(f==-1){
            printf("FORK ERROR\n");
            exit(1);
        }
        if(f==0){
            if(i==0) //The first child created is the employee that fills the machine. Id of this process is sent to every process
                filler = f;
            empOrder = i-1;
            break;
        }
        if(i==0)
            filler = f;

        else
            consumer[i-1] = f; //Process id's of the employees that consume coffee are stored
    }

    if(f != 0){ //Parent Process
        semid_sync = semget(KEYSEM_SYNC, 1, 0700|IPC_CREAT); //Semaphore and shared memory initializations
        semctl(semid_sync, 0, SETVAL, 0);
        semid_filler_sync = semget(KEYSEM_FILLER_SYNC, 1, 0700|IPC_CREAT);
        semctl(semid_filler_sync, 0, SETVAL, 0);
        semid_mutex = semget(KEYSEM_MUTEX, 1, 0700|IPC_CREAT);
        semctl(semid_mutex, 0, SETVAL, 1);

        shmid_water = shmget(KEYSHM_WATER, sizeof(int) , 0700|IPC_CREAT);
        shmwater_ptr = (int*)shmat(shmid_water, 0, 0);
        shmid_filler = shmget(KEYSHM_FILLER, sizeof(int) , 0700|IPC_CREAT);
        shmfiller_ptr = (int*)shmat(shmid_filler, 0, 0);

        *shmwater_ptr = maxWater; //Fill the machine with water
        *shmfiller_ptr = 1; //This shared memory controls the while loop in the water filler process
        sleep(2);

        kill(filler,12); //Give signal to water filler to make it start working

        for(j=0; j<employeeCount; j++)
            kill(consumer[j],12); //Start the other processes

        sem_wait(semid_sync, employeeCount); //Wait until all employees take their coffee

        *shmfiller_ptr = 0; //Make this value 0 so that filler process won't continue the loop.

        printf("Current water level %d cups\n", *shmwater_ptr);
        kill(filler,12); //Give signal to filler process for it to finish

        sem_wait(semid_filler_sync,1); // Wait for the filler process to finish

        shmdt(shmwater_ptr); //Give back the resources
        shmdt(shmfiller_ptr);
        semctl(semid_sync, 0, IPC_RMID, 0);
        semctl(semid_filler_sync, 0, IPC_RMID, 0);
        semctl(semid_mutex, 0, IPC_RMID, 0);
        shmctl(shmid_water, IPC_RMID, 0);
        shmctl(shmid_filler, IPC_RMID, 0);

        free(empCoffee); //Giving the memory back to the system
        free(consumer);
        printf("SIMULATION ENDS\n");
    }

    else if(i==0){  //Filler Process
        semid_filler_sync = semget(KEYSEM_FILLER_SYNC, 1, 0700|IPC_CREAT); //Semaphore and shared memory initalizations

        shmid_water = shmget(KEYSHM_WATER, sizeof(int) , 0700|IPC_CREAT);
        shmwater_ptr = (int*)shmat(shmid_water, 0, 0);
        shmid_filler = shmget(KEYSHM_FILLER, sizeof(int) , 0700|IPC_CREAT);
        shmfiller_ptr = (int*)shmat(shmid_filler, 0, 0);

        pause(); // Wait for the parent process' signal to begin

        while(*shmfiller_ptr == 1){
            pause(); // Wait for a request to fill the machine
            printf("Employee %d wakes up and fills the coffee machine\n", getpid());
            *shmwater_ptr = maxWater;  // Fill the machine
            printf("Current water level %d cups\n", *shmwater_ptr);
            sem_signal(semid_filler_sync,1);    //Send signal to the employee that made the request
        }
        shmdt(shmfiller_ptr);
        shmdt(shmwater_ptr);
        free(empCoffee); //Giving the memory back to the system
        free(consumer);
    }

    else{   //Employee Process

        pause(); // Wait for the parent process' signal to begin

        semid_sync = semget(KEYSEM_SYNC, 1, 0700|IPC_CREAT);    //Semaphore and shared memory initalizations
        semid_mutex = semget(KEYSEM_MUTEX, 1, 0700|IPC_CREAT);
        semid_filler_sync = semget(KEYSEM_FILLER_SYNC, 1, 0700|IPC_CREAT);

        shmid_water = shmget(KEYSHM_WATER, sizeof(int) , 0700|IPC_CREAT);
        shmwater_ptr = (int*)shmat(shmid_water, 0, 0);

        sem_wait(semid_mutex,1); //CRITICAL SECTION BEGIN

        printf("Current water level %d cups\n", *shmwater_ptr); //
        printf("Employee %d wants coffee Type %d\n", getpid(), empCoffee[empOrder]);
        if(*shmwater_ptr - empCoffee[empOrder] < 1){ // Check if the water is enough
            printf("Employee %d WAITS\n", getpid());
            kill(filler,12);    //If water is not enough, send signal to the filler process and wait for it to fill the water
            sem_wait(semid_filler_sync,1);
        }

        *shmwater_ptr -= empCoffee[empOrder]; // Use the water and take the coffee
        printf("Employee %d SERVED\n", getpid());
        shmdt(shmwater_ptr);

        sem_signal(semid_mutex ,1); //CRITICAL SECTION END

        sleep(2);

        free(empCoffee); //Giving the memory back to the system
        free(consumer);

        sem_signal(semid_sync,1); //Send signal to parent process
        sleep(2);
    }

    return 0;
}
