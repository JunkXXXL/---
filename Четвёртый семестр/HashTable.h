#pragma once
#include <iostream>
#include <string>

struct chain
{
	int* value = nullptr;
	int* next = nullptr;
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
	void print();
	HashTable operator=(HashTable& tb);
	int* operator[](int el);

private:
	chain* _memory = nullptr;
	int _N = 0;
	int i = 0;
};


