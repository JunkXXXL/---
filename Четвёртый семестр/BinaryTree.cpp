#include "BinaryTree.h"

int BinaryTree::sumKeys(Node* nd) const
{
	int to_ret = 0;

	if (nd->left != nullptr)
	{
		to_ret += sumKeys(nd->left);
	}
	if (nd->right != nullptr)
	{
		to_ret += sumKeys(nd->right);
	}

	return to_ret;
}

BinaryTree::BinaryTree(BinaryTree* tree)
{
	
}

BinaryTree::BinaryTree(int root_key)
{
	_root = new Node(root_key);
}

int BinaryTree::sumKeys() const
{
	int to_ret = 0;

	if (_root->left != nullptr)
	{
		to_ret += sumKeys(_root->left);
	}
	if (_root->right != nullptr)
	{
		to_ret += sumKeys(_root->right);
	}

	return to_ret;
}

void BinaryTree::print() const
{
	
}
