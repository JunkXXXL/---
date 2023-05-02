#include "SearchTree.h"

void SearchTree::addNode(int key)
{
	addNode(key, _root);
}

Node* SearchTree::_getMinKey(Node* node)
{
	SearchTreeIterator iter(this);
	Node* nearestKey = nullptr;
	while (iter.exists())
	{
		if (iter.getNode()->key != node->key)
		{
			if (node->key < iter.getNode()->key && nearestKey == nullptr)
			{
				nearestKey = iter.getNode();
			}
		}
		iter.moveToNext();
	}
	return nearestKey;
}

Node* SearchTree::_findParent(int key)
{
	if (_root->key == key) return nullptr;

	Node* parent = _root;
	while (true)
	{
		if (key <= parent->key)
		{
			if (parent->left->key != key) parent = parent->left;
			else return parent;
		}
		else
		{
			if (parent->right->key != key) parent = parent->right;
			else return parent;
		}
	}
	return nullptr;
}

bool SearchTree::deleteNode(int key)
{
	std::vector<int> vec = getVector();
	bool inVec = false;
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == key) inVec = true;
	}

	if (inVec == false) return false;

	Node* parent = _findParent(key);
	Node* runner = findNode(key);
	if (runner->getChildrenCount() == 0)
	{
		if (parent != nullptr) 
		{
			if (parent->left == runner)parent->left = nullptr;
			else parent->right = nullptr;
		}
		else
		{
			runner->key = 0;
		}
		return true;
	}
	else if (runner->getChildrenCount() == 2)
	{
			Node* minKey = _getMinKey(runner);
			Node* minKeyParent = _findParent(minKey->key);
			int key = minKey->key;
			deleteNode(minKey->key);
			runner->key = key;
			return true;
	}
	else if (runner->getChildrenCount() == 1)
	{
		if (parent != nullptr)
		{
			if (runner->left != nullptr && parent->left == runner)
			{
				parent->left = runner->left;
				delete runner;
			}
			else if (runner->left != nullptr && parent->right == runner)
			{
				parent->right = runner->left;
				delete runner;
			}
			else if (runner->right != nullptr && parent->left == runner)
			{
				parent->left = runner->right;
				delete runner;
			}
			else
			{
				parent->right = runner->right;
				delete runner;
			}
			return true;
		}
		else
		{
			if (runner->left != nullptr)
			{
				_root = runner->left;
				delete runner;
			}
			else
			{
				_root = runner->right;
				delete runner;
			}
		}
	}

	return false;
}

SearchTree::SearchTree(const SearchTree& tree)
{
	_root = new Node(tree._root);
}

SearchTree::SearchTree(Node* node)
{
	_root = node;
}

void SearchTree::addNode(int key, Node* node)
{
	if (node->getChildrenCount() == 0)
	{
		if (node->key < key)
		{
			node->right = new Node(key);
		}
		else
		{
			node->left = new Node(key);
		}
		return;
	}

	if (node->key < key)
	{
		if (node->right != nullptr)
		{
			addNode(key, node->right);
		}
		else
		{
			node->right = new Node(key);
		}
	}
	else
	{
		if (node->left != nullptr)
		{
			addNode(key, node->left);
		}
		else
		{
			node->left = new Node(key);
		}
	}
}

SearchTree SearchTree::copyUnderTree(Node* node)
{
	SearchTree toRet(new Node(node));
	return toRet;
}

int SearchTree::minKey() const
{
	Node* pointer = _root;
	while (pointer->left != nullptr)
	{
		pointer = pointer->left;
	}
	return pointer->key;
}

int SearchTree::maxKey() const
{
	Node* pointer = _root;
	while (pointer->right != nullptr)
	{
		pointer = pointer->right;
	}
	return pointer->key;
}

Node* SearchTree::findNode(int value) const
{
	return findNode(value, _root);
}

int SearchTree::getHeigthNode(Node* nd) const
{
	return 	getHeigth(nd);
}

SearchTree& SearchTree::operator=(const SearchTree& other)
{
	if (other._root != _root)
	{
		clear();
		delete _root;
		_root = new Node(other._root);
	}
	return *this;
}

Node* SearchTree::findNode(int value, Node* node) const
{
	if (node->key == value)
	{
		return node;
	}
	if (node->getChildrenCount() == 0)
	{
		return nullptr;
	}

	if (node->key < value)
	{
		if (node->right != nullptr)
		{
			return findNode(value, node->right);
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		if (node->left != nullptr)
		{
			return findNode(value, node->left);
		}
		else
		{
			return nullptr;
		}
	}
}

std::vector<int> SearchTree::getVector() const
{
	std::vector<int> vector;
	SearchTreeIterator iter(this);

	while (iter.exists())
	{
		vector.push_back(iter.value());
		iter.moveToNext();
	}

	return vector;
}