#include<stdio.h>
#include<stdlib.h>

int main()
{
	int n = 5;
	pid_t pid;
	pid = fork();
	switch(pid)
	{
	case -1:
		perror("fork");
	case 0:
		n = 6;
		printf("in child %p\n",&n);
		break;
	default:
		printf("in parent %p\n",&n);
		
	
	}

	return 0;
}
