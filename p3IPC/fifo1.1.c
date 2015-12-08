#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
//#include<s.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/sem.h>
#include"header2.h"

static int sem_id;
#define FIFO_NAME "fifo_file"
#define FIFO_NAME1 "fifo_cl2"
struct client *req_client();
union semun 
{
	int val;

};
int main()
{
	struct client *k;
	k = req_client();
	//pro_client(k);
	return 0;
}
struct client *req_client()
{
	int res, fifo_id, i;
	int open_mode = O_RDONLY;
	struct client *k;
	k = (struct client*)malloc(sizeof(struct client));
	//if(access(FIFO_NAME, F_OK) == -1)
	//{
		res = mkfifo(FIFO_NAME, 0777);
		printf("%d!!!!\n",res);
		if(res != 0)
		{
			//fprintf(stdout, "Could not created fifo %s\n"FIFO_NAME);
			exit(EXIT_FAILURE);
		}
		sem_id = semget((key_t)111, 2, 0666|O_CREAT);
		union semun sem_un;
		sem_un.val = 1;
		semctl(sem_id, 0, SETVAL, sem_un);
		for(i = 0; i < 3; i++)
		{
			semaphore_p();
			fifo_id = open(FIFO_NAME, open_mode);
			read(fifo_id, (k + i), sizeof(struct client));
			printf("%d.....%d\n", (k + i)->a, i);
			printf("%d.....%d\n", (k + i)->b, i);
			semaphore_v();
		}
	//}
	return k;
}

pro_client(struct client *k)
{
	int open_mode = O_WRONLY;
	int res, fifo_id, i;
	union semun sem_un;
	res = mkfifo(FIFO_NAME1, 0777);
	printf("%d!!!...\n",res);
	if(res != 0)
	{
		exit(EXIT_FAILURE);
	}
	union semun sem_un;
	sem_un.val = 1;
	semctl(sem_id , 1, SETVAL , sem_un);
	for(i = 0; i < 3; i++)
	{
		semaphore_p();
		fifo_id = open(FIFO_NAME, open_mode);
		write(fifo_id, (k + i), sizeof(struct client));
		printf("%d!!!!%d\n", (k + i)->a, i);
		printf("%d!!!!%d\n", (k + i)->b, i);
		semaphore_v();
	}
	return 0;
}
semaphore_p()
{
	struct sembuf sem_buf;
	sem_buf.sem_num = 0;
	sem_buf.sem_op = -1;
	sem_buf.sem_flg = SEM_UNDO;
	semop(sem_id, &sem_buf, 1);
	
}
semaphore_v()
{
	struct sembuf sem_buf;
	sem_buf.sem_num = 0;
	sem_buf.sem_op = 1;
	sem_buf.sem_flg = SEM_UNDO;
	semop(sem_id, &sem_buf, 1);
	
}
