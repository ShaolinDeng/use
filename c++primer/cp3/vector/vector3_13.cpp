#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<int> vec;
	int temp;
    cout<<"input the numbers:"<<endl;
	while(cin>>temp)
			vec.push_back(temp);
    if(vec.size()==0)
    {
        cout<<"No Element"<<endl;
        return 1;}
    cout<<"sum of each pair in the vector:"<<endl;


    for(vector<int>::size_type index=0;index<vec.size()-1;index+=2)
    {	cout<<vec[index]+vec[index+1]<<"\t";
        if((index+1)%6==0)
            cout<<endl;
    }
    if(vec.size()%2!=0)
        {
        cout<<endl
            <<"the last element is single:"
            <<"and its value is:"
            <<vec[vec.size()-1]<<endl;
        }    
	return 0;
}
