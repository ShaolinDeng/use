#include <stdio.h>
char getChar(int x,int y)
{
	char c;
	unsigned int a=x;
	(a+y>10)?(c=1):(c=2);
	return c;
}
int main()
{
	char c1=getChar(7,4);
	char c2=getChar(7,3);
	char c3=getChar(7,-7);
	char c4=getChar(7,-8);

	printf("c1=%d\n",c1);

	printf("c1=%d\n",c2);
	printf("c1=%d\n",c3);
	printf("c1=%d\n",c4);

	unsigned int b=-7;
	printf("7 + -7 %d",7+b);

	printf(" 0x %X",b&&0xFFFF);
	return 0;
}
