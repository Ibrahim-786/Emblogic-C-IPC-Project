#include"header.h"

int main()
{
	int arr[2], arr1[2], adc_count, adp_count, f;
	int sum, a, m;
	char k;
	//pipe(arr);
	if(pipe(arr) < 0)
	{
		perror("pipe");
		goto OUT;
	}
	if(pipe(arr1) < 0)
	{
		perror("pipe");
		goto OUT;
	}
	pid_t pid, pid1;
	struct add ad;
	printf("%s\n",__FILE__);
	printf("rfd :-%d\nwfd :-%d\n", arr[0], arr[1]);
	pid = fork();
	switch(pid)
	{
	case -1:
		perror("fork");
		goto OUT;
	case 0:
		printf("In the chid 1 having %d pid.\n",pid);
		printf("In the chid 1 having %d ppid.\n",getppid());
		printf("%s\n",__FILE__);
		invoke_cl(arr);
	default:
		printf("In the parent.\n");
		adc_count = read(arr[0], &ad, sizeof(struct add));
		printf("Successfull in reading  %d character after write by client.\n",adc_count);
		
	/*	invoke_clpross(ad,arr1);
		adp_count = read(arr1[0], &sum, 1);
		printf("The number of element read in %s is :-%d\n",__FILE__,adp_count);
		printf("The number of element read in %s is :-%d\n",__FILE__, sum);*/
	}
	
	sleep(2);
	pid1 = fork();
	switch(pid1)
	{
	case -1:
		perror("fork");
		goto OUT;
	case 0:
		printf("In the 2 chid having %d pid.\n",pid1);
		invoke_clpross(ad,arr1);
	default:
		wait(&m);
		adp_count = read(arr1[0], &sum, 1);
		printf("The number of element read in %s is :-%d\n",__FILE__,adp_count);
		printf("The number of element read in %s is :-%d\n",__FILE__, sum);
		f = write(arr[1], &sum, 1);
		printf("The number of element write  in %s is :-%d  %d\n",__FILE__, f, sum);
		sprintf(&k,"%d", getpid());
		system("kill -n getpid()");
	}

	return 0;
OUT:
	return -1;
}

int invoke_cl(int *arr)
{
	char rfd[4], wfd[4];
	sprintf(rfd, "%d", arr[0]);
	sprintf(wfd, "%d", arr[1]);
	
	execl("./add_cl", "add_cl", rfd, wfd, NULL);
	execlp("ls", "ls","-l", NULL);
	printf("%s  after execl\n",__FILE__);
	return 0;
}

int invoke_clpross(struct add ad, int *arr1)
{
	int  count;
	char rfd[4], wfd[4];
	printf("%s rfd :-%d\nwfd :-%d\n", __FILE__,arr1[0], arr1[1]);
	count = write(arr1[1], &ad, sizeof(struct add));
	printf("Successfull in write 1 %d character after write.\n", count);
	sprintf(rfd, "%d", arr1[0]);
	sprintf(wfd, "%d", arr1[1]);
	execl("./add_pro", "add_pro", rfd, wfd, NULL);
	printf("Successfull in write %d character after write.\n", count);
	return 0;
OUT:
	return -1;
}
