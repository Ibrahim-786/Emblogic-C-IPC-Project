#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<unistd.h>

struct add
{
        char oper;
        int oprn1, oprn2;
};
int invoke_clpross(struct add, int *);
int invoke_cl(int *);
