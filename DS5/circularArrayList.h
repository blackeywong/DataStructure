#ifndef _CIRCULARARRAYLIST_H
#define _CIRCULARARRAYLIST_H
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include "exceptions.h"
#include "changelength.h"
#include "linearlist.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第二版  第五章
//Exercise 31-36
template<class T>
class CircularArrayList : public LinearList<T>
{//Exerciese 31
public:
	CircularArrayList(int initialCapacity = 10);
	CircularArrayList(const CircularArrayList<T>& l);
	~CircularArrayList() {delete [] element;}

	bool empty() const {return listSize == 0;}
	int size() const {return listSize;}
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(ostream& out) const;

	int capacity() const {return arrayLength;}

public:

	CircularArrayList<T>& reverse(); //Exercise 33
	CircularArrayList<T>& meld(CircularArrayList<T>& a, CircularArrayList<T>& b); //Exercise 34
	CircularArrayList<T>& merge(CircularArrayList<T>& a, CircularArrayList<T>& b); //Exercise 35
	CircularArrayList<T>& split(CircularArrayList<T>& a, CircularArrayList<T>& b); //Exercise 36

public:
	class iterator;
	iterator begin() {return iterator(element+first, element, arrayLength);}
	iterator end() {return iterator(element+last, element, arrayLength);}

protected:
	void checkIndex(int theIndex) const;
	void changeArraySize(int capacity);
	void increaseArray(int capacity);
	void decreaseArray(int capacity);

	T* element;
	int arrayLength;
	int first, last, listSize;
	int initialCapacity;
};

template<class T>
class CircularArrayList<T>::iterator{//Exerciese 32
public:
	typedef bidirectional_iterator_tag iterator_capacity;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;

	iterator(T* thePosition, T* theInitial, int theArrayLength) : position(thePosition), initial(theInitial),  arrayLength(theArrayLength){}

	T& operator*() const {return *position;}
	T* operator&() const {return &*position;}

	iterator& operator++(){
		++position;
		if(position - initial == arrayLength)
			position = initial;
		return *this;
	}
	iterator operator++(int){
		iterator old = * this;
		++position;
		if(position - initial == arrayLength)
			position = initial;
		return old;
	}
	iterator& operator--(){
		--position;
		if(position < initial)
			position += arrayLength;
		return *this;
	}
	iterator operator--(int){
		iterator old = * this;
		--position;
		if(position < initial)
			position += arrayLength;
		return old;
	}

	bool operator!=(const iterator right) const {return position != right.position;}
	bool operator==(const iterator right) const {return position == right.position;}

	T& operator[](int i) { return *(initial + (((position-initial) + i)%arrayLength)); }
	ptrdiff_t operator-(const typename  CircularArrayList<T>::iterator & right) const { return position - right.position; }
	//bool operator<(const iterator right) const { return position < right.position; }
	//bool operator>(const iterator right) const { return position > right.position; }
	//bool operator<=(const iterator right) const { return position <= right.position; }
	//bool operator>=(const iterator right) const { return position >= right.position; }

protected:
	int arrayLength;
	T* initial;
	T* position;
};

template<class T>
CircularArrayList<T>::CircularArrayList(int theInitialCapacity){
	if(theInitialCapacity <1){
		ostringstream s;
		s << "Initial capacity = " << theInitialCapacity << " must be < 0";
		throw IllegalParameterValue(s.str());
	}

	initialCapacity = theInitialCapacity;
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	first = last = 0;
	listSize = 0;
}

template<class T>
CircularArrayList<T>::CircularArrayList(const CircularArrayList<T>& theList){
	arrayLength = theList.arrayLength;
	initialCapacity = theList.initialCapacity;
	listSize = theList.listSize;
	element = new T[arrayLength];
	circularCopy(theList.element +theList.first, theList.element + theList.last + 1, theList.element, theList.arrayLength, element);
	first = 0;
	last = listSize;
}

template<class T>
void CircularArrayList<T>::checkIndex(int theIndex) const
{
	if(theIndex < 0 || theIndex >=listSize){
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw IllegalIndex(s.str());
	}
}

template<class T>
void CircularArrayList<T>::changeArraySize(int capacity)
{
	T* temp = new T[capacity];
	circularCopy(&(element[first]), &(element[last]), element, arrayLength, temp);
	delete[]element;
	element = temp;

	arrayLength = capacity;
	first = 0;
	last = listSize;
}

template<class T>
void CircularArrayList<T>::increaseArray(int capacity)
{
	if(capacity <= arrayLength) return;
	
	changeArraySize(capacity);
}

template<class T>
void CircularArrayList<T>::decreaseArray(int capacity)
{
	if(capacity > arrayLength || capacity < 0) return;
	if(capacity < initialCapacity) capacity = initialCapacity;
	if(capacity == arrayLength) return;
	changeArraySize(capacity);
}

template<class T>
T& CircularArrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	return element[(theIndex+first) % arrayLength];
}

template<class T>
int CircularArrayList<T>::indexOf(const T& theElement) const
{
	for(int i=0;i<listSize;i++)
	{
		if(element[(i+first) % arrayLength] == theElement){
			return i;
		}
	}
	return -1;
}

template<class T>
void CircularArrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	if(theIndex >= (listSize+1) / 2){
		for(int i=theIndex;i<listSize-1;i++)
		{
			element[(i+first) % arrayLength] = element[(i+first+1) % arrayLength];
		}
		element[last-1].~T();
		last--;
		last = (last +arrayLength) % arrayLength;
	}else{
		for(int i=theIndex;i>0;i--)
		{
			element[(i+first) % arrayLength] = element[(i+first-1 + arrayLength) % arrayLength];
		}	
		element[first].~T();
		first++;
		first %= arrayLength;
	}
	
	listSize--;
	if(listSize < arrayLength/4)
		decreaseArray(arrayLength/2);
}

template<class T>
void CircularArrayList<T>::insert(int theIndex, const T& theElement)
{
	if(theIndex <0 || theIndex > listSize){
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw IllegalIndex(s.str());
	}

	if(listSize == arrayLength)
		increaseArray(2 * arrayLength);

	if(theIndex >= (listSize+1) / 2){//move backward
		for(int i=listSize;i>theIndex;i--)
		{
			element[(i+first) % arrayLength] = element[(i+first-1+arrayLength) % arrayLength];
		}
		last++;
		last %= arrayLength;
	}else{//move forward
		for(int i=0;i<theIndex;i++)
		{
			element[(i+first-1+arrayLength) % arrayLength] = element[(i+first) % arrayLength];
		}	
		first--;
		first = (first +arrayLength) % arrayLength;
	}

	element[(theIndex+first) % arrayLength] = theElement;
	listSize++;
}

template<class T>
CircularArrayList<T>& CircularArrayList<T>::reverse() {
	for (int i = 0; i < listSize / 2; i++) {
		swap(element[(i+first) % arrayLength], element[(listSize - i - 1+arrayLength) %arrayLength]);
	}

	return *this;
}

template<class T>
CircularArrayList<T>& CircularArrayList<T>::meld(CircularArrayList<T>& a, CircularArrayList<T>& b)
{
	int minSize = a.size() < b.size() ? a.size() : b.size();
	if(minSize == 0) return *this;

	CircularArrayList<T>& maxList = a.size() > b.size() ? a : b;
	int newArrayLength = a.size() > b.size() ? a.arrayLength : b.arrayLength;

	if(a.size() + b.size() > arrayLength)
		newArrayLength *= 2;

	increaseArray(newArrayLength);

	for(int i =0;i<minSize;i++)
	{
		element[i*2] = a.element[(i+a.first) % a.arrayLength];
		element[i*2+1] = b.element[(i+b.first) % b.arrayLength];
	}

	for(int i = minSize;i < maxList.listSize;i++){
		element[minSize + i] = maxList.element[(i+maxList.first) % maxList.arrayLength];
	}

	listSize = a.size() + b.size();

	return *this;
}

template<class T>
CircularArrayList<T>& CircularArrayList<T>::merge(CircularArrayList<T>& a, CircularArrayList<T>& b)
{
	if(a.size() == 0 && b.size() == 0) return *this;

	int newArrayLength = a.size() > b.size() ? a.arrayLength : b.arrayLength;

	if(a.size() + b.size() > arrayLength)
		newArrayLength *= 2;

	increaseArray(newArrayLength);
	int i=0, ia = 0, ib=0;
	for(int i =0;i<a.size() + b.size();i++)
	{
		if(ia < a.size() && ib < b.size()){
			if(a.element[(ia+a.first) % a.arrayLength]<=b.element[(ib+b.first) % b.arrayLength])
				element[i] = a.element[(ia++ +a.first) % a.arrayLength];
			else
				element[i] = b.element[(ib++ +b.first) % b.arrayLength];
			
		}else{
			if(ia < a.size() && ib >= b.size())
				element[i] = a.element[(ia++ +a.first) % a.arrayLength];
			else if(ia >= a.size() && ib < b.size())
				element[i] = b.element[(ib++ +b.first) % b.arrayLength];
		}
	}

	listSize = a.size() + b.size();

	return *this;
}

template<class T>
CircularArrayList<T>& CircularArrayList<T>::split(CircularArrayList<T>& a, CircularArrayList<T>& b)
{
	if(size() == 0) return *this;

	a.increaseArray(listSize);
	b.increaseArray(listSize);

	int i=0, ia = 0, ib=0;
	for(int i =0;i<listSize;i++)
	{
		if(i % 2 == 0){
			a.element[ia++] = element[(i+first) % arrayLength];
		}else{
			b.element[ib++] = element[(i+first) % arrayLength];
		}
	}

	a.listSize = (listSize+1) /2;
	b.listSize = listSize /2;

	return *this;
}

template<class T>
void CircularArrayList<T>::output(ostream& out) const
{
	for(int i=0;i<listSize;i++)
	{
		cout << element[(i+first) % arrayLength] << " ";
	}
}

template<class T>
ostream& operator<<(ostream& out, const CircularArrayList<T>& x)
{
	x.output(out);
	out << endl;
	return out;
}

#endif