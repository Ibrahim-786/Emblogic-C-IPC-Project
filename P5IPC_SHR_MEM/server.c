#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include"sh_header.h"
struct acc_dat *req_client();
int *pro_client(struct acc_dat *); 
int read_write_operation(int *);
int shm_id, running;
int flag, flag1, flag2;
void *shr_ptr = 0;

void sig_hand(int sig)
{
	flag = 1;
}
void sig_hand1(int sig)
{
	flag1 = 1;
}
void sig_hand2(int sig)
{
	flag2 = 1;
}

int main()
{
	running = 1;
	struct acc_dat *req_dat;
	int res, *arr;
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
	req_dat = req_client();
	arr = pro_client(req_dat);
	read_write_operation(arr);
	return 0;
}

struct acc_dat *req_client()
{
	int j[3];
	struct sh_use *shared_data;
	struct acc_dat *req_dat;
	req_dat = (struct acc_dat *)malloc(sizeof(struct acc_dat)*3);
	shared_data = (struct sh_use *)shr_ptr;  // initially shr_ptr is void . Now first type caste the pointer into the struct and assign to the structure
	shared_data->type = 0; //Assign 0 to first element of the struct the data which is about to share b/w the processes
	while(running)
	{
		if(shared_data->type == 1)
		{
			(req_dat + 0)->oprn = shared_data->oprn;	
			(req_dat + 0)->opr1 = shared_data->opr1;	
			(req_dat + 0)->opr2 = shared_data->opr2;	
			printf("%d__________  %d  _____________%c\n",(req_dat + 0)->opr1, (req_dat + 0)->opr2, (req_dat + 0)->oprn);
			j[0] = 1;
			shared_data->type = 5;
		}	
		if(shared_data->type == 2)
		{
			(req_dat + 1)->oprn = shared_data->oprn;	
			(req_dat + 1)->opr1 = shared_data->opr1;	
			(req_dat + 1)->opr2 = shared_data->opr2;	
			printf("%d__________  %d  _____________%c\n",(req_dat + 1)->opr1, (req_dat + 1)->opr2, (req_dat + 1)->oprn);
			j[1] = 1;
			shared_data->type = 6;
		}	
		if(shared_data->type == 3)
		{
			(req_dat + 2)->oprn = shared_data->oprn;	
			(req_dat + 2)->opr1 = shared_data->opr1;	
			(req_dat + 2)->opr2 = shared_data->opr2;	
			printf("%d__________  %d  _____________%c\n",(req_dat + 2)->opr1, (req_dat + 2)->opr2, (req_dat + 2)->oprn);
			j[2] = 1;
			shared_data->type = 7;
		}
		if(j[0] == 1 && j[1] == 1 && j[2] == 1)
			running = 0;	
	}
	if(shmdt(shr_ptr) == -1)
	{
		fprintf(stderr, "shmdat failed\n");
	}
	return req_dat;
}

int *pro_client(struct acc_dat *req_client)
{
	printf("%d = \n",req_client->opr1);
	int *arr, siz;
	char **p;
	arr = (int *)malloc(sizeof(int)*6);
	pid_t pid;
	char rfd[4], wfd[4], pid_p[4];
	*(p + 0) = "./add_pro";
	*(p + 1) = "./sub_pro";
	*(p + 2) = "./mul_pro";
	int j = 0;
	printf("rfd  %d  wfd %d\n ", arr[0], arr[1]);
	for(i = 0; i < 3; i++)
	{
		if(pipe(arr + j))
		{
			perror("pipe");
		}
		pid = fork();
		switch(pid)
		{
			case -1:
				perror("fork");
				exit(EXIT_FAILURE);
			case 0:
				siz = write(arr[1], req_client, sizeof(struct acc_dat));
				printf("In %s number of bytes write in the pipe is %d\n", __func__, siz);
				sprintf(rfd, "%d", arr[i]);
				sprintf(wfd, "%d", arr[i + 1]);
				sprintf(pid_p, "%d", getppid());
				execl(*(p + i), *(p + i), rfd, wfd, pid_p, NULL);
		}
		j += 2;;
	}
	return arr;
}

int read_write_operation(int *arr)
{
	int *res1;
	res1 = (int *)malloc(sizeof(int)*3);
	int *res;
	int shm_id1;
	void *shr_id1 = 0;
	void *shr_ptr1 = 0;
	printf("%s!!!!!!!!  %d !!!!! %d\n", __FILE__, arr[0], arr[1]);
	signal(2, sig_hand);
	signal(3, sig_hand1);
	signal(4, sig_hand2);
	while(1)
	{
		if(flag == 1)
		{
		printf("%d  +++++++++++++\n",arr[0]);
		read(arr[0], (res1 + 0) , sizeof(int));
		printf("%d                       ____________\n",res1);

		shm_id1 = shmget(1804, sizeof(int), 0666|IPC_CREAT);
		if(shm_id1 == -1)
		{
			fprintf(stderr, "shmget failed\n");
			exit(EXIT_FAILURE);
		}
		shr_ptr1 = shmat(shm_id1, 0, 0);
		if(shr_ptr1 == -1)
		{
			fprintf(stderr, "shr_ptr failed\n");
			exit(EXIT_FAILURE);
		}
		res = (int *)shr_ptr;
		*res = res1;
		}
	}
	return 0;
}

