/*#include"header.h"
int sum;
void ouch(int sig)
{
	(void)	signal(SIGINT, SIG_DFL);	
}
int main(int argc, char *argv[])
{
	int sum,ret;
	int rfd,  wfd, count;
	struct add ad3;
	if(argc != 3)
	{
		perror("execl");
		goto OUT;
	}
	printf("%s\n",__FILE__);
	ad3.oper = '+';
	ad3.oprn1 = 13;
	ad3.oprn2 = 23;
	rfd = atoi(argv[1]);
	wfd = atoi(argv[2]);
	count = write(wfd, &ad3, sizeof(struct add));
	printf("The number of character write %s is: %d\n",__FILE__, count);
//	(void)signal(SIGINT,ouch);
//	while(1)
//	{
		
		//read(rfd, &sum, 1);
		//printf("Number read is :- %d\n",sum);
//	}
//	sleep(1);
	//read(rfd, &sum, 1);
	//printf("Number read is :- %d\n",sum);
	return 0;
OUT:
	return 1;
}*/

#include"header.h"

int main(int argc, char * argv[])
{
	int sum, rfd, wfd, count;
	struct add ad;
	if(argc != 3)
	{
		perror("execl");
		goto OUT;
	}
	printf("%s\n",__FILE__);
	ad.oper = '+';
	ad.oprn1 = 13;
	ad.oprn2 = 23;
	rfd = atoi(argv[1]);
	wfd = atoi(argv[2]);
	printf("%d,%d\n",rfd, wfd);
	count = write(wfd, &ad, sizeof(struct add));
	printf("%s number of character write is :- %d\n",__FILE__, count);

	return 0;
OUT:
	return -1;
}
