#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>

enum Errors
{
	errorLenghtLessZero = 1,
	errorWrongSymbol,
	errorWrongIndex,
	errorIndexOutBooleanVector,
	errorWrongMatrixSizes,
};

class BoolVector
{
private:
	unsigned char *_data;
	unsigned int _len;
	unsigned int _cells;

	void _shiftLeft();
	void _shiftRight();

public: 
	BoolVector();
	BoolVector(const unsigned char* input);
	BoolVector(const char* input);
	BoolVector(const BoolVector& vec);
	BoolVector(const int len, bool var);

	~BoolVector();

	friend std::ostream& operator<< (std::ostream& out, const BoolVector& vec);
	friend std::istream& operator>> (std::istream& in, BoolVector& vec);

	void print() const;

	void inverse();
	void inverseComponent(const int pos);
	void setComponent(const int pos, const bool value);

	int countWeight() const;
	int getCell() const;
	int getLen() const;

	bool operator[](int pos) const;
	bool operator==(const BoolVector& vec);
	bool operator!=(const BoolVector& vec);
	BoolVector operator= (const BoolVector& vec);
	BoolVector operator& (const BoolVector& vec);
	BoolVector operator|(const BoolVector& vec);
	BoolVector operator^ (const BoolVector& vec);
	BoolVector operator~ ();
	BoolVector operator<< (const int shift);
	BoolVector operator>> (const int shift);
};

