#include <stdio.h>
#include <string.h>
#include <math.h>
bool mysushu(int m){
	int temp=sqrt(m);
	for (int i=2;i<=temp;i++)
	{
		if(! m%temp)
		{
			return true;
		}
		else
			break;
	}
	return false;
}

int main()
{
	int n=1,m=2;int count=0;
	int i=1;
	printf("please input a range:a,b\n");
	scanf("%d,%d",&m,&n);
	for(i=m;i<=n;i++)
	{
		if (mysushu(i))
		{
			printf("%d is a sushu\n",i);
			count++;
		}
		else
			break;
	}
	printf("%d-%d have %d suhu",m,n,count);
return 0;
}
