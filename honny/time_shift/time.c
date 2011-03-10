#include <stdio.h>
#include <time.h>
int main()
{
    int i;
    int begin,end;
    int a=578;
    int b=1024;
    
    unsigned int sum=0;
    begin=time(NULL);
    for(i==0;i<2000000000;++i)
    {
        #ifdef NOTHING
        #elif MULTI
            sum+=a*b;
            sum-=a*b;
        #else
            sum+=(a<<10);
            sum-=(a<<10);
        #endif
    }
    end=time(NULL);
    printf("sum=%d,time:%ds\n",sum,end-begin);
    return 0;
}


