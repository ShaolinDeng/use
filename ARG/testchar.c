#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int test(char *src)
{
	char dest[1024]={0};
	strcpy(dest,src,strlen(src)-1);
	return 1;
}

int main()
{
	char * a="hello";
	int b=test(a);
	printf("%d",b);
	pause();
	return 0;
}
