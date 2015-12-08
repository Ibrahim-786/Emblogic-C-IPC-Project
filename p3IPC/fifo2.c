#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#include"header2.h"
#define FIFO_NAME "fifo_file"
#define BUFFE_SIZE PIPE_BUF
#define TEN_MEG (1024 * 1024 * 10)

int main()
{
	int pipe_fd;
	int res;
	int open_mode = O_WRONLY;
	int byte_sent = 0;
	struct client k;
	k.a = 5;
	k.b = 10;
	//char buffer[30] = "vishal chopra1";
	//len = strlrn(buffer);
//	if(access(FIFO_NAME, F_OK) == -1)
//	{
		pipe_fd = open(FIFO_NAME, open_mode);
	//	if(pipe_fd != -1)
	//	{
			/*while(byte_sent < TEN_MEG)
			  {
			  res = write(pipe_fd, buffer, BUFFE_SIZE);
			  if(res == -1)
			  {
			  printf("Error whilie writing 0n fifo\n");
			  exit(EXIT_FAILURE);
			//printf("k ==== %d\n",k);
			}
			byte_sent += res;

			}*/
			res = write(pipe_fd, &k, sizeof(struct client));
			if(res == -1)
			{
				printf("Error whilie writing 0n fifo\n");
				exit(EXIT_FAILURE);
				//printf("k ==== %d\n",k);
			}
			printf("%d %d  %d\n", getpid(), k.a, k.b);
		//}
//	}
	printf("Process %d opening FIFO O_WRONLY\n", getpid());
	printf("Process %d result %d\n", getpid(), pipe_fd);

	printf("Process %d finished\n",getpid());
		//	close(pipe_fd);
	return 0;
}

