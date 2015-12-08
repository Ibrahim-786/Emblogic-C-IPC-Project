/*#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
*/
#include"header.h"
#define FIFO_NAME "fifo_file"
#define FIFO_NAME1 "fifo_file1"
#define BUFFE_SIZE PIPE_BUF
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p();
static int semaphore_v();
static int sem_id;
union semun
{
	int val;
	//struct semid_ds *buff;
	//unsigned short *array;

};

int main()
{
	char buffer[3];
	struct elements *k;
	k = (struct elements*)malloc(sizeof(struct elements)*3);
	req_client(k);
	pro_client(k);
	return 0;
}
req_client(struct elements *k)
{
	int pipe_fd;
	int res, i, j = 0;
	//int pause_time;
	//int byte_sent = 0;

	int open_mode = O_RDONLY;
	if(access(FIFO_NAME, F_OK) == -1)
	{
		res = mkfifo(FIFO_NAME, 0777);
		if(res != 0)
		{
			fprintf(stderr, "Could not createdfifo %s\n", FIFO_NAME);
			exit(EXIT_FAILURE);
		}
	}
	printf("Process %d opening FIFO O_RDONLY\n", getpid());
	for(i = 0; i < 3; i++)
	{
		pipe_fd = open(FIFO_NAME, open_mode);

		//srand((unsigned int )getpid()); 
		sem_id = semget((key_t)1234, 2, 0666|IPC_CREAT);

		union semun sem_un;
		sem_un.val = 1;
		semctl(sem_id, 0, SETVAL, sem_un);
		printf("Process %d result %d\n", getpid(), pipe_fd);
		if(pipe_fd != -1)
		{
			semaphore_p();
			res = read(pipe_fd, (k + i), sizeof(struct elements));
			printf("%d %d  %d\n", res, (k + i)->a, (k + i )->b);
			if(res == -1)
			{
				printf("Error whilie writing 0n fifo\n");
				exit(EXIT_FAILURE);
			}
			semaphore_v();
		}
		printf("%d....................\n", i);
		j++; 
	}

	printf("Process %d finished\n",getpid());

}

pro_client(struct elements *k)
{
        int open_mode = O_WRONLY;
        int res, fifo_id, i;
        union semun sem_un;
        res = mkfifo(FIFO_NAME1, 0777);
        printf("%d!!!..........................................................\n",res);
        if(res != 0)
        {
                exit(EXIT_FAILURE);
        }
        sem_un.val = 1;
        semctl(sem_id , 2, SETVAL , sem_un);
        for(i = 0; i < 3; i++)
        {
                semaphore_p();
                fifo_id = open(FIFO_NAME1, open_mode);
                write(fifo_id, (k + i), sizeof(struct elements));
                printf("%d!!!!%d\n", (k + i)->a, i);
                printf("%d!!!!%d\n", (k + i)->b, i);
                semaphore_v();
        }
        return 0;
}

int semaphore_p()
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;  //index of the semaphore with id sem_id     
	sem_b.sem_op = -1;      //operation to be performed on the semaphore 
	sem_b.sem_flg = SEM_UNDO;
	semop(sem_id, &sem_b, 1);
	return 0;
}

int semaphore_v()
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;  //index of the semaphore with id sem_id     
	sem_b.sem_op = 1;      //operation to be performed on the semaphore 
	sem_b.sem_flg = SEM_UNDO;
	semop(sem_id, &sem_b, 1);
	return 0;
}

