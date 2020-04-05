#pragma once
#ifndef _POLYNOMIALINCIRCULAR_H
#define _POLYNOMIALINCIRCULAR_H
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

//数据结构算法与应用-C++语言描述 第六章
//Exercise 71

struct PolynomialNode {
	double coeff;
	int exp;
	PolynomialNode* next;
	PolynomialNode() { coeff = 0; exp = -1; next = nullptr; }
	PolynomialNode(double theCoeff, int theExp) : coeff(theCoeff), exp(theExp) { next = nullptr; }
};

//use Circular with head node to store digits of every non-zero coefficient and exponent. 
class Polynomial {
public:
	Polynomial() { firstNode = new PolynomialNode(); this->listSize = 0; firstNode->next = firstNode; }
	Polynomial(istream& in);
	//Polynomial(const Polynomial& other) :Polynomial() { copyData(other); }
	Polynomial(const Polynomial& other) {firstNode = new PolynomialNode(); this->listSize = 0; firstNode->next = firstNode;  copyData(other); }
	~Polynomial() { clear(); }

	Polynomial& operator=(const Polynomial& other) { copyData(other); return *this; }

	int getDegree() const;
	double valueOf(const int exponent) const;
	void output(ostream& out) const;
	void clear();

	void copyData(const Polynomial& other);

	Polynomial& add(const Polynomial& right);
	Polynomial& subtract(const Polynomial& right);
	Polynomial& multiply(const Polynomial& right);
	Polynomial& divide(const Polynomial& right);
protected:
	void checkIndex(const int exponent) const;
	void BubbleSort();

	PolynomialNode* firstNode;
	int listSize;
};

ostream& operator<<(ostream& out, Polynomial& bi);
#endif