#include "BinaryTree.h"
#include <random>
#include <time.h>
#include "BinaryTreeIterator.h"

struct ChildsInfo
{
	int leftChild = 0;
	int rightChild = 0;
	bool answer = true;
};

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

BinaryTree::BinaryTree(BinaryTree* tree)
{
	_root = new Node(tree->_root);
}

BinaryTree::BinaryTree(Node* nd)
{
	_root = nd;
}

BinaryTree::BinaryTree(int root_key)
{
	_root = new Node(root_key);
}

BinaryTree::~BinaryTree()
{
	clear(_root);
	delete _root;
}

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

int BinaryTree::sumKeys() const
{
	return sumKeys(_root);
}

int BinaryTree::getNodeLevel(Node* node) const
{
	int nowHeight = getHeigth(node);
	return getHeigth() - nowHeight;
}

std::vector<int> BinaryTree::getVector() const
{
	std::vector<int> to_ret;
	BinaryTreeIterator iter(this);

	while (iter.exists())
	{
		to_ret.push_back(iter.value());
		iter.moveToNext();
	}
	return to_ret;
}

void BinaryTree::print() const
{
	BinaryTreeIterator iter(this);
	
	while (iter.exists())
	{
		std::cout << iter.value() << " ";
		iter.moveToNext();
	}
}

const Node* BinaryTree::findNode(int value) const
{
	BinaryTreeIterator iter(this);

	while (iter.exists())
	{
		if (iter.value() == value)
		{
			return iter.getNode();
		}
		iter.moveToNext();
	}
	return nullptr;
}

const Node* BinaryTree::getRoot() const
{
	return _root;
}

void BinaryTree::clear() //clear
{
	clear(_root);
	_root->key = 0;
}

void BinaryTree::clear(Node* node)
{
	if (node->left != nullptr)
	{
		clear(node->left);
		delete node->left;
	}
	if (node->right != nullptr)
	{
		clear(node->right);
		delete node->right;
	}
}

void BinaryTree::printLeaf() const
{
	printLeaf(_root);
}

BinaryTree& BinaryTree::operator=(BinaryTree& other)
{
	if (other._root != _root)
	{
		clear();
		delete _root;
		_root = new Node(other._root);
	}

	return *this;
}

void BinaryTree::printLeaf(Node* usel) const
{
	if (usel->left != nullptr)
	{
		printLeaf(usel->left);
	}
	if (usel->right != nullptr)
	{
		printLeaf(usel->right);
	}
	if (usel->left == nullptr && usel->right == nullptr)
	{
		std::cout << usel->key << " ";
	}
}

bool BinaryTree::isEmpty()
{
	return _root;
}

int BinaryTree::getHeigth(Node* usel) const
{
	int rightHight = 1;
	int leftHight = 1;
	if (usel->left != nullptr)
	{
		leftHight += getHeigth(usel->left);
	}
	if (usel->right != nullptr)
	{
		rightHight += getHeigth(usel->right);
	}

	return (rightHight > leftHight) ? rightHight : leftHight;
}

int BinaryTree::getHeigth() const
{
	return getHeigth(_root);
}

BinaryTree BinaryTree::copyUnderTree(Node* usel)
{
	BinaryTree to_ret(new Node(usel));
	
	return to_ret;
}

int BinaryTree::nodeCount(Node* node) const
{
	int count = 1;
	if (node->left != nullptr)
	{
		count += nodeCount(node->left);
	}
	if (node->right != nullptr)
	{
		count += nodeCount(node->right);
	}
	return count;
}

int BinaryTree::nodeCount() const
{
	return nodeCount(_root);
}

int BinaryTree::maxKey() const
{
	return maxKey(_root);
}

int BinaryTree::minKey() const
{
	return minKey(_root);
}

void BinaryTree::addNodeRandomly(Node* usel, int value)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	Node* pointer = usel;
	bool switcher = gen() % 2;
	if (switcher)
	{
		if (pointer->right != nullptr)
		{
			addNodeRandomly(pointer->right, value);
		}
		else
		{
			pointer->right = new Node(value);
		}
	}
	else
	{
		if (pointer->left != nullptr)
		{
			addNodeRandomly(pointer->left, value);
		}
		else
		{
			pointer->left = new Node(value);
		}
	}
}

void BinaryTree::addNodeRandomly(int value)
{
	addNodeRandomly(_root, value);
}

ChildsInfo BinaryTree::isBalance(Node* node) const
{
	ChildsInfo inf;
	if (node->left != nullptr)
	{
		ChildsInfo inf1 = isBalance(node->left);
		inf.leftChild += inf1.leftChild;
		inf.rightChild += inf1.rightChild;
	}
	if (node->right != nullptr)
	{
		ChildsInfo inf2 = isBalance(node->right);
		inf.leftChild += inf2.leftChild;
		inf.rightChild += inf2.rightChild;
	}

	if (abs(inf.leftChild - inf.rightChild) > 1)
	{
		inf.answer = false;
	}
	return inf;
}

bool BinaryTree::isBalance() const
{
	ChildsInfo answer = isBalance(_root);
	return answer.answer;
}
