#include <signal.h>

int interrupt()
{
    printf("Interrupt called\n");
    sleep(3);
    printf("Interrupt Func Ended.\n");
}

int catchquit()
{
    printf("quit called\n");
    sleep(3);
    printf("quit ended.\n");
}

main()
{
    signal(SIGINT,interrupt);
    signal(SIGQUIT,catchquit);
    printf("Interrupt set for SIGINT\n");
    sleep(10);
    printf("Program NORMAL ended.\n");
    return;
}
