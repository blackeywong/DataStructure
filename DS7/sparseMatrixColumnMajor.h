#pragma once
#ifndef _SPARSEMATRIXCOLUMNMAJOR_H
#define _SPARSEMATRIXCOLUMNMAJOR_H
#include <vector>
#include <iostream>
#include <iterator>
#include "../DS5/exceptions.h"
#include "matrixTerm.h"
using namespace std;
//Exercise 44

template<class T>
class sparseMatrixColumnMajor {
	template<class T>
	friend ostream& operator<<(ostream& out, sparseMatrixColumnMajor<T>& x);
	template<class T>
	friend istream& operator>>(istream& in, sparseMatrixColumnMajor<T>& x);
public:
	sparseMatrixColumnMajor() {}
	sparseMatrixColumnMajor(sparseMatrixColumnMajor<T>& x);
	void transpose(sparseMatrixColumnMajor<T>& b);
	void add(sparseMatrixColumnMajor<T>& b, sparseMatrixColumnMajor<T>& c);
	void multiply(sparseMatrixColumnMajor<T>& b, sparseMatrixColumnMajor<T>& c);//Exercise 46
	T get(int theRow, int theColumn) const;
	void set(int theRow, int theColumn, const T& theValue);
private:
	void checkIndex(int theRow, int theColumn) const;
	int rows;
	int cols;
	vector<matrixTerm<T>> terms;
};

template<class T>
ostream& operator<<(ostream& out, sparseMatrixColumnMajor<T>& x) {
	out << "rows = " << x.rows << " columns = " << x.cols << endl;
	out << "nonzero terms = " << x.terms.size() << endl;

	for (auto i = x.terms.begin(); i != x.terms.end(); i++) {
		out << "a(" << (*i).row << "," << (*i).col << ") = " << (*i).value << endl;
	}

	return out;
}

template <class T>
istream& operator>>(istream& in, sparseMatrixColumnMajor<T>& x) {
	int numberOfTerms;
	in >> x.cols >> x.rows >> numberOfTerms;
	if (x.rows <= 0 || x.cols <= 0 || numberOfTerms < 0) throw IllegalParameterValue("input rows, cols or numberofTerms is bad.");

	x.terms.resize(numberOfTerms);
	matrixTerm<T> mTerm;
	int lastRow = 0, lastCol = 0;
	for (int i = 0; i < numberOfTerms; i++) {
		in >>mTerm.col >> mTerm.row >> mTerm.value;
		if (mTerm.row <= 0 || mTerm.row > x.rows || mTerm.col <= 0 || mTerm.col > x.cols || mTerm.value == 0) throw IllegalParameterValue("input row, col or value is bad.");
		if (mTerm.col < lastCol || mTerm.col == lastCol && mTerm.row <= lastRow) throw IllegalParameterValue("input row, col should increase");
		x.terms[i] = mTerm;
		lastRow = mTerm.row;
		lastCol = mTerm.col;
	}
	return in;
}

template<class T>
sparseMatrixColumnMajor<T>::sparseMatrixColumnMajor(sparseMatrixColumnMajor<T>& x) {
	rows = x.rows;
	cols = x.cols;
	auto bi = back_inserter(terms);
	copy(x.terms.begin(), x.terms.end(), bi);
}

template<class T>
void sparseMatrixColumnMajor<T>::transpose(sparseMatrixColumnMajor<T>& b) {
	b.cols = rows;
	b.rows = cols;
	b.terms.resize(terms.size());

	int* colSize = new int[rows + 1];
	int* colNext = new int[rows + 1];

	for (int i = 1; i <= rows; i++) {
		colSize[i] = 0;
	}
	for (auto i = terms.begin(); i != terms.end(); i++) {
		colSize[(*i).row]++;
	}

	colNext[1] = 0;
	for (int i = 2; i <= rows; i++) {
		colNext[i] = colNext[i - 1] + colSize[i - 1];
	}

	matrixTerm<T> mTerm;
	for (auto i = terms.begin(); i != terms.end(); i++) {
		mTerm.row = (*i).col;
		mTerm.col = (*i).row;
		mTerm.value = (*i).value;
		b.terms[colNext[mTerm.col]++] = mTerm;
	}

	delete[] colSize;
	delete[] colNext;
}

template<class T>
void sparseMatrixColumnMajor<T>::add(sparseMatrixColumnMajor<T>& b, sparseMatrixColumnMajor<T>& c) {
	if (rows != b.rows || cols != b.cols)
		throw IllegalParameterValue("size not match.");

	c.rows = rows;
	c.cols = cols;
	c.terms.clear();

	auto it = terms.begin();
	auto ib = b.terms.begin();
	while (it != terms.end() && ib != b.terms.end()) {
		int index1 = ((*it).col - 1) * rows + (*it).row;
		int index2 = ((*ib).col - 1) * rows + (*ib).row;

		if (index1 < index2) {
			c.terms.push_back(*it);
			it++;
		}
		else if (index1 > index2) {
			c.terms.push_back(*ib);
			ib++;
		}
		else {
			if ((*it).value + (*ib).value != 0) {
				matrixTerm<T> mTerm((*it).row, (*it).col, (*it).value + (*ib).value);
				c.terms.push_back(mTerm);
			}
			it++;
			ib++;
		}
	}

	for (; it != terms.end(); it++) {
		c.terms.push_back(*it);
	}
	for (; ib != b.terms.end(); it++) {
		c.terms.push_back(*ib);
	}
}

template<class T>
void sparseMatrixColumnMajor<T>::checkIndex(int theRow, int theColumn) const {
	if (theRow <1 || theRow> rows || theColumn <1 || theColumn > cols)
		throw OutOfBounds();
}

template<class T>
T sparseMatrixColumnMajor<T>::get(int theRow, int theColumn) const {
	checkIndex(theRow, theColumn);
	int start = 0, end = terms.size() - 1;
	if (start > end) return 0;
	do {
		int middle = (start + end) / 2;
		if (terms[middle].col == theColumn && terms[middle].row == theRow) {
			return terms[middle].value;
		}
		if (terms[middle].col < theColumn || terms[middle].col == theColumn && terms[middle].row < theRow)
			start = middle + 1;
		else
			end = middle - 1;

	} while (start <= end);

	return 0;
}

template<class T>
void  sparseMatrixColumnMajor<T>::set(int theRow, int theColumn, const T& theValue) {
	checkIndex(theRow, theColumn);
	int start = 0, end = terms.size() - 1;
	do {
		int middle = (start + end) / 2;
		if (terms[middle].col == theColumn && terms[middle].row == theRow) {
			if (theValue == 0)
				terms.erase(terms.begin() + middle);
			else
				terms[middle].value = theValue;
			return;
		}
		else if (terms[middle].col < theColumn || terms[middle].col == theColumn && terms[middle].row < theRow)
			start = middle + 1;
		else
			end = middle - 1;

	} while (start <= end);

	if (theValue != 0)
		terms.insert(terms.begin() + start, matrixTerm<T>(theRow, theColumn, theValue));
}

template<class T>
void sparseMatrixColumnMajor<T>::multiply(sparseMatrixColumnMajor<T>& b, sparseMatrixColumnMajor<T>& c) {
	if (cols != b.rows) throw IllegalParameterValue("size not match in mulply.");

	c.rows = rows;
	c.cols = b.cols;
	c.terms.clear();

	int n = 0;//used to remember where the loop should be go back in terms vector
	for (int i = 1; i <= b.cols; i++) {
		int k = n;
		for (int j = 1; j <= rows; j++) {
			int result = 0;
			n = k;
			while (k < b.terms.size() && b.terms[k].col == i) {
				result += get(j, b.terms[k].row) * b.terms[k].value;
				k++;
			}
			if (result != 0) {
				c.terms.push_back(matrixTerm<T>(j, i, result));
			}
			if (j < rows)
				k = n;
			else
				n = k;
		}
	}
}

#endif
