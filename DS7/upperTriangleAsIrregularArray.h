#pragma once
#ifndef _UPPERTRIANGLEASIRREGULARARRAY_H
#define _UPPERTRIANGLEASIRREGULARARRAY_H
#include <iostream>
#include "../DS5/exceptions.h"
//#include "lowerTriangleAsIrregularArray.h"
using namespace std;
//���ݽṹ�㷨��Ӧ��-C++�������� ������
//Exercise 26
template<class T> class lowerTriangleAsIrregularArray;
template<class T>
class upperTriangleAsIrregularArray {
	template<class T>
	friend ostream& operator<<(ostream&, const upperTriangleAsIrregularArray<T>&);
	template<class T>
	friend istream& operator>>(istream&, upperTriangleAsIrregularArray<T>&);
public:
	upperTriangleAsIrregularArray(int theN = 10);
	upperTriangleAsIrregularArray(const upperTriangleAsIrregularArray<T>& m);
	~upperTriangleAsIrregularArray();
	T get(int i, int j) const;
	void set(int i, int j, const T& value);
	upperTriangleAsIrregularArray<T>& operator=(const upperTriangleAsIrregularArray<T>&);
	upperTriangleAsIrregularArray<T> operator+(const upperTriangleAsIrregularArray<T>&) const;
	upperTriangleAsIrregularArray<T> operator-(const upperTriangleAsIrregularArray<T>&) const;
	upperTriangleAsIrregularArray<T> operator*(const upperTriangleAsIrregularArray<T>&) const;
	lowerTriangleAsIrregularArray<T> transpose();
private:
	void checkIndex(int i, int j) const;
	void clear();
	void initialize();
	int n;
	T** element;
};


template<class T>
void upperTriangleAsIrregularArray<T>::checkIndex(int i, int j) const {
	if (i < 1 || i> n || j <1 || j> n) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream& out, const upperTriangleAsIrregularArray<T>& m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			if (i <= j) out << m.element[i][j-i];
			else out << " ";
			out << " ";
		}
		out << endl;
	}

	return out;
}

template<class T>
istream& operator>>(istream& in, upperTriangleAsIrregularArray<T>& m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n - i; j++) {
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
upperTriangleAsIrregularArray<T>::upperTriangleAsIrregularArray(int theN) {
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	initialize();
}

template<class T>
upperTriangleAsIrregularArray<T>::upperTriangleAsIrregularArray(const upperTriangleAsIrregularArray<T>& m) {
	n = m.n;
	initialize();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			element[i][j] = m.element[i][j];
		}
	}
}

template<class T>
upperTriangleAsIrregularArray<T>::~upperTriangleAsIrregularArray() {
	clear();
}

template<class T>
void upperTriangleAsIrregularArray<T>::clear() {
	for (int i = 0; i < n; i++) {
		delete[] element[i];
	}
	delete[] element;
	element = nullptr;
}

template<class T>
void upperTriangleAsIrregularArray<T>::initialize() {
	element = new T * [n];
	for (int i = 0; i < n; i++) {
		element[i] = new T[n - i];
	}
}

template<class T>
T upperTriangleAsIrregularArray<T>::get(int i, int j) const {
	checkIndex(i, j);
	if (i > j) return 0;

	return element[i - 1][j-i];
}

template<class T>
void upperTriangleAsIrregularArray<T>::set(int i, int j, const T& value) {
	checkIndex(i, j);
	if (i <= j) element[i - 1][j-i] = value;
	//ignore other positions
}

template<class T>
upperTriangleAsIrregularArray<T>& upperTriangleAsIrregularArray<T>::operator=(const upperTriangleAsIrregularArray<T>& m) {
	if (&m == this) return *this;
	clear();
	n = m.n;
	initialize();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			element[i][j] = m.element[i][j];
		}
	}
	return *this;
}

template<class T>
upperTriangleAsIrregularArray<T> upperTriangleAsIrregularArray<T>::operator+(const upperTriangleAsIrregularArray<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");

	upperTriangleAsIrregularArray<T> result(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			result.element[i][j] = element[i][j] + m.element[i][j];
		}
	}
	return result;
}

template<class T>
upperTriangleAsIrregularArray<T> upperTriangleAsIrregularArray<T>::operator-(const upperTriangleAsIrregularArray<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");

	upperTriangleAsIrregularArray<T> result(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			result.element[i][j] = element[i][j] - m.element[i][j];
		}
	}
	return result;
}

template<class T>
upperTriangleAsIrregularArray<T> upperTriangleAsIrregularArray<T>::operator*(const upperTriangleAsIrregularArray<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");

	upperTriangleAsIrregularArray<T> result(n);
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
lowerTriangleAsIrregularArray<T> upperTriangleAsIrregularArray<T>::transpose() {
	lowerTriangleAsIrregularArray<T> result(n);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			result.set(i, j, get(j, i));
		}
	}
	return result;
}

#endif
