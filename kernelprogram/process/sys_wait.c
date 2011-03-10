#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

main()
{
    int pid,status,exit_status;

    if ((pid=fork()) <0)
    {
        perror("fork failed");
        exit(1);
    }

    if (!pid)
    {    /*  子进程 */
        sleep(4);
    exit(5); /* 使用非零值退出，以便主进程观察 */
    }

/*  父进程 */
if (wait(&status) <0) {
    perror("wait failed");
    exit(1);
}
/*  将 status 与 0xFF(255) 与来测试低 8 位 */
if (status & 0xFF)
    printf("Somne low-roderbits not zero\n");
    else {
        exit_status=status >> 8;
        exit_status &=0xFF;
        printf("Exit status from %d was %d\n", pid,exit_status);
    }
exit(0);
}
