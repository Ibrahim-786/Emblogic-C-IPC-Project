#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include"sm_header.h"

int main()
{
	int shm_id;
	struct sh_use *shr_data;
	void *shr_ptr = 0;
	shm_id = shmget(1803, sizeof(struct sh_use), 0666|IPC_CREAT);
	if(shm_id == -1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	shr_ptr = shmat(shm_id, 0, 0);
	shr_data = (struct sh_use *)shr_ptr;
	while(1)
	{
		shr_data->entered_data = 1;
		printf("Enter the text:- ");
		fgets(shr_data->some_text, TEXT_SZ, stdin);
	}
	return 0;
}
