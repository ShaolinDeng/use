/***********
输入一个整形数组，数组里有正数也有负数。
数组中连续的一个或多个整数组成一个子数组，每个子数组都有一个和。
求所有子数组的和的最大值。要求时间复杂度为O(n)。

例如输入的数组为1, -2, 3, 10, -4, 7, 2, -5，和最大的子数组为3, 10, -4, 7, 2，
因此输出为该子数组的和18。

*********************/

#include <iostream>

using namespace std;

int maxSum(int* a, int n)
{
	int sum=0;
	int b=0;

	for(int i=0; i<n; i++)
	{
		if(b<0)
			b=a[i];
		else
			b+=a[i];
		if(sum<b)
			sum=b;
	}
	return sum;
}

int main()
{
	
	
	
	int a[10]={1,-8,6,3,-1,5,7,-2,0,1};
	cout<<maxSum(a,10)<<endl;
	return 0;
}
