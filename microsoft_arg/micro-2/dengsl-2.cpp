/***
  设计包含min函数的栈（栈）
  定义栈的数据结构，要求添加一个min函数，能够得到栈的最小元素。
  要求函数min、push以及pop的时间复杂度都是O(1)
 
结合链表一起做。

	首先我做插入以下数字：10，7，3，3，8，5，2， 6
    0: 10 -> NULL (MIN=10, POS=0)
	1: 7 -> [0] (MIN=7, POS=1) 用数组表示堆栈，第0个元素表示栈底
	2: 3 -> [1] (MIN=3, POS=2)
    3: 3 -> [2] (MIN=3, POS=3)
	4: 8 -> NULL (MIN=3, POS=3) 技巧在这里，因为8比当前的MIN大，所以弹出8不会对当前的MIN产生影响
    5：5 -> NULL (MIN=3, POS=3)
	6: 2 -> [2] (MIN=2, POS=6) 如果2出栈了，那么3就是MIN
	7: 6 -> [6]

	出栈的话采用类似方法修正。


	所以，此题的第1小题，即是借助辅助栈，保存最小值，
	且随时更新辅助栈中的元素。
	如先后，push 2 6 4 1 5
	stack A  stack B（辅助栈）

	4:  5       1      //push 5,min=p->[3]=1     ^
	3:  1       1      //push 1,min=p->[3]=1     |   //此刻push进A的元素1小于B中栈顶元素2
	2:  4       2      //push 4,min=p->[0]=2     |
	1:  6       2      //push 6,min=p->[0]=2     |
	0:  2       2      //push 2,min=p->[0]=2     |

	push第一个元素进A，也把它push进B，
	当向Apush的元素比B中的元素小，  则也push进B，即更新B。否则，不动B，保存原值。
	向栈A push元素时，顺序由下至上。
	辅助栈B中，始终保存着最小的元素。

	然后，pop栈A中元素，5 1 4 6 2
	A       B ->更新 
	4:   5       1    1     //pop 5,min=p->[3]=1      |
	3:   1       1    2     //pop 1,min=p->[0]=2      |
	2:   4       2    2     //pop 4,min=p->[0]=2      |
	1:   6       2    2     //pop 6,min=p->[0]=2      |
	0:   2       2    NULL  //pop 2,min=NULL          v

	当pop A中的元素小于B中栈顶元素时，则也要pop B中栈顶元素。

	---------------------------------------------------
	*******************/
template<typename T>
class StackSuppliedMin{
	public:
		vector<T> datas;
		vector<size_t> minStack;

		void push(T data){
			datas.push_back(data);
			if (minStack.empty() || data < datas[minStack.back()])
				minStack.push_back(datas.size()-1);
		}

		void pop(){
			assert(!datas.empty());
			if (datas.back() == datas[minStack.back()])
				minStack.pop_back();
			datas.pop_back();
		}

		T min(){
			assert(!datas.empty() && !minStack.empty());
			return datas[minStack.back()];
		}

		void display();
};
