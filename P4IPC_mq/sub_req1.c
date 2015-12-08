#include"header.h"
int main(int argc, char *argv[])
{
	int sum, msg_id, msg_id3;
	int rfd,  wfd, count;
	printf("%s\n",__FILE__);
	//	struct client ad;
	struct my_mess op;
	struct my_mess1 dat;
	op.oper = '-';
	op.opr1 = 24;
	op.opr2 = 35;
	msg_id = msgget(999, 0666|IPC_CREAT);
	if(msg_id == -1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	op.type = 2;
	if(msgsnd(msg_id, &op, sizeof(struct my_mess), 0) == -1)
	{
		perror("msgsnd");	
		exit(EXIT_FAILURE);
	}
	msg_id3 = msgget(996, 0666|IPC_CREAT);
        if(msg_id3 == -1)
        {
                perror("msgget");
                exit(EXIT_FAILURE);
        }

	if(msgrcv(msg_id3, &dat, sizeof(struct my_mess1), 57, 0)== -1)
	{
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}
	printf("%d::::::::::::::::11\n",dat.res);

	return 0;
OUT:
	return 1;
}
