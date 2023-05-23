#pragma once
#include "BoolVector.h"
#include <string>
#include<stdio.h>
#include<windows.h>

class Set: public virtual BoolVector
{
private:
	int _power;
public:
	Set();
	Set(const BoolVector& vc);
	Set(const char* ch);
	Set(const unsigned char ch);
	Set(const Set&);
	Set(const std::string& vec);
	~Set();

	void print();
	std::string getSymbols();

	int getPower() const;
	bool has(const unsigned char element_pos) const;

	Set& operator=(const Set& st);
	bool operator== (const Set& st);
	bool operator!= (const Set& st);
	Set operator| (const Set& st);
	Set operator& (const Set& st);
	Set operator/ (const Set& st);
	Set operator~ ();
	Set operator+ (const unsigned char element);
	Set operator- (const unsigned char element);

	friend std::ostream& operator<< (std::ostream& out, const Set& st);
	friend std::istream& operator>> (std::istream& in, Set& ch);
};

