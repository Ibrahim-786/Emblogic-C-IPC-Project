#include<stdio.h>
#include<stdlib.h>

int main()
{
	int i;
	char **p;
	p = (char**)malloc(sizeof(char*)* 100);
	
	*(p + 0) = "vishal1234";
	*(p + 1) = "munish1123";
	*(p + 2) = "shallu2123";
	for(i = 0; i< 30; i++)
	{
		printf("ch = %p\n", (*(p  + 0) + i));
	}
	/*printf("1\n");
	for(i = 0; i< 10; i++)
	{
		printf("ch = %p\n", (*(p + 1) + i));
	}
	printf("1\n");
	for(i = 0; i< 10; i++)
	{
		printf("ch = %p\n", (*(p + 2) + i));
	}
	printf("1\n");*/
	printf("%d\n", p);
	printf("%d\n", (*p));
	return 0;
}
