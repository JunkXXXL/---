#pragma once
#include "Node.h"
#include <vector>
#include <iostream>

class BinaryTree
{
private:
	Node* _root = nullptr;

	int sumKeys(Node* node) const;
	int maxKey(Node* usel) const;
	int minKey(Node* usel) const;
	int nodeCount(Node* usel) const;
	int getHeigth(Node* usel) const;
	void clear(Node* usel);
	void printLeaf(Node* usel) const;
	void addNodeRandomly(Node* usel, int value);

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
	BinaryTree copyUnderTree(Node* usel = nullptr);
	int nodeCount() const;
	int maxKey() const;
	int minKey() const;
	void addNodeRandomly(int value);
	bool isBalance(Node* usel = nullptr) const;
	int sumKeys() const;
	int getNodesLevel(Node * usel) const;
	std::vector<int> getVector(Node* usel = nullptr) const;
	void print() const;
	void printLeaf() const;
	BinaryTree& operator=(BinaryTree& other);

};