#include <iostream>
using namespace std;
void QuickSort(int *pData,int left,int right)
{
int i(left),j(right),middle(0),iTemp(0);
middle=pData[(left+right)/2];//求中间值
middle=pData[(rand()%(right-left+1))+left]; //生成大于等于left小于等于right的随机数
do{
while((pData[i]<middle)&&(i<right))//从左扫描大于中值的数
i++;
while((pData[j]>middle) && (j>left))//从右扫描小于中值的数
j--;
//找到了一对值,交换
if(i<=j){
iTemp=pData[j];
pData[j]=pData[i];
pData[i]=iTemp;
i++;
j--;
}
}while(i<=j);//如果两边扫描的下标交错，就停止（完成一次）
//当左边部分有值(left<j)，递归左半边
if(left<j){
QuickSort(pData,left,j);
}
//当右边部分有值(right>i)，递归右半边
if(right>i){
QuickSort(pData,i,right);
}
}
int main()
{
int data[]={10,9,8,7,6,5,4};
const int count(6);
QuickSort(data,0,count);
for(int i(0);i!=7;++i)
{
    cout<<data[i]<<""<<flush;
}
cout<<endl;
return 0;
}

