#pragma once
#ifndef _CMATRIX_H
#define _CMATRIX_H
#include "../DS5/exceptions.h"
#include "matrix.h"
//数据结构算法与应用-C++语言描述 第七章
//Exercise 34
template<class T>
class cMatrix {
	template<class T>
	friend ostream& operator<<(ostream&, const cMatrix<T>&);
	template<class T>
	friend istream& operator>>(istream&, cMatrix<T>&);
public:
	cMatrix(int theN = 10);
	cMatrix(const cMatrix<T>&);
	~cMatrix() { delete[] element; }
	int size() const { return n; }
	T get(int, int) const;
	void set(int, int, const T&);
	cMatrix<T>& operator=(const cMatrix<T>&);
	cMatrix<T> operator+(const cMatrix<T>&) const;
	cMatrix<T> operator-(const cMatrix<T>&) const;
	matrix<T> operator*(const cMatrix<T>&) const;
	matrix<T> transpose();
private:
	void checkIndex(int i, int j) const;
	int n;
	T* element;
};

template<class T>
void cMatrix<T>::checkIndex(int i, int j) const {
	if (i < 1 || i> n || j <1 || j> n) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream& out, const cMatrix<T>& m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			if (i == 0) out << m.element[j];
			else if (i == m.n - 1) out << m.element[j + m.n];
			else if (j == 0) out << m.element[i + m.n * 2 - 1];
			else
				out << " ";
			out << " ";
		}
		out << endl;
	}
	return out;
}

template<class T>
istream& operator>>(istream& in, cMatrix<T>& m)
{
	for (int i = 0; i < 3 * m.n - 2; i++) {
		if (in) in >> m.element[i];
		else m.element[i] = 0;
	}
	return in;
}


template<class T>
cMatrix<T>::cMatrix(int theN) {
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	element = new T[3 * n - 2];
}

template<class T>
cMatrix<T>::cMatrix(const cMatrix<T>& m) {
	n = m.n;
	element = new T[3 * n - 2];
	copy(m.element, m.element + 3 * n - 2, element);
}

template<class T>
T cMatrix<T>::get(int i, int j) const {
	checkIndex(i, j);
	if (i == 1) return element[j-1];
	if (i == n) return element[j + n -1];
	if (j == 1) return element[i + n * 2 - 2];
	return 0;

}

template<class T>
void cMatrix<T>::set(int i, int j, const T& value) {
	checkIndex(i, j);
	if (i == 1) element[j-1] = value;
	else if (i == n) element[j + n-1] = value;
	else if (j == 1) element[i + n * 2 -2] = value;
	//ignore others
}

template<class T>
cMatrix<T>& cMatrix<T>::operator=(const cMatrix<T>& m) {
	n = m.n;
	delete[] element;
	element = new T[3 * n - 2];
	copy(m.element, m.element + 3 * n - 2, element);
	return *this;
}

template<class T>
cMatrix<T> cMatrix<T>::operator+(const cMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	cMatrix<T> result(n);
	for (int i = 0; i < 3 * n - 2; i++) {
		result.element[i] = element[i] + m.element[i];
	}
	return result;
}

template<class T>
cMatrix<T> cMatrix<T>::operator-(const cMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	cMatrix<T> result(n);
	for (int i = 0; i < 3 * n - 2; i++) {
		result.element[i] = element[i] - m.element[i];
	}
	return result;
}

template<class T>
matrix<T> cMatrix<T>::operator*(const cMatrix<T>& m) const {
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
matrix<T> cMatrix<T>::transpose() {
	matrix<T> result(n, n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			result(j, i) = get(i, j);
		}
	}
	return result;
}

#endif