#include <unistd.h>
#include <stdio.h>
int main()
{
	int ret;
	ret=truncate("./pirate.txt",45);
	if(ret==-1)
	{
		perror("turncate");
		return -1;
	}
	return 0;
}
