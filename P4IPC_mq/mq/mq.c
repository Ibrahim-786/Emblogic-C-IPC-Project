#include"header.h"
#define MAX_TEXT 512
struct my_msg_st
{
	long int my_msg_type;
	char some_text[MAX_TEXT];
};

int main()
{
	int running=1;
	char buffer[BUFSIZ];
	int msgid;
	struct my_msg_st some_data;
	msgid=msgget((key_t)1234,0666|IPC_CREAT);
	if(msgid==-1){
		printf("msgget failed\n");
		exit(EXIT_FAILURE);			
	}
	while(running){
		printf("enter the text:");
		fgets(buffer,BUFSIZ,stdin);
		some_data.my_msg_type=1;
		strcpy(some_data.some_text, buffer);
		if(msgsnd(msgid, (void*)&some_data,MAX_TEXT,0)==-1)
		{
			printf("msgsnd failed\n");	
			exit(EXIT_FAILURE);
		}
		if(strncmp(buffer,"end",3)==0)
		{
			running=0;
		}
	}
	exit(EXIT_SUCCESS);

}
