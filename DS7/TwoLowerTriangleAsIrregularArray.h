#pragma once
#ifndef _TWOLOWERTRIANGLEASIRREGULARARRAY_H
#define _TWOLOWERTRIANGLEASIRREGULARARRAY_H
#include <iostream>
#include "../DS5/exceptions.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第七章
//Exercise 26
template<class T>
class TwoLowerTriangleAsIrregularArray {
	template<class T>
	friend ostream& operator<<(ostream&, const TwoLowerTriangleAsIrregularArray<T>&);
	template<class T>
	friend istream& operator>>(istream&, TwoLowerTriangleAsIrregularArray<T>&);
public:
	TwoLowerTriangleAsIrregularArray(int theN = 10);
	TwoLowerTriangleAsIrregularArray(const TwoLowerTriangleAsIrregularArray<T>& m);
	~TwoLowerTriangleAsIrregularArray();
	T getA(int i, int j) const;
	void setA(int i, int j, const T& value);
	T getB(int i, int j) const;
	void setB(int i, int j, const T& value);
private:
	void checkIndex(int i, int j) const;
	void clear();
	void initialize();
	int n;
	T** element;
};


template<class T>
void TwoLowerTriangleAsIrregularArray<T>::checkIndex(int i, int j) const {
	if (i < 1 || i> n || j <1 || j> n) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream& out, const TwoLowerTriangleAsIrregularArray<T>& m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j <= i; j++) {
			out << m.element[i][j] << " ";
		}
		out << endl;
	}
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j <= i; j++) {
			out << m.element[j][i+1] << " ";
		}
		out << endl;
	}
	return out;
}

template<class T>
istream& operator>>(istream& in, TwoLowerTriangleAsIrregularArray<T>& m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j <= i; j++) {
			if (in) {
				in >> m.element[i][j];
			}
			else
			{
				m.element[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j <= i; j++) {
			if (in) {
				in >> m.element[j][i+1];
			}
			else
			{
				m.element[j][i+1] = 0;
			}
		}
	}
	return in;
}

template<class T>
TwoLowerTriangleAsIrregularArray<T>::TwoLowerTriangleAsIrregularArray(int theN) {
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	initialize();
}

template<class T>
TwoLowerTriangleAsIrregularArray<T>::TwoLowerTriangleAsIrregularArray(const TwoLowerTriangleAsIrregularArray<T>& m) {
	n = m.n;
	initialize();
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j <= m.n+1; j++) {
			element[i][j] = m.element[i][j];
		}
	}
}

template<class T>
TwoLowerTriangleAsIrregularArray<T>::~TwoLowerTriangleAsIrregularArray() {
	clear();
}

template<class T>
void TwoLowerTriangleAsIrregularArray<T>::clear() {
	for (int i = 0; i < n; i++) {
		delete[] element[i];
	}
	delete[] element;
	element = nullptr;
}

template<class T>
void TwoLowerTriangleAsIrregularArray<T>::initialize() {
	element = new T * [n];
	for (int i = 0; i < n; i++) {
		element[i] = new T[n + 1];
	}
}

template<class T>
T TwoLowerTriangleAsIrregularArray<T>::getA(int i, int j) const {
	checkIndex(i, j);
	if (i < j) return 0;

	return element[i - 1][j - 1];
}

template<class T>
void TwoLowerTriangleAsIrregularArray<T>::setA(int i, int j, const T& value) {
	checkIndex(i, j);
	if (i >= j) element[i - 1][j - 1] = value;
	//ignore other positions
}

template<class T>
T TwoLowerTriangleAsIrregularArray<T>::getB(int i, int j) const {
	checkIndex(i, j);
	if (i < j) return 0;

	return element[j - 1][i];
}

template<class T>
void TwoLowerTriangleAsIrregularArray<T>::setB(int i, int j, const T& value) {
	checkIndex(i, j);
	if (i >= j) element[j-1][i] = value;
	//ignore other positions
}

#endif
