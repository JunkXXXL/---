#pragma once
class Node
{

private:

	Node* left = nullptr, * right = nullptr;
	int key;

public:

	Node(int k, int n, Node* pr = nullptr, Node* l = nullptr, Node* r = nullptr) { key = k; left = l; right = r; };
	Node(int k) { key = k; };
	Node() { key = 0; }
	Node(Node* nd);

	int getKey() const;
	int getChildrenCount() const;

	friend class BinaryTree;
	friend class BinaryTreeIterator;
};

