#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include"header.h"

struct my_mess *req_client();
int pro_client(struct my_mess *);
int read_pro();

int msg_id, msg_id1, msg_id3, msg_id2;
int main()
{
	struct my_mess *con_dat;
	con_dat = req_client();
	pro_client(con_dat);
	read_pro();
	/*if(msgctl(msgget, IPC_RMID,0) == -1)
	  {
	  printf("failure");
	 exit(EXIT_FAILURE);
	  }*/

	return 0;
}

struct my_mess *req_client()
{
	struct my_mess *con_dat;
	con_dat = (struct my_mess *)malloc(sizeof(struct my_mess)*3);
	msg_id = msgget(999, 0666|IPC_CREAT);
	if(msg_id == -1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	
	if(msgrcv(msg_id , (con_dat + 0), sizeof(struct my_mess),0, 0)== -1)
	{
		perror("msgecv");
		exit(EXIT_FAILURE);
	}
	printf("%s the operator is : %c\n", __FILE__, (con_dat + 0)->oper);
	printf("%s the operator is : %d\n", __FILE__, (con_dat + 0)->opr1);
	printf("%s the operator is : %d\n", __FILE__, (con_dat + 0)->opr2);
	return con_dat;
}

int pro_client(struct my_mess *con_dat)
{
	msg_id1 = msgget(994, 0666|IPC_CREAT);
	if(msg_id1 == -1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	if(msgsnd(msg_id1, (con_dat + 0), sizeof(struct my_mess), 0))
	{
		perror("msgsnd");
		exit(EXIT_FAILURE);
	}
	return 0;
}

int read_pro()
{
	struct my_mess1 dat;

	printf("%s  %d\n",__func__, dat.res);
	msg_id2 = msgget(995, 0666|IPC_CREAT);
        if(msg_id2 == -1)
        {
                perror("msgget");
                exit(EXIT_FAILURE);
        }

	if(msgrcv(msg_id2, &dat, sizeof(struct my_mess1), 0, 0)== -1)
	{
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}
	printf("%s  %d\n",__func__, dat.res);
	msg_id3 = msgget(996, 0666|IPC_CREAT);
        if(msg_id3 == -1)
        {
                perror("msgget");
                exit(EXIT_FAILURE);
        }

	if(msgsnd(msg_id3, &dat, sizeof(struct my_mess1), 0))
	{
		perror("msgsnd");
		exit(EXIT_FAILURE);
	}
	return 0;
}
