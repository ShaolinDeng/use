#include <iostream>
using namespace std;

class Node{
	public:
		int data;
		Node *left;
		Node *right;

		Node(int d = 0, Node *lr = 0, Node *rr = 0):data(d), left(lr), right(rr){}
};

Node *create()
{
	Node *root;
	Node *p4 = new Node(4);
	Node *p8 = new Node(8);
	Node *p6 = new Node(6, p4, p8);

	Node *p12 = new Node(12);
	Node *p16 = new Node(16);
	Node *p14 = new Node(14, p12, p16);

	Node *p10 = new Node(10, p6, p14);
	root = p10;

	return root;
}

Node *change(Node *p, bool asRight)
{
	if (!p)
		return NULL;
	Node *pLeft = change(p->left, false);
	if (pLeft)
		pLeft->right = p;
	p->left = pLeft;

	Node *pRight = change(p->right, true);
	if (pRight)
		pRight->left = p;
	p->right = pRight;

	Node *r = p;
	if (asRight)
	{
		while (r->left)
			r = r->left;
	}else{
		while (r->right)
			r = r->right;
	}
	return r;
}

int main(){
	Node *root = create();
	Node *tail = change(root, false);
	while (tail)
	{
		cout << tail->data << " ";
		tail = tail->left;
	}
	cout << endl;

	root = create();
	Node *head = change(root, true);
	while (head)
	{
		cout << head->data << " ";
		head = head->right;
	}
	cout << endl;
	return 0;
}
