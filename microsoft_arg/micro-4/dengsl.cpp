/********************
  题目：输入一个整数和一棵二元树。
  从树的根结点开始往下访问一直到叶结点所经过的所有结点形成一条路径。
  打印出和与输入整数相等的所有路径。
  例如 输入整数22和如下二元树
  10  
  / /   
  5  12   
  /   /   
  4     7
  则打印出两条路径：10, 12和10, 5, 7。
  二元树节点的数据结构定义为：
  struct BinaryTreeNode // a node in the binary tree
  {
  int m_nValue; // value of node
  BinaryTreeNode *m_pLeft; // left child of node
  BinaryTreeNode *m_pRight; // right child of node
  };
 ************************/
void FindPath
(
 BinaryTreeNode*   pTreeNode,    // a node of binary tree
 int               expectedSum,  // the expected sum
 std::vector<int>& path,         // a path from root to current node
 int&              currentSum    // the sum of path
 )
{
	if(!pTreeNode)
		return;

	currentSum += pTreeNode->m_nValue;
	path.push_back(pTreeNode->m_nValue);

	// if the node is a leaf, and the sum is same as pre-defined,
	// the path is what we want. print the path
	bool isLeaf = (!pTreeNode->m_pLeft && !pTreeNode->m_pRight);
	if(currentSum == expectedSum && isLeaf)
	{   
		std::vector<int>::iterator iter = path.begin();
		for(; iter != path.end(); ++ iter)
			std::cout << *iter << '/t';
		std::cout << std::endl;
	}

	// if the node is not a leaf, goto its children
	if(pTreeNode->m_pLeft)
		FindPath(pTreeNode->m_pLeft, expectedSum, path, currentSum);
	if(pTreeNode->m_pRight)
		FindPath(pTreeNode->m_pRight, expectedSum, path, currentSum);

	// when we finish visiting a node and return to its parent node,
	// we should delete this node from the path and
	// minus the node's value from the current sum
	currentSum -= pTreeNode->m_nValue;
	path.pop_back();
}
