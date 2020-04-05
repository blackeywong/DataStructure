#pragma once
#ifndef _TRIDIAGONALBYCOLUMNS_H
#define _TRIDIAGONALBYCOLUMNS_H
#include "../DS5/exceptions.h"
#include "matrix.h"
//数据结构算法与应用-C++语言描述 第七章
//Exercise 22
template<class T>
class tridiagonalByColumns {
	template<class T>
	friend ostream& operator<<(ostream&, const tridiagonalByColumns<T>&);
	template<class T>
	friend istream& operator>>(istream&, tridiagonalByColumns<T>&);
public:
	tridiagonalByColumns(int theN = 10);
	tridiagonalByColumns(const tridiagonalByColumns<T>&);
	~tridiagonalByColumns() { delete[] element; }
	T get(int, int) const;
	void set(int, int, const T&);
	tridiagonalByColumns<T>& operator=(const tridiagonalByColumns<T>&);
	tridiagonalByColumns<T> operator+(const tridiagonalByColumns<T>&) const;
	tridiagonalByColumns<T> operator-(const tridiagonalByColumns<T>&) const;
	matrix<T> operator*(const tridiagonalByColumns<T>&) const;
	tridiagonalByColumns<T> transpose();
private:
	void checkIndex(int i, int j) const;
	int n;
	T* element;
};

template<class T>
void tridiagonalByColumns<T>::checkIndex(int i, int j) const {
	if (i < 1 || i> n || j <1 || j> n) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream & out, const tridiagonalByColumns<T> & m) {
	for (int i = 1; i <= m.n; i++) {
		for (int j = 1; j <= m.n; j++) {
			if (i == j || i - j == 1 || i - j == -1) out << m.get(i, j);
			else out << " ";
			out << " ";
		}
		out << endl;
	}
	return out;
}

template<class T>
istream& operator>>(istream & in, tridiagonalByColumns<T> & m)
{
	for (int i = 0; i < m.n * 3 - 2; i++) {
		if (in) in >> m.element[i];
		else m.element[i] = 0;
	}
	return in;
}


template<class T>
tridiagonalByColumns<T>::tridiagonalByColumns(int theN) {
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	element = new T[n * 3 - 2];
}

template<class T>
tridiagonalByColumns<T>::tridiagonalByColumns(const tridiagonalByColumns<T> & m) {
	n = m.n;
	element = new T[n * 3 - 2];
	copy(m.element, m.element + n * 3 - 2, element);
}

template<class T>
T tridiagonalByColumns<T>::get(int i, int j) const {
	checkIndex(i, j);
	switch (i - j) {
	case 1: 
	case 0: 
	case -1:  
		return element[i + j * 2 - 3]; //2 + (j-2)*3 + (i -j +1)
	default: return 0;
	}
}

template<class T>
void tridiagonalByColumns<T>::set(int i, int j, const T & value) {
	checkIndex(i, j);
	switch (i - j) {
	case 1: 
	case 0: 
	case -1: 
		element[i + j * 2 - 3] = value;
		break;
	default: break;//ignore other positions
	}
}

template<class T>
tridiagonalByColumns<T>& tridiagonalByColumns<T>::operator=(const tridiagonalByColumns<T> & m) {
	n = m.n;
	delete[] element;
	element = new T[n * 3 - 2];
	copy(m.element, m.element + n * 3 - 2, element);
	return *this;
}

template<class T>
tridiagonalByColumns<T> tridiagonalByColumns<T>::operator+(const tridiagonalByColumns<T> & m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	tridiagonalByColumns<T> result(n);
	for (int i = 0; i < n * 3 - 2; i++) {
		result.element[i] = element[i] + m.element[i];
	}
	return result;
}

template<class T>
tridiagonalByColumns<T> tridiagonalByColumns<T>::operator-(const tridiagonalByColumns<T> & m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	tridiagonalByColumns<T> result(n);
	for (int i = 0; i < n * 3 - 2; i++) {
		result.element[i] = element[i] - m.element[i];
	}
	return result;
}

template<class T>
matrix<T> tridiagonalByColumns<T>::operator*(const tridiagonalByColumns<T> & m) const {
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
tridiagonalByColumns<T> tridiagonalByColumns<T>::transpose() {
	tridiagonalByColumns<T> result(n);
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