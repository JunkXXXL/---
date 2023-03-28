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

int BinaryTree::maxKey(Node* usel) const
{
	int max = usel->key;
	if (usel->left != nullptr)
	{
		int newMAX = maxKey(usel->left);
		if (newMAX > max)
		{
			max = newMAX;
		}
	}
	if (usel->right != nullptr)
	{
		int newMAX = maxKey(usel->right);
		if (newMAX > max)
		{
			max = newMAX;
		}
	}
	return max;
}

int BinaryTree::minKey(Node* usel) const
{
	int min = usel->key;
	if (usel->left != nullptr)
	{
		int newMIN = minKey(usel->left);
		if (newMIN < min)
		{
			min = newMIN;
		}
	}
	if (usel->right != nullptr)
	{
		int newMIN = minKey(usel->right);
		if (newMIN < min)
		{
			min = newMIN;
		}
	}
	return min;
}

int BinaryTree::nodeCount(Node* usel) const
{
	int count = 1;
	if (usel->left != nullptr)
	{
		count += nodeCount(usel->left);
	}
	if (usel->right != nullptr)
	{
		count += nodeCount(usel->right);
	}
	return count;
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

const Node* BinaryTree::getRoot() const
{
	return _root;
}

bool BinaryTree::isEmpty()
{
	return _root;
}

int BinaryTree::nodeCount() const
{
	int count = 1;
	if (_root->left != nullptr)
	{
		count += nodeCount(_root->left);
	}
	if (_root->right != nullptr)
	{
		count += nodeCount(_root->right);
	}
	return count;
}

int BinaryTree::maxKey() const
{
	int max = _root->key;
	if (_root->left != nullptr)
	{
		int newMAX = maxKey(_root->left);
		if (newMAX > max) 
		{
			max = newMAX;
		}
	}
	if (_root->right != nullptr)
	{
		int newMAX = maxKey(_root->right);
		if (newMAX > max)
		{
			max = newMAX;
		}
	}
	return max;
}

int BinaryTree::minKey() const
{
	int min = _root->key;
	if (_root->left != nullptr)
	{
		int newMIN = minKey(_root->left);
		if (newMIN < min)
		{
			min = newMIN;
		}
	}
	if (_root->right != nullptr)
	{
		int newMIN = minKey(_root->right);
		if (newMIN < min)
		{
			min = newMIN;
		}
	}
	return min;
}
