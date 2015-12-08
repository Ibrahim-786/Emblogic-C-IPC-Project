#include<stdio.h>

struct add_opr
{
	int var1, var2;
	char oprnd;
};
int main(int argc, char *argv[])
{
	int rfd_pipe, wfd_pipe;
	if(argc < 2)
	{
		printf("insufficent arguments\n");
		return -1;
	}
	rfd_pipe = atoi(argv + 1);
	wfd_pipe = atoi(argv + 2);
	return 0;
}
