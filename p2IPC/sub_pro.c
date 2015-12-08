#include"header.h"

int main(int argc, char *argv[])
{
	int rfd, wfd, count, count1, sub, piid;
	struct add ad;
	if(argc != 4)
	{
		perror("execl");
		goto OUT;
	}
	rfd = atoi(argv[1]);
	wfd = atoi(argv[2]);
	piid = atoi(argv[3]);
	count = read(rfd, &ad, sizeof(struct add));
	printf("In %s  number of bytes read %d\n", __FILE__, count);
	sub = ad.oprn2 - ad.oprn1;
	count1 = write(wfd, &sub, sizeof(int));
	printf("In %s  number of bytes read %d\n", __FILE__, count1);
	kill(piid, 3);
	return 0;
OUT:
	return -1;
}
