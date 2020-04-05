#pragma once
#ifndef _TOEPLITZMATRIX_H
#define _TOEPLITZMATRIX_H
#include "../DS5/exceptions.h"
#include "matrix.h"
//数据结构算法与应用-C++语言描述 第七章
//Exercise 34
template<class T>
class toeplitzMatrix {
	template<class T>
	friend ostream& operator<<(ostream&, const toeplitzMatrix<T>&);
	template<class T>
	friend istream& operator>>(istream&, toeplitzMatrix<T>&);
public:
	toeplitzMatrix(int theN = 10);
	toeplitzMatrix(const toeplitzMatrix<T>&);
	~toeplitzMatrix() { delete[] element; }
	int size() const { return n; }
	T get(int, int) const;
	void set(int, int, const T&);
	toeplitzMatrix<T>& operator=(const toeplitzMatrix<T>&);
	toeplitzMatrix<T> operator+(const toeplitzMatrix<T>&) const;
	toeplitzMatrix<T> operator-(const toeplitzMatrix<T>&) const;
	matrix<T> operator*(const toeplitzMatrix<T>&) const;
	toeplitzMatrix<T> transpose();
private:
	void checkIndex(int i, int j) const;
	int n;
	T* element;
};

template<class T>
void toeplitzMatrix<T>::checkIndex(int i, int j) const {
	if (i < 1 || i> n || j <1 || j> n) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream& out, const toeplitzMatrix<T>& m) {
	for (int i = 1; i <= m.n; i++) {
		for (int j = 1; j <= m.n; j++) {
			if (i <= j) out << m.element[j - i] << " ";
			else out << m.element[i - j + m.n - 1] << " ";
		}
		out << endl;
	}
	return out;
}

template<class T>
istream& operator>>(istream& in, toeplitzMatrix<T>& m)
{
	for (int i = 0; i < 2 * m.n - 1; i++) {
		if (in) in >> m.element[i];
		else m.element[i] = 0;
	}
	return in;
}


template<class T>
toeplitzMatrix<T>::toeplitzMatrix(int theN) {
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	element = new T[2 * n - 1];
}

template<class T>
toeplitzMatrix<T>::toeplitzMatrix(const toeplitzMatrix<T>& m) {
	n = m.n;
	element = new T[2 * n - 1];
	copy(m.element, m.element + 2 * n - 1, element);
}

template<class T>
T toeplitzMatrix<T>::get(int i, int j) const {
	checkIndex(i, j);
	if (i < j) return element[j-i];
	else return element[i-j+n-1];
}

template<class T>
void toeplitzMatrix<T>::set(int i, int j, const T& value) {//set one value means set one line
	checkIndex(i, j);
	if (i < j) element[j - i] = value;
	if (i >= j) element[i - j + n - 1] = value;
}

template<class T>
toeplitzMatrix<T>& toeplitzMatrix<T>::operator=(const toeplitzMatrix<T>& m) {
	n = m.n;
	delete[] element;
	element = new T[2 * n - 1];
	copy(m.element, m.element + 2 * n - 1, element);
	return *this;
}

template<class T>
toeplitzMatrix<T> toeplitzMatrix<T>::operator+(const toeplitzMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	toeplitzMatrix<T> result(n);
	for (int i = 0; i < 2 * n - 1; i++) {
		result.element[i] = element[i] + m.element[i];
	}
	return result;
}

template<class T>
toeplitzMatrix<T> toeplitzMatrix<T>::operator-(const toeplitzMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	toeplitzMatrix<T> result(n);
	for (int i = 0; i < 2 * n - 1; i++) {
		result.element[i] = element[i] - m.element[i];
	}
	return result;
}

template<class T>
matrix<T> toeplitzMatrix<T>::operator*(const toeplitzMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	matrix<T> result(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int res = 0;
			for (int k = 0; k < n; k++) {
				res += get(i + 1, k + 1) * m.get(k + 1, j + 1);
			}
			result(i + 1, j + 1) = res;
		}
	}
	return result;
}

template<class T>
toeplitzMatrix<T> toeplitzMatrix<T>::transpose() {
	toeplitzMatrix<T> result(*this);
	for (int i = 1; i < n; i++) {
		swap(result.element[i], result.element[i+n-1]);
	}
	return result;
}

#endif