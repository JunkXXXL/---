#include "BinaryTreeIterator.h"
#include <vector>

void BinaryTreeIterator::_writeVector()
{
	_nodeVec.push_back(_tree);
	int counter = 0;
	while (_nodeVec.size() > counter)
	{
		if (_nodeVec[counter]->left != nullptr) _nodeVec.push_back(_nodeVec[counter]->left);
		if (_nodeVec[counter]->right != nullptr) _nodeVec.push_back(_nodeVec[counter]->right);
		counter++;
	}
}

BinaryTreeIterator::BinaryTreeIterator(const BinaryTree *tree)
{
	_tree = tree->getRoot();
	_writeVector();
}

BinaryTreeIterator::BinaryTreeIterator(BinaryTree* tree)
{
	_tree = tree->getRoot();
	_writeVector();
}

BinaryTreeIterator::~BinaryTreeIterator()
{
	Node* pointer = nullptr;
	while (!_nodeVec.empty())
	{
		_nodeVec.pop_back();
	}
}

bool BinaryTreeIterator::exists() const
{
	if (_position < _nodeVec.size()) return true;
	else return false;
}

int BinaryTreeIterator::value() const
{
	if (exists()) return _nodeVec[_position]->getKey();
	else throw "Binary Tree is not exist";
}

void BinaryTreeIterator::moveToNext()
{
	_position++;
}

Node* BinaryTreeIterator::getNode()
{
	return _nodeVec[_position];
}
