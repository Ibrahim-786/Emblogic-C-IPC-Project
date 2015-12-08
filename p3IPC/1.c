#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
int main(int argc, char *argv[])
{
	int res;
	int open_mode = 0;
	res = mkfifo("/tmp/fifo__", 0777);
	if(res == 0)
		printf("FIFO created\n");
	open("/tmp/fifo", O_WRONLY | O_NONBLOCK);
	if(argc < 2)
	{
		fprintf(stdout, "Usage: %s <some combination of\ O_RDONLY O_WRONLY O_NONBLOCK>\n", *argv);
	}
	//argv++;
	if(strncmp(*argv, "O_RDONLY", 8) == 0)
		open_mode |= O_RDONLY;
	if(strncmp(*argv, "O_WRONLY", 8) == 0)
		open_mode |= O_WRONLY;
	if(strncmp(*argv, "O_NONBLOCK", 10) == 0)
		open_mode |= O_NONBLOCK;

	printf("%d\n", open_mode);
	exit(EXIT_SUCCESS);	
	return 0;
}
