#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
int bitlen(int);

int opfd();
char *masterar(int);
int compression(int, char *, int);
int compress(int, char *);
int decompress(int , char *);
