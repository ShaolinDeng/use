#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

failure( char* s)
{
    perror(s);
    exit(1);
}
printpos( char* string, int fildes)
{
    long pos;
    if ((pos=lseek(fildes,0L,1))<0L)
        failure("lseek failed");
    printf("%s: %ld \n",string,pos);
}
main()
{
    int fd; /*  文件描述符 */
    int pid;/*  进程标识符 */
    char buf[10]; /*    数据缓冲区 */
    /*  打开文件    */
    if ((fd=open("data",O_RDONLY))<0)
        failure("open failed");
    read(fd,buf,10); /* advance file pointer */
    printpos("Before fork",fd);
    /* fork 新进程 */
    if ((pid=fork())<0)
        failure("fork failed");
    else if (!pid)
        /*  子进程 */
       printpos("Child before read",fd);
     read(fd,buf,10);
     printpos("child after read",fd);
 else {
    /*  父进程 */
    /*  等待子进程运行结束 */
    wait(NULL);
    printpos("parent after wait",fd);
    }
}
