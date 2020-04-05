#pragma once
#ifndef _MATRIXTERM_H
#define _MATRIXTERM_H
template<class T>
struct matrixTerm {
	int row;
	int col;
	T value;
	matrixTerm<T>() {}
	matrixTerm<T>(int theRow, int theCol, T theValue) : row(theRow), col(theCol), value(theValue) {}
};
#endif