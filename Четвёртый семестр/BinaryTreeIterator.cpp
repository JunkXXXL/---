#include "BinaryTreeIterator.h"
#include <stack>

BinaryTreeIterator::BinaryTreeIterator(const BinaryTree *tree)
{
	_tree = tree->getRoot();
	_head = tree->getRoot();
	_treeHigth = tree->getHeigth();
}

BinaryTreeIterator::BinaryTreeIterator(BinaryTree* tree)
{
	_tree = tree->getRoot();
	_head = tree->getRoot();
	_treeHigth = tree->getHeigth();
}

bool BinaryTreeIterator::exists() const
{
	if (_tree == nullptr) return false;
	else return true;
}

int BinaryTreeIterator::value() const
{
	if (exists()) return _tree->getKey();
	else throw "Binary Tree is not exist";
}

void BinaryTreeIterator::moveToNext()
{
	int elements = (2 << _treeHigth) - 1;
	_position++;

	_tree = _head;
	std::stack<bool> wayToNext;

	if (_position < elements)
	{
		bool toStack;
		bool toward; //0 - left   1 - right

		for (int pos = _position; pos > 0; pos = (pos % 2) ? pos / 2 : (pos / 2 - 1))
		{
			toStack = !(pos % 2);
			wayToNext.push(toStack);
		}

		while (!wayToNext.empty())
		{
			toward = wayToNext.top();
			wayToNext.pop();

			if (toward == true && _tree != nullptr)
			{
				_tree = _tree->right;
			}
			else if (toward == false && _tree != nullptr)
			{
				_tree = _tree->left;
			}
			if (_tree == nullptr)
			{
				moveToNext();
				break;
			}

		}
	}
	else
	{
		_tree = nullptr;
	}
}

const Node* BinaryTreeIterator::getNode()
{
	return _tree;
}
