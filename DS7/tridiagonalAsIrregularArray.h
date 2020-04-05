#pragma once
#ifndef _TIRDIAGONALASIRREGULARARRAY_H
#define _TIRDIAGONALASIRREGULARARRAY_H
#include <iostream>
#include "../DS5/exceptions.h"
#include "matrix.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第七章
//Exercise 25
template<class T>
class tridiagonalAsIrregularArray {
	template<class T>
	friend ostream& operator<<(ostream&, const tridiagonalAsIrregularArray<T>&);
	template<class T>
	friend istream& operator>>(istream&, tridiagonalAsIrregularArray<T>&);
public:
	tridiagonalAsIrregularArray(int theN = 10);
	tridiagonalAsIrregularArray(const tridiagonalAsIrregularArray<T>& m);
	~tridiagonalAsIrregularArray();
	T get(int i, int j) const;
	void set(int i, int j, const T& value);
	tridiagonalAsIrregularArray<T>& operator=(const tridiagonalAsIrregularArray<T>&);
	tridiagonalAsIrregularArray<T> operator+(const tridiagonalAsIrregularArray<T>&) const;
	tridiagonalAsIrregularArray<T> operator-(const tridiagonalAsIrregularArray<T>&) const;
	matrix<T> operator*(const tridiagonalAsIrregularArray<T>&) const;
	tridiagonalAsIrregularArray<T> transpose();
private:
	void checkIndex(int i, int j) const;
	void clear();
	void initialize();
	int n;
	T** element;
};


template<class T>
void tridiagonalAsIrregularArray<T>::checkIndex(int i, int j) const {
	if (i < 1 || i> n || j <1 || j> n) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream& out, const tridiagonalAsIrregularArray<T>& m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			if (i == j || i - j == 1 || i - j == -1) {
				if (i == 0 || i == 1) out << m.element[i][j];
				else out << m.element[i][j - i + 1]; //j - (i-1)
			}
			else out << " ";
			out << " ";
		}
		out << endl;
	}

	return out;
}

template<class T>
istream& operator>>(istream& in, tridiagonalAsIrregularArray<T>& m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < 3; j++) {
			if ((i == 0 || i == m.n - 1) && j == 2) break;
			if (in) {
				in >> m.element[i][j];
			}
			else
			{
				m.element[i][j] = 0;
			}
		}
	}

	return in;
}

template<class T>
tridiagonalAsIrregularArray<T>::tridiagonalAsIrregularArray(int theN) {
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	initialize();
}

template<class T>
tridiagonalAsIrregularArray<T>::tridiagonalAsIrregularArray(const tridiagonalAsIrregularArray<T>& m){
	n = m.n;
	initialize();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			if ((i == 0 || i == m.n - 1) && j == 2) break;
			element[i][j] = m.element[i][j];
		}
	}
}

template<class T>
tridiagonalAsIrregularArray<T>::~tridiagonalAsIrregularArray() {
	clear();
}

template<class T>
void tridiagonalAsIrregularArray<T>::clear() {
	for (int i = 0; i < n; i++) {
		delete[] element[i];
	}
	delete[] element;
	element = nullptr;
}

template<class T>
void tridiagonalAsIrregularArray<T>::initialize() {
	element = new T * [n];
	for (int i = 0; i < n; i++) {
		if(i == 0 || i == n - 1)
			element[i] = new T[2];
		else
			element[i] = new T[3];
	}
}

template<class T>
T tridiagonalAsIrregularArray<T>::get(int i, int j) const {
	checkIndex(i, j);
	switch (i - j) {
	case 1: 
	case 0: 
	case -1:  
		if (i == 1 || i == 2) return element[i-1][j-1];
		else return element[i-1][j - i + 1]; //j - (i-1)
	default: return 0;
	}
}

template<class T>
void tridiagonalAsIrregularArray<T>::set(int i, int j, const T& value) {
	checkIndex(i, j);
	switch (i - j) {
	case 1: 
	case 0: 
	case -1: 
		if (i == 1 || i == 2) element[i-1][j-1] = value;
		else element[i-1][j - i + 1] = value;
		break;
	default: break;//ignore other positions
	}
}

template<class T>
tridiagonalAsIrregularArray<T>& tridiagonalAsIrregularArray<T>::operator=(const tridiagonalAsIrregularArray<T> & m) {
	if (&m == this) return *this;
	clear();
	n = m.n;
	initialize();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			if ((i == 0 || i == n - 1) && j == 2) break;
			element[i][j] = m.element[i][j];
		}
	}
	return *this;
}

template<class T>
tridiagonalAsIrregularArray<T> tridiagonalAsIrregularArray<T>::operator+(const tridiagonalAsIrregularArray<T> & m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");

	tridiagonalAsIrregularArray<T> result(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			if ((i == 0 || i == n - 1) && j == 2) break;
			result.element[i][j] = element[i][j] + m.element[i][j];
		}
	}
	return result;
}

template<class T>
tridiagonalAsIrregularArray<T> tridiagonalAsIrregularArray<T>::operator-(const tridiagonalAsIrregularArray<T> & m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");

	tridiagonalAsIrregularArray<T> result(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			if ((i == 0 || i == n - 1) && j == 2) break;
			result.element[i][j] = element[i][j] - m.element[i][j];
		}
	}
	return result;
}

template<class T>
matrix<T> tridiagonalAsIrregularArray<T>::operator*(const tridiagonalAsIrregularArray<T> & m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");

	matrix<T> result(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result(i + 1, j + 1) = 0;
			for (int k = 0; k < n; k++) {
				result(i + 1, j + 1) += get(i + 1, k + 1) * m.get(k + 1, j + 1);
			}
		}
	}

	return result;
}

template<class T>
tridiagonalAsIrregularArray<T> tridiagonalAsIrregularArray<T>::transpose() {
	tridiagonalAsIrregularArray<T> result(n);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			switch (i - j) {
			case -1:
			case 0:
			case 1:
				result.set(i, j, get(j, i));
				break;
			default: break;//ignore others
			}
		}
	}
	return result;

}

#endif
