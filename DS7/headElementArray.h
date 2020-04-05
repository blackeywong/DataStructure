#pragma once
#ifndef _HEADELEMENTARRAY_H
#define _HEADELEMENTARRAY_H

template<class T>
struct headElementArray {
	int row;
	vector<T> rowArray;
	headElementArray() {}
	headElementArray(int theRow) : row(theRow) {}
	bool operator==(const headElementArray<T>& b) const { return rowArray == b.rowArray; }
	bool operator!=(const headElementArray<T>& b) const { return rowArray != b.rowArray; }
	headElementArray<T>& operator=(const headElementArray<T>& b) { row = b.row; rowArray = b.rowArray; return *this; }
};

#endif
