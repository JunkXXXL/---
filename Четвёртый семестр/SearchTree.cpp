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
	Node* runner = findNode(key);
	if (runner == nullptr)
		return false;

	Node* parent = _findParent(key);
	
	if (runner->getChildrenCount() == 0)
	{
		if (parent != nullptr) 
		{
			if (parent->left == runner)
				parent->left = nullptr;
			else
				parent->right = nullptr;
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




std::vector<std::vector<int>> SearchTree::_makeTableW(int len, std::vector<int> q, std::vector<int> p)
{
	std::vector<std::vector<int>> table;
	for (int i = 0; i < len; i++)
	{
		table.push_back(std::vector<int>());
		for (int j = 0; j < len; j++) table[i].push_back(0);
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

std::vector<std::vector<int>> SearchTree::_makeTableR(int len, std::vector<std::vector<int>> W)
{
	std::vector<std::vector<int>> C;
	std::vector<std::vector<int>> R;
	for (int i = 0; i < len; i++)
	{
		C.push_back(std::vector<int>());
		R.push_back(std::vector<int>());
		for (int j = 0; j < len; j++) C[i].push_back(0);
		for (int j = 0; j < len; j++) R[i].push_back(0);
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

	return R;
}

bool SearchTree::_checkInTree(int key, SearchTree& tree)
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

Node* SearchTree::_addToTree(int key, Node* nd, Node* Parent)
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

Node* SearchTree::_createOptimalTree(std::vector<int> keys, std::vector<std::vector<int>> matrix, int i, int j)
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

SearchTree SearchTree::optimalTree(int len, std::vector<int> keys, std::vector<int> frequency, std::vector<int> q)
{

	std::vector<std::vector<int>> W = SearchTree::_makeTableW(len, q, keys);
	std::vector<std::vector<int>> R = SearchTree::_makeTableR(len, W);

	SearchTree Tree(frequency[R[0][len - 1]]);
	Node* head = Tree.getRoot();

	Tree._root = _createOptimalTree(frequency, R, 0, len - 1);

	return Tree;
}

int main14()
{
	std::vector<int> p;
	p.push_back(-1); p.push_back(2); p.push_back(1);
	p.push_back(1); p.push_back(5);
	std::vector<int> q;
	q.push_back(1); q.push_back(10); q.push_back(1);
	q.push_back(1); q.push_back(10);
	std::vector<int> frequency;
	frequency.push_back(0); frequency.push_back(10);
	frequency.push_back(20); frequency.push_back(30);
	frequency.push_back(40);

	SearchTree Tree = SearchTree::optimalTree(5, p, frequency, q);

	Tree.print();
	return 0;
}