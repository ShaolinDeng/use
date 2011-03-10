#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int>ivec;
	int ival;
	cout<<"Enter number:(ctrl+d)" <<endl;
	while(cin>>ival)
		ivec.push_back(ival);

	int *parr=new int[ivec.size()];
	size_t ix=0;
	for(vector<int>::iterator iter=ivec.begin();
					iter!=ivec.end();++iter,++ix)
	{
		cout<<"the vector of"<<ix<<" is "<<*iter<<endl;
		parr[ix]=*iter;
		cout<<"the number of the array "<<ix<<"is "<<parr[ix]<<endl;
	}
	delete[] parr;
	return 0;
}
