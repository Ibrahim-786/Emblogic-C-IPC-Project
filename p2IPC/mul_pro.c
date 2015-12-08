#include"header.h"

int main(int argc, char *argv[])
{
	int rfd, wfd, count, count1, mul, piid;
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
	printf("In %s  number  of bytes read %d\n", __FILE__, count);
	mul = ad.oprn1 * ad.oprn2;
        count1 = write(wfd, &mul, sizeof(int));
	printf("%d--------------\n",mul);
        printf("In %s  number of bytes write %d\n", __FILE__, count1);
	kill(piid,4);
	return 0;
OUT:
	return -1;
}
