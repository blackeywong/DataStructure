#pragma once
#ifndef _SQUAREBANDMATRIX_H
#define _SQUAREBANDMATRIX_H
#include <iostream>
#include "../DS5/exceptions.h"
#include "matrix.h"
//数据结构算法与应用-C++语言描述 第七章
//Exercise 37
template<class T>
class squareBandMatrix {
	template<class T>
	friend ostream& operator<<(ostream&, const squareBandMatrix<T>&);
	template<class T>
	friend istream& operator>>(istream&, squareBandMatrix<T>&);
public:
	squareBandMatrix(int theN = 10, int theA = 3);
	squareBandMatrix(const squareBandMatrix<T>&);
	~squareBandMatrix() { delete[] element; }
	T get(int, int) const;
	void set(int, int, const T&);
	squareBandMatrix<T>& operator=(const squareBandMatrix<T>&);
	squareBandMatrix<T> operator+(const squareBandMatrix<T>&) const;
	squareBandMatrix<T> operator-(const squareBandMatrix<T>&) const;
	matrix<T> operator*(const squareBandMatrix<T>&) const;
	squareBandMatrix<T> transpose();
private:
	void checkIndex(int i, int j) const;
	int n;
	int a;
	int cnt;
	T* element;
};

template<class T>
void squareBandMatrix<T>::checkIndex(int i, int j) const {
	if (i < 0 || i> n-1 || j <0 || j> n-1) throw OutOfBounds();
}

template<class T>
ostream& operator<<(ostream& out, const squareBandMatrix<T>& m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			if (i >= j && i-j < m.a) out << m.element[((m.n - m.a + 1) + (m.n - (i - j) - 1)) * ((m.a - 1) - (i - j)) / 2 + j];
			else if (i < j && j-i < m.a) out << m.element[((m.n - m.a + 1) + m.n) * m.a / 2 + ((m.n-1)+m.n - (j - i) + 1) * ((j - i) - 1) / 2 + i];
			else out << " ";
			out << " ";
		}
		out << endl;
	}
	return out;
}

template<class T>
istream& operator>>(istream& in, squareBandMatrix<T>& m)
{
	for (int i = 0; i < m.cnt; i++) {
		if (in) in >> m.element[i];
		else m.element[i] = 0;
	}
	return in;
}


template<class T>
squareBandMatrix<T>::squareBandMatrix(int theN, int theA) {
	if (theN < 1) throw IllegalParameterValue("matrix size should be >=1");

	n = theN;
	a = theA;
	cnt = n * n - (1 + n - a) * (n - a);//n*n -2*(1+...+(n-a)) = n*n - (1+n-a)*(n-a) 
	element = new T[cnt];
}

template<class T>
squareBandMatrix<T>::squareBandMatrix(const squareBandMatrix<T>& m) {
	n = m.n;
	a = m.a;
	cnt = m.cnt;
	element = new T[cnt];
	copy(m.element, m.element + cnt, element);
}

template<class T>
T squareBandMatrix<T>::get(int i, int j) const {
	checkIndex(i, j);
	if (i >= j && i-j<a) return element[((n-a+1)+(n-(i-j)-1))*((a-1)-(i-j))/2+j];
	else if(i<j && j-i<a) return element[((n-a+1)+n)*a/2+((n - 1) + n-(j-i)+1)*((j-i)-1)/2+i];
	else return 0;
}

template<class T>
void squareBandMatrix<T>::set(int i, int j, const T& value) {//set one value means set one line
	checkIndex(i, j);
	if (i >= j && i-j < a) element[((n - a + 1) + (n - (i - j) - 1)) * ((a - 1) - (i - j)) / 2 + j] = value;
	else if (i < j && j-i < a) element[((n - a + 1) + n) * a / 2 + ((n - 1) + n - (j - i) + 1) * ((j - i) - 1) / 2 + i] = value;
	//ignore others
}

template<class T>
squareBandMatrix<T>& squareBandMatrix<T>::operator=(const squareBandMatrix<T>& m) {
	n = m.n;
	a = m.a;
	cnt = m.cnt;
	delete[] element;
	element = new T[cnt];
	copy(m.element, m.element + cnt, element);
	return *this;
}

template<class T>
squareBandMatrix<T> squareBandMatrix<T>::operator+(const squareBandMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	squareBandMatrix<T> result(n, a);
	for (int i = 0; i < cnt; i++) {
		result.element[i] = element[i] + m.element[i];
	}
	return result;
}

template<class T>
squareBandMatrix<T> squareBandMatrix<T>::operator-(const squareBandMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	squareBandMatrix<T> result(n, a);
	for (int i = 0; i < cnt; i++) {
		result.element[i] = element[i] - m.element[i];
	}
	return result;
}

template<class T>
matrix<T> squareBandMatrix<T>::operator*(const squareBandMatrix<T>& m) const {
	if (n != m.n) throw IllegalParameterValue("must have same size");
	matrix<T> result(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int res = 0;
			for (int k = 0; k < n; k++) {
				res += get(i, k) * m.get(k, j);
			}
			result(i + 1, j + 1) = res;
		}
	}
	return result;
}

template<class T>
squareBandMatrix<T> squareBandMatrix<T>::transpose() {
	squareBandMatrix<T> result(*this);
	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < n; j++) {
	//		result.set(j, i, get(i, j));
	//	}
	//}
	//int orig = ((n - a + 1) + n - 1) * (a - 1) / 2;//index of D[0,0]
	for (int i = 1; i < a; i++){
		for (int j = 0; j < n-i; j++) {
			swap(result.element[((n - a + 1) + (n - ((j+i) - j) - 1)) * ((a - 1) - ((j+i) - j)) / 2 + j], 
				result.element[((n - a + 1) + n) * a / 2 + ((n - 1) + n - ((j+i) - j) + 1) * (((j+i) - j) - 1) / 2 + j]);
		}
	}
	return result;
}

#endif