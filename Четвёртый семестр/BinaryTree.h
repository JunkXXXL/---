#pragma once
#include "Node.h"
#include <vector>
#include <iostream>
#include "BinaryTreeIterator.h"

class BinaryTree
{
public:
	int size() const;
	BinaryTree() {_root = new Node(0); }
	BinaryTree(const BinaryTree& tree);
	BinaryTree(Node* nd);
	BinaryTree(int root_key);
	virtual ~BinaryTree();
	
	virtual bool deleteNode(int key);
	virtual Node* findNode(int value) const;

	Node* getRoot() const;
	void clear();
	bool isEmpty();
	int getHeigth() const;
	BinaryTree copyUnderTree(Node* node = nullptr);
	int nodeCount() const;
	virtual int maxKey() const;
	virtual int minKey() const;
	virtual void addNode(int value);
	bool isBalance() const;
	int sumKeys() const;
	int getNodeLevel(Node * node) const;
	virtual std::vector<int> getVector() const;
	void printLeaf() const;
	BinaryTree& operator=(const BinaryTree& other);
	void print() const;

	//static SearchTree& toBalance(SearchTree* tree);
	static BinaryTree optimalTree(int len, int* keys, int* frequency, int* q);
	static int** _makeTableW(int len, int* q, int* p);
	static int** _makeTableR(int len, int** W);
	static bool _checkInTree(int key, BinaryTree& tree);
	static Node* _addToTree(int key, Node* nd, Node* Parent);
	static Node* _createOptimalTree(int* keys, int** matrix, int i, int j);

	friend class BinaryTreeTesterclass;

protected:
	Node* _root = nullptr;

	int sumKeys(Node* node) const;
	int maxKey(Node* node) const;
	int minKey(Node* node) const;
	int nodeCount(Node* node) const;
	int getHeigth(Node* node) const;
	void clear(Node* node);
	void printLeaf(Node* node) const;
	void addNode(Node* node, int value);
	int isBalance(Node* node) const;
	void print(Node* root, int marginLeft, int levelSpacing) const;

	Node* _goDown(Node* node);
	bool _instructionToDeleteNodeWithTwoChild(const Node* node, BinaryTreeIterator iter);
	bool _instructionToDeleteRootWithTwoChild(const Node* node, BinaryTreeIterator iter);
	bool _instructionToDeleteNodeWithOneChild(const Node* node, BinaryTreeIterator iter);
	bool _instructionToDeleteRootWithOneChild(const Node* node, BinaryTreeIterator iter);
};