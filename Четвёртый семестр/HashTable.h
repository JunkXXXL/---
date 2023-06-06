#pragma once
#include <iostream>
#include <string>

struct chain
{
	int* value = nullptr;
	int* key = nullptr;
	chain* next = nullptr;
};

class HashTable
{
public:
	HashTable() {};
	HashTable(int len);
	HashTable(HashTable& el);
	~HashTable();

	bool addElement(int key, int value);
	bool deleteElement(int key);
	bool isExist(int position);
	bool isFull();
	void print();
	HashTable operator=(HashTable& tb);
	int* operator[](int el);

private:
	chain* _memory = nullptr;
	int _N = 0;
};


