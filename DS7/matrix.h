#pragma once
#ifndef _MATRIX_H
#define _MATRIX_H
#include <iostream>
#include "../DS5/exceptions.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第七章
//Exercise 15,16
template<class T>
class matrix {
	template<class T>
	friend ostream& operator<<(ostream&, const matrix<T>&);
	template<class T>
	friend istream& operator>>(istream&, matrix<T>&);//Exercise 15
public:
	matrix(int theRows = 0, int theColumns = 0);
	matrix(const matrix<T>&);
	~matrix(){delete[] element;}
	int getRows() const { return rows; }
	int getColumns() const { return columns; }
	T& operator()(int i, int j) const;
	matrix<T>& operator=(const matrix<T>&);
	matrix<T> operator++() const;
	matrix<T> operator+(const matrix<T>&) const;
	matrix<T> operator--() const;
	matrix<T> operator-(const matrix<T>&) const;
	matrix<T> operator*(const matrix<T>&) const;
	matrix<T>& operator+=(const T&);
	matrix<T>& operator-=(const T&);//Exercise 15
	matrix<T>& operator*=(const T&);//Exercise 15
	matrix<T>& operator/=(const T&);//Exercise 15
	matrix<T> transpose();//Exercise 16
private:
	int rows;
	int columns;
	T* element;
};

template<class T>
ostream& operator<<(ostream& out, const matrix<T>& m) {
	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m.columns; j++) {
			out << m.element[i * m.columns + j] << " ";
		}
		out << endl;
	}

	return out;
}

template<class T>
istream& operator>>(istream& in, matrix<T>& m) {
	in >> m.rows >> m.columns;
	if (m.rows < 0 || m.columns < 0) throw IllegalParameterValue("Rows and columns must be >=0");
	if (m.rows == 0 && m.columns > 0 || m.columns == 0 && m.rows > 0) throw IllegalParameterValue("Both or neither rows and columns should be zero.");
	delete[] m.element;
	m.element = new T[m.rows * m.columns];

	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m.columns; j++) {
			if (in) {
				in >> m.element[i * m.columns + j];
			}
			else
			{
				m.element[i * m.columns + j] = 0;
			}
		}
	}

	return in;
}

template<class T>
matrix<T>::matrix(int theRows, int theColumns) :rows(theRows), columns(theColumns) {
	if (rows < 0 || columns < 0) throw IllegalParameterValue("Rows and columns must be >=0");
	if (rows == 0 && columns > 0 || columns == 0 && rows > 0) throw IllegalParameterValue("Both or neither rows and columns should be zero.");
	element = new T[rows * columns];
}

template<class T>
matrix<T>::matrix(const matrix<T>& right) {
	rows = right.rows;
	columns = right.columns;
	element = new T[rows * columns];
	copy(right.element, right.element + rows * columns, element);
}

template<class T>
T& matrix<T>::operator()(int i, int j) const {
	if (i<1 || i>rows || j<1 || j>columns) throw OutOfBounds();
	return element[(i-1) * rows + j-1];
}

template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& right){
	if (&right == this) return *this;

	rows = right.rows;
	columns = right.columns;
	delete[] element;
	element = new T[rows * columns];
	copy(right.element, right.element + rows * columns, element);
	return *this;
}

template<class T>
matrix<T> matrix<T>::operator++() const {
	matrix<T> result(rows, columns);
	for (int i = 0; i < rows * columns; i++) {
		result.element[i] = ++element[i];
	}
	return result;
}

template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& right) const {
	if (rows != right.rows || columns != right.columns) throw IllegalParameterValue("matrix addition should got same rows and columns.");

	matrix<T> result(rows, columns);
	for (int i = 0; i < rows * columns; i++) {
		result.element[i] = element[i] + right.element[i];
	}
	return result;
}

template<class T>
matrix<T> matrix<T>::operator--() const {
	matrix<T> result(rows, columns);
	for (int i = 0; i < rows * columns; i++) {
		result.element[i] = --element[i];
	}
	return result;
}

template<class T>
matrix<T> matrix<T>::operator-(const matrix<T>& right) const {
	if (rows != right.rows || columns != right.columns) throw IllegalParameterValue("matrix substraction should got same rows and columns.");

	matrix<T> result(rows, columns);
	for (int i = 0; i < rows * columns; i++) {
		result.element[i] = element[i] - right.element[i];
	}
	return result;
}

template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& right) const {
	if (columns != right.rows) throw IllegalParameterValue("matrix multply must have m * n and n *s .");

	matrix<T> result(rows, right.columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < right.columns; j++) {
			result.element[i * rows + j] = 0;
			for (int k = 0; k < columns; k++) {
				result.element[i * rows + j] += element[i * columns + k] * right.element[k * right.columns + j];
			}
		}
	}

	//int ct = 0, cm = 0, cw = 0;
	//for (int i = 1; i <= rows; i++) {
	//	for (int j = 1; j <= right.columns; j++) {
	//		T sum = element[ct] * right.element[cm];
	//		for (int k = 2; k <= columns; k++) {
	//			ct++;
	//			cm += right.columns;
	//			sum += element[ct] * right.element[cm];
	//		}
	//		result.element[cw++] = sum;
	//		ct -= columns - 1;
	//		cm = j;
	//	}
	//	ct += columns;
	//	cm = 0;
	//}

	return result;
}

template<class T>
matrix<T>& matrix<T>::operator+=(const T& value) {
	for (int i = 0; i < rows * columns; i++) {
		element[i] += value;
	}
	return *this;
}

template<class T>
matrix<T>& matrix<T>::operator-=(const T& value) {
	for (int i = 0; i < rows * columns; i++) {
		element[i] -= value;
	}
	return *this;
}

template<class T>
matrix<T>& matrix<T>::operator*=(const T& value) {
	for (int i = 0; i < rows * columns; i++) {
		element[i] *= value;
	}
	return *this;
}

template<class T>
matrix<T>& matrix<T>::operator/=(const T& value) {
	if (value == 0) throw IllegalParameterValue("divide 0");
	for (int i = 0; i < rows * columns; i++) {
		element[i] /= value;
	}
	return *this;
}

template<class T>
matrix<T> matrix<T>::transpose() {
	matrix<T> result(columns, rows);
	for (int i = 0; i < rows * columns; i++) {
		result.element[(i%columns) * rows + i/columns] = element[i];
	}
	return result;

}

#endif
