#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdio.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>

struct client
{
	char opt;
	int opr1, opr2;

};
