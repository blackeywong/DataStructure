#pragma once
#ifndef _HEADELEMENT_H
#define _HEADELEMENT_H

template<class T>
struct headElement {
	int row;
	ExtendedChain<T> rowChain;
	headElement() {}
	headElement(int theRow) : row(theRow) {}
	bool operator==(const headElement<T>& b) const { return rowChain == b.rowChain; }
	bool operator!=(const headElement<T>& b) const { return rowChain != b.rowChain; }
	headElement<T>& operator=(const headElement<T>& b) { row = b.row; rowChain = b.rowChain; return *this; }
};

#endif
