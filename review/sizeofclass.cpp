#include <iostream>
using namespace std;

class Class1
{
	char contents[];
};
class Class2
{
};
int main()
{
	cout<<sizeof(Class1)<<endl;
	cout<<sizeof(Class2)<<endl;
	return 0;
}

