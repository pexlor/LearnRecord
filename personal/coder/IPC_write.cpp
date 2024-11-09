#include <iostream>
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/shm.h>  
#include <string.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>

typedef struct Info
{
	int a = 0;
	int b = 1;
}info;

int main()  
{  
	int i;  
	char buff[100];  
	int shmid;  
	shmid=shmget((key_t)2345, sizeof(info), 0666 | IPC_CREAT);
	if(shmid == -1){
		return -1;
	}
	printf("Key of shared memory is %d\n",shmid);  
	
	pid_t pid = fork();
	if(pid == 0){
		info * shared_memory_child = (info*)shmat(shmid,NULL,0); //process attached to shared memory segment 
		shared_memory_child->a = 1000;
		shared_memory_child->b = 9999;

	}else{
		info * shared_memory = (info*)shmat(shmid,NULL,0); //process attached to shared memory segment 
		wait(NULL);
		printf(" a = %d b = %d\n",shared_memory->a,shared_memory->b);
		shmctl(shmid, IPC_RMID, NULL);
	}
}