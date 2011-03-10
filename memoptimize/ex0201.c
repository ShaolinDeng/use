#include <stdio.h>
#include <stdlib.h>
int n=10;
const int n1=20;
int m;

int main()
{
	int s=7;
	static int s1=30;
	char * p=(char *)malloc(20);
	printf("global var address=%p\n",&n);
	printf("const global var address=%p\n",&n1);
	printf("global un var address=%p\n",&m);
	printf("stack var address=%p\n",&s);
    printf("static var address=%p\n",&s1);
	printf("heap  var address=%p\n",p);
	pause();
}


