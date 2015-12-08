#include"header.h"
/*void ouch(int sig)
{
         //(void)  signal(SIGINT, SIG_DFL);        
}*/

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		perror("execl");
	}
	int rfd, wfd, count,count1, sum, piid;
	struct add ad;
	rfd = atoi(argv[1]);							
	wfd = atoi(argv[2]);
	piid = atoi(argv[3]);
	count = read(rfd, &ad, sizeof(struct add));
	printf("In %s  number of bytes read %d\n", __FILE__, count);
	sum = ad.oprn1 + ad.oprn2;
	count1 = write(wfd, &sum, sizeof(int));
	printf("In %s  number of bytes write %d\n", __FILE__, count1);
	kill(piid, 2);
	return 0;
OUT:
	return -1;
}
