#pragma once
#include "BinaryTree.h"
#include "SearchTreeIterator.h"

class SearchTree: public BinaryTree
{
	private:
		void addNode(int key, Node* node);
		Node* findNode(int value, Node* node) const;
		Node* _findParent(int key);
		Node* _getMinKey(Node* node);

	public:
		SearchTree() { _root = new Node(0); }
		SearchTree(const SearchTree& tree);
		SearchTree(Node* node);
		SearchTree(int key) { _root = new Node(key); }

		void addNode(int key) override;
		bool deleteNode(int key) override;
		SearchTree copyUnderTree(Node* node = nullptr) ;
		int minKey() const override;
		int maxKey() const override;
		Node* findNode(int value) const override;
		int getHeigthNode(Node* nd = nullptr) const;
		SearchTree& operator=(const SearchTree& other);
		std::vector<int> getVector() const override;

		friend class SearchTreeIterator;
};

