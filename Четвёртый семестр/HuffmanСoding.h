#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "set.h"

class Huffman—oding
{
public:

	class Node
	{
	public:
		Node(std::string symbols);
		Node(char symbol);
		~Node();
		Node* getLeft();
		Node* getRight();
		void setLeft(Huffman—oding::Node* nd);
		void setRight(Huffman—oding::Node* nd);
		void setFrequency(int freq);
		void addFrequency(int freq);
		int getFrequency();
		Set* getSymbols();
		void operator+=(Node* second);
		Node* operator+(Node* second);

	private:
		Set* _Symbols;
		int _frequency = 1;
		Node* _right = nullptr;
		Node* _left = nullptr;
	};
	~Huffman—oding();
	void build();
	float encode(std::string& filePath, std::string& name);
	bool decode(std::string& filePath, std::string& name);
	void printTree();

private:
	void printTree(Huffman—oding::Node* root, int margin);
	//BinaryTree tree;
	Huffman—oding::Node* _root = nullptr;
	int _findPosition(std::vector<Node*> keys, char symbol);
	std::string _getWord(char symbol);
};

