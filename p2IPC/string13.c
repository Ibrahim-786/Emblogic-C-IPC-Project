#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char* conCat(char *, char *);
int main()
{
	char *dest,*dest1, *src;
	int len, i = 0;
	dest = (char*) malloc (sizeof(char)*50);
	if(!dest)
	{
		printf("Malloc Failed\n");
		exit(EXIT_FAILURE);
	}
	src = (char*) malloc (sizeof(char));
	if(!src)
	{
		printf("Malloc Failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Enter Destination string: \n");
	gets(dest);	
	while(1)
	{
		printf("%d: %c\n",i,*(dest+i));
		i++;
		if(*(dest+i) == '\0')
			break;
	}
	if(strlen(dest) > 31)
		dest = realloc(dest, 55);
/*	printf("Enter Source string : \n");
	gets(src);	
	dest = conCat(dest,src);
	printf("Concat: %s", dest);
	printf("\nLength of concat string is %d\n", strlen(dest));
*/
}

char * conCat(char * dest, char *src)
{
	int destLen, srcLen, i = 0;
	destLen = strlen(dest);
	printf("Length of Destination String is %d\n", destLen);
	srcLen = strlen(src);
	printf("Length of Source String is %d\n", srcLen);
	printf("\n");
	realloc(dest, sizeof(char)* 5);
	while(*(src+i) != '\0')
	{
		*(dest+(destLen+i)) = *(src+i);
		i++;
	}
	return dest;
}
