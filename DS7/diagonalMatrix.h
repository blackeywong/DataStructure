#pragma once
#ifndef _DIAGONALMATRIX_H
#define _DIAGONALMATRIX_H
#include "../DS5/exceptions.h"
//数据结构算法与应用-C++语言描述 第七章
//Exercise 20
template<class T>
class diagonalMatrix {
	template<class T>
	friend ostream& operator<<(ostream&, const diagonalMatrix<T>&);
	template<class T>
	friend istream& operator>>(istream&, diagonalMatrix<T>&);
public:
	diagonalMatrix(int theN = 10);
	diagonalMatrix(const diagonalMatrix<T>&);
	~diagonalMatrix() { delete[] element; }
	T get(int, int) const;
	void set(int, int, const T&);
	diagonalMatrix<T>& operator=(const diagonalMatrix<T>&);
	diagonalMatrix<T> operator+(const diagonalMatrix<T>&) const;
	diagonalMatrix<T> operator-(const diagonalMatrix<T>&) const;
	diagonalMatrix<T> operator*(const diagonalMatrix<T>&) const;
	diagonalMatrix<T> transpose() { return *this; }
private:
	void checkIndex(int i, int j) const;
	int n;
	T* element;
};

template<class T>
void diagonalMatrix<T>::checkIndex(int i, int j) const {
	if (i < 1 || i> n || j <1 || j> n) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream& out, const diagonalMatrix<T>& m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			if (i == j) out << m.element[i];
			else out << " ";
			out << " ";
		}
		out << endl;
	}
	return out;
}

template<class T>
istream& operator>>(istream& in, diagonalMatrix<T>& m)
{
	for (int i = 0; i < m.n; i++) {
		if (in) in >> m.element[i];
		else m.element[i] = 0;
	}
	return in;
}


template<class T>
diagonalMatrix<T>::diagonalMatrix(int theN){
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	element = new T[n];
}

template<class T>
diagonalMatrix<T>::diagonalMatrix(const diagonalMatrix<T>& m) {
	n = m.n;
	element = new T[n];
	copy(m.element, m.element + n, element);
}

template<class T>
T diagonalMatrix<T>::get(int i, int j) const {
	checkIndex(i, j);
	if (i == j) return element[i - 1];
	else return 0;
}

template<class T>
void diagonalMatrix<T>::set(int i, int j, const T& value) {
	checkIndex(i, j);
	if (i == j) element[i - 1] = value;
	//ignore i != j
}

template<class T>
diagonalMatrix<T>& diagonalMatrix<T>::operator=(const diagonalMatrix<T>& m) {
	n = m.n;
	delete[] element;
	element = new T[n];
	copy(m.element, m.element + n, element);
	return *this;
}

template<class T>
diagonalMatrix<T> diagonalMatrix<T>::operator+(const diagonalMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	diagonalMatrix<T> result(n);
	for (int i = 0; i < n; i++) {
		result.element[i] = element[i] + m.element[i];
	}
	return result;
}

template<class T>
diagonalMatrix<T> diagonalMatrix<T>::operator-(const diagonalMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	diagonalMatrix<T> result(n);
	for (int i = 0; i < n; i++) {
		result.element[i] = element[i] - m.element[i];
	}
	return result;
}

template<class T>
diagonalMatrix<T> diagonalMatrix<T>::operator*(const diagonalMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	diagonalMatrix<T> result(n);
	for (int i = 0; i < n; i++) {
		result.element[i] = element[i] * m.element[i];
	}
	return result;
}

#endif