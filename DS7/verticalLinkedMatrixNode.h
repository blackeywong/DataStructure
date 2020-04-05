#pragma once
#ifndef _VERTICALLINKEDMATRIXNODE_H
#define _VERTICALLINKEDMATRIXNODE_H

template<class T>
struct verticalLinkedMatrixNode {
	int row;
	int col;
	T value;
	verticalLinkedMatrixNode* down;
	verticalLinkedMatrixNode* right;
	verticalLinkedMatrixNode():verticalLinkedMatrixNode(0, 0, 0){}
	verticalLinkedMatrixNode(int theRow, int theCol, const T& theValue) : row(theRow), col(theCol), value(theValue), down(nullptr), right(nullptr) {}
	verticalLinkedMatrixNode(verticalLinkedMatrixNode<T>& node) : verticalLinkedMatrixNode(node.row, node.col, node.value){}
	bool operator==(const verticalLinkedMatrixNode<T>& b) const { return value == b.value; }
	bool operator!=(const verticalLinkedMatrixNode<T>& b) const { return value != b.value; }
	verticalLinkedMatrixNode<T>& operator=(const verticalLinkedMatrixNode<T>& b) { row = b.row; col = b.col;  value = b.value; return *this; }
};

#endif
