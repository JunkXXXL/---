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

		//static SearchTree& toBalance(SearchTree* tree);
		static SearchTree optimalTree(int len, std::vector<int> keys, std::vector<int> frequency, std::vector<int> q);
		static std::vector<std::vector<int>> _makeTableW(int len, std::vector<int> q, std::vector<int> p);
		static std::vector<std::vector<int>> _makeTableR(int len, std::vector<std::vector<int>> W);
		static bool _checkInTree(int key, SearchTree& tree);
		static Node* _addToTree(int key, Node* nd, Node* Parent);
		static Node* _createOptimalTree(std::vector<int> keys, std::vector<std::vector<int>> matrix, int i, int j);

		friend class SearchTreeIterator;
};

