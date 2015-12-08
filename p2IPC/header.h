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
//int invoke_clpross(struct add, int *);
int invoke_clients(int *);
int read_req(int *, struct add *);
int invoke_procl(int *, struct add *, int *);
int ff;
/*void ouch(int sig)
{
	ff = 1;
}*/
