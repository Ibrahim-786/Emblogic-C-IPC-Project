#include"header.h"
int main(int argc, char *argv[])
{
	int fd, ndc, flag, i, ndc_temp, cl, fdc;
	char ch, *ma;
	if(argc != 2)
	{
		printf("Insufficient argument \n");
		goto out;
	}
	fd = opfd(argv[1]);
	ma = masterar(fd);	
	
	printf("File %s open successfulelly at fd :- \n",argv[1]);	
	
	printf("The string compress is :-%s\n",ma);
	
/*	while( (ndc_temp) > 1)
	{
		ndc_temp = ndc_temp / 2;
		k++;
	}*/
	ndc = strlen(ma);
	cl = bitlen(ndc);
	
	fdc = compression(fd, ma, cl);
//	decompress(fdc, ma);
	
	close(fd);
	exit(EXIT_SUCCESS);
	return 0;
	out:
	exit(EXIT_FAILURE);
}

int opfd(char *a)
{
	int fd;
	fd = open(a,O_RDONLY);
	if(fd < 0)
	{
		printf("In the fd loop %d\n",fd);
		exit(EXIT_FAILURE);
	}
	printf("The value read from the textfile %d\n",fd);
	return fd;
}
char *masterar(int fd)
{
	
	char *ma, ch;
	int flag, i, ndc;
	ndc = 0;
	ma = (char*)malloc(sizeof(char));
	while(read(fd,&ch,1) && ch != 10)
	{
		flag = 1;	
		if(ndc > 0)		
		{
			ma = (char *)realloc(ma, ndc + 1);	
			if(ma == NULL)

			{
				perror("realloc");
				return NULL;
			}	
		
			for(i = 0; i < ndc; i++)
			{
				if(ch == *(ma + i))
				{
					flag = 0;
					break;
				}
			}
		}
		if(flag )
		{
			*(ma + ndc) = ch;
			ndc++;
			printf("%d\n",ch);
		}
		
	}
		printf("The number of data bit data compress:- %d\n",ndc);
		return ma;
} 
int compression(int fd, char *ma, int ndc)
{
	int fdc;
	switch(ndc)
	{
		case 4:
		{
			printf("Before compress\n");
			fdc = compress(fd,  ma);
			printf("After compress\n");
		}
	}
	return fdc;	
}

int compress(int fd, char *ma)
{
	int  i, byt, cfd;
	char ch, a;
	i = byt = 0;
	cfd = open("codekey",O_RDWR|O_CREAT,777);
	lseek(fd, 0,SEEK_SET); 
	while(read(fd,&ch,1)&& ch != 10)
	{
		byt = byt ^ byt;
		i = 0;
		while(*(ma+i) != '\0')
		{
			if(ch == *(ma + i))
			{
				break;
			}
			i++;
		}
		//a = i;
		sprintf(&a,"%d",i);
		a = a<<4;
		byt = byt | a;
		i = 0;
		read(fd,&ch,1);
		while(*(ma+i) != '\0')
		{
			if(ch == *(ma + i))
			{
				break;
			}
			i++;
		}
		//a = i;
		sprintf(&a,"%d",i);
		a = a<<4;
		a = a>>4;
		byt = byt | a;
		write(cfd,&byt,1);
	}
	byt = '\0';
	write(cfd,&byt,1);

	return cfd;
	
}	

int bitlen(int ndc)
{
	int k;
	if(ndc > 127)
		k = 8;
	else if(ndc > 63)
		k = 7;
	else if(ndc > 31)
		k = 6;
	else if(ndc > 15)
		k = 5;
	else if(ndc > 7)
		k = 4;
	else if(ndc > 3)
		k = 3;
	else if(ndc > 1)
		k = 2;
	else if(ndc > 0)
		k = 1;
	printf("Compressed data is %d bit data\n",k );
	return k;
}

/*decompress(int fdc, char *ma)
{
	int i, i_no;
	char ch;
	lseek(fdc, 0, SEEK_END);
	
	i = 0;
	while(read(fdc,&ch,1)&&ch != 10)
	{
		ch = ch>>4;
		while(ma != 0)
		{
			if(ch == i)
			{
				i_no = i; 
				break;
			}
		}
	}
	return 0;
}*/
