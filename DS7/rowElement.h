#pragma once
#ifndef _ROWELEMENT_H
#define _ROWELEMENT_H
template<class T>
struct rowElement {
	int col;
	T value;
	rowElement() {}
	rowElement(int theCol, T theValue) : col(theCol), value(theValue) {}
	bool operator==(const rowElement<T>& b) const { return value == b.value; }
	bool operator!=(const rowElement<T>& b) const { return value != b.value; }
	rowElement& operator=(const rowElement<T>& b) { col = b.col; value = b.value; return *this; }
};

#endif
