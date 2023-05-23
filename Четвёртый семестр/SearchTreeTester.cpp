#include "SearchTreeTester.h"

bool SearchTreeTester::isSearchTree(const BinaryTree tree)
{
	std::vector<int> keys;

	getKeysLnr(keys, tree.getRoot());

	for (int i = 1; i < keys.size(); i++)
	{
		if (keys[i] <= keys[i - 1])
		{
			return false;
		}
	}
	return true;
}

void SearchTreeTester::getKeysLnr(std::vector<int>& keys, Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	getKeysLnr(keys, node->left);
	keys.push_back(node->key);
	getKeysLnr(keys, node->right);
}

BinaryTree* SearchTreeTester::allocateTree()
{
	return new SearchTree;
}

void SearchTreeTester::check_addAndCount(const BinaryTree& tree, const int size)
{
	BinaryTreeTesterClass::check_addAndCount(tree, size);
	assert(isSearchTree(tree));
}

void SearchTreeTester::check_remove(const BinaryTree& tree, const int size)
{
	BinaryTreeTesterClass::check_remove(tree, size);
	assert(isSearchTree(tree));
}

void SearchTreeTester::check_assign(const BinaryTree& firstTree, const BinaryTree& secondTree)
{
	assert(firstTree.getRoot() != secondTree.getRoot());

}
