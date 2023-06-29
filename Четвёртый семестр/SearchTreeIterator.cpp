#include "SearchTreeIterator.h"

SearchTreeIterator::SearchTreeIterator(const SearchTree* tree)
{
	_tree = tree->getRoot();
	_writeInStack(_tree);
	moveToNext();
}

SearchTreeIterator::~SearchTreeIterator()
{
	Node* pointer = nullptr;
	while (!_nodeStack.empty())
	{
		_nodeStack.pop();
	}
}

SearchTreeIterator::SearchTreeIterator(SearchTree* tree)
{
	_tree = tree->getRoot();
	_writeInStack(_tree);
	moveToNext();
}

bool SearchTreeIterator::exists() const
{
	return (_tree != nullptr);
}

int SearchTreeIterator::value() const
{
	return _tree->getKey();
}

Node* SearchTreeIterator::getNode()
{
	return _tree;
}

void SearchTreeIterator::moveToNext()
{
	if (_nodeStack.empty())
		_tree = nullptr;
	else
	{
		_tree = _nodeStack.top();
		_nodeStack.pop();
	}
}

void SearchTreeIterator::_writeInStack(Node* node)
{
	if (node == nullptr)
	{
		return;
	}
	_writeInStack(node->right);
	_nodeStack.push(node);
	_writeInStack(node->left);
}