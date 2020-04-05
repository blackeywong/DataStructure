#pragma once
#ifndef _LOWERTRIANGLEASIRREGULARARRAY_H
#define _LOWERTRIANGLEASIRREGULARARRAY_H
#include <iostream>
#include "../DS5/exceptions.h"
#include "upperTriangleAsIrregularArray.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第七章
//Exercise 26
template<class T>
class lowerTriangleAsIrregularArray {
	template<class T>
	friend ostream& operator<<(ostream&, const lowerTriangleAsIrregularArray<T>&);
	template<class T>
	friend istream& operator>>(istream&, lowerTriangleAsIrregularArray<T>&);
public:
	lowerTriangleAsIrregularArray(int theN = 10);
	lowerTriangleAsIrregularArray(const lowerTriangleAsIrregularArray<T>& m);
	~lowerTriangleAsIrregularArray();
	T get(int i, int j) const;
	void set(int i, int j, const T& value);
	lowerTriangleAsIrregularArray<T>& operator=(const lowerTriangleAsIrregularArray<T>&);
	lowerTriangleAsIrregularArray<T> operator+(const lowerTriangleAsIrregularArray<T>&) const;
	lowerTriangleAsIrregularArray<T> operator-(const lowerTriangleAsIrregularArray<T>&) const;
	lowerTriangleAsIrregularArray<T> operator*(const lowerTriangleAsIrregularArray<T>&) const;
	upperTriangleAsIrregularArray<T> transpose();
private:
	void checkIndex(int i, int j) const;
	void clear();
	void initialize();
	int n;
	T** element;
};


template<class T>
void lowerTriangleAsIrregularArray<T>::checkIndex(int i, int j) const {
	if (i < 1 || i> n || j <1 || j> n) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream& out, const lowerTriangleAsIrregularArray<T>& m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j <= i; j++) {
			out << m.element[i][j] << " ";
		}
		out << endl;
	}

	return out;
}

template<class T>
istream& operator>>(istream& in, lowerTriangleAsIrregularArray<T>& m) {
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

	return in;
}

template<class T>
lowerTriangleAsIrregularArray<T>::lowerTriangleAsIrregularArray(int theN) {
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	initialize();
}

template<class T>
lowerTriangleAsIrregularArray<T>::lowerTriangleAsIrregularArray(const lowerTriangleAsIrregularArray<T>& m) {
	n = m.n;
	initialize();
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j <= i; j++) {
			element[i][j] = m.element[i][j];
		}
	}
}

template<class T>
lowerTriangleAsIrregularArray<T>::~lowerTriangleAsIrregularArray() {
	clear();
}

template<class T>
void lowerTriangleAsIrregularArray<T>::clear() {
	for (int i = 0; i < n; i++) {
		delete[] element[i];
	}
	delete[] element;
	element = nullptr;
}

template<class T>
void lowerTriangleAsIrregularArray<T>::initialize() {
	element = new T * [n];
	for (int i = 0; i < n; i++) {
		element[i] = new T[i+1];
	}
}

template<class T>
T lowerTriangleAsIrregularArray<T>::get(int i, int j) const {
	checkIndex(i, j);
	if(i < j) return 0;

	return element[i - 1][j - 1];
}

template<class T>
void lowerTriangleAsIrregularArray<T>::set(int i, int j, const T& value) {
	checkIndex(i, j);
	if (i >= j) element[i - 1][j - 1] = value;
	//ignore other positions
}

template<class T>
lowerTriangleAsIrregularArray<T>& lowerTriangleAsIrregularArray<T>::operator=(const lowerTriangleAsIrregularArray<T>& m) {
	if (&m == this) return *this;
	clear();
	n = m.n;
	initialize();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			element[i][j] = m.element[i][j];
		}
	}
	return *this;
}

template<class T>
lowerTriangleAsIrregularArray<T> lowerTriangleAsIrregularArray<T>::operator+(const lowerTriangleAsIrregularArray<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");

	lowerTriangleAsIrregularArray<T> result(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			result.element[i][j] = element[i][j] + m.element[i][j];
		}
	}
	return result;
}

template<class T>
lowerTriangleAsIrregularArray<T> lowerTriangleAsIrregularArray<T>::operator-(const lowerTriangleAsIrregularArray<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");

	lowerTriangleAsIrregularArray<T> result(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			result.element[i][j] = element[i][j] - m.element[i][j];
		}
	}
	return result;
}

template<class T>
lowerTriangleAsIrregularArray<T> lowerTriangleAsIrregularArray<T>::operator*(const lowerTriangleAsIrregularArray<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");

	lowerTriangleAsIrregularArray<T> result(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int res = 0;
			for (int k = 0; k < n; k++) {
				res += get(i + 1, k + 1) * m.get(k + 1, j + 1);
			}
			result.set(i + 1, j + 1, res);
		}
	}

	return result;
}

template<class T>
upperTriangleAsIrregularArray<T> lowerTriangleAsIrregularArray<T>::transpose() {
	upperTriangleAsIrregularArray<T> result(n);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			result.set(j, i, get(i, j));
		}
	}
	return result;

}

#endif
