#include "HashTable.h"

int HashFunction(int K, int N)
{
	int i = 1;
	int res = ((K % N) + i * (1 + K % (N - 2))) % N;
	return abs(res);
}

HashTable::HashTable(int len)
{
	if (len <= 2)
	{
		throw "HashTable can't use len less than 3";
	}
	_memory = new chain[len];
	_N = len;
}

HashTable::HashTable(HashTable& other)
{
	_N = other._N;
	_memory = new chain[_N];
	for (int i = 0; i < _N; i++)
	{
		if (other._memory[i].value != nullptr)
		{
			_memory[i].value = new int{ *other._memory[i].value };
			_memory[i].key = new int{ *other._memory[i].key };

			chain* thisPointer = _memory[i].next;
			chain* otherPointer = other._memory[i].next;
			while (otherPointer != nullptr)
			{
				thisPointer = new chain;
				thisPointer->key = new int{ *otherPointer->key };
				thisPointer->value = new int{ *otherPointer->value };
				thisPointer->next = nullptr;

				thisPointer = thisPointer->next;
				otherPointer = otherPointer->next;
			}
		}
		
	}
}

HashTable HashTable::operator=(HashTable& other)
{
	if (&other != this)
	{
		this->~HashTable();
		_N = other._N;
		_memory = new chain[_N];
		for (int i = 0; i < _N; i++)
		{
			if (other._memory[i].value != nullptr)
			{
				_memory[i].value = new int{ *other._memory[i].value };
				_memory[i].key = new int{ *other._memory[i].key };

				chain* thisPointer = _memory[i].next;
				chain* otherPointer = other._memory[i].next;
				while (otherPointer != nullptr)
				{
					thisPointer = new chain;
					thisPointer->key = new int{ *otherPointer->key };
					thisPointer->value = new int{ *otherPointer->value };
					thisPointer->next = nullptr;

					thisPointer = thisPointer->next;
					otherPointer = otherPointer->next;
				}
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
			{
				delete _memory[i].value;
				delete _memory[i].key;
			}
			chain* pointer = _memory[i].next;
			while (pointer != nullptr)
			{
				chain* deletePointer = pointer;
				pointer = pointer->next;
				delete deletePointer->value;
				delete deletePointer->key;
				delete deletePointer;
			}
		}
		delete _memory;
	}
}

bool HashTable::isFull()
{
	for (int i = 0; i < _N; i++)
	{
		if (_memory[i].value == nullptr)
			return false;
	}
	return true;
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
		_memory[position].key = new int{ key };
		return true;
	}
	else
	{
		chain* pointer = _memory[position].next;
		chain* prev = &_memory[position];
		while (pointer != nullptr) {
			prev = pointer;
			pointer = pointer->next;
		}
		
		prev->next = new chain;
		pointer = prev->next;
		pointer->key = new int{ key };
		pointer->value = new int{ value };
		return true;
	}

	return false;
}

bool HashTable::deleteElement(int key)
{
	int position = HashFunction(key, _N);
	if (isExist(position))
	{
		chain* pointer = &_memory[position];
		chain* prePointer = pointer;

		while (*pointer->key != key)
		{
			if (pointer->next != nullptr) 
			{
				prePointer = pointer;
				pointer = pointer->next;
			}
			else
				return false;
		}

		if (prePointer == pointer)
		{
			delete pointer->value;
			delete pointer->key;
			_memory[position] = *_memory[position].next;
		}
		else
		{
			prePointer->next = pointer->next;

			delete pointer->value;
			delete pointer->key;
			delete pointer;
		}
		return true;
	}
	return false;
}

void HashTable::print()
{
	for (int i = 0; i < _N; i++)
	{
		if (_memory[i].value != nullptr) {
			std::cout << HashFunction(i, _N) << " => " 
				<< *_memory[i].key << " : " << *_memory[i].value;
			chain* pointer = _memory[i].next;
			while (pointer != nullptr)
			{
				std::cout << " -> " << *pointer->key << " : " << *pointer->value;
				pointer = pointer->next;
			}
			std::cout << '\n';
		}
	}
}

int& HashTable::operator[](int key)
{
	int position = HashFunction(key, _N);
	if (_memory[position].value == nullptr)
		throw "key is not found";
	if (*_memory[position].key == key)
		return *_memory[position].value;

	chain* pointer = _memory[position].next;
	while (pointer != nullptr)
	{
		if (*pointer->key == key)
			return *pointer->value;
		pointer = pointer->next;
	}

	throw "key is not found";
}
