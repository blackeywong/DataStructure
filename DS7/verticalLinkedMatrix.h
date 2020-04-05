#pragma once
#ifndef _VERTICALLINKEDMATRIX_H
#define _VERTICALLINKEDMATRIX_H
#include <iostream>
#include <iterator>
#include "../DS5/exceptions.h"
#include "../DS6/extendedchain.h"
#include "verticalLinkedMatrixNode.h"

using namespace std;
//Exercise 53
template<class T>
class verticalLinkedMatrix {
	template<class T>
	friend ostream& operator<<(ostream& out, verticalLinkedMatrix<T>& x);
	template<class T>
	friend istream& operator>>(istream& in, verticalLinkedMatrix<T>& x);
public:
	verticalLinkedMatrix() { firstNode = new verticalLinkedMatrixNode<T>(0, 0, 0); number = 0; }
	verticalLinkedMatrix(verticalLinkedMatrix<T>& x);
	~verticalLinkedMatrix() { clear(); }
	void transpose(verticalLinkedMatrix<T>& b);
	void add(verticalLinkedMatrix<T>& b, verticalLinkedMatrix<T>& c);
	void substract(verticalLinkedMatrix<T>& b, verticalLinkedMatrix<T>& c);
	void multiply(verticalLinkedMatrix<T>& b, verticalLinkedMatrix<T>& c);
	T get(int theRow, int theColumn);
	void set(int theRow, int theColumn, const T& theValue);
	void clear();
private:
	void insertNode(verticalLinkedMatrixNode<T>* cur, verticalLinkedMatrixNode<T>* node);
	void insertCol(verticalLinkedMatrixNode<T>* node);
	void eraseCol(verticalLinkedMatrixNode<T>* node);
	void copy(verticalLinkedMatrix<T>& a, verticalLinkedMatrix<T>& b);
	void checkIndex(int theRow, int theColumn) const;
	int number;
	verticalLinkedMatrixNode<T>* firstNode;
};

template<class T>
ostream& operator<<(ostream& out, verticalLinkedMatrix<T>& x) {
	out << "firstNode->row = " << x.firstNode->row << " columns = " << x.firstNode->col << endl;
	out << "nonzero terms = " << x.number << endl;
	verticalLinkedMatrixNode<T>* cur = x.firstNode->right;
	for (int i = 0; i < x.number;i++) {
		out << "a(" << cur->row << "," << cur->col << ") = " << cur->value << endl;
		cur = cur->right;
	}

	return out;
}

template <class T>
istream& operator>>(istream& in, verticalLinkedMatrix<T>& x) {
	in >> x.firstNode->row >> x.firstNode->col >> x.number;
	if (x.firstNode->row <= 0 || x.firstNode->col <= 0 || x.number < 0) throw IllegalParameterValue("input rows, cols or numberofTerms is bad.");

	int lastRow = 0, lastCol = 0;
	int row, col;
	T value;
	verticalLinkedMatrixNode<T>* cur = nullptr;
	for (int i = 0; i < x.number; i++) {
		in >> row >> col >> value;
		if (row <= 0 || row > x.firstNode->row || col <= 0 || col > x.firstNode->col || value == 0) throw IllegalParameterValue("input row, col or value is bad.");
		if (row < lastRow || row == lastRow && col <= lastCol) throw IllegalParameterValue("input row, col should increase");
		verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(row, col, value);
		x.insertNode(cur, newNode);
		cur = newNode;

		lastRow = row;
		lastCol = col;
	}
	return in;
}

template<class T>
void verticalLinkedMatrix<T>::insertNode(verticalLinkedMatrixNode<T>* cur, verticalLinkedMatrixNode<T>* node) {
	if (cur == nullptr) {
		firstNode->right = node;
		node->right = node;
		firstNode->down = node;
		node->down = node;
	}
	else {
		node->right = cur->right;
		cur->right = node;
		insertCol(node);
	}
}

template<class T>
void verticalLinkedMatrix<T>::insertCol(verticalLinkedMatrixNode<T>* node) {
	verticalLinkedMatrixNode<T>* preCol = firstNode->down, * curCol = preCol->down;

	if (preCol->col > node->col || preCol->col == node->col && preCol->row > node->row) {//need to insert at the beginning
		verticalLinkedMatrixNode<T>* last = firstNode->down;
		while (last->down != firstNode->down)
			last = last->down;
		last->down = node;
		firstNode->down = node;
		node->down = preCol;
	}
	else {
		while (curCol != firstNode->down
			&& (curCol->col < node->col || curCol->col == node->col && curCol->row < node->row)) {
			if (curCol != preCol) {
				preCol = curCol;
				curCol = curCol->down;
			}
			else
				break;
		}
		preCol->down = node;
		node->down = curCol;
	}
}

template<class T>
void verticalLinkedMatrix<T>::eraseCol(verticalLinkedMatrixNode<T>* node) {
	verticalLinkedMatrixNode<T>* preCol = firstNode->down, * curCol = preCol->down;

	while (curCol != node) {
		preCol = curCol;
		curCol = curCol->down;
	}
	preCol->down = curCol->down;
}

template<class T>
void verticalLinkedMatrix<T>::copy(verticalLinkedMatrix<T>& a, verticalLinkedMatrix<T>& b) {
	b.clear();
	b.firstNode->row = a.firstNode->row;
	b.firstNode->col = a.firstNode->col;
	b.number = a.number;

	verticalLinkedMatrixNode<T>* curB = nullptr, * curA = a.firstNode->right;
	for (int i = 0; i < a.number; i++) {
		verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(curA->row, curA->col, curA->value);
		b.insertNode(curB, newNode);
		curB = newNode;
		curA = curA->right;
	}
}

template<class T>
verticalLinkedMatrix<T>::verticalLinkedMatrix(verticalLinkedMatrix<T> & x) : verticalLinkedMatrix() {
	copy(x, *this);
}

template<class T>
void verticalLinkedMatrix<T>::clear() {
	if (firstNode->right != nullptr) {
		verticalLinkedMatrixNode<T>* cur = firstNode->right->right;
		while (cur != firstNode->right) {
			verticalLinkedMatrixNode<T>* toDel = cur;
			cur = cur->right;
			delete toDel;
		}
		delete cur;
	}
	number = 0;
	firstNode->row = 0;
	firstNode->col = 0;
	firstNode->right = nullptr;
	firstNode->down = nullptr;
}

template<class T>
void verticalLinkedMatrix<T>::checkIndex(int theRow, int theColumn) const {
	if (theRow <1 || theRow> firstNode->row || theColumn <1 || theColumn > firstNode->col)
		throw OutOfBounds();
}

template<class T>
T verticalLinkedMatrix<T>::get(int theRow, int theColumn) {
	checkIndex(theRow, theColumn);
	if (firstNode->right == nullptr)
		return 0;

	verticalLinkedMatrixNode<T> * curRow = firstNode->right;
	do{
		if (curRow->row == theRow && curRow->col == theColumn) {//found the posistion
			return curRow->value;
		}
		curRow = curRow->right;
	}while (curRow != firstNode->right);
	return 0;
}

template<class T>
void  verticalLinkedMatrix<T>::set(int theRow, int theColumn, const T & theValue) {
	checkIndex(theRow, theColumn);

	verticalLinkedMatrixNode<T> * curRow = firstNode->right, *preRow = curRow;
	if (curRow == nullptr && theValue != 0) {
		verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(theRow, theColumn, theValue);
		firstNode->right = newNode;
		newNode->right = newNode;
		firstNode->down = newNode;
		newNode->down = newNode;
		return;
	}

	while (true) {
		if (curRow->row == theRow && curRow->col == theColumn) {//found the posistion
			if (theValue != 0) {
				curRow->value = theValue;
			}
			else {//remove the node
				preRow->right = curRow->right;
				eraseCol(curRow);
				delete curRow;
				number--;
			}
			return;
		}
		else if (curRow->row > theRow || curRow->row == theRow && curRow->col > theColumn){
			verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(theRow, theColumn, theValue);
			if (curRow == preRow) {//insert as first
				verticalLinkedMatrixNode<T>* last = firstNode->right;
				while (last->right != firstNode->right)
					last = last->right;
				last->right = newNode;
				firstNode->right = newNode;
				newNode->right = curRow;
			}
			else {
				preRow->right = newNode;
				newNode->right = curRow;
			}
			insertCol(newNode);
			number++;
			return;
		}
		else if (curRow != preRow && curRow == firstNode->right
			|| curRow != preRow && number == 1) {//insert as last
			verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(theRow, theColumn, theValue);
			preRow->right = newNode;
			newNode->right = curRow;
			insertCol(newNode);
			number++;
			return;
		}
		preRow = curRow;
		curRow = curRow->right;
	}

}

template<class T>
void verticalLinkedMatrix<T>::transpose(verticalLinkedMatrix<T> & b) {
	b.clear();
	b.firstNode->row = firstNode->col;
	b.firstNode->col = firstNode->row;
	b.number = number;

	verticalLinkedMatrixNode<T>* cur = firstNode->down, * curB = nullptr;
	for (int i = 0; i < number; i++) {
		verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(cur->col, cur->row, cur->value);
		b.insertNode(curB, newNode);
		curB = newNode;
		cur = cur->down;
	}
}

template<class T>
void verticalLinkedMatrix<T>::add(verticalLinkedMatrix<T> & b, verticalLinkedMatrix<T> & c) {
	if (firstNode->row != b.firstNode->row || firstNode->col != b.firstNode->col)
		throw IllegalParameterValue("size not match.");

	c.clear();
	c.firstNode->row = firstNode->row;
	c.firstNode->col = firstNode->col;
	c.number = 0;

	if (number == 0) {
		copy(b, c);
		return;
	}
	if (b.number == 0) {
		copy(*this, c);
		return;
	}
	
	int countA = 0, countB = 0;
	verticalLinkedMatrixNode<T>* curA = firstNode->right, * curB = b.firstNode->right, * curC = nullptr;
	while(countA < number && countB < b.number) {
		if (curA->row < curB->row || curA->row == curB->row && curA->col < curB->col) {
			verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(*curA);
			c.insertNode(curC, newNode);
			curC = newNode;
			c.number++;
			curA = curA->right;
			countA++;
		}
		else if (curA->row > curB->row || curA->row == curB->row && curA->col > curB->col) {
			verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(*curB);
			c.insertNode(curC, newNode);
			curC = newNode;
			c.number++;
			curB = curB->right;
			countB++;
		}
		else if(curA->row == curB->row && curA->col == curB->col) {
			T val = curA->value + curB->value;
			if (val != 0) {
				verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(curA->row, curA->col, val);
				c.insertNode(curC, newNode);
				curC = newNode;
				c.number++;
			}
			curA = curA->right;
			curB = curB->right;
			countA++;
			countB++;
		}
	}

	while (countA < number) {
		verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(*curA);
		c.insertNode(curC, newNode);
		curC = newNode;
		c.number++;
		curA = curA->right;
		countA++;
	}
	while (countB < b.number) {
		verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(*curB);
		c.insertNode(curC, newNode);
		curC = newNode;
		c.number++;
		curB = curB->right;
		countB++;
	}
}

template<class T>
void verticalLinkedMatrix<T>::substract(verticalLinkedMatrix<T> & b, verticalLinkedMatrix<T> & c) {
	if (firstNode->row != b.firstNode->row || firstNode->col != b.firstNode->col)
		throw IllegalParameterValue("size not match.");

	c.clear();
	c.firstNode->row = firstNode->row;
	c.firstNode->col = firstNode->col;
	c.number = 0;

	if (b.number == 0) {
		copy(*this, c);
		return;
	}

	if (number == 0) {
		copy(b, c);
		verticalLinkedMatrixNode<T>* curC = c.firstNode->right;
		do {
			curC->value = -curC->value;
			curC = curC->right;
		} while (curC != c.firstNode->right);

		return;
	}

	int countA = 0, countB = 0;
	verticalLinkedMatrixNode<T>* curA = firstNode->right, * curB = b.firstNode->right, * curC = nullptr;
	while (countA < number && countB < b.number) {
		if (curA->row < curB->row || curA->row == curB->row && curA->col < curB->col) {
			verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(*curA);
			c.insertNode(curC, newNode);
			curC = newNode;
			c.number++;
			curA = curA->right;
			countA++;
		}
		else if (curA->row > curB->row || curA->row == curB->row && curA->col > curB->col) {
			verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(*curB);
			newNode->value = -newNode->value;
			c.insertNode(curC, newNode);
			curC = newNode;
			c.number++;
			curB = curB->right;
			countB++;
		}
		else if (curA->row == curB->row && curA->col == curB->col) {
			T val = curA->value - curB->value;
			if (val != 0) {
				verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(curA->row, curA->col, val);
				c.insertNode(curC, newNode);
				curC = newNode;
				c.number++;
			}
			curA = curA->right;
			curB = curB->right;
			countA++;
			countB++;
		}
	}

	while (countA < number) {
		verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(*curA);
		c.insertNode(curC, newNode);
		curC = newNode;
		c.number++;
		curA = curA->right;
		countA++;
	}
	while (countB < b.number) {
		verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(*curB);
		newNode->value = -newNode->value;
		c.insertNode(curC, newNode);
		curC = newNode;
		c.number++;
		curB = curB->right;
		countB++;
	}
}

template<class T>
void verticalLinkedMatrix<T>::multiply(verticalLinkedMatrix<T> & b, verticalLinkedMatrix<T> & c) {
	if (firstNode->col != b.firstNode->row) throw IllegalParameterValue("size not match in mulply.");

	c.clear();
	c.firstNode->row = firstNode->row;
	c.firstNode->col = b.firstNode->col;
	c.number = 0;

	if (number == 0 || b.number == 0) {
		return;
	}

	verticalLinkedMatrixNode<T>* curA = firstNode->right, *curB = b.firstNode->down, *curC = nullptr;
	for (int i = 1; i <= c.firstNode->row; i++) {
		if (i < curA->row)
			continue;
		for (int j = 1; j <= c.firstNode->col; j++) {
			if (j < curB->col)
				continue;
			int result = 0;
			verticalLinkedMatrixNode<T>* curA2 = curA;
			while (i == curA2->row && j == curB->col) {
				if (curA2->col < curB->row)
					curA2 = curA2->right;
				else if (curA2->col > curB->row)
					curB = curB->down;
				else {
					result += curA2->value * curB->value;
					curA2 = curA2->right;
					curB = curB->down;
				}
			}
			if (result != 0) {
				verticalLinkedMatrixNode<T>* newNode = new verticalLinkedMatrixNode<T>(i, j, result);
				c.insertNode(curC, newNode);
				curC = newNode;
				c.number++;
			}
			while (curB->col < j + 1 && b.number != 1 && c.firstNode->col != 1
				&& (firstNode->down->col == j || curB != b.firstNode->down))
				curB = curB->down;
		}
		while (curA->row < i+1 && number !=1 && c.firstNode->row != 1
			&& (firstNode->right->row == i || curA != firstNode->right))
			curA = curA->right;
	}
}
#endif
