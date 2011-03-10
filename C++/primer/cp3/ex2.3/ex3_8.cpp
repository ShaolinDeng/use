#include <iostream>
#include <string>
using namespace std;
int main()
{
	string result_str,str;

	cout<<"Enter strings(Ctrl+Z to end):"<<endl;
	while(cin>>str)
			result_str=result_str+str;

	cout<<"String equal to the concatenation of these strings is:"
			<<endl<<result_str<<endl;
	return 0;
}
