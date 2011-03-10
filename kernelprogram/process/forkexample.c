#include <stdio.h>
#include <unistd.h>
#include <time.h>
main()
{
time_t timep;
time(&timep);
pid_t pid;
printf("Now only one process\n");
printf("Calling fork… \n");
pid=fork();
printf("the function fork() beginning, now the  time is :%s",ctime(&timep));
if (!pid)
printf("I’m the child\n");
else if (pid>0)
printf("I’m the parent, child has pid %d\n",pid);
else
printf("Fork fail!\n");
}
