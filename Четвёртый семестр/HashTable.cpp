#include "HashTable.h"

int HashFunction(int K, int N)
{
	int i = 1;
	int res = (K % N) + i * (1 + K % (N - 2)) % N;
	return res;
}

HashTable::HashTable(int len)
{
	if (len <= 0)
	{
		throw "HashTable can't use len less than 1";
	}
	_memory = new int* [len] {nullptr};
	_N = len;
}

HashTable::HashTable(HashTable& el)
{
	_N = el._N;
	_memory = new int* [_N] {nullptr};
	for (int i = 0; i < _N; i++)
	{
		if (el._memory[i] != nullptr)
			_memory[i] = new int{ *el._memory[i] };
	}
}

HashTable HashTable::operator=(HashTable& tb)
{
	if (&tb != this)
	{
		this->~HashTable();
		_N = tb._N;
		_memory = new int* [_N] {nullptr};
		for (int i = 0; i < _N; i++)
		{
			if (tb._memory[i] != nullptr)
				_memory[i] = new int{ *tb._memory[i] };
		}
	}
	return *this;
}

HashTable::~HashTable()
{
	if (_memory != nullptr) {
		for (int i = 0; i < _N; i++)
		{
			if (_memory[i] != nullptr)
			{
				delete _memory[i];
			}
		}
		delete[] _memory;
	}
}

bool HashTable::isExist(int position)
{
	if (_memory[position] == nullptr)
		return false;
	else
		return true;
}

bool HashTable::addElement(int key, int value)
{
	int position = HashFunction(key, _N);
	if (!isExist(position))
	{
		_memory[position] = new int{ value };
		return true;
	}

	return false;
}

bool HashTable::deleteElement(int key)
{
	int position = HashFunction(key, _N);
	if (isExist(position))
	{
		delete _memory[position];
		return true;
	}
	return false;
}

void HashTable::print()
{
	for (int i = 0; i < _N; i++)
	{
		if (_memory[i] != nullptr)
			std::cout << i << " : " << *_memory[i] << '\n';
		else
			std::cout << i << " : " << " \n";
	}
}

int* HashTable::operator[](int el)
{
	int position = HashFunction(el, _N);
	return _memory[position];
}
