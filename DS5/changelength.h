#ifndef _CHANGELENGTH_H
#define _CHANGELENGTH_H

#include <algorithm>
#include "linearlist.h"
#include "exceptions.h"
using namespace std;

template<class T>
void changeLength1D(T*& a, int oldLength, int newLength){
	if(newLength<0)
		throw IllegalParameterValue("new length must be >=0");

	T* temp = new T[newLength];
	int number = min(oldLength, newLength);
	copy(a, a+number, temp);
	delete[]a;
	a = temp;
}

//Exercise 3
template<class T>
void changeLength2D(T**& a, int oldRow, int oldCol, int newRow, int newCol){
	if(newRow < 0 || newCol < 0)
		throw IllegalParameterValue("new row/column must be >=0");

	int minRow = min(oldRow, newRow);
	int minCol = min(oldCol, newCol);
	T** temp = new T*[newRow];
	for(int i=0;i<minRow;i++){
		temp[i] = new T[newCol];
		copy<int*>(a[i], a[i]+minCol, temp[i]);
	}
	for(int i=0;i<oldRow;i++)
		delete[]a[i];
	delete[]a;
	a = temp;
}

template<class T>
void circularCopy(T* start, T* end, T* initial, int arrayLength, T* dest){
	int size = end - start;
	size = size >= 0 ? size : size + arrayLength;
	for(int i=0;i<size;i++)
		dest[i] = *(initial + ((i+(start-initial)) % arrayLength));
}


#endif