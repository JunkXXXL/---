#pragma once
#include "Node.h"
#include <vector>
#include <iostream>

class BinaryTree
{
private:
	Node* _root = nullptr;

	int sumKeys(Node* node) const;
	int maxKey(Node* node) const;
	int minKey(Node* node) const;
	int nodeCount(Node* node) const;
	int getHeigth(Node* node) const;
	void clear(Node* node);
	void printLeaf(Node* node) const;
	void addNodeRandomly(Node* node, int value);

public:

	BinaryTree() {_root = new Node(0); }
	BinaryTree(BinaryTree* tree);
	BinaryTree(Node* nd);
	BinaryTree(int root_key);
	~BinaryTree();
	
	void addNode();
	bool deleteNode();
	const Node* findNode(int value) const;

	const Node* getRoot() const;
	void clear();
	bool isEmpty();
	int getHeigth() const;
	BinaryTree copyUnderTree(Node* node = nullptr);
	int nodeCount() const;
	int maxKey() const;
	int minKey() const;
	void addNodeRandomly(int value);
	ChildsInfo isBalance(Node* node = nullptr) const;
	bool isBalance() const;
	int sumKeys() const;
	int getNodeLevel(Node * node) const;
	std::vector<int> getVector() const;
	void print() const;
	void printLeaf() const;
	BinaryTree& operator=(BinaryTree& other);

};