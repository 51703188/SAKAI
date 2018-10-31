#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 256


int main(int argc, char* argv[])
{
	int *shm0, *shm1, shmid0, shmid1, k;
	
	key_t key;

	// create key
	if((key=ftok(".",'a'))==-1) {
		perror("key created\n");
		return 1;
	}

	if((shmid0 = shmget(key, SIZE, IPC_CREAT | 0666)) == -1) {
		perror("SM0 created\n");
		return 2;
	}

	if((shmid1 = shmget(key, SIZE, IPC_CREAT | 0666)) == -1) {
		perror("SM1 created\n");
		return 2;
	}
	// assisn SM to process
	shm0 = (int*) shmat(shmid0,0,0);
	shm1 = (int*) shmat(shmid1,0,0);
	switch(fork()){
		case -1: perror("fork error\n");
				return 4;
		case 0:
				shm0[0] = argc - 1;
				printf("size of array = %d\n", shm0[0]);
				int i;
				for(i = 1; i < shm0[0]; i++) {
					shm0[i] = argv[i]; 
				}
				sleep(3);
				shmdt((void*) shm0);
				shmdt((void*) shm1);
				shmctl(shmid0, IPC_RMID, (struct shmid_ds*)0);
				return 0;
		default:
				sleep(1);
				int j, sum =0 ;
				for(j = 0; j < shm0[0]; j++) {
					shm1[i] = shm0[i+1];
				}
				
				for(j = 0; j < shm0[0]; j++) {
					sum += shm0[i+1];
				}

				shmdt((void*) shm0);
				shmdt((void*) shm1);
				sleep(5);
				return 0;
	}
	return 0;
}
