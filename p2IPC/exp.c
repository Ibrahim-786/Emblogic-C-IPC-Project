#include<stdio.h>
#include<stdlib.h>

int main()
{
	int *p, i;
	p = malloc(sizeof(int)*2);
	for(i = 0; i < 3; i++)
	{
		scanf("%d",(p + i));
	}
	for(i = 0; i < 3; i++)
	{
		printf("%d\n",*(p + i));
	}
		printf("%d\n",(*p));
	return 0;
}
