#include <stdio.h>

// check char size and __attribute__
struct s{
char s1;
int  s2;
long s3;
} __attribute__((aligned(4))) sS;

struct p{
char s1;
int  s2;
long s3;
} __attribute__((packed)) sP;

void main(void)
{
// check char size and __attribute__
 char i;
 long j;
 int  k;
 
 printf("char=%d,long=%d,int=%d \n",sizeof(i),sizeof(j),sizeof(k));
 printf("char=%d,long=%d,int=%d,s struct=%d\n",sizeof(sS.s1),sizeof(sS.s2),sizeof(sS.s3),sizeof(sS));
 printf("char=%d,long=%d,int=%d,s struct=%d\n",sizeof(sP.s1),sizeof(sP.s2),sizeof(sP.s3),sizeof(sP));
}
