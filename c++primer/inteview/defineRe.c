#include <stdio.h>
#define STR(s) #s
#define CONS(a,b) (int)(a##e##b)

#define WORD_LO(xxx)  ((byte)((word)(xxx)&255))

#define WORD_HI(xxx)  ((byte)((word)(xxx)>>8))
int main()
{
	printf(STR(vck));
	printf("\n");
	printf("%d\n",CONS(2,3));



	return 0;
}
