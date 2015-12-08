#include<stdio.h>
#include<stdlib.h>
#include"sh_header.h"
int main(int argc, char *argv[])
{
	struct acc_dat dat;
	int rfd, wfd, res, siz, pid;
	rfd = atoi(argv[1]);
	wfd = atoi(argv[2]);
	pid = atoi(argv[3]);
	printf("%s rfd = %d wfd = %d\n",__FILE__, rfd, wfd);
	read(rfd, &dat, sizeof(struct acc_dat));
	printf("%s __ %d ___ %d ___ %c\n", __FILE__, dat.opr1, dat.opr2, dat.oprn);
	res = dat.opr2 - dat.opr1;
	siz = write(wfd, &res, sizeof(int));
	printf("%s  %d res = %d\n", __FILE__, siz, res);
	kill(pid, 3);
	return 0;
}
