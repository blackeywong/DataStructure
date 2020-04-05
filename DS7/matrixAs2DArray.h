#pragma once
#ifndef _MATRIXAS2DARRAY_H
#define _MATRIXAS2DARRAY_H
#include <iostream>
#include "../DS5/exceptions.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第七章
//Exercise 17
template<class T>
class matrixAs2DArray {
	template<class T>
	friend ostream& operator<<(ostream&, const matrixAs2DArray<T>&);
	template<class T>
	friend istream& operator>>(istream&, matrixAs2DArray<T>&);
public:
	matrixAs2DArray() : rows(0), columns(0), element(nullptr) { }
	matrixAs2DArray(int theRows, int theColumns);
	matrixAs2DArray(const matrixAs2DArray<T>& right);
	~matrixAs2DArray();
	T& operator()(int i, int j) const;
	matrixAs2DArray<T>& operator=(const matrixAs2DArray<T>&);
	matrixAs2DArray<T> operator+(const matrixAs2DArray<T>&) const;
	matrixAs2DArray<T> operator-(const matrixAs2DArray<T>&) const;
	matrixAs2DArray<T> operator*(const matrixAs2DArray<T>&) const;
	matrixAs2DArray<T> transpose();
private:
	void clear();
	void initialize();
	int rows;
	int columns;
	T** element;
};

template<class T>
ostream& operator<<(ostream& out, const matrixAs2DArray<T>& m) {
	for (int i = 1; i <= m.rows; i++) {
		for (int j = 1; j <= m.columns; j++) {
			out << m.element[i][j] << " ";
		}
		out << endl;
	}

	return out;
}

template<class T>
istream& operator>>(istream& in, matrixAs2DArray<T>& m) {
	m.clear();

	in >> m.rows >> m.columns;
	if (m.rows < 0 || m.columns < 0) throw IllegalParameterValue("Rows and columns must be >=0");
	if (m.rows == 0 && m.columns > 0 || m.columns == 0 && m.rows > 0) throw IllegalParameterValue("Both or neither rows and columns should be zero.");
	m.initialize();
	for (int i = 1; i <= m.rows; i++) {
		for (int j = 1; j <= m.columns; j++) {
			if (in) {
				in >> m.element[i][j];
			}
			else
			{
				m.element[i][j] = 0;
			}
		}
	}

	return in;
}

template<class T>
matrixAs2DArray<T>::matrixAs2DArray(int theRows, int theColumns) :rows(theRows), columns(theColumns) {
	if (rows < 0 || columns < 0) throw IllegalParameterValue("Rows and columns must be >=0");
	if (rows == 0 && columns > 0 || columns == 0 && rows > 0) throw IllegalParameterValue("Both or neither rows and columns should be zero.");
	if (rows == 0) {
		element = nullptr;
		return;
	}
	initialize();
}

template<class T>
matrixAs2DArray<T>::matrixAs2DArray(const matrixAs2DArray<T>& right): matrixAs2DArray(){
	if (&right == this) return;
	clear();
	rows = right.rows;
	columns = right.columns;
	initialize();
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= columns; j++) {
			element[i][j] = right.element[i][j];
		}
	}
}

template<class T>
matrixAs2DArray<T>::~matrixAs2DArray() {
	clear();
}


template<class T>
void matrixAs2DArray<T>::clear() {
	for (int i = 1; i <= rows; i++) {
		delete[] element[i];
	}
	delete[] element;
	element = nullptr;
}

template<class T>
void matrixAs2DArray<T>::initialize() {
	element = new T * [rows + 1];
	for (int i = 1; i <= rows; i++) {
		element[i] = new T[columns + 1];
	}
}

template<class T>
T& matrixAs2DArray<T>::operator()(int i, int j) const {
	if (i<1 || i>rows || j<1 || j>columns) throw OutOfBounds();
	return element[i][j];
}

template<class T>
matrixAs2DArray<T>& matrixAs2DArray<T>::operator=(const matrixAs2DArray<T>& right) {
	if (&right == this) return *this;
	clear();
	rows = right.rows;
	columns = right.columns;
	initialize();
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= columns; j++) {
			element[i][j] = right.element[i][j];
		}
	}
	return *this;
}

template<class T>
matrixAs2DArray<T> matrixAs2DArray<T>::operator+(const matrixAs2DArray<T>& right) const {
	if (rows != right.rows || columns != right.columns) throw IllegalParameterValue("matrixAs2DArray addition should got same rows and columns.");

	matrixAs2DArray<T> result(rows, columns);
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= columns; j++) {
			result.element[i][j] = element[i][j] + right.element[i][j];
		}
	}
	return result;
}

template<class T>
matrixAs2DArray<T> matrixAs2DArray<T>::operator-(const matrixAs2DArray<T>& right) const {
	if (rows != right.rows || columns != right.columns) throw IllegalParameterValue("matrixAs2DArray substraction should got same rows and columns.");

	matrixAs2DArray<T> result(rows, columns);
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= columns; j++) {
			result.element[i][j] = element[i][j] - right.element[i][j];
		}
	}
	return result;
}

template<class T>
matrixAs2DArray<T> matrixAs2DArray<T>::operator*(const matrixAs2DArray<T>& right) const {
	if (columns != right.rows) throw IllegalParameterValue("matrixAs2DArray multply must have m * n and n *s .");

	matrixAs2DArray<T> result(rows, right.columns);
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= right.columns; j++) {
			result.element[i][j] = 0;
			for (int k = 1; k <= columns; k++) {
				result.element[i][j] += element[i][k] * right.element[k][j];
			}
		}
	}

	return result;
}

template<class T>
matrixAs2DArray<T> matrixAs2DArray<T>::transpose() {
	matrixAs2DArray<T> result(columns, rows);
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= columns; j++) {
			result.element[j][i] = element[i][j];
		}
	}
	return result;

}

#endif
