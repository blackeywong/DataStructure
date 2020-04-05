#pragma once
#ifndef _BIGINTEGERINVECTOR_H
#define _BIGINTEGERINVECTOR_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

//数据结构算法与应用-C++语言描述 第六章
//Exercise 69

//use vector to store digits of every digit. sign: 1(positive) or -1(negative)
class BigInteger {
public:
	BigInteger() { digits = new vector<int>;}
	BigInteger(const string& number);
	BigInteger(const BigInteger& other):BigInteger() { copyData(other);}
	~BigInteger() { delete digits; }

	BigInteger& operator=(const BigInteger& other) { copyData(other); return *this; }

	bool operator==(const BigInteger& right) const { return equals(right); }
	bool operator!=(const BigInteger& right) const { return ! equals(right); }
	bool operator<(const BigInteger& right) const { return lessThan(right); }
	bool operator<=(const BigInteger& right) const { return lessThan(right) || equals(right); }
	bool operator>(const BigInteger& right) const { return right.lessThan(*this); }
	bool operator>=(const BigInteger& right) const { return right.lessThan(*this) || right.equals(*this); }

	BigInteger& operator+=(const BigInteger& right);
	BigInteger& operator-=(const BigInteger& right);
	BigInteger& operator*=(const BigInteger& right);
	BigInteger& operator/=(const BigInteger& right);
	BigInteger& operator%=(const BigInteger& right);

	void output(ostream& out) const;
public:
	void copyData(const BigInteger& other);
	bool equals(const BigInteger& right) const;
	bool lessThan(const BigInteger& right) const;

protected:
	//helper func. add/minus digits only, ignore sign.
	void add(const BigInteger& right);
	void minus(const BigInteger& right);
	BigInteger multiply(const BigInteger& right);
	void divide(const BigInteger& right, BigInteger& quotient, BigInteger& remainder);

	bool lessThanIgnoreSign(const BigInteger& right) const;

	vector<int>* digits;
	int sign;//1(positive) or -1(negative)
};

ostream& operator<<(ostream& out, BigInteger& bi);

#endif