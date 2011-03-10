#include <stdio.h>
#include <unistd.h>

main()
{
    int pid;
    /* fork 子进程 */
    pid=fork();
    switch(pid) {
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            execl("/bin/ls","ls","-l","--color",NULL);
            perror("execl failed");
            exit(1);
        default:
            wait(NULL);
            printf("ls completed\n");
            exit(0);
                            }
}
