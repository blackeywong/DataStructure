#pragma once
#ifndef _ANTIDIAGONALMATRIX_H
#define _ANTIDIAGONALMATRIX_H
#include "../DS5/exceptions.h"
#include "matrix.h"
#include "diagonalMatrix.h"
//数据结构算法与应用-C++语言描述 第七章
//Exercise 35
template<class T>
class antidiagonalMatrix {
	template<class T>
	friend ostream& operator<<(ostream&, const antidiagonalMatrix<T>&);
	template<class T>
	friend istream& operator>>(istream&, antidiagonalMatrix<T>&);
public:
	antidiagonalMatrix(int theN = 10);
	antidiagonalMatrix(const antidiagonalMatrix<T>&);
	~antidiagonalMatrix() { delete[] element; }
	T get(int, int) const;
	void set(int, int, const T&);
	T& operator()(int i, int j) const;
	antidiagonalMatrix<T>& operator=(const antidiagonalMatrix<T>&);
	antidiagonalMatrix<T> operator+(const antidiagonalMatrix<T>&) const;
	antidiagonalMatrix<T> operator-(const antidiagonalMatrix<T>&) const;
	diagonalMatrix<T> operator*(const antidiagonalMatrix<T>&) const;
	antidiagonalMatrix<T> transpose();
private:
	void checkIndex(int i, int j) const;
	int n;
	T* element;
};

template<class T>
void antidiagonalMatrix<T>::checkIndex(int i, int j) const {
	if (i < 1 || i> n || j <1 || j> n) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream& out, const antidiagonalMatrix<T>& m) {
	for (int i = 1; i <= m.n; i++) {
		for (int j = 1; j <= m.n; j++) {
			if (i + j == m.n + 1) out << m.element[i-1];
			else out << " ";
			out << " ";
		}
		out << endl;
	}
	return out;
}

template<class T>
istream& operator>>(istream& in, antidiagonalMatrix<T>& m)
{
	for (int i = 0; i < m.n; i++) {
		if (in) in >> m.element[i];
		else m.element[i] = 0;
	}
	return in;
}


template<class T>
antidiagonalMatrix<T>::antidiagonalMatrix(int theN) {
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	element = new T[n];
}

template<class T>
antidiagonalMatrix<T>::antidiagonalMatrix(const antidiagonalMatrix<T>& m) {
	n = m.n;
	element = new T[n];
	copy(m.element, m.element + n, element);
}

template<class T>
T antidiagonalMatrix<T>::get(int i, int j) const {
	checkIndex(i, j);
	if (i + j == n+1) return element[i - 1];
	else return 0;
}

template<class T>
void antidiagonalMatrix<T>::set(int i, int j, const T& value) {
	checkIndex(i, j);
	if (i + j == n + 1) element[i - 1] = value;
	//ignore i + j != n + 1
}

template<class T>
T& antidiagonalMatrix<T>::operator()(int i, int j) const {
	checkIndex(i, j);
	if (i + j == n + 1) return element[i - 1];
	else return 0;
}

template<class T>
antidiagonalMatrix<T>& antidiagonalMatrix<T>::operator=(const antidiagonalMatrix<T>& m) {
	n = m.n;
	delete[] element;
	element = new T[n];
	copy(m.element, m.element + n, element);
	return *this;
}

template<class T>
antidiagonalMatrix<T> antidiagonalMatrix<T>::operator+(const antidiagonalMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	antidiagonalMatrix<T> result(n);
	for (int i = 0; i < n; i++) {
		result.element[i] = element[i] + m.element[i];
	}
	return result;
}

template<class T>
antidiagonalMatrix<T> antidiagonalMatrix<T>::operator-(const antidiagonalMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	antidiagonalMatrix<T> result(n);
	for (int i = 0; i < n; i++) {
		result.element[i] = element[i] - m.element[i];
	}
	return result;
}

template<class T>
diagonalMatrix<T> antidiagonalMatrix<T>::operator*(const antidiagonalMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	diagonalMatrix<T> result(n);
	for (int i = 0; i < n; i++) {
		result.set(i+1,i+1, element[i] * m.element[n-i-1]);
	}
	return result;
}

template<class T>
antidiagonalMatrix<T> antidiagonalMatrix<T>::transpose() {
	antidiagonalMatrix<T> result(n);
	for (int i = 0; i < n / 2; i++) {
		swap(element[i], element[n-i-1]);
	}
	return *this; 
}

#endif