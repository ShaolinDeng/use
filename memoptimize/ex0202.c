#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	char *p;
	p=malloc(20);
	printf("0X%x\n",*(p-4));
	strcpy(p,"hello world");
	printf("%s\n",p);
	free(p);
	return 0;
}
