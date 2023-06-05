#include "HashTable.h"

int HashFunction(int K, int N)
{
	int i = 0;
	int res = abs(K % N) + i * (1 + K % (N - 2)) % N;
	return res;
}

HashTable::HashTable(int len)
{
	if (len <= 0)
	{
		throw "HashTable can't use len less than 1";
	}
	_memory = new chain [len];
	_N = len;
}

HashTable::HashTable(HashTable& el)
{
	_N = el._N;
	_memory = new chain [_N];
	for (int i = 0; i < _N; i++)
	{
		if (el._memory[i].value != nullptr)
		{
			_memory[i].value = new int{ *el._memory[i].value };
			_memory[i].next = new int{ *el._memory[i].next };
		}
	}
}

HashTable HashTable::operator=(HashTable& tb)
{
	if (&tb != this)
	{
		this->~HashTable();
		_N = tb._N;
		_memory = new chain [_N];
		for (int i = 0; i < _N; i++)
		{
			if (tb._memory[i].value != nullptr)
			{
				_memory[i].value = new int{ *tb._memory[i].value };
			}
		}
	}
	return *this;
}

HashTable::~HashTable()
{
	if (_memory != nullptr) {
		for (int i = 0; i < _N; i++)
		{
			if (_memory[i].value != nullptr)
				delete _memory[i].value;
			if (_memory[i].next != nullptr)
				delete _memory[i].next;
		}
		delete _memory;
	}
}

bool HashTable::isExist(int position)
{
	if (position >= 0 && position < _N)
	{
		if (_memory[position].value == nullptr)
			return false;
		else
			return true;
	}
	throw "position out of range";
}

bool HashTable::addElement(int key, int value)
{
	int position = HashFunction(key, _N);
	if (!isExist(position))
	{
		_memory[position].value = new int{ value };
		return true;
	}
	else 
	{
		int pos = position;
		while (_memory[pos].next != nullptr)
			pos = *_memory[pos].next;

		for (int i = 0; i < _N; i++)
		{
			if (_memory[i].value == nullptr)
			{
				_memory[i].value = new int{ value };
				_memory[position].next = new int{ i };
				return true;
			}
		}
	}

	return false;
}

bool HashTable::deleteElement(int key)
{
	int position = HashFunction(key, _N);
	if (isExist(position))
	{
		delete _memory[position].value;
		_memory[position].value = nullptr;
		
		int pos = position;
		while (_memory[pos].next != nullptr)
		{
			_memory[pos].value = _memory[*_memory[pos].next].value;
			pos = *_memory[pos].next;
		}

		_memory[pos].value = nullptr;
		return true;
	}
	return false;
}

void HashTable::print()
{
	for (int i = 0; i < _N; i++)
	{
		if (_memory[i].value != nullptr)
			std::cout << i << " : " << *_memory[i].value << '\n';
		else
			std::cout << i << " : " << " \n";
	}
}

int* HashTable::operator[](int el)
{
	int position = HashFunction(el, _N);
	return _memory[position].value;
}
