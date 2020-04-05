#pragma once
#ifndef _INDIRECTLIST_H
#define _INDIRECTLIST_H
#include <iostream>
#include "exceptions.h"
using namespace std;

//数据结构算法与应用-C++语言描述 第三章
//Exercise 60-66


template<class T>
void Swap(T* &a, T* &b)
{
	T* tmp = a;
	a = b;
	b = tmp;
}
template<class T> class IndirectList;

template<class T>
class IndirectListIterator {
public:
	IndirectListIterator(const IndirectList<T>& c):list(c) {
		if(c.length == 0) location = -1;
		else location = 0;
	}

	T* Next() {
		if(location == list.length) return nullptr;
		return list.table[location++];
	}
private:
	int location;
	const IndirectList<T>& list;
};

template<class T>
class IndirectList {
	template<class T>
	friend ostream& operator<<(ostream& out, const IndirectList<T>& l);
	template<class T>
	friend IndirectList<T> & Reverse(IndirectList<T> & l);
	friend class IndirectListIterator<T>;
public:
	IndirectList(int MaxListSize = 10);
	~IndirectList();
	bool IsEmpty() { return length == 0; }
	int Length() const{ return length; }
	bool Find(int k, T& x) const;
	int Search(const T& x) const; //61
	IndirectList<T>& Delete(int k, T& x);
	IndirectList<T>& Insert(int k, const T& x);
	void Output(ostream&out) const; //60

	int BinarySearch(T&x); //63
	void InsertionSort(); //64
	void SelectionSort(); //65
	void BubbleSort(); //65
	void RankSort(); //65


private:
	int length;
	int MaxSize;
	T** table;
};

template<class T>
IndirectList<T>::IndirectList(int MaxListSize)
{
	MaxSize = MaxListSize;
	table = new T* [MaxSize];
	length = 0;
}

template<class T>
IndirectList<T>::~IndirectList(){
	for(int i=0;i<length;++i){
		delete table[i];
	}
	delete [] table;
}

template<class T>
bool IndirectList<T>::Find(int k, T& x) const
{
	if (k < 1 || k > length)
	{
		cout << "bad k:" << k << endl;
		return false;
	}

	x = *table[k-1];
	return true;
}

template<class T>
int IndirectList<T>::Search(const T& x) const
{
	for (int i = 0; i < length; i++)
	{
		if (*table[i] == x)
			return i+1;
	}
	return -1;
}

template<class T>
IndirectList<T>& IndirectList<T>::Insert(int k, const T& x)
{
	if (k<0 || k>length)
	{
		cout << "bad k:" << k << endl;
		return *this;
	}

	if (length == MaxSize) {
		MaxSize *= 2;
		T** old = table;
		table = new T *[MaxSize];
		for (int i = 0; i < length; i++) {
			table[i] = old[i];
		}
		delete [] old;
	}


	for (int i = length; i > k; i--) {
		table[i] = table[i - 1];
	}
	T * t = new T(x);
	table[k] =t;
	length++;

	return *this;
}

template<class T>
IndirectList<T>& IndirectList<T>::Delete(int k, T& x)
{
	if (! Find(k,x))
		return *this;
	delete table[k-1];

	for (int i = k-1; i < length; i++)
		table[i] = table[i + 1];

	length--;

	if (length < MaxSize / 4)
	{
		T** old = table;
		table /= 2;
		table = new T*[MaxSize];
		for (int i = 0; i < length; i++)
			table[i] = old[i];
		delete[]old;
	}

	return *this;
}

template<class T>
void IndirectList<T>::Output(ostream&out) const
{
	for (int i = 0; i < length; i++)
		out << *table[i] << " ";
	out << endl;
}

template<class T>
int IndirectList<T>::BinarySearch(T&x)
{
	int left = 0, right = length -1, middle = (length -1) /2;
	while(left <= right){
		if(*table[middle] == x) return middle;
		if(*table[middle]>x) {
			right = middle-1;
		}else{
			left = middle+1;
		}
		middle = (left + right)/2;
	}
	return -1;
}

template<class T>
void IndirectList<T>::InsertionSort()
{
	if(length <=1) return;

	for(int i=1;i<length;++i){
		for(int j=i;j>=1;--j){
			if(*table[j] < *table[j-1]){
				Swap(table[j], table[j-1]);
			}
		}
	
	}
}

template<class T>
void IndirectList<T>::SelectionSort()
{
	if (length <= 1) return;

	for (int i = length-1; i > 0; --i) {
		//find max from 0 to i
		int max = 0;
		for (int j = 1; j <= i; ++j) {
			if (*table[j] > * table[max]) {
				max = j;
			}
		}

		Swap(table[max], table[i]);
	}
}

template<class T>
void IndirectList<T>::BubbleSort()
{
	if (length <= 1) return;

	for (int i = length - 1; i > 0; --i) {
		for (int j = 0; j < i; ++j) {
			if (*table[j] > * table[j+1]) {
				Swap(table[j], table[j+1]);
			}
		}
	}
}

template<class T>
void IndirectList<T>::RankSort()
{
	if (length <= 1) return;

	int* rank = new int(length)={0};

	for (int i = 0; i < length; ++i) {
		for (int j = i; j < length; ++j) {
			if (*table[j] > * table[j + 1]) {
				++rank[j];
			}
			else {
				++rank[j + 1];
			}
		}
	}

	for (int i = 0; i < length; i++) {
		while (rank[i] != i) {
			Swap(table[i], table[rank[i]]);

			int tmp = rank[i];
			rank[i] = rank[tmp];
			rank[tmp] = tmp;
		}
	}
}

template<class T>
ostream& operator<<(ostream& out, const IndirectList<T>& l){
	l.Output(out);
	return out;
}
int element[] = { 2,6,5,7,7,4 };
int table[] = { 0,5,2,1,3,4 };

template<class T>
void TableSort(T* element, int* table, int length)//66
{
	//if (length <= 1) return;
	//T tmp;
	//for (int i = 0; i < length; i++) {
	//	if (table[i] != i) {
	//		tmp = 
	//	}
	//}
}

#endif