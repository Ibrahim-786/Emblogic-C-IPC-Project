#include"header.h"
int sum;
void ouch(int sig)
{
	(void)	signal(SIGINT, SIG_DFL);	
}
int main(int argc, char *argv[])
{
	int sum, ret;
	int rfd,  wfd, count;
	if(argc != 3)
	{
		perror("execl");
		goto OUT;
	}
	printf("%s\n",__FILE__);
	struct add ad;
	ad.oper = '+';
	ad.oprn1 = 13;
	ad.oprn2 = 23;
	rfd = atoi(argv[1]);
	wfd = atoi(argv[2]);
	count = write(wfd, &ad, sizeof(struct add));
	printf("The number of character write in the adder client:- %d\n",count);
	(void)signal(SIGINT,ouch);
	while(1)
	{
		
		//read(rfd, &sum, 1);
		//printf("Number read is :- %d\n",sum);
	}
	sleep(1);
	//read(rfd, &sum, 1);
	//printf("Number read is :- %d\n",sum);
	return 0;
OUT:
	return 1;
}
