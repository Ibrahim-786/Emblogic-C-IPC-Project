#include<stdio.h>
#include<stdlib.h>

int main()
{
	int arr[5], arr1[5], arr2[10], i, j;
	for(i = 0; i < 5; i++)
	{
		scanf("%d",(arr+i));
	}
	for(j = 0; j < 5; j++)
	{
		//gets();
		scanf("%d",(arr1+j));
	}
	j = 0;
	for(i = 0; i < 10 ; i++)
	{
		if(i < 5)
			arr2[i] = arr[i];
		else
		{
			arr2[i] = arr1[j];
			j++;
		}	
	}
	for(i = 0; i < 10; i++)
	{
		printf("%d\n",*(arr2+i));
	}
	return 0;
}
