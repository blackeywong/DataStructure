#pragma once
#ifndef _VECTORLIST_H
#define _VECTORLIST_H

#include <iostream>
#include <vector>
#include <sstream>
#include "linearlist.h"
#include "exceptions.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第二版  第五章
//Exercise 37-40
template<class T>
class VectorList : public LinearList<T> {
public:
	VectorList(int initialCapacity = 10);
	VectorList(const VectorList<T>&);
	~VectorList() { delete element; }

	bool empty() const { return element->empty(); }
	int size() const { return (int)element->size(); }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(ostream& out) const;

	int capacity() const { return (int)element->capacity(); }

	VectorList<T>& half(); //Exercise 37
	VectorList<T>& meld(VectorList<T>& a, VectorList<T>& b); //Exercise 38
	VectorList<T>& merge(VectorList<T>& a, VectorList<T>& b); //Exercise 39
	VectorList<T>& split(VectorList<T>& a, VectorList<T>& b); //Exercise 40

protected:
	void checkIndex(int theIndex) const;

	vector<T>* element;
};

template<class T>
VectorList<T>::VectorList(int initialCapacity) {
	if (initialCapacity < 1) {
		ostringstream s;
		s << "Initial capcity = " << initialCapacity << " Must be > 0";
		throw IllegalParameterValue(s.str());
	}
	element = new vector<T>;
	element->reserve(initialCapacity);
}

template<class T>
VectorList<T>::VectorList(const VectorList<T>& theList) {
	element = new vector<T>(*theList.element);
}

template<class T>
void VectorList<T>::checkIndex(int theIndex) const {
	if (theIndex < 0 || theIndex > size()-1) {
		ostringstream s;
		s << "index = " << theIndex << " size = " << size();
		throw IllegalIndex(s.str());
	}
}

template<class T>
T& VectorList<T>::get(int theIndex) const
{
	return element->at(theIndex);
}

template<class T>
int VectorList<T>::indexOf(const T& theElement) const
{
	auto index = find(element->begin(), element->end(), theElement);
	if (index != element->end())
		return (int)(index - element->begin());
	else
		return -1;
}

template<class T>
void VectorList<T>::erase(int theIndex) {
	checkIndex(theIndex);
	element->erase(element->begin() + theIndex);
}

template<class T>
void VectorList<T>::insert(int theIndex, const T& theElement) {
	if (theIndex < 0 || theIndex > size()) {
		ostringstream s;
		s << "index = " << theIndex << " size = " << size();
		throw IllegalIndex(s.str());
	}
	element->insert(element->begin() + theIndex, theElement);
}


template<class T>
VectorList<T>& VectorList<T>::half() {
	for (int i = 1; i < (size()+1)/2; i++) {
		(*element)[i] = (*element)[i*2];
	}
	int origSize = size();
	for (int i = (size() + 1) / 2; i < origSize; i++) {
		element->erase(element->end() - 1);
	}

	return *this;
}

template<class T>
VectorList<T>& VectorList<T>::meld(VectorList<T>& a, VectorList<T>& b)
{
	int i = 0, ia = 0, ib = 0;
	while (ia < a.size() && ib < b.size()) {
		element->push_back(a.get(ia++));
		element->push_back(b.get(ib++));
	}
	while (ia < a.size()) {
		element->push_back(a.get(ia++));
	}
	while (ib < b.size()) {
		element->push_back(b.get(ib++));
	}
	return *this;
}

template<class T>
VectorList<T>& VectorList<T>::merge(VectorList<T>& a, VectorList<T>& b)
{
	int i = 0, ia = 0, ib = 0;
	while (ia < a.size() && ib < b.size()) {
		if(a.get(ia) <= b.get(ib))
			element->push_back(a.get(ia++));
		else
			element->push_back(b.get(ib++));
	}
	while (ia < a.size()) {
		element->push_back(a.get(ia++));
	}
	while (ib < b.size()) {
		element->push_back(b.get(ib++));
	}

	return *this;
}

template<class T>
VectorList<T>& VectorList<T>::split(VectorList<T>& a, VectorList<T>& b)
{
	int i = 0;
	while (i<size()) {
		if(i%2 == 0)
			a.element->push_back(get(i++));
		else
			b.element->push_back(get(i++));
	}

	return *this;
}
template<class T>
void VectorList<T>::output(ostream& out) const
{
	for (T& t : *element)
		out << t << " ";
	out << endl;
}

template<class T>
ostream& operator<<(ostream& out, VectorList<T>& l) {
	l.output(out);
	return out;
}

#endif