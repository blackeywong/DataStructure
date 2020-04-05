#pragma once
#ifndef _SQUAREBANDASIRREGULARARRAY_H
#define _SQUAREBANDASIRREGULARARRAY_H
#include <iostream>
#include <algorithm>
#include "../DS5/exceptions.h"
#include "matrix.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第七章
//Exercise 37
template<class T>
class squareBandAsIrregularArray {
	template<class T>
	friend ostream& operator<<(ostream&, const squareBandAsIrregularArray<T>&);
	template<class T>
	friend istream& operator>>(istream&, squareBandAsIrregularArray<T>&);
public:
	squareBandAsIrregularArray(int theN = 10, int theA = 3);
	squareBandAsIrregularArray(const squareBandAsIrregularArray<T>& m);
	~squareBandAsIrregularArray();
	T get(int i, int j) const;
	void set(int i, int j, const T& value);
	squareBandAsIrregularArray<T>& operator=(const squareBandAsIrregularArray<T>&);
	squareBandAsIrregularArray<T> operator+(const squareBandAsIrregularArray<T>&) const;
	squareBandAsIrregularArray<T> operator-(const squareBandAsIrregularArray<T>&) const;
	matrix<T> operator*(const squareBandAsIrregularArray<T>&) const;
	squareBandAsIrregularArray<T> transpose();
private:
	void checkIndex(int i, int j) const;
	void clear();
	void initialize();
	int n;
	int a;
	T** element;
};


template<class T>
void squareBandAsIrregularArray<T>::checkIndex(int i, int j) const {
	if (i < 0 || i> n-1 || j <0 || j> n-1) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream & out, const squareBandAsIrregularArray<T> & m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			if (i < m.a && j - i < m.a) out << m.element[i][j];
			else if (i >= m.a && i - j < m.a) out << m.element[i][j-(i- m.a+1)];
			else out << " ";
			out << " ";
		}
		out << endl;
	}

	return out;
}

template<class T>
istream& operator>>(istream & in, squareBandAsIrregularArray<T> & m) {
	for (int i = 0; i < m.n; i++) {
		int size = i < (m.n + 1) / 2 ? min(m.a + i, m.n) : min(m.a + (m.n - 1 - i), m.n);
		for (int j = 0; j < size; j++) {
			if (in)
				in >> m.element[i][j];
			else
				m.element[i][j] = 0;
		}
	}

	return in;
}

template<class T>
squareBandAsIrregularArray<T>::squareBandAsIrregularArray(int theN, int theA) {
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	a = theA;
	initialize();
}

template<class T>
squareBandAsIrregularArray<T>::squareBandAsIrregularArray(const squareBandAsIrregularArray<T> & m) {
	n = m.n;
	a = m.a;
	initialize();
	for (int i = 0; i < n; i++) {
		int size = i < (n + 1) / 2 ? min(a + i, n) : min(a + (n - 1 - i), n);
		for (int j = 0; j < size; j++) {
			element[i][j] = m.element[i][j];
		}
	}
}

template<class T>
squareBandAsIrregularArray<T>::~squareBandAsIrregularArray() {
	clear();
}

template<class T>
void squareBandAsIrregularArray<T>::clear() {
	for (int i = 0; i < n; i++) {
		delete[] element[i];
	}
	delete[] element;
	element = nullptr;
}

template<class T>
void squareBandAsIrregularArray<T>::initialize() {
	element = new T * [n];
	for (int i = 0; i < n; i++) {
		int size = i < (n + 1) / 2 ? min(a + i, n) : min(a+(n-1-i), n);
		element[i] = new T[size];
	}
}

template<class T>
T squareBandAsIrregularArray<T>::get(int i, int j) const {
	checkIndex(i, j);
	if (i < a && j - i < a) return element[i][j];
	else if (i >= a && i - j < a) return element[i][j - (i - a + 1)];
	else return 0;
}

template<class T>
void squareBandAsIrregularArray<T>::set(int i, int j, const T & value) {
	checkIndex(i, j);
	if (i < a && j - i < a) element[i][j] = value;
	else if (i >= a && i - j < a) element[i][j - (i - a + 1)] = value;
	//ignore other positions
}

template<class T>
squareBandAsIrregularArray<T>& squareBandAsIrregularArray<T>::operator=(const squareBandAsIrregularArray<T> & m) {
	if (&m == this) return *this;
	clear();
	n = m.n;
	a = m.a;
	initialize();
	for (int i = 0; i < n; i++) {
		int size = i < (n + 1) / 2 ? min(a + i, n) : min(a + (n - 1 - i), n);
		for (int j = 0; j < size; j++) {
			element[i][j] = m.element[i][j];
		}
	}
	return *this;
}

template<class T>
squareBandAsIrregularArray<T> squareBandAsIrregularArray<T>::operator+(const squareBandAsIrregularArray<T> & m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");

	squareBandAsIrregularArray<T> result(n);
	for (int i = 0; i < n; i++) {
		int size = i < (n + 1) / 2 ? min(a + i, n) : min(a + (n - 1 - i), n);
		for (int j = 0; j < size; j++) {
			result.element[i][j] = element[i][j] + m.element[i][j];
		}
	}
	return result;
}

template<class T>
squareBandAsIrregularArray<T> squareBandAsIrregularArray<T>::operator-(const squareBandAsIrregularArray<T> & m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");

	squareBandAsIrregularArray<T> result(n);
	for (int i = 0; i < n; i++) {
		int size = i < (n + 1) / 2 ? min(a + i, n) : min(a + (n - 1 - i), n);
		for (int j = 0; j < size; j++) {
			result.element[i][j] = element[i][j] - m.element[i][j];
		}
	}
	return result;
}

template<class T>
matrix<T> squareBandAsIrregularArray<T>::operator*(const squareBandAsIrregularArray<T> & m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");

	matrix<T> result(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result(i + 1, j + 1) = 0;
			for (int k = 0; k < n; k++) {
				result(i + 1, j + 1) += get(i, k) * m.get(k, j);
			}
		}
	}

	return result;
}

template<class T>
squareBandAsIrregularArray<T> squareBandAsIrregularArray<T>::transpose() {
	squareBandAsIrregularArray<T> result(*this);

	for (int i = 1; i < a; i++) {
		for (int j = 0; j < n - i; j++) {
			T& ra = j+i < a ? result.element[j+i][j] : result.element[j+i][j - (j+i - a + 1)];
			T& rb = j < a ? result.element[j][i+j] : result.element[j][i+j - (j - a + 1)];
			swap(ra, rb);
		}
	}
	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < n; j++) {
	//		result.set(i, j, get(j, i));
	//	}
	//}
	return result;

}

#endif
