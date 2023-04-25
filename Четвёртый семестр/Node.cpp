#include "Node.h"

Node::Node(Node* nd)
{
	key = nd->key;
	if (nd->right != nullptr)
	{
		right = new Node(nd->right);
	}
	if (nd->left != nullptr)
	{
		left = new Node(nd->left);
	}
}

int Node::getKey() const
{
	return key;
}

int Node::getChildrenCount() const
{
	int to_ret = 0;
	if (left != nullptr) to_ret++;
	if (right != nullptr) to_ret++;
	return to_ret;
}

