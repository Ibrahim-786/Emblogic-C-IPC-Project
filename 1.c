#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include"sm_header.h"

int main()
{
	int shm_id, running;
	running = 1;
	struct sh_use *shared_data;
	void *shr_ptr = 0;
	shm_id = shmget(1803, sizeof(struct sh_use), 0666|IPC_CREAT);
	if(shm_id == -1)
	{
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}
	shr_ptr = shmat(shm_id, 0, 0);
	if(shr_ptr == -1)
	{
		fprintf(stderr, "shr_ptr failed\n");
		exit(EXIT_FAILURE);
	}
	shared_data = (struct sh_use *)shr_ptr;  // initially shr_ptr is void . Now first type caste the pointer into the struct and assign to the structure
	shared_data->entered_data = 0; //Assign 0 to first element of the struct the data which is about to share b/w the processes
	while(running)
	{
		if(shared_data->entered_data)
		{
		
			printf("The data enter in the shared resource is :- %s\n",shared_data->some_text);
			shared_data->entered_data = 0;
			if(strncmp(shared_data->some_text, "end", 3) == 0)
			{
				running = 0;
			}
		}	
	}
	if(shmdt(shr_ptr) == -1)
	{
		fprintf(stderr, "shmdat failed\n");
	}
	return 0;
}

