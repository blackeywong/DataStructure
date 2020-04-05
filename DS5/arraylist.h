#ifndef _ARRAYLIST_H
#define _ARRAYLIST_H
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>
#include "exceptions.h"
#include "linearlist.h"
#include "changelength.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第二版  第五章
//Exercise 5-30
template<class T>
class ArrayList : public LinearList<T>
{
public:
	ArrayList(int initialCapacity = 10);
	ArrayList(const ArrayList<T>& l);
	~ArrayList() {delete [] element;}

	bool empty() const {return listSize == 0;}
	int size() const {return listSize;}
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(ostream& out) const;

	int capacity() const {return arrayLength;}
	void trimToSize();//Exercise 5
	void setSize(int len);//Exercise 6

public:
	T& operator[](int i);//Exercise 7
	bool operator==(const ArrayList<T>& right) const;//Exercise 8
	bool operator!=(const ArrayList<T>& right) const;//Exercise 9
	bool operator<(const ArrayList<T>& right) const;//Exercise 10

	void push_back(const T& x); //Exercise 11
	void pop_back(T& x); //Exercise 12

	ArrayList<T>& swapList(ArrayList<T>& l); //Exercise 13
	void reserve(int theCapacity); //Exercise 14
	T set(int theIndex, const T& theElement);//Exercise 15
	void clear(); //Exercise 16
	void removeRange(int start, int count); //Exercise 17
	int lastIndexOf(const T& theElement) const;//Exercise 18

	ArrayList<T>& reverse(); //Exercise 22
	ArrayList<T>& leftShift(int shift); //Exercise 23
	ArrayList<T>& circularShift(int shift); //Exercise 24
	ArrayList<T>& half(); //Exercise 25

	ArrayList<T>& meld(ArrayList<T>& a, ArrayList<T>& b); //Exercise 28
	ArrayList<T>& merge(ArrayList<T>& a, ArrayList<T>& b); //Exercise 29
	ArrayList<T>& split(ArrayList<T>& a, ArrayList<T>& b); //Exercise 30

public:
	class iterator;
	iterator begin() {return iterator(element);}
	iterator end() {return iterator(element+listSize);}

protected:
	void checkIndex(int theIndex) const;
	void increaseArray(int capacity);
	void decreaseArray(int capacity);//Exercise 20

	T* element;
	int arrayLength;
	int listSize;
	int initialCapacity;
};

template<class T>
class ArrayList<T>::iterator{
public:
	typedef bidirectional_iterator_tag iterator_capacity;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	//typedef const T* const_pointer;
	typedef T* pointer;
	typedef T& reference;

	iterator(T* thePosition = 0) : position(thePosition), initial(thePosition) {}

	T& operator*() const {return *position;}
	T* operator&() const {return &*position;}

	iterator& operator++(){++position; return *this;}
	iterator operator++(int){iterator old = * this; ++position; return old;}
	iterator& operator--(){--position; return *this;}
	iterator operator--(int){iterator old = * this; --position; return old;}

	bool operator!=(const iterator right) const {return position != right.position;}
	bool operator==(const iterator right) const {return position == right.position;}

	T& operator[](int i) { return *(initial + i); }//Exercise 27
	ptrdiff_t operator-(const typename  ArrayList<T>::iterator & right) const { return position - right.position; }
	T& operator-(const typename ptrdiff_t & diff) const { return *(position - diff); }
	//bool operator<(const iterator right) const { return position < right.position; }
	//bool operator>(const iterator right) const { return position > right.position; }
	//bool operator<=(const iterator right) const { return position <= right.position; }
	//bool operator>=(const iterator right) const { return position >= right.position; }

protected:
	T* initial;
	T* position;
};

template<class T>
ArrayList<T>::ArrayList(int theInitialCapacity){
	if(theInitialCapacity <1){
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
ArrayList<T>::ArrayList(const ArrayList<T>& theList){
	arrayLength = theList.arrayLength;
	initialCapacity = theList.initialCapacity;
	listSize = theList.listSize;
	element = new T[arrayLength];
	copy(theList.element, theList.element + listSize,element);
}

template<class T>
void ArrayList<T>::checkIndex(int theIndex) const
{
	if(theIndex < 0 || theIndex >=listSize){
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw IllegalIndex(s.str());
	}
}

template<class T>
void ArrayList<T>::increaseArray(int capacity)
{
	if(capacity <= arrayLength) return;
	
	changeLength1D(element, arrayLength, capacity);
	arrayLength = capacity;
}

template<class T>
void ArrayList<T>::decreaseArray(int capacity)
{
	if(capacity >= arrayLength || capacity < 0) return;
	if(capacity < initialCapacity) capacity = initialCapacity;
	
	changeLength1D(element, arrayLength, capacity);
	arrayLength = capacity;
}

template<class T>
T& ArrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	return element[theIndex];
}

template<class T>
int ArrayList<T>::indexOf(const T& theElement) const
{
	int theIndex = static_cast<int> (find(element, element + listSize, theElement) - element);

	if(theIndex == listSize)
		return -1;
	else return theIndex;
}

template<class T>
void ArrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	copy(element + theIndex +1, element + listSize, element + theIndex);
	element[--listSize].~T();

	if(listSize < arrayLength/4)
		decreaseArray(arrayLength/2);
}

template<class T>
void ArrayList<T>::insert(int theIndex, const T& theElement)
{
	if(theIndex <0 || theIndex > listSize){
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw IllegalIndex(s.str());
	}

	if(listSize == arrayLength)
		increaseArray(2 * arrayLength);

	copy_backward(element + theIndex, element + listSize, element + listSize + 1);

	element[theIndex] = theElement;
	listSize++;
}

template<class T>
void ArrayList<T>::trimToSize()
{
	if(arrayLength == listSize) return;
	int oldLen = arrayLength;
	arrayLength = max(listSize, 1);
	changeLength1D(element, oldLen, arrayLength); 
}

template<class T>
void ArrayList<T>::setSize(int len){
	if(len <0 || len > listSize)
		return;

	listSize = len;
}

template<class T>
T& ArrayList<T>::operator[](int i)
{
	checkIndex(i);
	return element[i];
}

template<class T>
bool ArrayList<T>::operator==(const ArrayList<T>& right) const 
{
	if(size() != right.size()) return false;

	for(int i=0;i<size();i++)
	{
		if(element[i] != right.element[i]) return false;
	}

	return true;
}

template<class T>
bool ArrayList<T>::operator!=(const ArrayList<T>& right) const 
{
	if(size() != right.size()) return true;

	for(int i=0;i<size();i++)
	{
		if(element[i] != right.element[i]) return true;
	}

	return false;	
}

template<class T>
bool ArrayList<T>::operator<(const ArrayList<T>& right) const 
{
	int minSize = min(size(), right.size());

	for(int i=0;i<size();i++)
	{
		if(element[i] < right.element[i]) return true;
	}
	if(size() < right.size()) return true;
	return false;
}

template<class T>
void ArrayList<T>::push_back(const T& x)
{
	if(listSize == arrayLength) 
		increaseArray(2 * arrayLength);

	element[listSize++] = x;
}

template<class T>
void ArrayList<T>::pop_back(T& x)
{
	if(listSize == 0) return;
	x = element[--listSize];

	if(listSize < arrayLength/4)
		decreaseArray(arrayLength/2);
}

template<class T>
ArrayList<T>& ArrayList<T>::swapList(ArrayList<T>& l)
{
	swap(element, l.element);
	swap(listSize, l.listSize);
	swap(arrayLength, l.arrayLength);
	return *this;
}

template<class T>
void ArrayList<T>::reserve(int theCapacity)
{
	if(theCapacity <= arrayLength) return;
	changeLength1D(element, arrayLength, theCapacity);
	arrayLength = theCapacity;
}

template<class T>
T ArrayList<T>::set(int theIndex, const T& theElement)
{
	checkIndex(theIndex);
	T tmp = element[theIndex];
	element[theIndex] = theElement;
	return tmp;
}

template<class T>
void ArrayList<T>::clear()
{
	for(int i=0;i<listSize;i++)
		element[i].~T();

	listSize = 0;

	decreaseArray(initialCapacity);
}

template<class T>
void ArrayList<T>::removeRange(int start, int count)
{
	checkIndex(start);
	checkIndex(start+count-1);

	copy(element+start+count, element+listSize, element+start);

	for(int i=start+count;i<listSize;i++)
		element[i].~T();

	listSize -= count;

	if(listSize < arrayLength/4)
		decreaseArray(arrayLength/2);
}

template<class T>
int ArrayList<T>::lastIndexOf(const T& theElement) const
{
	for(int i = listSize -1;i>=0;i--)
		if(element[i] == theElement)
			return i;

	return -1;
}

template<class T>
ArrayList<T>& ArrayList<T>::reverse() {
	for (int i = 0; i < listSize / 2; i++) {
		swap(element[i], element[listSize - i - 1]);
	}

	return *this;
}

template<class T>
ArrayList<T>& ArrayList<T>::leftShift(int shift) {
	if (shift < 0 || shift > listSize) {
		ostringstream s;
		s << "shift = " << shift << " size = " << listSize;
		throw IllegalParameterValue(s.str());
	}

	copy(element + shift, element + listSize, element);
	listSize -= shift;

	for (int i = listSize - shift; i < listSize; i++)
		element[i].~T();

	if (listSize < arrayLength / 4)
		changeLength1D(element, arrayLength, arrayLength / 2);

	return *this;
}

template<class T>
ArrayList<T>& ArrayList<T>::circularShift(int shift) {
	if (shift < 0) {
		ostringstream s;
		s << "shift = " << shift << " size = " << listSize;
		throw IllegalParameterValue(s.str());
	}

	shift %= listSize;

	reverse();
	std::reverse(element, element + listSize - shift);
	std::reverse(element + listSize - shift, element + listSize);

	return *this;
}


template<class T>
ArrayList<T>& ArrayList<T>::half() {
	if (listSize <=1) return *this;

	for (int i = 1; i < (listSize + 1) / 2; i++) {
		element[i] = element[i * 2];
	}

	int old = listSize;
	listSize = (listSize + 1) / 2;

	for (int i = listSize; i < old; i++)
		element[i].~T();

	if (listSize < arrayLength / 4)
		changeLength1D(element, arrayLength, arrayLength / 2);

	return *this;
}

template<class T>
ArrayList<T>& ArrayList<T>::meld(ArrayList<T>& a, ArrayList<T>& b)
{
	int minSize = a.size() < b.size() ? a.size() : b.size();
	if(minSize == 0) return *this;

	int maxSize = a.size() > b.size() ? a.size() : b.size();
	T* maxEle = a.size() > b.size() ? a.element : b.element;
	int newArrayLength = a.size() > b.size() ? a.arrayLength : b.arrayLength;

	if(a.size() + b.size() > arrayLength)
		newArrayLength *= 2;

	increaseArray(newArrayLength);

	for(int i =0;i<minSize;i++)
	{
		element[i*2] = a.element[i];
		element[i*2+1] = b.element[i];
	}

	for(int i = minSize;i < maxSize;i++){
		element[minSize + i] = maxEle[i];
	}

	listSize = a.size() + b.size();

	return *this;
}

template<class T>
ArrayList<T>& ArrayList<T>::merge(ArrayList<T>& a, ArrayList<T>& b)
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
			if(a.element[ia]<=b.element[ib])
				element[i] = a.element[ia++];
			else
				element[i] = b.element[ib++];
			
		}else{
			if(ia < a.size() && ib >= b.size())
				element[i] = a.element[ia++];
			else if(ia >= a.size() && ib < b.size())
				element[i] = b.element[ib++];
		}
	}

	listSize = a.size() + b.size();

	return *this;
}

template<class T>
ArrayList<T>& ArrayList<T>::split(ArrayList<T>& a, ArrayList<T>& b)
{
	if(size() == 0) return *this;

	a.increaseArray(listSize);
	b.increaseArray(listSize);

	int i=0, ia = 0, ib=0;
	for(int i =0;i<listSize;i++)
	{
		if(i % 2 == 0){
			a.element[ia++] = element[i];
		}else{
			b.element[ib++] = element[i];
		}
	}

	a.listSize = (listSize+1) /2;
	b.listSize = listSize /2;

	return *this;
}

template<class T>
void ArrayList<T>::output(ostream& out) const
{
	copy(element, element + listSize, ostream_iterator<T>(cout, " "));
}

template<class T>
ostream& operator<<(ostream& out, const ArrayList<T>& x)
{
	x.output(out);
	out << endl;
	return out;
}

template<class T>
ArrayList<T>& reverse(ArrayList<T>& l) {//Exercise 22
	if (l.size() <= 1) return l;
	
	T x;
	for (int i = 0; i < l.size(); i++) {
		x = l.get(0);
		l.erase(0);
		l.insert(l.size() - i, x);
	}

	return l;
}

template<class T>
ArrayList<T>& half(ArrayList<T>& l) {//Exercise 26
	if (l.size() <= 1) return l;

	for (int i = 1; i < l.size(); i += 2) {
		l.erase(i);
	}

	return l;
}

#endif