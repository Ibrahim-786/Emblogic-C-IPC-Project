#include"header.h"
struct my_msg_st
{
        long int my_msg_type;
        char some_text[BUFSIZ]; 
};                                
int main()
{
	int running=1;
	char buffer[BUFSIZ];
	int msgid;
	long int msg_to_receive=0;
	struct my_msg_st some_data;
	msgid=msgget((key_t)1234,0666|IPC_CREAT);
	if(msgid==-1){
	printf("msgget failed=%d\n",errno);
	exit(EXIT_FAILURE);			
	}
	while(running){
	some_data.my_msg_type=1;
	if(msgrcv(msgid, (void*)&some_data,BUFSIZ,msg_to_receive,0)==-1)
	{
		printf("msgsnd failed\n");	
		exit(EXIT_FAILURE);
	}
	printf("you wrote : %s",some_data.some_text);
	if(strncmp(buffer,"end",3)==0)
	{
	running=0;
	}
	}
	if(msgctl(msgid,IPC_RMID,0)==-1)
	{
		printf("failed\n");	
		exit(EXIT_FAILURE);
	}
		exit(EXIT_SUCCESS);
	
}
