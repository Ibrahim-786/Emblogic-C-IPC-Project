#include<stdio.h>
#include<fcntl.h>
int main()
{
	int ret, fd;
	ret = fork();
	fd = open("vishal",O_RDONLY|O_CREAT);
	printf("%d\n",fd);

	return 0;
}
