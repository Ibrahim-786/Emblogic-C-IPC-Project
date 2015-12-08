#include"header.h"
int main(int argc, char *argv[])
{
	int  i, a;
	char *ma;
	if(argc != 2)
	{
		perror("Error");
		return -1;
	}
	int fd;
	fd = open(argv[1],O_RDONLY,0777);
	printf("T = %d",fd);
	printf("before call\n");
	ma = masterar(fd);
	printf("after call\n");
	a = strlen(ma);
	for(i = 0; i < a; i++)
	{
		printf("the value at %d --- %c\n", i, *(ma + i));
	}
	

	return 0;
}


char *masterar(int mfd)
{
	int  k, ndc, i, a, flag;
	char ch, *ma;
	ma = (char*)malloc(1);
	k = 0;
	ndc = 0;
	
	while(read(mfd,&ch,1))
	{
		flag = 1;
		if(k >0)
		{
			ma = (char *)realloc(ma, k+1);
			if(ma == NULL)
			{
				perror("realloc");
				return -1;
			}
		}
		for(i = 0; i <= ndc; i++)
		{
			if(*(ma + i) == ch)		
			{
				flag = 0;
				break;
			}
		}
		if(flag == 1)
		{
			*(ma + ndc) = ch;
			ndc++;
			k++;
			
		}
		
	}
	*(ma + ndc + 1) = '\0';
	return ma;
}
