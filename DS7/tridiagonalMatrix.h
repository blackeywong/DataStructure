#pragma once
#ifndef _TRIDIAGONALMATRIX_H
#define _TRIDIAGONALMATRIX_H
#include "../DS5/exceptions.h"
#include "matrix.h"
//数据结构算法与应用-C++语言描述 第七章
//Exercise 21
template<class T>
class tridiagonalMatrix {
	template<class T>
	friend ostream& operator<<(ostream&, const tridiagonalMatrix<T>&);
	template<class T>
	friend istream& operator>>(istream&, tridiagonalMatrix<T>&);
public:
	tridiagonalMatrix(int theN = 10);
	tridiagonalMatrix(const tridiagonalMatrix<T>&);
	~tridiagonalMatrix() { delete[] element; }
	T get(int, int) const;
	void set(int, int, const T&);
	tridiagonalMatrix<T>& operator=(const tridiagonalMatrix<T>&);
	tridiagonalMatrix<T> operator+(const tridiagonalMatrix<T>&) const;
	tridiagonalMatrix<T> operator-(const tridiagonalMatrix<T>&) const;
	matrix<T> operator*(const tridiagonalMatrix<T>&) const;
	tridiagonalMatrix<T> transpose();
private:
	void checkIndex(int i, int j) const;
	int n;
	T* element;
};

template<class T>
void tridiagonalMatrix<T>::checkIndex(int i, int j) const {
	if (i < 1 || i> n || j <1 || j> n) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream & out, const tridiagonalMatrix<T> & m) {
	for (int i = 1; i <= m.n; i++) {
		for (int j = 1; j <= m.n; j++) {
			if (i == j || i-j == 1|| i-j == -1) out << m.get(i,j);
			else out << " ";
			out << " ";
		}
		out << endl;
	}
	return out;
}

template<class T>
istream& operator>>(istream & in, tridiagonalMatrix<T> & m)
{
	for (int i = 0; i < m.n *3 - 2; i++) {
		if (in) in >> m.element[i];
		else m.element[i] = 0;
	}
	return in;
}


template<class T>
tridiagonalMatrix<T>::tridiagonalMatrix(int theN) {
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	element = new T[n * 3 - 2];
}

template<class T>
tridiagonalMatrix<T>::tridiagonalMatrix(const tridiagonalMatrix<T> & m) {
	n = m.n;
	element = new T[n * 3 - 2];
	copy(m.element, m.element + n * 3 - 2, element);
}

template<class T>
T tridiagonalMatrix<T>::get(int i, int j) const {
	checkIndex(i, j);
	switch (i - j) {
	case 1: return element[i-2];
	case 0: return element[n+i-2];
	case -1:  return element[2*n+i-2];
	default: return 0;
	}
}

template<class T>
void tridiagonalMatrix<T>::set(int i, int j, const T & value) {
	checkIndex(i, j);
	switch (i - j) {
	case 1: element[i - 2] = value;
	case 0: element[n + i - 2] = value;
	case -1:  element[2 * n + i - 2] = value;
	default: break;//ignore other positions
	}
}

template<class T>
tridiagonalMatrix<T>& tridiagonalMatrix<T>::operator=(const tridiagonalMatrix<T> & m) {
	n = m.n;
	delete[] element;
	element = new T[n * 3 - 2];
	copy(m.element, m.element + n * 3 - 2, element);
	return *this;
}

template<class T>
tridiagonalMatrix<T> tridiagonalMatrix<T>::operator+(const tridiagonalMatrix<T> & m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	tridiagonalMatrix<T> result(n);
	for (int i = 0; i < n * 3 - 2; i++) {
		result.element[i] = element[i] + m.element[i];
	}
	return result;
}

template<class T>
tridiagonalMatrix<T> tridiagonalMatrix<T>::operator-(const tridiagonalMatrix<T> & m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	tridiagonalMatrix<T> result(n);
	for (int i = 0; i < n * 3 - 2; i++) {
		result.element[i] = element[i] - m.element[i];
	}
	return result;
}

template<class T>
matrix<T> tridiagonalMatrix<T>::operator*(const tridiagonalMatrix<T> & m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	matrix<T> result(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result(i+1,j+1) = 0;
			for (int k = 0; k < n; k++) {
				result(i+1, j+1) += get(i + 1, k + 1) * m.get(k + 1, j + 1);
			}
		}
	}
	return result;
}

template<class T>
tridiagonalMatrix<T> tridiagonalMatrix<T>::transpose() {
	tridiagonalMatrix<T> result(n);
	copy(element, element + n - 1, result.element + n * 2 - 1); //copy the lower diagonal line
	copy(element + n - 1 , element + n * 2 - 1, result.element + n - 1); //copy the diagonal line
	copy(element + n * 2 - 1, element + n * 3 - 2, result.element); //copy the upper diagonal line
	return result;
}

#endif