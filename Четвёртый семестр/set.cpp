#include "set.h"

Set::Set() : BoolVector(256, 0)
{
	_power = 0;
}

Set::Set(const BoolVector& vc): BoolVector(vc)
{
	_power = vc.countWeight();
	if (_power > 256 || _power < 0) throw std::string("out of range");
}

Set::Set(const char* ch): BoolVector(256, 0)
{
	unsigned char pointer = ch[0];
	unsigned char counter = 0;
	while (pointer != '\0')
	{
		BoolVector::setComponent(pointer, 1);
		counter++;
		pointer = ch[counter];
	}
	_power = counter--;
}

Set::Set(const unsigned char ch): BoolVector(256, 0)
{
	BoolVector::setComponent(ch, 1);
	_power = 1;
}

Set::Set(const std::string& vec) : BoolVector(256, 0)
{
	unsigned char el;
	_power = 0;
	for (int i = 0; i < vec.length(); i++)
	{
		el = vec[i];
		if (!has(el)) 
		{
			_power += 1;
			BoolVector::setComponent(el, 1);
		}
	}
}

Set::Set(const Set& st): BoolVector(st)//??
{
	_power = st._power;
}

Set::~Set()
{

}

void Set::print()
{
	for (unsigned char i = 0; i < 255; i++)
	{
		if (BoolVector::operator[](i)) std::cout << i;
	}
}

std::string Set::getSymbols()
{
	std::string symbols;
	for (unsigned char i = 0; i < 255; i++)
	{
		if (BoolVector::operator[](i)) symbols += i;
	}
	return symbols;
}

int Set::getPower() const
{
	return _power;
}

bool Set::has(const unsigned char element_pos) const
{
	return operator[](element_pos);
}

Set& Set::operator=(const Set& st)
{
	if (this == &st) return *this;
	BoolVector::operator=(st);
	_power = st._power;
	return *this;
}

bool Set::operator==(const Set& st)
{
	return BoolVector::operator==(st);
}

bool Set::operator!=(const Set& st)
{
	return BoolVector::operator!=(st);
}

Set Set::operator|(const Set& st)
{
	Set to_ret(BoolVector::operator|(st));
	to_ret._power = to_ret.countWeight();
	return to_ret;
}

Set Set::operator&(const Set& st)
{
	Set to_ret(BoolVector::operator&(st));
	to_ret._power = to_ret.countWeight();
	return to_ret;
}

Set Set::operator/(const Set& st)
{
	Set to_ret(BoolVector::operator^(st));
	to_ret._power = to_ret.countWeight();
	return to_ret;
}

Set Set::operator~()
{
	Set to_ret(BoolVector::operator~());
	to_ret._power = 256 - _power;
	return to_ret;
}

Set Set::operator-(const unsigned char element)
{
	Set to_ret(*this);
	if (to_ret[element])
	{
		to_ret.setComponent(element, 0);
		to_ret._power -= 1;
	}
	return to_ret;
}

Set Set::operator+(const unsigned char element)
{
	Set to_ret(*this);
	if (!to_ret[element])
	{
		to_ret.setComponent(element, 1);
		to_ret._power += 1;
	}
	return to_ret;
}

std::ostream& operator<<(std::ostream& out, const Set& st)
{
	std::string outputTag[33] = 
	{ std::string("NULL"), std::string("START OF HEADING"), std::string("START OF TEXT"), std::string("END OF TEXT"),
	std::string("END OF TRANSMISSION"), std::string("ENQUIRY"), std::string("ACKNOWLEDGE"), std::string("BELL"), std::string("BACKSPASE"),
	std::string("HORIZONTAL TAB"), std::string("LINE FEED"), std::string("VERTICAL TAB"), std::string("FORM FEED"), std::string("CARRIAGE RETURN"),
	std::string("SHIFT OUT"), std::string("SHIFT IN"), std::string("DATA LINK ESCAPE"), std::string("DEVICE CONTROL 1"),
	std::string("DEVICE CONTROL 2"), std::string("DEVICE CONTROL 3"), std::string("DEVICE CONTROL 4"), std::string("NEGATIVE ACKNOWLEDGE"),
	std::string("SYNCHRONIUS IDLE"), std::string("END OF TRANS BLOCK"), std::string("CANCEL"), std::string("END OF MEDIUM"), std::string("SUBSTITUTE"),
	std::string("ESCAPE"), std::string("FILE SEPARATION"), std::string("GROUP SEPARATION"), std::string("RECORD SEPARATION"), std::string("UNIT SEPARATION"),
	std::string("SPASE") };

	for (int i = 0; i < 33; i++)
	{
		out << outputTag[i] << " " << st[i] << '\n';
	}
	for (int i = 33; i < 256; i++)
	{
		out << (unsigned char)i << " " << st[i] << '\n';
	}
	return out;
	// TODO: вставьте здесь оператор return
}

std::istream& operator>>(std::istream& in, Set& st)
{
	unsigned char inp = 'A';
	while (true)
	{
		std::cout << "Do you want to input special symbol? Y/N\n";
		in >> inp;

		if (inp == 'N')
		{
			unsigned char ch;
			in >> ch;
			st.setComponent(ch, 1);
		}
		else if (inp == 'Y')
		{
			int pos = -1;
			while (!(pos >= 0 && pos < 33))
			{
				std::cout << "Input position of special symbol 0-32\n";
				in >> pos;
			}
			st.setComponent(pos, 1);
		}
		else {
			std::cout << "Do you want to exit? Y/N\n";
			in >> inp;
			if (inp == 'Y')
				return in;
		}
	}
}
