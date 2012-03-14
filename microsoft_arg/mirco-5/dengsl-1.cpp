/************************************
.查找最小的k个元素（数组）
题目：输入n个整数，输出其中最小的k个。
例如输入1，2，3，4，5，6，7和8这8个数字，则最小的4个数字为1，2，3和4
*************************/
#include<iostream>
using namespace std;

class MinK{
	public:
		MinK(int *arr,int si):array(arr),size(si){}

		bool kmin(int k,int*& ret){
			if(k>size)
			{
				ret=NULL;
				return false;
			}
			else
			{
				ret=new int[k--];
				int i;
				for(i=0;i<=k;++i)
					ret[i]=array[i];
				for(int j=(k-1)/2;j>=0;--j)
					shiftDown(ret,j,k);
				for(;i<size;++i)
					if(array[i]<ret[0])
					{
						ret[0]=array[i];
						shiftDown(ret,0,k);
					}
				return true;
			}
		}

		void remove(int*& ret){
			delete[] ret;
			ret=NULL;
		}

	private:
		void shiftDown(int *ret,int pos,int length){
			int t=ret[pos];
			for(int s=2*pos+1;s<=length;s=2*s+1){
				if(s<length&&ret[s]<ret[s+1])
					++s;
				if(t<ret[s])
				{
					ret[pos]=ret[s];
					pos=s;
				}
				else break;
			}
			ret[pos]=t;
		}

		int *array;
		int size;
};


int main()
{
	int array[]={1,2,3,4,5,6,7,8};
	MinK mink(array,sizeof(array)/sizeof(array[0]));
	int *ret;
	int k=4;
	if(mink.kmin(k,ret))
	{
		for(int i=0;i<k;++i)
			cout<<ret[i]<<endl;
		mink.remove(ret);
	}
	return 0;
}
