#include "Huffman�oding.h"


Huffman�oding::Node::Node(std::string symbols)
{
	_Symbols = new Set(symbols);
}

Huffman�oding::Node::Node(char symbol)
{
	_Symbols = new Set(symbol);
}

Huffman�oding::Node::~Node()
{
	delete _Symbols;
	delete _left;
	delete _right;
}

Huffman�oding::~Huffman�oding()
{
	delete _root;
}

Huffman�oding::Node* Huffman�oding::Node::getLeft()
{
	return _left;
}

Huffman�oding::Node* Huffman�oding::Node::getRight()
{
	return _right;
}

void Huffman�oding::Node::setLeft(Huffman�oding::Node* nd)
{
	_left = nd;
}

void Huffman�oding::Node::setRight(Huffman�oding::Node* nd)
{
	_right = nd;
}

void Huffman�oding::Node::setFrequency(int freq)
{
	_frequency = freq;
}

void Huffman�oding::Node::addFrequency(int freq)
{
	_frequency += freq;
}

int Huffman�oding::Node::getFrequency()
{
	if (this != nullptr)
	{
		return _frequency;
	}
	else
		return -1;
}

Set* Huffman�oding::Node::getSymbols()
{
	return _Symbols;
}

void Huffman�oding::printCode()
{
	if (_root != nullptr)
	{
		Set* symbols;
		Node* nd = _root->getLeft();
		for (int LeftRight = 0; LeftRight < 2; LeftRight++) 
		{
			if (nd != nullptr)
			{
				symbols = nd->getSymbols();
				std::string letters = symbols->getSymbols();
				int len = letters.size();
				for (int i = 0; i < len; i++)
				{
					std::cout << letters[i] << " : " << _getWord(letters[i]) << '\n';
				}
			}
			nd = _root->getRight();
		}
	}
}

void Huffman�oding::Node::operator+=(Node* second)
{
	_frequency += second->getFrequency();
	*_Symbols = (_Symbols->operator|(*second->getSymbols()));
}

Huffman�oding::Node* Huffman�oding::Node::operator+(Node* second)
{
	//Node* toRet(*this);
	//*toRet += second;
	//return toRet;

	Node* toRet = new Node(' ');
	toRet->_frequency = _frequency + second->getFrequency();
	*toRet->_Symbols = (_Symbols->operator|(*second->getSymbols()));
	toRet->_left = this;
	toRet->_right = second;
	return toRet;
}

int Huffman�oding::_findPosition(std::vector<Node*> keys, char symbol)
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

void Huffman�oding::printTree(Huffman�oding::Node* root, int margin)
{
	if (root == nullptr) return;

	printTree(root->getRight(), margin + 8);
	std::cout << std::string(margin, ' ');
	root->getSymbols()->print();
	std::cout << ":" << root->getFrequency() << "\n";
	printTree(root->getLeft(), margin + 8);
}

void Huffman�oding::printTree()
{
	printTree(_root, 0);
	std::cout << "\n";
}

std::string Huffman�oding::_getWord(char symbol)
{
	std::string Nword = "";
	Huffman�oding::Node* pointer = _root;
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


bool comp(Huffman�oding::Node* nd1, Huffman�oding::Node* nd2)
{
	return nd1->getFrequency() > nd2->getFrequency();
}

int Huffman�oding::build(std::string& filePath, std::string& name)
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
	return letters;
}

float Huffman�oding::encode(std::string& filePath, std::string& name)
{
	int letters = 0;
	int buildCode = build(filePath, name);

	if (buildCode == -1)
		return -1;
	else
		letters = buildCode;

	std::cout << _root->getLeft()->getFrequency() << " "
		<< _root->getRight()->getFrequency();
	std::cout << "\n";
	if (_root->getLeft() != nullptr)
		_root->getLeft()->getSymbols()->print();
	if (_root->getRight() != nullptr)
		_root->getRight()->getSymbols()->print();

	unsigned char symbol;
	std::ifstream fFile;
	std::ofstream fencode(filePath + "encoded.txt");
	fFile.open(filePath + name);

	std::string code;
	int bites = 0;
	while (fFile >> std::noskipws >> symbol)
	{
		code = _getWord(symbol);
		fencode << code;
		bites += code.size();
	}
	fFile.close();
	fencode.close();
	float compressionRate = (float)bites / (letters * 8);
	return compressionRate;
}

bool Huffman�oding::decode(std::string& filePath, std::string& name)
{
	std::ifstream fFile(filePath + name);
	std::ofstream decoded(filePath + "Decoded.txt");
	if (!fFile.is_open())
		return false;

	Node* pointer = _root;
	unsigned char symbol;
	while (fFile >> symbol)
	{
		if (symbol == '0')
		{
			if (pointer->getLeft() != nullptr)
				pointer = pointer->getLeft();
			else
			{
				decoded << pointer->getSymbols()->getSymbols();
				pointer = _root->getLeft();
			}
		}
		if (symbol == '1')
		{
			if (pointer->getRight() != nullptr)
				pointer = pointer->getRight();
			else
			{
				decoded << pointer->getSymbols()->getSymbols();
				pointer = _root->getRight();
			}
		}
	}
	decoded << pointer->getSymbols()->getSymbols();

	decoded.close();
	fFile.close();
	return true;
}