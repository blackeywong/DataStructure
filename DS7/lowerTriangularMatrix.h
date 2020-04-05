#pragma once
#ifndef _LOWERTRIANGULARMATRIX_H
#define _LOWERTRIANGULARMATRIX_H
#include "../DS5/exceptions.h"
#include "upperTriangularMatrix.h"
#include "matrix.h"
//数据结构算法与应用-C++语言描述 第七章
//Exercise 28, 29, 31
template<class T>
class lowerTriangularMatrix {
	template<class T>
	friend ostream& operator<<(ostream&, const lowerTriangularMatrix<T>&);
	template<class T>
	friend istream& operator>>(istream&, lowerTriangularMatrix<T>&);
public:
	lowerTriangularMatrix(int theN = 10);
	lowerTriangularMatrix(const lowerTriangularMatrix<T>&);
	~lowerTriangularMatrix() { delete[] element; }
	int size() const { return n; }
	T get(int, int) const;
	void set(int, int, const T&);
	lowerTriangularMatrix<T>& operator=(const lowerTriangularMatrix<T>&);
	lowerTriangularMatrix<T> operator+(const lowerTriangularMatrix<T>&) const;
	lowerTriangularMatrix<T> operator-(const lowerTriangularMatrix<T>&) const;
	lowerTriangularMatrix<T> operator*(const lowerTriangularMatrix<T>&) const;
	upperTriangularMatrix<T> transpose();
private:
	void checkIndex(int i, int j) const;
	int n;
	T* element;
};

template<class T>
void lowerTriangularMatrix<T>::checkIndex(int i, int j) const {
	if (i < 1 || i> n || j <1 || j> n) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream& out, const lowerTriangularMatrix<T>& m) {
	for (int i = 1; i <= m.n; i++) {
		for (int j = 1; j <= i; j++) {
			out << m.element[(i * (i - 1)) / 2 + j - 1] << " ";
		}
		out << endl;
	}
	return out;
}

template<class T>
istream& operator>>(istream& in, lowerTriangularMatrix<T>& m)
{
	for (int i = 0; i < (m.n * (m.n + 1)) / 2; i++) {
		if (in) in >> m.element[i];
		else m.element[i] = 0;
	}
	return in;
}


template<class T>
lowerTriangularMatrix<T>::lowerTriangularMatrix(int theN) {
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	element = new T[(n * (n + 1)) / 2];
}

template<class T>
lowerTriangularMatrix<T>::lowerTriangularMatrix(const lowerTriangularMatrix<T>& m) {
	n = m.n;
	element = new T[(n * (n + 1)) / 2];
	copy(m.element, m.element + (n * (n + 1)) / 2, element);
}

template<class T>
T lowerTriangularMatrix<T>::get(int i, int j) const {
	checkIndex(i, j);
	if (i < j) return 0;

	return element[(i*(i-1))/2+j-1];
}

template<class T>
void lowerTriangularMatrix<T>::set(int i, int j, const T& value) {
	checkIndex(i, j);
	if (i >= j) element[(i * (i - 1)) / 2 + j - 1] = value;
	//ignore other positions
}

template<class T>
lowerTriangularMatrix<T>& lowerTriangularMatrix<T>::operator=(const lowerTriangularMatrix<T>& m) {
	n = m.n;
	delete[] element;
	element = new T[(n * (n + 1)) / 2];
	copy(m.element, m.element + (n * (n + 1)) / 2, element);
	return *this;
}

template<class T>
lowerTriangularMatrix<T> lowerTriangularMatrix<T>::operator+(const lowerTriangularMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	lowerTriangularMatrix<T> result(n);
	for (int i = 0; i < (n * (n + 1)) / 2; i++) {
		result.element[i] = element[i] + m.element[i];
	}
	return result;
}

template<class T>
lowerTriangularMatrix<T> lowerTriangularMatrix<T>::operator-(const lowerTriangularMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	lowerTriangularMatrix<T> result(n);
	for (int i = 0; i < (n * (n + 1)) / 2; i++) {
		result.element[i] = element[i] - m.element[i];
	}
	return result;
}

template<class T>
lowerTriangularMatrix<T> lowerTriangularMatrix<T>::operator*(const lowerTriangularMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	lowerTriangularMatrix<T> result(n);
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
upperTriangularMatrix<T> lowerTriangularMatrix<T>::transpose() {
	upperTriangularMatrix<T> result(n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			result.set(j, i, get(i, j));
		}
	}
	return result;
}
//Exercise 32
template<class T>
matrix<T> operator*(const lowerTriangularMatrix<T>& m1, const upperTriangularMatrix<T>& m2) {
	if (m1.size() != m2.size()) throw IllegalParameterValue("must have same size");
	matrix<T> result(m1.size(), m1.size());
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1.size(); j++) {
			int res = 0;
			for (int k = 0; k < m1.size(); k++) {
				res += m1.get(i + 1, k + 1) * m2.get(k + 1, j + 1);
			}
			result(i + 1, j + 1) = res;
		}
	}
	return result;
}

#endif