#include <stdio.h>
int main()
{
 	const int b=10;
	const  int * const a=&b;
	int const * const c=&b;
	printf("a:%d\n",*a);
	printf("c:%d\n",*c);
}
