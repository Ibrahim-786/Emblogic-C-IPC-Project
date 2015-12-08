#include"header.h"
int main(int argc, char *argv[])
{
	int fd, ndc;
	char *ma, ch;
	fd = open(argv[1],O_RDONLY);
	printf("fd is at %d",fd);
	 if(fd < 0)
        {
                printf("In the fd loop %d",fd);
                goto out;
        }
	ndc = 0;
        printf("File %s open successfulelly at fd :- \n",argv[1]);
        printf("The value read from the textfile %d\n",fd);

        ma = (char*)malloc(sizeof(char));
        while(read(fd,&ch,1) && ch !=0)
        {
           //     printf("ch = %c",ch);

             //   printf("ndc %d",ndc);
                if(ndc > 0)
                {
                        ma = (char *)realloc(ma, ndc);
                        if(ma == NULL)
                        {
                                perror("realloc");
                                goto out;
			             goto out;
                        }
                }
                *(ma + ndc) = ch;
                ndc++;

        }
        printf("The string is %s\n",ma);
        close(fd);
        exit(EXIT_SUCCESS);
        return 0;
        out:
        exit(EXIT_FAILURE);
}
