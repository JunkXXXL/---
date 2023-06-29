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
	if (table.addElement(10, 10))
		std::cout << "Error. Copy element was added \n";
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

void HashTableTester::checkRemove(int MaxSize)
{
	srand(time(0));
	std::vector<int> vec;
	HashTable table(MaxSize);
	int value = 0;

	std::random_device rd;
	std::mt19937 g(rd());

	for (int i = 0; i < MaxSize; i++)
	{
		value = MaxSize + rand() % (2*MaxSize);
		vec.push_back(value);
		table.addElement(value, value);
	}
	
	int position = 0;
	std::shuffle(vec.begin(), vec.end(), g);
	while (position != vec.size())
	{
		if (table._getElement(vec[position]) == nullptr)
		{
			if (table.deleteElement(vec[position]) == false)
			{
				//всё окей, нормальное поведение функции, 
				//не может удалить элемент, которого нет
			}
			else
			{
				std::cout << "Check remove error, deleted dublicate chain ";
			}
		}
		else
		{
			if (table.deleteElement(vec[position]) == true)
			{
				//функция удалила эллемент
			}
			else
			{
				std::cout << "Check remove error, didn't delete chain";
			}
		}
		position++;
	}
}

void HashTableTester::add(int MaxSize)
{
	srand(time(0));
	HashTable table1(MaxSize);
	int value = 0;
	std::set<int> keys;

	for (int i = 0; i < MaxSize; i++)
	{
		value = MaxSize + rand() % MaxSize;
		if (!keys.count(value))
		{
			if (table1.addElement(value, value) == false)
			{
				std::cout << "Check add error, key can't be added ";
			}
			keys.insert(value);
		}
	}
}

void HashTableTester::search(int MaxSize)
{
	srand(time(0));
	HashTable table1(MaxSize);
	int value = 0;
	std::set<int> keys;
	std::vector<int> vec;

	for (int i = 0; i < MaxSize; i++)
	{
		value = MaxSize + rand() % MaxSize;
		if (!keys.count(value))
		{
			table1.addElement(value, value);
			keys.insert(value);
			vec.push_back(value);
		}
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(vec.begin(), vec.end(), g);

	int counter = 0;
	while (counter < vec.size())
	{
		table1[vec[counter]];
		counter++;
	}
}

void HashTableTester::test(int MaxSize, bool EnableOutput)
{
	if (EnableOutput == true)
	{
		std::cout << "assign is testing...";
		assign(MaxSize);
		std::cout << "OK\n";

		std::cout << "destructor is testing...";
		destructor(MaxSize);
		std::cout << "OK\n";

		std::cout << "Remove is testing...";
		checkRemove(MaxSize);
		std::cout << "OK\n";
		
		std::cout << "search is testing...";
		search(MaxSize);
		std::cout << "OK\n";

		std::cout << "Add is testing...";
		add(MaxSize);
		std::cout << "OK\n";

		std::cout << "collision is testing...";
		checkCollision();
		std::cout << "OK\n";

		std::cout << "copy is testing...";
		checkCopy(MaxSize);
		std::cout << "OK\n";
	}
	else
	{
		assign(MaxSize);
		checkRemove(MaxSize);
		destructor(MaxSize);
		checkCollision();
		checkCopy(MaxSize);
	}
}