#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include"sh_header.h"

int main()
{
	int shm_id, shm_id1;
	struct sh_use *shr_data;
	void *shr_ptr = 0;
	void *shr_ptr1 = 0;
	int *res1;
	//res1 = (int *)malloc(sizeof(int));
	//*res1 = 0;
	shm_id = shmget(1803, sizeof(struct sh_use), 0666|IPC_CREAT);
	if(shm_id == -1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	shr_ptr = shmat(shm_id, 0, 0);
	shr_data = (struct sh_use *)shr_ptr;
	shr_data->oprn = '+';
	shr_data->opr1 = 10;
	shr_data->opr2 = 11;
	shr_data->type = 1;
	shm_id1 = shmget(1804, sizeof(int), 0666|IPC_CREAT);
	if(shm_id1 == -1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	shr_ptr1 = shmat(shm_id1, 0, 0);
	res1 = (int *)shr_ptr1;
	
	while(!*res1)
	{
		printf("%d\n",*res1);
		sleep(1);	
	}
	printf("%d___________________\n",*res1);
	if(shmdt(shr_ptr1) == -1)
        {
                fprintf(stderr, "shmdat failed\n");
        }

	return 0;
}
