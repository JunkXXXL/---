#include "HashTableTester.h"

void HashTableTester::assign(int MaxSize)
{
	HashTable table1(MaxSize);
	HashTable table2(MaxSize);

	for (int i = MaxSize; i < 2*MaxSize; i++)
	{
		table1.addElement(i, i);
	}

	table2 = table1;

	for (int i = MaxSize; i < 2 * MaxSize; i++)
	{
		table1.deleteElement(i);
		table2[i];
	}
}

void HashTableTester::destructor(int MaxSize)
{
	for (int i = 0; i < 1000000; i++)
	{
		HashTable table2(MaxSize);
		for (int i = 0; i < MaxSize; i++)
		{
			table2.addElement(i, i);
		}
	}
}

void HashTableTester::checkCollision()
{
	HashTable table(3);
	for (int i = 0; i < 100; i++)
	{
		table.addElement(i, i);
		table[i];
	}
}

void HashTableTester::checkCopy(int MaxSize)
{
	HashTable table1(MaxSize);
	for (int i = MaxSize; i < 2 * MaxSize; i++)
	{
		table1.addElement(i, i);
	}

	HashTable table2(table1);

	for (int i = MaxSize; i < 2 * MaxSize; i++)
	{
		table1.deleteElement(i);
		table2[i];
	}
}

void HashTableTester::test(int MaxSize, bool EnableOutput)
{
	if (EnableOutput == true)
	{
		std::cout << "assign is testing...\n";
		assign(MaxSize);
		std::cout << "OK\n\n";

		std::cout << "destructor is testing...\n";
		destructor(MaxSize);
		std::cout << "OK\n\n";

		std::cout << "collision is testing...\n";
		checkCollision();
		std::cout << "OK\n\n";

		std::cout << "copy is testing...\n";
		checkCopy(MaxSize);
		std::cout << "OK\n\n";
	}
	else
	{
		assign(MaxSize);
		destructor(MaxSize);
		checkCollision();
		checkCopy(MaxSize);
	}
}