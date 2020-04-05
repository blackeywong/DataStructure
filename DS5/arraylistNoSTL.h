#ifndef _ARRAYLISTNOSTL_H
#define _ARRAYLISTNOSTL_H
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include "exceptions.h"
#include "linearlist.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第二版  第五章
//Exercise 44
template<class T>
class ArrayListNoSTL : public LinearList<T>
{
public:
	ArrayListNoSTL(int initialCapacity = 10);
	ArrayListNoSTL(const ArrayListNoSTL<T>& l);
	~ArrayListNoSTL() { delete[] element; }

	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(ostream& out) const;

	int capacity() const { return arrayLength; }

public:
	class iterator;
	iterator begin() { return iterator(element); }
	iterator end() { return iterator(element + listSize); }

protected:
	void checkIndex(int theIndex) const;

	T* element;
	int arrayLength;
	int listSize;
	int initialCapacity;
};

template<class T>
ArrayListNoSTL<T>::ArrayListNoSTL(int theInitialCapacity) {
	if (theInitialCapacity < 1) {
		ostringstream s;
		s << "Initial capacity = " << theInitialCapacity << " must be > 0";
		throw IllegalParameterValue(s.str());
	}

	initialCapacity = theInitialCapacity;
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

template<class T>
ArrayListNoSTL<T>::ArrayListNoSTL(const ArrayListNoSTL<T>& theList) {
	arrayLength = theList.arrayLength;
	initialCapacity = theList.initialCapacity;
	listSize = theList.listSize;
	element = new T[arrayLength];
	for (int i = 0; i < listSize; ++i)
	{
		element[i] = theList.element[i];
	}
}

template<class T>
void ArrayListNoSTL<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize) {
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw IllegalIndex(s.str());
	}
}

template<class T>
T& ArrayListNoSTL<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	return element[theIndex];
}

template<class T>
int ArrayListNoSTL<T>::indexOf(const T& theElement) const
{
	for (int i = 0; i < listSize; i++)
	{
		if (element[i] == theElement)
			return i;
	}
	return -1;
}

template<class T>
void ArrayListNoSTL<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	for (int i = theIndex; i < listSize; i++)
		element[i] = element[i + 1];
	element[--listSize].~T();

}

template<class T>
void ArrayListNoSTL<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex <0 || theIndex > listSize) {
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw IllegalIndex(s.str());
	}

	for (int i = listSize; i > theIndex; i--) {
		element[i] = element[i - 1];
	}

	element[theIndex] = theElement;
	listSize++;
}

template<class T>
void ArrayListNoSTL<T>::output(ostream& out) const
{
	for (int i = 0; i < listSize; i++)
		out << element[i] << " ";
}

template<class T>
ostream& operator<<(ostream& out, const ArrayListNoSTL<T>& x)
{
	x.output(out);
	out << endl;
	return out;
}

#endif