#include"header.h"

int main(int argc, char *argv[])
{
	int rfd, wfd, count, sum, k;
	char a;
	struct add ad;
	if(argc != 3)
	{
		perror("execl");
		goto OUT;
	}
	rfd = atoi(argv[1]);
	wfd = atoi(argv[2]);
	printf("%s rfd :-%d\nwfd :-%d\n", __FILE__,rfd, wfd);
	count = read(rfd, &ad, sizeof(struct add));
	printf("%d bytes successfully read in %s\n", count, __FILE__);
	printf("%s %d\n", __FILE__, ad.oprn1);
	a = ad.oper;
	sum = ad.oprn1 + ad.oprn2;
	printf("The ascii value of the operator is:- %d\n",ad.oper);
	printf("In %s sum = %d\n", __FILE__, sum);	
	k = write(wfd, &sum, 1);
	printf("The sum is write with bytes :- %d\n",k);
	//sleep(4);
	return 0;
OUT:
	return -1;
}
