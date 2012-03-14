





void change(Node *p, Node *&last) //中序遍历
{
	if (!p)
		return;
	change(p->left, last);
	if (last)
		last->right = p;
	p->left = last;

	last = p;
	change(p->right, last);
}

void main()
{
	Node *root = create();
	Node *tail = NULL;
	change(root, tail);
	while (tail)
	{
		cout << tail->data << " ";
		tail = tail->left;
	}
	cout << endl;
}


