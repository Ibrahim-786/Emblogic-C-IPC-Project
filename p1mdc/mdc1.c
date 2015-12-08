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
	printf("fcd in the main = %d\n",fdc);
	decompress(fdc, ma);
	close(fdc);
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
		case 3:
			{
				fd = compress3(fd,ma);
			}
		case 4:
		{
			fdc = compress(fd,  ma);
		}
		
	}
	return fdc;	
}
int compress3(int fdc, char *ma)         //3 bit compression code..
{ 
	int i, i_no, fdd, j;
	unsigned char ch, m, p, k, n, r, t, v, x, byte, a, n1, t1;
	lseek(fdc, 0, SEEK_SET);
	fdd = open("Decompress1", O_RDWR|O_CREAT, 0777);
	i = 0;
	j = 7;
	byte = 0;
	while(read(fdc,&ch,1)&& ch != NULL)
	{
		byte = byte ^ byte;
		
		while(*(ma+i) != '\0')
		{
			if(ch == *(ma + i))
			{
				break;
			}
			i++;
		}
	
		m = i;
		m = m << 5;
		byte = byte | m;	
		read(fdc, &ch, 1);
		if(ch == NULL)
		{
			m = m^ m;
			m = j;
			m <<= 5;
			m >>= 3;
			byte = byte | m;
			write(fdd, &byte, 1);
		}
		i = 0;
		while(*(ma + i) != '\0')
		{
			if(ch == *(ma + i))
			{
				break;
			}
			i++;
		}
		k = i;
		k = k << 5;
		k = k >> 3;
		byte =  byte | k;
		read(fdc, &ch, 1);
		if(ch == NULL)
		{
			k = k^ k;
			k = j;
			k <<= 5;
			k >>= 6;
			byte = byte | k;
			write(fdd, &byte, 1);
			break;
		}
		i = 0;
		while(*(ma + i) != '\0')
		{
			if(ch == *(ma + i))
			{
				break;
			}
			i++;
		}
		n = i;
		n = n << 5;
		n = n >> 6;
		byte = byte | n;
		write(fdd, &byte, 1);
		printf("%d\n", byte);
		byte = byte ^ byte;
		n1 = i;
		n1 <<= 7;
		byte = byte | n1;
		read(fdc, &ch, 1);
		if(ch == NULL)
		{
			write(fdd, &byte, 1);
		}
		if(ch == NULL)
		{
			write(fdd, &byte, 1);
			break;
		}
		i = 0;
		while(*(ma + i) != '\0')
		{
			if(ch == *(ma + i))
			{
				break;
			}
			i++;
		}
		p = i;
		p <<= 5;
		p >>= 1;
		byte = byte | p;
		read(fdc, &ch, 1);
		if(ch == NULL)
		{
			write(fdd, &byte, 1);
		}
		i = 0;
		while(*(ma + i) != '\0')
		{
			if(ch == *(ma + i))
			{
				break;
			}
			i++;
		}
		r = i;
		r <<= 5;
		r >>= 4;
		byte = byte | r;
		read(fdc, &ch, 1);
		if(ch == NULL)
		{
			write(fdd, &byte, 1);
		}
		i = 0;
		while(*(ma + i) != '\0')
		{
			if(ch == *(ma + i))
			{
				break;
			}
			i++;
		}	
		t = i;
		t <<= 7;
		t >>= 7;
		byte = byte | t;
		write(fdd, &byte, 1);
		printf("%d\n", byte);
	
		byte = byte ^ byte;	
		t1 = i;
		t1 <<= 6;
		byte = byte | t1;
		read(fdc, &ch, 1);
		if(ch == NULL)
		{
			write(fdd, &byte, 1);
			break;
		}
		i = 0;
		while(*(ma + i) != '\0')
		{
			if(ch == *(ma + i))
			{
				break;
			}
			i++;
		}
		v = i;
		v <<= 5;
		v >>= 2;
		byte = byte | v;
		read(fdc, &ch, 1);
		if(ch == NULL)
		{
			write(fdd, &byte, 1);
		}
		i = 0;	
		while(*(ma + i) != '\0')
		{
			if(ch == *(ma + i))
			{
				break;
			}
			i++;
		}
		x = i;
		x <<= 5;
		x >>= 5;
		byte = byte | x;
		write(fdd, &byte,1);
		printf("%d\n", byte);
		byte = byte ^ byte;
	
	}
	 	
	return 0;
}

int compress(int fd, char *ma)  //Four bit compression
{
	int  i, cfd;
	unsigned char ch, a, byt;
	i = byt = 0;
	cfd = open("codekey",O_RDWR|O_CREAT,777);
	printf("cfd in the function = %d\n",cfd);
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
		a = i;
		//sprintf(&a,"%d",i);
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
		a = i;
		//sprintf(&a,"%d",i);
		a = a<<4;
		a = a>>4;
		byt = byt | a;
		printf("yeh hai saab 2 time= %d\n",byt);
		printf("%c\n",byt);
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


int decompress( int fdc, char *ma)
{
	int i, i_no, fdd, r, z, k, l;
	unsigned char ch, *j,  m;
	lseek(fdc, 0, SEEK_SET);
	fdd = open("Decompress",O_RDWR|O_CREAT,0777);
	i = z = r = 0;
	j = (int *)malloc(40);
	while(read(fdc,&ch,1)&& ch != NULL)
	{
		i = 0;
		l = 0;
		k = 0;
		k = ch>>4;
		while(*(ma + i) != '\0')
		{
			if(k == i)
			{
				*(j + z) = *(ma + i);
				z++;
			write(fdd,(ma + i),1);
				break;
			}
			i++;
		}
	
		
		ch = ch <<4;
		ch = ch >> 4;
		l = ch;
		
		i = 0;
		while(*(ma + i) != '\0')
		{
			
			if(l == i)
			{
				i_no = i; 
 			*(j + z) = *(ma + i);
 			z++;
			write(fdd,(ma + i),1);
				break;
			}
			i++;
		}
	}
	*(j + z + 1) = '\0';
	write(fdd,(j + z +1), 1);
	printf("z = %d\n",z);
	for(i = 0; i < z; i++)
	{
		printf("h = %c\n",*(j + i));
	}
	return 0;
}
