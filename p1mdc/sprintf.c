#include<stdio.h>

int main()
{
	char *c;
	int b,a = 34;
	b = sprintf(&c,"%d",a);
	printf("ch = %c\n b = %d\n",c,b);
	return 0;
}
