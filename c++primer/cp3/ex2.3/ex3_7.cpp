#include <iostream>
#include <string>
using namespace std;

int main()
{
string s1,s2;
cout <<"please input two strings:"<<endl;
cin>>s1>>s2;

if(s1==s2)
	cout<<"they are equal."<<endl;
else if(s1>s2)
	cout<<"\""<<s1<<"\"is bigger than"
		<< "\""<<s2<<"\""<<endl;
else 
	cout<<"\""<<s2<<"\"is bigger than"
		<<"\""<<s1<<"\""<<endl;
	return 0;
}
