#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
struct my_mess
{
	long int type;
	char text[512];
};
int main()
{
	int msg_id, run;
	run = 1;
	char buf[BUFSIZ];
	struct my_mess con_dat;
	msg_id = msgget(333, 0666|IPC_CREAT);
	if(msg_id == -1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	while(run)
	{
		con_dat.type = 33;
		if(msgrcv(msg_id, &con_dat, 512, 0)== -1)
		{
			perror("msgecv");
			exit(EXIT_FAILURE);
		}
		printf("you wrote :- %s\n",con_dat.text);
		/*if(strncmp(buff, "end", 3) == 0);
		{
			run = 0;
		}*/
		
	}
	if(msgctl(msgget, IPC_RMID,0) == -1)
	{
		printf("failure");
		exit(EXIT_FAILURE);
	}	
	return 0;
}
