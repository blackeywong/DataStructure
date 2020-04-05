#pragma once
#ifndef _LINKEDMATRIX_H
#define _LINKEDMATRIX_H
#include <iostream>
#include <iterator>
#include "../DS5/exceptions.h"
#include "../DS6/extendedchain.h"
#include "rowElement.h"
#include "headElement.h"

using namespace std;
//Exercise 51
template<class T>
class linkedMatrix {
	template<class T>
	friend ostream& operator<<(ostream& out, linkedMatrix<T>& x);
	template<class T>
	friend istream& operator>>(istream& in, linkedMatrix<T>& x);
public:
	linkedMatrix() {}
	linkedMatrix(linkedMatrix<T>& x);
	void transpose(linkedMatrix<T>& b);
	void add(linkedMatrix<T>& b, linkedMatrix<T>& c);
	void substract(linkedMatrix<T>& b, linkedMatrix<T>& c);
	void multiply(linkedMatrix<T>& b, linkedMatrix<T>& c);
	T get(int theRow, int theColumn);
	void set(int theRow, int theColumn, const T& theValue);
private:
	void checkIndex(int theRow, int theColumn) const;
	int rows;
	int cols;
	int number;
	ExtendedChain<headElement<rowElement<T>>> headerChain;
};

template<class T>
ostream& operator<<(ostream& out, linkedMatrix<T>& x) {
	out << "rows = " << x.rows << " columns = " << x.cols << endl;
	out << "nonzero terms = " << x.number << endl;
	for (auto i = x.headerChain.begin(); i != x.headerChain.end(); i++) {
		for (auto j = (*i).rowChain.begin(); j != (*i).rowChain.end(); j++) {
			out << "a(" << (*i).row << "," << (*j).col << ") = " << (*j).value << endl;
		}
	}

	return out;
}

template <class T>
istream& operator>>(istream& in, linkedMatrix<T>& x) {
	in >> x.rows >> x.cols >> x.number;
	if (x.rows <= 0 || x.cols <= 0 || x.number < 0) throw IllegalParameterValue("input rows, cols or numberofTerms is bad.");

	for (int i = 1; i <= x.rows; i++) {
		headElement<rowElement<T>> head(i);
		head.rowChain.clear();
		x.headerChain.push_back(head);
	}

	int lastRow = 0, lastCol = 0;
	int row, col;
	T value;
	auto iter = x.headerChain.begin();
	for (int i = 0; i < x.number; i++) {
		in >> row >> col >> value;
		if (row <= 0 || row > x.rows || col <= 0 || col > x.cols || value == 0) throw IllegalParameterValue("input row, col or value is bad.");
		if (row < lastRow || row == lastRow && col <= lastCol) throw IllegalParameterValue("input row, col should increase");
		rowElement<T> ele(col, value);
		while ((*iter).row < row) 
			iter++;
		(*iter).rowChain.push_back(ele);
		lastRow = row;
		lastCol = col;
	}
	return in;
}

template<class T>
linkedMatrix<T>::linkedMatrix(linkedMatrix<T>& x) {
	rows = x.rows;
	cols = x.cols;
	number = x.number;
	headerChain = x.headerChain;
}

template<class T>
void linkedMatrix<T>::transpose(linkedMatrix<T>& b) {
	b.headerChain.clear();

	ExtendedChain<rowElement<T>>* bin;
	bin = new ExtendedChain<rowElement<T>>[cols + 1];

	typename ExtendedChain<headElement<rowElement<T>>>::iterator ih = headerChain.begin(), ihEnd = headerChain.end();

	while(ih != ihEnd) {
		int r = ih->row;

		typename ExtendedChain<rowElement<T>>::iterator ir = ih->rowChain.begin(), irEnd = ih->rowChain.end();

		rowElement<T> x;
		x.col = r;

		while (ir != irEnd) {
			x.value = ir->value;
			bin[ir->col].push_back(x);
			ir++;
		}
		ih++;
	}

	b.rows = cols;
	b.cols = rows;
	b.number = number;

	headElement<rowElement<T>> h;
	for (int i = 1; i <= cols; i++) {
		h.row = i;
		h.rowChain = bin[i];
		b.headerChain.push_back(h);
		if (!bin[i].empty()) {
			bin[i].zero();
		}
	}
	h.rowChain.zero();

	delete[] bin;

}

template<class T>
void linkedMatrix<T>::add(linkedMatrix<T>& b, linkedMatrix<T>& c) {
	if (rows != b.rows || cols != b.cols)
		throw IllegalParameterValue("size not match.");

	c.rows = rows;
	c.cols = cols;
	c.headerChain.clear();
	c.number = 0;

	for (int i = 1; i <= rows; i++) {
		headElement<rowElement<T>> head(i);
		head.rowChain.clear();
		c.headerChain.push_back(head);
	}

	auto ha = headerChain.begin(), hb = b.headerChain.begin(), hc = c.headerChain.begin();
	for (; ha != headerChain.end(); ha++, hb++, hc++) {
		auto ra = (*ha).rowChain.begin(), rb = (*hb).rowChain.begin();
		while (ra != (*ha).rowChain.end() && rb != (*hb).rowChain.end()) {
			if ((*ra).col < (*rb).col) {
				(*hc).rowChain.push_back(*ra);
				c.number++;
				ra++;
			}
			else if ((*ra).col > (*rb).col) {
				(*hc).rowChain.push_back(*rb);
				c.number++;
				rb++;
			}
			else {
				T val = (*ra).value + (*rb).value;
				if (val != 0) {
					rowElement<T> ele((*ra).col, val);
					(*hc).rowChain.push_back(ele);
					c.number++;
				}
				ra++;
				rb++;
			}
		}

		for (; ra != (*ha).rowChain.end(); ra++) {
			(*hc).rowChain.push_back(*ra);
			c.number++;
		}
		for (; rb != (*hb).rowChain.end(); rb++) {
			(*hc).rowChain.push_back(*rb);
			c.number++;
		}
	}

}

template<class T>
void linkedMatrix<T>::substract(linkedMatrix<T>& b, linkedMatrix<T>& c) {
	if (rows != b.rows || cols != b.cols)
		throw IllegalParameterValue("size not match.");

	c.rows = rows;
	c.cols = cols;
	c.headerChain.clear();
	c.number = 0;

	for (int i = 1; i <= rows; i++) {
		headElement<rowElement<T>> head(i);
		head.rowChain.clear();
		c.headerChain.push_back(head);
	}

	auto ha = headerChain.begin(), hb = b.headerChain.begin(), hc = c.headerChain.begin();
	for (; ha != headerChain.end(); ha++, hb++, hc++) {
		auto ra = (*ha).rowChain.begin(), rb = (*hb).rowChain.begin();
		while (ra != (*ha).rowChain.end() && rb != (*hb).rowChain.end()) {
			if ((*ra).col < (*rb).col) {
				(*hc).rowChain.push_back(*ra);
				c.number++;
				ra++;
			}
			else if ((*ra).col > (*rb).col) {
				rowElement<T> ele((*rb).col, -(*rb).value);
				(*hc).rowChain.push_back(ele);
				c.number++;
				rb++;
			}
			else {
				T val = (*ra).value - (*rb).value;
				if (val != 0) {
					rowElement<T> ele((*ra).col, val);
					(*hc).rowChain.push_back(ele);
					c.number++;
				}
				ra++;
				rb++;
			}
		}

		for (; ra != (*ha).rowChain.end(); ra++) {
			(*hc).rowChain.push_back(*ra);
			c.number++;
		}
		for (; rb != (*hb).rowChain.end(); rb++) {
			rowElement<T> ele((*rb).col, -(*rb).value);
			(*hc).rowChain.push_back(ele);
			c.number++;
		}
	}

}

template<class T>
void linkedMatrix<T>::checkIndex(int theRow, int theColumn) const {
	if (theRow <1 || theRow> rows || theColumn <1 || theColumn > cols)
		throw OutOfBounds();
}

template<class T>
T linkedMatrix<T>::get(int theRow, int theColumn) {
	checkIndex(theRow, theColumn);
	
	typename ExtendedChain<headElement<rowElement<T>>>::iterator ih = headerChain.begin();
	for (; ih != headerChain.end(); ih++) {
		if ((*ih).row == theRow)
			break;
	}

	for (auto ir = (*ih).rowChain.begin(); ir != (*ih).rowChain.end(); ir++) {
		if ((*ir).col == theColumn)
			return (*ir).value;
	}
	return 0;
}

template<class T>
void  linkedMatrix<T>::set(int theRow, int theColumn, const T & theValue) {
	checkIndex(theRow, theColumn);
	typename ExtendedChain<headElement<rowElement<T>>>::iterator ih = headerChain.begin();
	for (; ih != headerChain.end(); ih++) {
		if ((*ih).row == theRow)
			break;
	}

	auto ir = (*ih).rowChain.begin();
	while( ir != (*ih).rowChain.end()) {
		if((*ir).col > theColumn)
			break;
		else if ((*ir).col == theColumn) {
			if (theValue != 0)
				(*ir).value = theValue;
			else {
				(*ih).rowChain.erase((*ih).rowChain.iteratorToIndex(ir));
				number--;
			}
			return;
		}
		ir++;
	}
	
	if (theValue == 0)
		return;

	//insert
	rowElement<T> ele(theColumn, theValue);
	(*ih).rowChain.insert((*ih).rowChain.iteratorToIndex(ir), ele);
	number++;
}

template<class T>
void linkedMatrix<T>::multiply(linkedMatrix<T> & b, linkedMatrix<T> & c) {
	if (cols != b.rows) throw IllegalParameterValue("size not match in mulply.");

	c.rows = rows;
	c.cols = b.cols;
	c.headerChain.clear();
	c.number = 0;

	for (int i = 1; i <= rows; i++) {
		headElement<rowElement<T>> head(i);
		head.rowChain.clear();
		c.headerChain.push_back(head);
	}

	auto ha = headerChain.begin(), hc = c.headerChain.begin();
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= b.cols; j++) {
			int result = 0;
			auto ra = (*ha).rowChain.begin();
			while (ra != (*ha).rowChain.end()) {
				result += (*ra).value * b.get((*ra).col, j);
				ra++;
			}
			if (result != 0) {
				rowElement<T> ele(j, result);
				(*hc).rowChain.push_back(ele);
				c.number++;
			}
		}
		ha++;
		hc++;
	}
}
#endif
