#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
struct my_mess
{
	long int type;
	char text[512];
};
int main()
{
	int msg_id, run;
	run = 1;
	char  buff[BUFSIZ];
	struct my_mess con_dat;
	msg_id = msgget(333, 0666|IPC_CREAT);
	if(msg_id == -1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	while(run)
	{
		printf("Enter the text:-");
		fgets(buff, BUFSIZ, stdin);
		con_dat.type = 33;
		strcpy(con_dat.text, buff);
		if(msgsnd(msg_id, &con_dat, 512, 0)== -1)
		{
			perror("msgsend");
			exit(EXIT_FAILURE);
		}
		if(strcmp(buff, "end"));
		{
			run = 0;
		}
	}	
	return 0;
}
