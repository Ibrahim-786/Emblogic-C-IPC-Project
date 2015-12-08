#include<stdio.h>
int call(int , int);
int main()
{
	int a = 5,b = 6, k;
	k = call(a,b);
	printf("in main = %d",k);
	return 0;
}

int call(int a, int b)
{
	int sum;
	sum = a + b;
	a = b;
}
