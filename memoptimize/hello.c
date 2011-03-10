#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main()
{
	char *p=(char*)malloc(20);
	strcpy(p,"123");
	pid_t pid=getpid();
	printf("pid:%d\n",pid);
	pause();
	return 0;
}
