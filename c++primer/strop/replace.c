#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

char* replace(const char*str,const char* sub1,const char* sub2,char*output)
{
	char* pOutput=NULL;
	const char* pStr=NULL;
	int lenSub1=strlen(sub1);
	int lenSub2=strlen(sub2);

	pOutput=output;
	pStr=str;
	while(*pStr!=0)
	{
		pStr=strstr(pStr,sub1);
		if(NULL!=pStr)
		{
			memcpy(pOutput,str,pStr-str);
			pOutput+=pStr-str;
			mencpy(pOutput,sub2,lenSub2);
			pOutput+=lenSub2;
			pStr+=lenSub1;
			str=pStr;
		}
		else
		{
			break;
		}
	}
	*pOutput='\0';
	if(*str!='\0')
	{
		strcpy(pOutput,str);
	}
	return output;
}

int main()
{
	char str[50]="";
	char sub1[10]="";
	char sub2[10]="";
	char output[100]="";

	cout<<"str:";
	cin>>str;
	cout<<"sub1";
	cin>>sub1;
	cout<<"sub2:";
	cin>>sub2;

	cout<<replace(str,sub1,sub2,output)<<endl;
	return 0;
}
