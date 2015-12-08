#include<stdio.h>

int main()
{
	int i = 33,j;
	char *ma;
	sprintf(ma,"%d",i);
	printf("%d\n",sizeof(ma));	
	printf("%c",ma);
	j=atoi(ma);
	printf("%d\n",j);
	printf("%d\n",sizeof(j));	
	return 0;
}
