#pragma once
#ifndef _POLYNOMIALINVECTOR_H
#define _POLYNOMIALINVECTOR_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

//数据结构算法与应用-C++语言描述 第六章
//Exercise 70

//use vector to store digits of every coefficient. The index is the exponent. 
class PolynomialInVector {
public:
	PolynomialInVector() { coefficients = new vector<int>; this->degree = 0; }
	PolynomialInVector(istream& in);
	PolynomialInVector(const PolynomialInVector& other) :PolynomialInVector() { copyData(other); }
	~PolynomialInVector() { delete coefficients; }

	PolynomialInVector& operator=(const PolynomialInVector& other) { copyData(other); return *this; }

	int getDegree() const { return this->degree; }
	int valueOf(const int exponent) const { checkIndex(exponent); return  (*coefficients)[exponent]; }
	void output(ostream& out) const;

	void copyData(const PolynomialInVector& other);

	PolynomialInVector& add(const PolynomialInVector& right);
	PolynomialInVector& subtract(const PolynomialInVector& right);
	PolynomialInVector& multiply(const PolynomialInVector& right);
	PolynomialInVector& divide(const PolynomialInVector& right);
protected:
	void checkIndex(const int exponent) const;
	vector<int>* coefficients;
	int degree;
};

ostream& operator<<(ostream& out, PolynomialInVector& bi);
#endif