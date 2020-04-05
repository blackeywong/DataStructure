#pragma once
#ifndef _LOWERSYMMETRICMATRIX_H
#define _LOWERSYMMETRICMATRIX_H
#include "../DS5/exceptions.h"
#include "upperTriangularMatrix.h"
#include "matrix.h"
//数据结构算法与应用-C++语言描述 第七章
//Exercise 33
template<class T>
class lowerSymmetricMatrix {
	template<class T>
	friend ostream& operator<<(ostream&, const lowerSymmetricMatrix<T>&);
	template<class T>
	friend istream& operator>>(istream&, lowerSymmetricMatrix<T>&);
public:
	lowerSymmetricMatrix(int theN = 10);
	lowerSymmetricMatrix(const lowerSymmetricMatrix<T>&);
	~lowerSymmetricMatrix() { delete[] element; }
	int size() const { return n; }
	T get(int, int) const;
	void set(int, int, const T&);
	lowerSymmetricMatrix<T>& operator=(const lowerSymmetricMatrix<T>&);
	lowerSymmetricMatrix<T> operator+(const lowerSymmetricMatrix<T>&) const;
	lowerSymmetricMatrix<T> operator-(const lowerSymmetricMatrix<T>&) const;
	matrix<T> operator*(const lowerSymmetricMatrix<T>&) const;
	lowerSymmetricMatrix<T> transpose();
private:
	void checkIndex(int i, int j) const;
	int n;
	T* element;
};

template<class T>
void lowerSymmetricMatrix<T>::checkIndex(int i, int j) const {
	if (i < 1 || i> n || j <1 || j> n) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream& out, const lowerSymmetricMatrix<T>& m) {
	for (int i = 1; i <= m.n; i++) {
		for (int j = 1; j <= m.n; j++) {
			if (i >= j)
				out << m.element[(i * (i - 1)) / 2 + j - 1] << " ";
			else
				out << m.element[(j * (j - 1)) / 2 + i - 1] << " ";
		}
		out << endl;
	}
	return out;
}

template<class T>
istream& operator>>(istream& in, lowerSymmetricMatrix<T>& m)
{
	for (int i = 0; i < (m.n * (m.n + 1)) / 2; i++) {
		if (in) in >> m.element[i];
		else m.element[i] = 0;
	}
	return in;
}


template<class T>
lowerSymmetricMatrix<T>::lowerSymmetricMatrix(int theN) {
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	element = new T[(n * (n + 1)) / 2];
}

template<class T>
lowerSymmetricMatrix<T>::lowerSymmetricMatrix(const lowerSymmetricMatrix<T>& m) {
	n = m.n;
	element = new T[(n * (n + 1)) / 2];
	copy(m.element, m.element + (n * (n + 1)) / 2, element);
}

template<class T>
T lowerSymmetricMatrix<T>::get(int i, int j) const {
	checkIndex(i, j);
	if (i >= j) return element[(i * (i - 1)) / 2 + j - 1];
	else return element[(j * (j - 1)) / 2 + i - 1];
	
}

template<class T>
void lowerSymmetricMatrix<T>::set(int i, int j, const T& value) {
	checkIndex(i, j);
	if (i >= j) element[(i * (i - 1)) / 2 + j - 1] = value;
	else element[(j * (j - 1)) / 2 + i - 1] = value;
}

template<class T>
lowerSymmetricMatrix<T>& lowerSymmetricMatrix<T>::operator=(const lowerSymmetricMatrix<T>& m) {
	n = m.n;
	delete[] element;
	element = new T[(n * (n + 1)) / 2];
	copy(m.element, m.element + (n * (n + 1)) / 2, element);
	return *this;
}

template<class T>
lowerSymmetricMatrix<T> lowerSymmetricMatrix<T>::operator+(const lowerSymmetricMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	lowerSymmetricMatrix<T> result(n);
	for (int i = 0; i < (n * (n + 1)) / 2; i++) {
		result.element[i] = element[i] + m.element[i];
	}
	return result;
}

template<class T>
lowerSymmetricMatrix<T> lowerSymmetricMatrix<T>::operator-(const lowerSymmetricMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	lowerSymmetricMatrix<T> result(n);
	for (int i = 0; i < (n * (n + 1)) / 2; i++) {
		result.element[i] = element[i] - m.element[i];
	}
	return result;
}

template<class T>
matrix<T> lowerSymmetricMatrix<T>::operator*(const lowerSymmetricMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	matrix<T> result(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int res = 0;
			for (int k = 0; k < n; k++) {
				res += get(i + 1, k + 1) * m.get(k + 1, j + 1);
			}
			//result.set(i + 1, j + 1, res);
			result(i + 1, j + 1) = res;
		}
	}
	return result;
}

template<class T>
lowerSymmetricMatrix<T> lowerSymmetricMatrix<T>::transpose() {
	return *this;
}

#endif