#pragma once
#ifndef _NEWMATRIXTERM_H
#define _NEWMATRIXTERM_H
template<class T>
struct newMatrixTerm {
	int col;
	T value;
	newMatrixTerm<T>() {}
	newMatrixTerm<T>(int theCol, T theValue) :col(theCol), value(theValue) {}
};
#endif