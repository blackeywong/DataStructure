#pragma once
#ifndef _NEWSPARSEMATRIX_H
#define _NEWSPARSEMATRIX_H
#include <vector>
#include <iostream>
#include <iterator>
#include "../DS5/exceptions.h"
#include "newMatrixTerm.h"
using namespace std;
//Exercise 47
template<class T>
class newSparseMatrix {
	template<class T>
	friend ostream& operator<<(ostream& out, newSparseMatrix<T>& x);
	template<class T>
	friend istream& operator>>(istream& in, newSparseMatrix<T>& x);
public:
	newSparseMatrix() {}
	newSparseMatrix(newSparseMatrix<T>& x);//Exercise 43
	void transpose(newSparseMatrix<T>& b);
	void add(newSparseMatrix<T>& b, newSparseMatrix<T>& c);
	void multiply(newSparseMatrix<T>& b, newSparseMatrix<T>& c);//Exercise 48
	T get(int theRow, int theColumn) const;
	void set(int theRow, int theColumn, const T& theValue);
private:
	void checkIndex(int theRow, int theColumn) const;
	int rows;
	int cols;
	vector<newMatrixTerm<T>> terms;
	vector<int> rowStart;
};

template<class T>
ostream& operator<<(ostream& out, newSparseMatrix<T>& x) {
	out << "rows = " << x.rows << " columns = " << x.cols << endl;
	out << "nonzero terms = " << x.terms.size() << endl;

	int theRow = 0;
	for (int i = 0; i < x.terms.size(); i++) {
		while (theRow != x.rows && i == x.rowStart[theRow + 1])
			theRow++;
		out << "a(" << theRow << "," << x.terms[i].col << ") = " << x.terms[i].value << endl;
	}

	return out;
}

template <class T>
istream& operator>>(istream& in, newSparseMatrix<T>& x) {
	int numberOfTerms;
	in >> x.rows >> x.cols >> numberOfTerms;
	if (x.rows <= 0 || x.cols <= 0 || numberOfTerms < 0) throw IllegalParameterValue("input rows, cols or numberofTerms is bad.");

	x.terms.resize(numberOfTerms);
	x.rowStart.resize(x.rows + 1);
	newMatrixTerm<T> mTerm;
	int lastRow = 0, lastCol = 0;
	int theRow = 0;
	int i = 0;
	for (; i < numberOfTerms; i++) {
		in >> theRow >> mTerm.col >> mTerm.value;
		if (theRow <= 0 || theRow > x.rows || mTerm.col <= 0 || mTerm.col > x.cols || mTerm.value == 0) throw IllegalParameterValue("input row, col or value is bad.");
		if (theRow < lastRow || theRow == lastRow && mTerm.col <= lastCol) throw IllegalParameterValue("input row, col should increase");
		x.terms[i] = mTerm;
		if (lastRow != theRow) {
			x.rowStart[theRow] = i;
			lastRow = theRow;
		}
		lastCol = mTerm.col;
	}
	while (theRow < x.rows) {
		x.rowStart[++theRow] = i;
	}
	return in;
}

template<class T>
newSparseMatrix<T>::newSparseMatrix(newSparseMatrix<T> & x) {
	rows = x.rows;
	cols = x.cols;
	auto bi = back_inserter(terms);
	copy(x.terms.begin(), x.terms.end(), bi);
	auto bi2 = back_inserter(rowStart);
	copy(x.rowStart.begin(), x.rowStart.end(), bi2);
}

template<class T>
void newSparseMatrix<T>::transpose(newSparseMatrix<T> & b) {
	b.cols = rows;
	b.rows = cols;
	b.terms.resize(terms.size());
	b.rowStart.resize(b.rows + 1);

	int* colSize = new int[cols + 1];
	int* colNext = new int[cols + 1];

	for (int i = 1; i <= cols; i++) {
		colSize[i] = 0;
	}
	for (auto i = terms.begin(); i != terms.end(); i++) {
		colSize[(*i).col]++;
	}

	colNext[1] = 0;
	for (int i = 2; i <= cols; i++) {
		colNext[i] = colNext[i - 1] + colSize[i - 1];
	}

	for (int i = 1; i <= cols;i++)
		b.rowStart[i] = colNext[i];//b.rowStart is the same as colNext

	newMatrixTerm<T> mTerm;
	int theRow = 0, lastRow = 0;
	for (int i = 0; i < terms.size(); i++) {
		if (theRow < rows && i == rowStart[theRow + 1])
			theRow++;
		mTerm.col = theRow;
		mTerm.value = terms[i].value;
		b.terms[colNext[terms[i].col]++] = mTerm;
	}

	delete[] colSize;
	delete[] colNext;
}

template<class T>
void newSparseMatrix<T>::add(newSparseMatrix<T> & b, newSparseMatrix<T> & c) {
	if (rows != b.rows || cols != b.cols)
		throw IllegalParameterValue("size not match.");

	c.rows = rows;
	c.cols = cols;
	c.terms.clear();
	c.rowStart.resize(cols+1);

	int* rowSize = new int[rows + 1];

	for (int i = 1; i < rows; i++) {
		rowSize[i] = rowStart[i+1] - rowStart[i];
	}
	rowSize[rows] = terms.size() - rowStart[rows];
	
	for (int i = 1; i <= rows; i++) {
		int index1 = rowStart[i];
		int index2 = b.rowStart[i];
		while (index1 < terms.size() && index2 < b.terms.size()
			&&(i == rows || index1 < rowStart[i+1] && index2 < b.rowStart[i+1])) {
			if (terms[index1].col < b.terms[index2].col) {
				c.terms.push_back(terms[index1]);
				index1++;
			}
			else if (terms[index1].col > b.terms[index2].col) {
				c.terms.push_back(b.terms[index2]);
				index2++;
				rowSize[i]++;
			}
			else{
				T val = terms[index1].value + b.terms[index2].value;
				if (val != 0) {
					newMatrixTerm<T> mTerm;
					mTerm.col = terms[index1].col;
					mTerm.value = val;
					c.terms.push_back(mTerm);
				}
				else {
					rowSize[i]--;
				}
				index1++;
				index2++;
			}
		}

		for (; index1 < terms.size() && (i == rows || index1 < rowStart[i + 1]); index1++) {
			c.terms.push_back(terms[index1]);
		}
		for (; index2 < b.terms.size() && (i == rows || index2 < b.rowStart[i + 1]); index2++) {
			c.terms.push_back(b.terms[index2]);
			rowSize[i] ++;
		}
	}

	c.rowStart[1] = 0;
	for (int i = 2; i <= rows; i++) {
		c.rowStart[i] = c.rowStart[i - 1] + rowSize[i - 1];
	}
	delete[] rowSize;
}

template<class T>
void newSparseMatrix<T>::checkIndex(int theRow, int theColumn) const {
	if (theRow <1 || theRow> rows || theColumn <1 || theColumn > cols)
		throw OutOfBounds();
}

template<class T>
T newSparseMatrix<T>::get(int theRow, int theColumn) const {
	checkIndex(theRow, theColumn);
	int start = rowStart[theRow], end = theRow == rows ? terms.size() - 1 : rowStart[theRow+1] - 1;
	if(start > end) return 0;
	do {
		int middle = (start + end) / 2;
		if (terms[middle].col == theColumn) {
			return terms[middle].value;
		}
		if (terms[middle].col < theColumn)
			start = middle + 1;
		else
			end = middle - 1;

	} while (start <= end);

	return 0;
}

template<class T>
void  newSparseMatrix<T>::set(int theRow, int theColumn, const T& theValue) {
	checkIndex(theRow, theColumn);
	int start = rowStart[theRow], end = theRow == rows ? terms.size() - 1 : rowStart[theRow + 1] - 1;
	do {
		int middle = (start + end) / 2;
		if (terms[middle].col == theColumn) {
			if (theValue == 0) {
				terms.erase(terms.begin() + middle);
				for (int i = theRow + 1; i <= rows; i++) {
					rowStart[i]--;
				}
			}
			else
				terms[middle].value = theValue;
			return;
		}
		else if (terms[middle].col < theColumn)
			start = middle + 1;
		else
			end = middle - 1;

	} while (start <= end);

	if (theValue != 0) {
		newMatrixTerm<T> mTerm;
		mTerm.col = theColumn;
		mTerm.value = theValue;
		terms.insert(terms.begin() + start, mTerm);

		for (int i = theRow + 1; i <= rows; i++) {
			rowStart[i]++;
		}
	}
}

template<class T>
void newSparseMatrix<T>::multiply(newSparseMatrix<T> & b, newSparseMatrix<T> & c) {
	if (cols != b.rows) throw IllegalParameterValue("size not match in mulply.");

	c.rows = rows;
	c.cols = b.cols;
	c.terms.clear();
	c.rowStart.resize(rows + 1);

	c.rowStart[1] = 0;
	for (int i = 1; i <= rows; i++) {
		if(i!=rows)
			c.rowStart[i + 1] = c.rowStart[i];
		for (int j = 1; j <= b.cols; j++) {
			int result = 0;
			int k = rowStart[i];
			while (k < terms.size() && (i == rows || k < rowStart[i+1])) {
				result += terms[k].value * b.get(terms[k].col, j);
				k++;
			}
			if (result != 0) {
				newMatrixTerm<T> mTerm;
				mTerm.col = j;
				mTerm.value = result;
				c.terms.push_back(mTerm);
				if (i != rows)
					c.rowStart[i + 1]++;
			}
		}
	}
}

#endif
