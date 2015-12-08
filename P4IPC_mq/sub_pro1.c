#include"header.h"
int msg_id, msg_id1;
int main()
{
	struct my_mess dat;
	struct my_mess1 dat1;
	int result;
	msg_id = msgget(994, 0666|IPC_CREAT);
	if(msg_id == -1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	if(msgrcv(msg_id, &dat, sizeof(struct my_mess), 2, 0)== -1)
	{
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}
	printf("%d  %s\n",dat.opr1, __FILE__);
	printf("%d  %s\n",dat.opr2, __FILE__);
	printf("%c  %s\n",dat.oper, __FILE__);
	result = dat.opr1 - dat.opr2;
	printf("result =   %d  in %s\n", result, __FILE__);
	dat1.type = 57;
	dat1.res = result;
	printf("%d  _____%s\n",dat1.res, __FILE__);
	//result = dat.opr2 - dat.opr1;
	msg_id1 = msgget(995, 0666|IPC_CREAT);
        if(msg_id1 == -1)
        {
                perror("msgget");
                exit(EXIT_FAILURE);
        }

	if(msgsnd(msg_id1, &dat1, sizeof(struct my_mess1), 0))
	{
		perror("msgsnd");
		exit(EXIT_FAILURE);
	}
	return 0;
}
