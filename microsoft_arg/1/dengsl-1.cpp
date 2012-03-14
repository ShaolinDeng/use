/*
   把二元查找树转变成排序的双向链表（树）
   题目：
   输入一棵二元查找树，将该二元查找树转换成一个排序的双向链表。
   要求不能创建任何新的结点，只调整指针的指向。
         10
        /  \
       6    14
      / \   / \
     4  8  12 16
   转换成双向链表
   4=6=8=10=12=14=16。

   首先我们定义的二元查找树 节点的数据结构如下：
   struct BSTreeNode
   {
   		int m_nValue; // value of node
   		BSTreeNode *m_pLeft; // left child of node
   		BSTreeNode *m_pRight; // right child of node
   };

**/






