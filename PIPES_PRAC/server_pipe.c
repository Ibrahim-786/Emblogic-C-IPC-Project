#include<stdio.h>
#include<unistd.h>

typedef int pid_process;
int main()
{
	int pipe_fd[2];
	int pipe_ret;
	char rfd, wfd;
	pid_process id_pid;	
	pipe_ret = pipe(pipe_fd);   /* 0 on success or -1 on failure*/
	if(pipe_ret < 0){
		perror("pipe");     /* Show an error due to which pipe not created */
		return -1;
	}

	printf("rfd = %d  wfd = %d\n", pipe_fd[0], pipe_fd[1]);
	id_pid = fork();

	switch(id_pid){
	
	case 0:
		printf("we are in the child process with pid = %d\n", getppid());
		sprintf(&rfd, "%d", pipe_fd[0]);
		sprintf(&wfd, "%d", pipe_fd[1]);
		execl();
	}
	return 0;
}
