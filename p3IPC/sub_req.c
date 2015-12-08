#include"header.h"
//int sum;
void ouch(int sig)
{
	//(void)	signal(SIGINT, SIG_DFL);	
}
int main(int argc, char *argv[])
{
	int sub,ret;
	int rfd,  wfd, count, ans;
	if(argc != 3)
	{
		perror("execl");
		goto OUT;
	}
	printf("%s\n",__FILE__);
	struct add ad2;
	ad2.oper = '-';
	ad2.oprn1 = 33;
	ad2.oprn2 = 43;
	rfd = atoi(argv[1]);
	wfd = atoi(argv[2]);
	count = write(wfd, &ad2, sizeof(struct add));
	printf("Number of character write in %s is %d\n", __FILE__, count);
	(void)signal(SIGINT,ouch);
       /*while(1)
       {
       		if(read(rfd, &ans, sizeof(int)))
		break;                   
       }*/
	//printf("%d1o------------\n",ans);
        printf("Before pause\n");
        pause();
        read(rfd, &sub, sizeof(int));
        printf("%d              :-\n",rfd);
        printf("%s                                Number read is :- %d\n", __FILE__, sub);

	return 0;
OUT:
	 return 1;
}
