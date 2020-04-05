#pragma once
#ifndef _BIGINTEGERINDOUBLE_H
#define _BIGINTEGERINDOUBLE_H
#include <algorithm>
#include <string>
#include <iostream>
#include "../extendedouble.h"

using namespace std;
//the lastNode is the lowest digits
class BigIntegerInDouble : public ExtendedDouble<int> {
public:
	BigIntegerInDouble() : ExtendedDouble<int>() {}
	BigIntegerInDouble(const string& number);
	BigIntegerInDouble(const BigIntegerInDouble& other) :BigIntegerInDouble() { copyData(other); }

	BigIntegerInDouble& operator=(const BigIntegerInDouble& other) { copyData(other); return *this; }

	bool operator==(const BigIntegerInDouble& right) const { return equals(right); }
	bool operator!=(const BigIntegerInDouble& right) const { return !equals(right); }
	bool operator<(const BigIntegerInDouble& right) const { return lessThan(right); }
	bool operator<=(const BigIntegerInDouble& right) const { return lessThan(right) || equals(right); }
	bool operator>(const BigIntegerInDouble& right) const { return right.lessThan(*this); }
	bool operator>=(const BigIntegerInDouble& right) const { return right.lessThan(*this) || right.equals(*this); }

	BigIntegerInDouble& operator+=(const BigIntegerInDouble& right);
	BigIntegerInDouble& operator-=(const BigIntegerInDouble& right);
	BigIntegerInDouble& operator*=(const BigIntegerInDouble& right);
	BigIntegerInDouble& operator/=(const BigIntegerInDouble& right);
	BigIntegerInDouble& operator%=(const BigIntegerInDouble& right);

	void output(ostream& out) const;
public:
	void copyData(const BigIntegerInDouble& other);
	bool equals(const BigIntegerInDouble& right) const;
	bool lessThan(const BigIntegerInDouble& right) const;

protected:
	//helper func. add/minus digits only, ignore sign.
	void add(const BigIntegerInDouble& right);
	void minus(const BigIntegerInDouble& right);
	BigIntegerInDouble multiply(const BigIntegerInDouble& right);
	void divide(const BigIntegerInDouble& right, BigIntegerInDouble& quotient, BigIntegerInDouble& remainder);
	void removeLeadingZero();

	bool lessThanIgnoreSign(const BigIntegerInDouble& right) const;

	int sign;//1(positive) or -1(negative)
};

ostream& operator<<(ostream& out, BigIntegerInDouble& bi);

BigIntegerInDouble operator+(BigIntegerInDouble& left, BigIntegerInDouble& right);
BigIntegerInDouble operator-(BigIntegerInDouble& left, BigIntegerInDouble& right);
BigIntegerInDouble operator*(BigIntegerInDouble& left, BigIntegerInDouble& right);
BigIntegerInDouble operator/(BigIntegerInDouble& left, BigIntegerInDouble& right);
BigIntegerInDouble operator%(BigIntegerInDouble& left, BigIntegerInDouble& right);

#endif