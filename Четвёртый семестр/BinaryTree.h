#pragma once
#include "Node.h"
#include <vector>

class BinaryTree
{
private:
	Node* _root = nullptr;

	int sumKeys(Node* nd) const;
	int maxKey(Node* usel) const;
	int minKey(Node* usel = nullptr) const;
	int nodeCount(Node* usel = nullptr) const;

public:

	BinaryTree() {_root = new Node(0); }
	BinaryTree(BinaryTree* tree);
	BinaryTree(int root_key);
	~BinaryTree();
	
	void addNode();
	bool deleteNode();
	Node& findNode();

	const Node* getRoot() const;
	void clean(Node* usel = nullptr);
	bool isEmpty();
	int getHigth(Node* usel = nullptr) const;
	BinaryTree& copyUnderTree(Node* usel = nullptr);
	int nodeCount() const;
	int maxKey() const;
	int minKey() const;
	void addNodeRandomly(Node* usel = nullptr);
	bool isBalance(Node* usel = nullptr) const;
	int sumKeys() const;
	int getNodesLevel(Node * usel) const;
	std::vector<int>& getVector(Node* usel = nullptr) const;
	void print() const;
	void printLeaf(Node* usel = nullptr) const;

};