#include"header.h"
#define SIZE 6
int ff = 2, jj = 2, mm = 3;
int arr1[6],pp[3], count2, sum2;
void ansa(int sig)
{
	ff = 1;
}
void ansb(int sig)
{
	jj = 1;
}
void ansc(int sig)
{
	mm = 1;
	
}
int main()
{
	pid_t pid;
	int arr[SIZE] ;
	int count, sum[3], count1, count2;
	struct add ad[3];
	invoke_clients(arr);
	read_req(arr, ad);
	invoke_pro(arr1, ad);
	(void)signal(2,ansa);
	(void)signal(3,ansb);
	(void)signal(4,ansc);
	while(1)
	{
		if(ff == 1)
		{
			count = read(arr1[0], (sum + 0), sizeof(int));
			printf("The number of character read after signal:  %d\n", count);
			printf("Sum after signal is: %d\n",sum[0]);
			ff = 0;
		}
		if(jj == 1)
		{
			count1 = read(arr1[2], (sum + 1), sizeof(int));
			printf("The number of character read after signal:  %d\n", count1);
			printf("Sub after signal is: %d\n",sum[1]);
			jj = 0;
		}
		if(mm == 1)
		{
			count2 = read(arr1[4], (sum + 2), sizeof(int));
			printf("The number of character read after signal:  %d\n", count2);
			printf("Mul after signal is: %d\n",sum[2]);
			mm = 0;
		}
		if(mm == 0 &&  jj == 0 && ff == 0 )
			break;
	
	}
	write_client(arr, sum, pp);

	return 0;
}

int invoke_clients(int *arr)
{
	int numcl, i, ret, j;
	char **p, rfd[4], wfd[4];
	p = malloc(sizeof(char) * 30);
	*(p + 0) = "./add_req";
        *(p + 1) = "./sub_req";
        *(p + 2) = "./mul_req";
	i = 0;
	for(j = 0; j < 3; j++)
	{
		printf("%s\n",*(p + j));
		if(pipe((arr + i)) < 0)
		{
			perror("pipe");
			goto OUT;
		}
		printf("%d\n",*(arr + i ));
		printf("%d\n",*(arr + i + 1));
		ret = fork();
		switch(ret)
		{
		case -1:
			perror("fork");
			goto OUT;
		
		case 0:
			sprintf(rfd, "%d", *(arr + i));
			sprintf(wfd, "%d", *(arr + i + 1));
			execl(*(p + j), *(p + j), rfd, wfd, NULL);
			printf("%s : %s\n", __FILE__, __func__);
		default:
			pp[j] = ret;
			printf("pid !!!!!!!!!!!!!! %d\n",pp[j]);
		}
		i += 2;

	}
	return 0;
OUT:
	 return -1;
}

read_req(int *arr, struct add *ad)
{
	int i, j, count;
	j = 0;
	
	for(i = 0; i < 3; i++)
	{
		count = read(arr[j], (ad + i), sizeof(struct add));
		printf("NUMBER of character read:- %d\n",count);
		printf("%c = %d - %d\n", (ad + i)->oper, (ad + i)->oprn1, (ad + i)->oprn2);
		j += 2;
	}	
	return 0;
}

int invoke_pro(int *arr1, struct add *ad)
{
	
	int numcl, i, ret, j, pid;
	char **p, rfd[4], wfd[4], piid[10];
	
	p = malloc(sizeof(char) * 30);
	*(p + 0) = "./add_pro";
        *(p + 1) = "./sub_pro";
        *(p + 2) = "./mul_pro";
	i = 0;
	pid = getpid();
	sprintf(piid, "%d", pid);
	printf("pid :- %d\n",pid);
	for(j = 0; j < 3; j++)
	{
		printf("%s\n",*(p + j));
		if(pipe((arr1 + i)) < 0)
		{
			perror("pipe");
			goto OUT;
		}
		printf("%d\n",*(arr1 + i ));
		printf("%d\n",*(arr1 + i + 1));
		ret = fork();
		switch(ret)
		{
		case -1:
			perror("fork");
			goto OUT;
		case 0:
			sprintf(rfd, "%d", *(arr1 + i));
			sprintf(wfd, "%d", *(arr1 + i + 1));
			write(*(arr1 + i + 1), (ad + j), sizeof(struct add));
			execl(*(p + j), *(p + j), rfd, wfd, piid, NULL);
			printf("%s :::::::::::: %s\n", __FILE__, __func__);
			
		}
		i += 2;

	}
	return 0;
OUT:
	return -1;
}

write_client(int *arr, int *sum, int *pp)
{
	int i, j;
	j = 0;
	for(i = 0; i < 3; i++)
	{
		printf("Ans%d !!!!!!!!!!!!!! %d\n",i , *(sum + i));
		kill(pp[i],2);
		write(*(arr + j +1), (sum + i), sizeof(int));
		j += 2;
	}
	return 0;
}
