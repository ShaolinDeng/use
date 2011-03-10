#include <stdlib.h>
#include <stdio.h>
int main()
{
	char *p=(char *)malloc(20);
	printf("heap address=%p\n",p);
	pause();
	return 0;
}
