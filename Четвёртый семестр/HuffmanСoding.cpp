#include "Huffman—oding.h"


Huffman—oding::Node::Node(std::string symbols)
{
	_Symbols = new Set(symbols);
}

Huffman—oding::Node::Node(char symbol)
{
	_Symbols = new Set(symbol);
}

Huffman—oding::Node::~Node()
{
	delete _Symbols;
	delete _left;
	delete _right;
}

Huffman—oding::~Huffman—oding()
{
	delete _root;
}

Huffman—oding::Node* Huffman—oding::Node::getLeft()
{
	return _left;
}

Huffman—oding::Node* Huffman—oding::Node::getRight()
{
	return _right;
}

void Huffman—oding::Node::setLeft(Huffman—oding::Node* nd)
{
	_left = nd;
}

void Huffman—oding::Node::setRight(Huffman—oding::Node* nd)
{
	_right = nd;
}

void Huffman—oding::Node::setFrequency(int freq)
{
	_frequency = freq;
}

void Huffman—oding::Node::addFrequency(int freq)
{
	_frequency += freq;
}

int Huffman—oding::Node::getFrequency()
{
	return _frequency;
}

Set* Huffman—oding::Node::getSymbols()
{
	return _Symbols;
}

void Huffman—oding::Node::operator+=(Node* second)
{
	// freq = a + b - ab
	int a = _Symbols->countWeight();
	int b = second->_Symbols->countWeight();
	int ab = (_Symbols->operator&(*second->_Symbols)).countWeight();
	_frequency = a + b - ab;
	*_Symbols = (_Symbols->operator|(*second->getSymbols()));
}

Huffman—oding::Node* Huffman—oding::Node::operator+(Node* second)
{
	Node* toRet = new Node(' ');

	int a = _Symbols->countWeight();
	int b = second->_Symbols->countWeight();
	int ab = (_Symbols->operator&(*second->_Symbols)).countWeight();
	toRet->_frequency = a + b - ab;
	*toRet->_Symbols = (_Symbols->operator|(*second->getSymbols()));
	return toRet;
}

int Huffman—oding::_findPosition(std::vector<Node*> keys, char symbol)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (keys[i]->getSymbols()->has(symbol))
		{
			return i;
		}
	}
	return -1;
}

std::string Huffman—oding::_getWord(char symbol)
{
	std::string Nword = "";
	Huffman—oding::Node* pointer = _root;
	while (true)
	{
		if (pointer->getLeft() == nullptr && pointer->getRight() == nullptr)
			return Nword;
		if (pointer->getLeft() != nullptr)
		{
			if (pointer->getLeft()->getSymbols()->has(symbol)) 
			{
				Nword += "0";
				pointer = pointer->getLeft();
				continue;
			}
		}
		if (pointer->getRight() != nullptr)
		{
			if (pointer->getRight()->getSymbols()->has(symbol))
			Nword += "1";
			pointer = pointer->getRight();
			continue;
		}
	}
	return Nword;
}

void Huffman—oding::build()
{

}

bool comp(Huffman—oding::Node* nd1, Huffman—oding::Node* nd2)
{
	return nd1->getFrequency() > nd2->getFrequency();
}

int Huffman—oding::encode(std::string& filePath, std::string& name)
{
	std::ifstream fFile(filePath + name);
	if (!fFile.is_open())
		return -1;
	
	std::vector<Node*> keys;
	Set elements;
	unsigned char symbol;
	int pos;
	int letters = 0;

	while (fFile >> std::noskipws >> symbol)
	{
		if (!elements.has(symbol))
		{
			elements = elements + symbol;
			keys.push_back(new Node(symbol));
		}
		else
		{
			pos = _findPosition(keys, symbol);
			keys[pos]->addFrequency(1);
		}
		letters++;
	}
	sort(keys.begin(), keys.end(), comp);
	fFile.close();

	Node* frst;
	Node* secnd;
	while (keys.size() > 2)
	{
		frst = keys[keys.size() - 1];
		secnd = keys[keys.size() - 2];
		keys.pop_back(); keys.pop_back();
		keys.push_back(frst->operator+(secnd));
		sort(keys.begin(), keys.end(), comp);
	}
	_root = new Node(" ");
	if (keys.size() > 0)
	{
		_root->setRight(keys[keys.size() - 1]);
		keys.pop_back();
	}
	if (keys.size() > 0)
	{
		_root->setLeft(keys[0]);
		keys.pop_back();
	}

	std::cout << _root->getLeft()->getFrequency() << " "
		<< _root->getRight()->getFrequency();
	std::cout << "\n";
	_root->getLeft()->getSymbols()->print();
	_root->getRight()->getSymbols()->print();

	std::ofstream fencode(filePath + "encoded.txt");
	fFile.open(filePath + name);

	std::string code;
	while (fFile >> std::noskipws >> symbol)
	{
		code = _getWord(symbol);
		fencode << code;
	}
	fFile.close();
	fencode.close();
	return 0;
}

bool Huffman—oding::decode(std::string& fileName)
{
	return false;
}