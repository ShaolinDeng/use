#include <stdio.h>
#include <string.h>
static void my_print(char *);
static void my_print2(char*);

main()
{
    char my_string[]="hello world!\n";
    my_print(my_string);
    my_print2(my_string);
}
void my_print(char *string)
{
    printf("The string is %s\n",string);
}
void my_print2(char * string)
{
    char * string2;
    int size,i;

    size=strlen(string);
    string2=(char*)malloc(size+1);

    for(i=0;i<size;i++)
        string2[size-i]=string;
        string2[size+1]='!';

        printf("the string printed backward is %s \n",string2);
}
