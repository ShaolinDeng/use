#include <stdio.h>
#include <unistd.h>

main()
{
    printf("Executing ls\n");
    execl("/bin/ls","ls","-l",NULL);

    /*  如果 execl 返回，说明调用失败 */
    perror("execl failed to run ls");
    exit(1);
}
