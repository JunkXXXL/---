#include "BinaryTree.h"
#include <random>
#include <time.h>


int BinaryTree::maxKey(Node* node) const
{
	int max = node->key;
	if (node->left != nullptr)
	{
		int newMAX = maxKey(node->left);
		if (newMAX > max)
		{
			max = newMAX;
		}
	}
	if (node->right != nullptr)
	{
		int newMAX = maxKey(node->right);
		if (newMAX > max)
		{
			max = newMAX;
		}
	}
	return max;
}

int BinaryTree::minKey(Node* node) const
{
	int min = node->key;
	if (node->left != nullptr)
	{
		int newMIN = minKey(node->left);
		if (newMIN < min)
		{
			min = newMIN;
		}
	}
	if (node->right != nullptr)
	{
		int newMIN = minKey(node->right);
		if (newMIN < min)
		{
			min = newMIN;
		}
	}
	return min;
}

BinaryTree::BinaryTree(const BinaryTree& tree)
{
	_root = new Node(tree._root);
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

void BinaryTree::print(Node* root, int marginLeft, int levelSpacing) const
{

		if (root == nullptr) {
			return;
		}
		print(root->right, marginLeft + levelSpacing, levelSpacing);
		std::cout << std::string(marginLeft, ' ') << root->key << std::endl;
		print(root->left, marginLeft + levelSpacing, levelSpacing);

}

Node* BinaryTree::_goDown(Node* node)
{
	if (node->getChildrenCount() == 0)
	{
		return nullptr;
	}
	if (node->getChildrenCount() == 2)
	{
		return node->left;
	}
	if (node->getChildrenCount() == 1)
	{
		if (node->left != nullptr)
		{
			return node->left;
		}
		else
		{
			return node->right;
		}
	}
	return nullptr;
}

bool BinaryTree::_instructionToDeleteNodeWithTwoChild(const Node* node, BinaryTreeIterator iter)
{
	while (iter.exists())
	{
		if (iter.getNode()->left == node)
		{
			Node* delPrevNode = iter.getNode();
			Node* delNode = iter.getNode()->left;
			Node* replaceNode = iter.getNode()->left->left;
			Node* replacePrevNode = iter.getNode()->left;

			while (_goDown(replaceNode) != nullptr)
			{
				replacePrevNode = replaceNode;
				replaceNode = _goDown(replaceNode);
			}

			//step 1
			if (delPrevNode != nullptr)
			{
				delPrevNode->left = replaceNode;
			}

			//step 3
			if (replacePrevNode->left == replaceNode)
			{
				replacePrevNode->left = nullptr;
			}
			else
			{
				replacePrevNode->right = nullptr;
			}

			//step 4
			replaceNode->left = delNode->left;
			replaceNode->right = delNode->right;

			//step 2
			delete delNode;
			return true;
		}
		if (iter.getNode()->right == node)
		{
			Node* delPrevNode = iter.getNode();
			Node* delNode = iter.getNode()->right;
			Node* replaceNode = iter.getNode()->right;
			Node* replacePrevNode = iter.getNode()->right->right;

			while (_goDown(replaceNode) != nullptr)
			{
				replacePrevNode = replaceNode;
				replaceNode = _goDown(replaceNode);
			}

			//step 1
			if (delPrevNode != nullptr)
			{
				delPrevNode->right = replaceNode;
			}

			//step 3
			if (replacePrevNode->left == replaceNode)
			{
				replacePrevNode->left = nullptr;
			}
			else
			{
				replacePrevNode->right = nullptr;
			}

			//step 4
			replaceNode->left = delNode->left;
			replaceNode->right = delNode->right;

			//step 2
			delete delNode;

			return true;
		}
		iter.moveToNext();
	}
	return false;
}

bool BinaryTree::_instructionToDeleteRootWithTwoChild(const Node* node, BinaryTreeIterator iter)
{
	Node* delNode = iter.getNode()->left;
	Node* replaceNode = iter.getNode()->left;
	Node* replacePrevNode = iter.getNode()->left->left;

	while (_goDown(replaceNode) != nullptr)
	{
		replacePrevNode = replaceNode;
		replaceNode = _goDown(replaceNode);
	}

	//step 1

	//step 3
	if (replacePrevNode->left == replaceNode)
	{
		replacePrevNode->left = nullptr;
	}
	else
	{
		replacePrevNode->right = nullptr;
	}

	//step 4
	replaceNode->left = delNode->left;
	replaceNode->right = delNode->right;

	//step 2
	delete delNode;
	_root = replaceNode;
	return true;
}

bool BinaryTree::_instructionToDeleteNodeWithOneChild(const Node* node, BinaryTreeIterator iter)
{
	while (iter.exists())
	{
		if (iter.getNode()->left == node)
		{
			Node* toDel = iter.getNode()->left;
			if (iter.getNode()->left->left != nullptr)
			{
				iter.getNode()->left = iter.getNode()->left->left;
			}
			else
			{
				iter.getNode()->left = iter.getNode()->left->right;
			}

			delete toDel;

			return true;
		}
		if (iter.getNode()->right == node)
		{
			Node* toDel = iter.getNode()->right;
			if (iter.getNode()->right->left != nullptr)
			{
				iter.getNode()->right = iter.getNode()->right->left;
			}
			else
			{
				iter.getNode()->right = iter.getNode()->right->right;
			}

			delete toDel;

			return true;
		}
		iter.moveToNext();
	}
	return false;
}

bool BinaryTree::_instructionToDeleteRootWithOneChild(const Node* node, BinaryTreeIterator iter)
{
	Node* toDel = iter.getNode();
	Node* newRoot = nullptr;
	if (toDel->left != nullptr)
	{
		newRoot = toDel->left;
	}
	else
	{
		newRoot = toDel->right;
	}
	delete toDel;
	_root = newRoot;

	return true;
}

void BinaryTree::print() const
{
	print(_root, 1, 3);
	std::cout << "\n";
}

bool BinaryTree::deleteNode(int key)
{
	const Node* node = findNode(key);
	if (node == nullptr) return false;

	if (node->getChildrenCount() == 0)
	{
		BinaryTreeIterator iter(this);
		while (iter.exists())
		{
			if (iter.getNode()->left == node)
			{
				delete iter.getNode()->left;
				iter.getNode()->left = nullptr;
				return true;
			}
			if (iter.getNode()->right == node)
			{
				delete iter.getNode()->right;
				iter.getNode()->right = nullptr;
				return true;
			}
			iter.moveToNext();
		}
		return false;
	}

	else if (node->getChildrenCount() == 1)
	{
		BinaryTreeIterator iter(this);
		if (iter.getNode() != nullptr)
		{
			return _instructionToDeleteNodeWithOneChild(node, iter);
		}
		else
		{
			return _instructionToDeleteRootWithOneChild(node, iter);
		}
	}

	else
	{
		BinaryTreeIterator iter(this);
		if (iter.getNode() != node)
		{
			return _instructionToDeleteNodeWithTwoChild(node, iter);
		}
		else
		{
			return _instructionToDeleteRootWithTwoChild(node, iter);
		}
	}

	return false;
}

Node* BinaryTree::findNode(int value) const
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

Node* BinaryTree::getRoot() const
{
	return _root;
}

void BinaryTree::clear() //clear
{
	clear(_root);
}

void BinaryTree::clear(Node* node)
{
	if (_root == nullptr) return;
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
	node->left = nullptr;
	node->right = nullptr;
}

void BinaryTree::printLeaf() const
{
	printLeaf(_root);
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other)
{
	if (other._root != _root)
	{
		clear();
		delete _root;
		_root = new Node(other._root);
	}

	return *this;
}

void BinaryTree::printLeaf(Node* node) const
{
	if (node->left != nullptr)
	{
		printLeaf(node->left);
	}
	if (node->right != nullptr)
	{
		printLeaf(node->right);
	}
	if (node->left == nullptr && node->right == nullptr)
	{
		std::cout << node->key << " ";
	}
}

bool BinaryTree::isEmpty()
{
	return _root;
	
}

int BinaryTree::getHeigth(Node* node) const
{
	int rightHight = 1;
	int leftHight = 1;
	if (node->left != nullptr)
	{
		leftHight += getHeigth(node->left);
	}
	if (node->right != nullptr)
	{
		rightHight += getHeigth(node->right);
	}

	return (rightHight > leftHight) ? rightHight : leftHight;
}

int BinaryTree::size() const
{
	int size = 0;
	BinaryTreeIterator iter(this);
	
	while (iter.exists())
	{
		size++;
		iter.moveToNext();
	}
	return size;
}

int BinaryTree::getHeigth() const
{
	return getHeigth(_root);
}

BinaryTree BinaryTree::copyUnderTree(Node* node)
{
	return BinaryTree(new Node(node));
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

void BinaryTree::addNode(Node* node, int value)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	Node* pointer = node;
	bool switcher = gen() % 2;
	if (switcher)
	{
		if (pointer->right != nullptr)
		{
			addNode(pointer->right, value);
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
			addNode(pointer->left, value);
		}
		else
		{
			pointer->left = new Node(value);
		}
	}
}

void BinaryTree::addNode(int value)
{
	addNode(_root, value);
}

int BinaryTree::isBalance(Node* node) const
{
	int inf = 0;
	if (node->left != nullptr)
	{
		inf += isBalance(node->left);
	}
	else
	{
		inf += 1;
	}
	if (node->right != nullptr)
	{
		inf -= isBalance(node->right);
	}
	else
	{
		inf -= 1;
	}
	return inf;
}

int** BinaryTree::_makeTableW(int len, int* q, int* p)
{
	int** table = new int* [len];
	for (int i = 0; i < len; i++)
	{
		table[i] = new int[len];
		for (int j = 0; j < len; j++) table[i][j] = 0;
		table[i][i] = q[i];
	}

	for (int row = 1; row < len; row++)
	{
		for (int line = 0; line < len - row; line++)
		{
			int j = row + line;
			table[line][j] = table[line][j - 1] + p[j] + q[j];
		}
	}

	return table;
}

int** BinaryTree::_makeTableR(int len, int** W)
{
	int** C = new int* [len];
	int** R = new int* [len];
	for (int i = 0; i < len; i++)
	{
		C[i] = new int[len] {0};
		R[i] = new int[len] {0};
		C[i][i] = W[i][i];
	}

	int minSum = INT_MAX;
	int line;
	int minK = -1;
	for (int counter = 1; counter < len; counter++) {
		line = 0;
		for (int row = counter; row < len; row++)
		{
			for (int k = row; k > line; k--)
			{
				if ((C[line][k - 1] + C[k][row]) < minSum)
				{
					minSum = C[line][k - 1] + C[k][row];
					minK = k;
				}
			}
			C[line][row] = W[line][row] + minSum;
			R[line][row] = minK;
			minSum = INT_MAX;
			line++;
		}
	}

	for (int i = 0; i < len; i++)
	{
		delete[] C[i];
	}
	delete[] C;

	return R;
}

bool BinaryTree::_checkInTree(int key, BinaryTree& tree)
{
	Node* root = tree.getRoot();
	while (root != nullptr)
	{
		if (root->key == key) return true;
		if (root->key > key) root = root->left;
		else root = root->left;
	}
	return false;
}

Node* BinaryTree::_addToTree(int key, Node* nd, Node* Parent)
{
	nd = new Node(key);
	if (nd->key < Parent->key)
	{
		Parent->left = nd;
	}
	else
	{
		Parent->right = nd;
	}
	return nd;
}

Node* BinaryTree::_createOptimalTree(int* keys, int** matrix, int i, int j)
{
	Node* root;
	if (i >= j)
	{
		root = nullptr;
		return root;
	}
	else
	{
		int k = matrix[i][j];
		root = new Node(keys[k]);
		root->left = _createOptimalTree(keys, matrix, i, k - 1);
		root->right = _createOptimalTree(keys, matrix, k, j);
	}
	return root;
}

BinaryTree BinaryTree::optimalTree(int len, int* keys, int* frequency, int* q)
{

	int** W = BinaryTree::_makeTableW(len, q, keys);
	int** R = BinaryTree::_makeTableR(len, W);

	BinaryTree Tree(frequency[R[0][len - 1]]);
	Node* head = Tree.getRoot();

	Tree._root = _createOptimalTree(frequency, R, 0, len - 1);

	for (int i = 0; i < len; i++)
	{
		delete[] W[i];
		delete[] R[i];
	}
	delete[] W;
	delete[] R;
	return Tree;
}

bool BinaryTree::isBalance() const
{
	return isBalance(_root);
}


int main()
{
	int* p = new int[5];
	p[0] = -1; p[1] = 2; p[2] = 1; p[3] = 1; p[4] = 5;
	int* q = new int[5];
	q[0] = 1; q[1] = 10; q[2] = 1; q[3] = 1; q[4] = 10;
	int* frequency = new int[5];
	frequency[0] = 0; frequency[1] = 10; frequency[2] = 20; frequency[3] = 30; frequency[4] = 40;

	BinaryTree Tree = BinaryTree::optimalTree(5, p, frequency, q); 

	
	delete[] p;
	delete[] q;
	delete[] frequency;
	Tree.print();
	return 0;
}