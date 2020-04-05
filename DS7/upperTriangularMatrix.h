#pragma once
#ifndef _UPPERTRIANGULARMATRIX_H
#define _UPPERTRIANGULARMATRIX_H
#include "../DS5/exceptions.h"

//数据结构算法与应用-C++语言描述 第七章
//Exercise 28, 29, 31
template<class T> class lowerTriangularMatrix;
template<class T>
class upperTriangularMatrix {
	template<class T>
	friend ostream& operator<<(ostream&, const upperTriangularMatrix<T>&);
	template<class T>
	friend istream& operator>>(istream&, upperTriangularMatrix<T>&);
public:
	upperTriangularMatrix(int theN = 10);
	upperTriangularMatrix(const upperTriangularMatrix<T>&);
	~upperTriangularMatrix() { delete[] element; }
	int size() const { return n; }
	T get(int, int) const;
	void set(int, int, const T&);
	upperTriangularMatrix<T>& operator=(const upperTriangularMatrix<T>&);
	upperTriangularMatrix<T> operator+(const upperTriangularMatrix<T>&) const;
	upperTriangularMatrix<T> operator-(const upperTriangularMatrix<T>&) const;
	upperTriangularMatrix<T> operator*(const upperTriangularMatrix<T>&) const;
	lowerTriangularMatrix<T> transpose();
private:
	void checkIndex(int i, int j) const;
	int n;
	T* element;
};

template<class T>
void upperTriangularMatrix<T>::checkIndex(int i, int j) const {
	if (i < 1 || i> n || j <1 || j> n) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream& out, const upperTriangularMatrix<T>& m) {
	for (int i = 1; i <= m.n; i++) {
		for (int j = 1; j <= m.n; j++) {
			if (i <= j) out << m.element[((m.n + m.n - i + 2) * (i - 1)) / 2 + j - i];
			else out << " ";
			out << " ";
		}
		out << endl;
	}
	return out;
}

template<class T>
istream& operator>>(istream& in, upperTriangularMatrix<T>& m)
{
	for (int i = 0; i < (m.n * (m.n + 1)) / 2; i++) {
		if (in) in >> m.element[i];
		else m.element[i] = 0;
	}
	return in;
}


template<class T>
upperTriangularMatrix<T>::upperTriangularMatrix(int theN) {
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	element = new T[(n * (n + 1)) / 2];
}

template<class T>
upperTriangularMatrix<T>::upperTriangularMatrix(const upperTriangularMatrix<T>& m) {
	n = m.n;
	element = new T[(n * (n + 1)) / 2];
	copy(m.element, m.element + (n * (n + 1)) / 2, element);
}

template<class T>
T upperTriangularMatrix<T>::get(int i, int j) const {
	checkIndex(i, j);
	if (i > j) return 0;

	return element[((n+n-i+2) * (i - 1)) / 2 + j - i];
}

template<class T>
void upperTriangularMatrix<T>::set(int i, int j, const T& value) {
	checkIndex(i, j);
	if (i <= j) element[((n + n - i + 2) * (i - 1)) / 2 + j - i] = value;
	//ignore other positions
}

template<class T>
upperTriangularMatrix<T>& upperTriangularMatrix<T>::operator=(const upperTriangularMatrix<T>& m) {
	n = m.n;
	delete[] element;
	element = new T[(n * (n + 1)) / 2];
	copy(m.element, m.element + (n * (n + 1)) / 2, element);
	return *this;
}

template<class T>
upperTriangularMatrix<T> upperTriangularMatrix<T>::operator+(const upperTriangularMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	upperTriangularMatrix<T> result(n);
	for (int i = 0; i < (n * (n + 1)) / 2; i++) {
		result.element[i] = element[i] + m.element[i];
	}
	return result;
}

template<class T>
upperTriangularMatrix<T> upperTriangularMatrix<T>::operator-(const upperTriangularMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	upperTriangularMatrix<T> result(n);
	for (int i = 0; i < (n * (n + 1)) / 2; i++) {
		result.element[i] = element[i] - m.element[i];
	}
	return result;
}

template<class T>
upperTriangularMatrix<T> upperTriangularMatrix<T>::operator*(const upperTriangularMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	upperTriangularMatrix<T> result(n);
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
lowerTriangularMatrix<T> upperTriangularMatrix<T>::transpose() {
	lowerTriangularMatrix<T> result(n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			result.set(i, j, get(j, i));
		}
	}
	return result;
}

#endif