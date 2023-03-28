#pragma once
#include "Node.h"
#include <vector>

class BinaryTree
{
private:
	Node* _root = nullptr;

public:

	BinaryTree() {_root = nullptr; }
	BinaryTree(BinaryTree* tree);
	BinaryTree(int root_key);
	~BinaryTree();
	
	void addNode();
	bool deleteNode();
	Node& findNode();

	Node* getRoot() const;
	void clean(Node* usel = nullptr);
	bool isEmpty(Node* usel = nullptr);
	int getHigth(Node* usel = nullptr) const;
	BinaryTree& copyUnderTree(Node* usel = nullptr);
	int nodeCount(Node* usel = nullptr) const;
	int maxKey(Node* usel = nullptr) const;
	int minKey(Node* usel = nullptr) const;
	void addNodeRandomly(Node* usel = nullptr);
	bool isBalance(Node* usel = nullptr) const;
	int sumKeys() const;
	int getNodesLevel(Node * usel) const;
	std::vector<int>& getVector(Node* usel = nullptr) const;
	void print() const;
	void printLeaf(Node* usel = nullptr) const;

};