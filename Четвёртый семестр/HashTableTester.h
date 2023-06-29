#pragma once
#include "HashTable.h"
#include <random>
#include <vector>
#include <set>

class HashTableTester
{
public:
	HashTableTester() {};
	~HashTableTester() {};

	void test(int MaxSize, bool EnableOutput);

	void assign(int MaxSize);
	void destructor(int MaxSize);
	void add(int MaxSize);
	void checkRemove(int MaxSize);
	void search(int MaxSize);
	void checkCollision();
	void checkCopy(int MaxSize);
};

