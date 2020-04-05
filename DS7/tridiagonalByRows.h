#pragma once
#ifndef _TRIDIAGONALBYROWS_H
#define _TRIDIAGONALBYROWS_H
#include "../DS5/exceptions.h"
#include "matrix.h"
//数据结构算法与应用-C++语言描述 第七章
//Exercise 23
template<class T>
class tridiagonalByRows {
	template<class T>
	friend ostream& operator<<(ostream&, const tridiagonalByRows<T>&);
	template<class T>
	friend istream& operator>>(istream&, tridiagonalByRows<T>&);
public:
	tridiagonalByRows(int theN = 10);
	tridiagonalByRows(const tridiagonalByRows<T>&);
	~tridiagonalByRows() { delete[] element; }
	T get(int, int) const;
	void set(int, int, const T&);
	tridiagonalByRows<T>& operator=(const tridiagonalByRows<T>&);
	tridiagonalByRows<T> operator+(const tridiagonalByRows<T>&) const;
	tridiagonalByRows<T> operator-(const tridiagonalByRows<T>&) const;
	matrix<T> operator*(const tridiagonalByRows<T>&) const;
	tridiagonalByRows<T> transpose();
private:
	void checkIndex(int i, int j) const;
	int n;
	T* element;
};

template<class T>
void tridiagonalByRows<T>::checkIndex(int i, int j) const {
	if (i < 1 || i> n || j <1 || j> n) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream & out, const tridiagonalByRows<T> & m) {
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
istream& operator>>(istream & in, tridiagonalByRows<T> & m)
{
	for (int i = 0; i < m.n * 3 - 2; i++) {
		if (in) in >> m.element[i];
		else m.element[i] = 0;
	}
	return in;
}


template<class T>
tridiagonalByRows<T>::tridiagonalByRows(int theN) {
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	element = new T[n * 3 - 2];
}

template<class T>
tridiagonalByRows<T>::tridiagonalByRows(const tridiagonalByRows<T> & m) {
	n = m.n;
	element = new T[n * 3 - 2];
	copy(m.element, m.element + n * 3 - 2, element);
}

template<class T>
T tridiagonalByRows<T>::get(int i, int j) const {
	checkIndex(i, j);
	switch (i - j) {
	case 1:
	case 0:
	case -1:
		return element[i * 2 + j - 3]; //2 + (i-2)*3 + (j -i +1)
	default: return 0;
	}
}

template<class T>
void tridiagonalByRows<T>::set(int i, int j, const T & value) {
	checkIndex(i, j);
	switch (i - j) {
	case 1:
	case 0:
	case -1:
		element[i *2 + j - 3] = value;
		break;
	default: break;//ignore other positions
	}
}

template<class T>
tridiagonalByRows<T>& tridiagonalByRows<T>::operator=(const tridiagonalByRows<T> & m) {
	n = m.n;
	delete[] element;
	element = new T[n * 3 - 2];
	copy(m.element, m.element + n * 3 - 2, element);
	return *this;
}

template<class T>
tridiagonalByRows<T> tridiagonalByRows<T>::operator+(const tridiagonalByRows<T> & m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	tridiagonalByRows<T> result(n);
	for (int i = 0; i < n * 3 - 2; i++) {
		result.element[i] = element[i] + m.element[i];
	}
	return result;
}

template<class T>
tridiagonalByRows<T> tridiagonalByRows<T>::operator-(const tridiagonalByRows<T> & m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	tridiagonalByRows<T> result(n);
	for (int i = 0; i < n * 3 - 2; i++) {
		result.element[i] = element[i] - m.element[i];
	}
	return result;
}

template<class T>
matrix<T> tridiagonalByRows<T>::operator*(const tridiagonalByRows<T> & m) const {
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
tridiagonalByRows<T> tridiagonalByRows<T>::transpose() {
	tridiagonalByRows<T> result(n);
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