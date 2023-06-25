#pragma once
#include "HashTable.h"

class HashTableTester
{
public:
	HashTableTester() {};
	~HashTableTester() {};

	void test(int MaxSize, bool EnableOutput);

	void assign(int MaxSize);
	void destructor(int MaxSize);
	//void add();
	//void remove();
	//void search();
	void checkCollision();
	//void checkRemoveElement();
	void checkCopy(int MaxSize);
};

