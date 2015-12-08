#include<stdio.h>
#include<pthread.h>

char text[BUFSIZ];
pthread_t thrd;
int main()
{
	
	pthread_create(&thrd, NULL, func_thr, );	

	return 0;
}


