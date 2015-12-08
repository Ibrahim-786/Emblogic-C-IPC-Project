#include"header.h"
//int sum;
void ouch(int sig)
{
	//(void)	signal(SIGINT, SIG_DFL);	
}
int main(int argc, char *argv[])
{
	int mul,ret, ans;
	int rfd,  wfd, count;
	if(argc != 3)
	{
		perror("execl");
		goto OUT;
	}
	printf("%s\n",__FILE__);
	struct add ad1;
	ad1.oper = '*';
	ad1.oprn1 = 17;
	ad1.oprn2 = 27;
	rfd = atoi(argv[1]);
	wfd = atoi(argv[2]);
	count = write(wfd, &ad1, sizeof(struct add));
	printf("The number of character write in %s is :- %d\n",__FILE__, count);
	(void)signal(SIGINT,ouch);
        printf("Before pause\n");
        pause();
        read(rfd, &ans, sizeof(int));
        printf("%d              :-\n",rfd);
        printf("%s                                Number read is :- %d\n", __FILE__, ans);

	return 0;
OUT:
	return 1;
}
