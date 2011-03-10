#include <iostream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

int main()
{
    vector <string> ivec;
    string temp;
    cout<<"input the text (CTRL+d to end)"<<endl;
    while (cin>>temp)
        ivec.push_back(temp);

    if(ivec.size()==0)
    {       cout<<"this empty vector!"<<endl;
        return 1;
    }
    cout<<"Transformed elements from the vector:"
        <<endl;
    for(vector<string>::size_type index=0;index<ivec.size()-1;index++)
    {
        for(string::size_type iindex=0;iindex<ivec[index].size()-1;iindex++)

        if(islower(ivec[index][iindex]))
        ivec[index][iindex]=toupper(ivec[index][iindex]);
                cout<<ivec[index]<<"";
                if((index+1)%8)
                cout<<endl;
                }
                return 0;
 }
