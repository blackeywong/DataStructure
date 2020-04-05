#pragma once
#ifndef _ARRAYLIST2_H
#define _ARRAYLIST2_H
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include "exceptions.h"
#include "changelength.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第二版  第五章
//Exercise 41-43
template<class T>
class ArrayList{
public:
	ArrayList(int initialCapacity, int count);
	~ArrayList() { delete[]element; delete[]first; delete[]last; };

	bool empty(int tableNo) const { return last[tableNo] > first[tableNo]; }
	int size(int tableNo) const;
	T& get(int tableNo, int k) const;
	void erase(int tableNo, int theIndex);//Exercise 43
	void insert(int tableNo, int theIndex, const T& theElement);//Exercise 41,42
	void output(ostream& out) const;

	int capacity() const { return arrayLength; }

protected:
	int TotalLength() const;

protected:
	int* first;
	int* last;
	int tableCount;
	int arrayLength;
	T* element;
};

template<class T>
ArrayList<T>::ArrayList(int initialCapacity, int count)
{
	if (initialCapacity < 1) {
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " must be > 0";
		throw IllegalParameterValue(s.str());
	}
	if (count < 1) {
		ostringstream s;
		s << "List count = " << count << " must be > 0";
		throw IllegalParameterValue(s.str());
	}

	arrayLength = initialCapacity;
	tableCount = count;
	element = new T[arrayLength]{ 0 };
	first = new int[tableCount + 2]{ 0 };
	last = new int[tableCount + 2]{ 0 };
	first[0] = last[0] = -1;
	first[tableCount + 1] = last[tableCount + 1] = arrayLength - 1;
	int interval = arrayLength / tableCount;
	first[1] = 0;
	last[1] = 0;
	for (int i = 2; i <= tableCount; ++i)
	{
		first[i] = first[i - 1] + interval;
		last[i] = last[i - 1] + interval;
	}
};

template<class T>
int ArrayList<T>::size(int tableNo) const
{
	return last[tableNo] - first[tableNo];
}

template<class T>
int ArrayList<T>::TotalLength() const
{
	int res = 0;

	for (int i = 1; i <= tableCount; i++) {
		res += size(i);
	}

	return res;

}

template<class T>
void ArrayList<T>::insert(int tableNo, int k, const T& x)
{
	if (k<0 || k>size(tableNo) + 1)
	{
		cout << "bad k:" << k << endl;
		return;
	}
	if (TotalLength() == arrayLength - 1) {
		T* old = element;
		element = new T[arrayLength * 2]{ 0 };
		for (int i = 0; i < arrayLength; ++i) {
			element[i] = old[i];
		}
		arrayLength *= 2;
		first[tableCount + 1] = last[tableCount + 1] = arrayLength - 1;
		delete[]old;
	}

	//find if there's pos. at later of the list
	bool found = false;
	int tableIndex1 = tableNo;
	for (; tableIndex1 <= tableCount + 1; ++tableIndex1) {
		if (last[tableIndex1] < first[tableIndex1 + 1]) {
			found = true;
			break;
		}
	}
	if (found)
	{
		//move tables
		for (int i = tableIndex1; i > tableNo; --i)
		{
			for (int j = last[i]; j > first[i]; --j)
			{
				element[j + 1] = element[j];
			}
			++last[i];
			++first[i];
		}
		//move for insert
		for (int j = last[tableNo]; j >= first[tableNo] + k + 1; --j)
		{
			element[j + 1] = element[j];
		}
		//insert
		element[first[tableNo] + k + 1] = x;
		++last[tableNo];

		return;
	}

	int tableIndex2 = tableNo;
	for (; tableIndex2 >= 0; --tableIndex2) {
		if (first[tableIndex2 - 1] < last[tableIndex2]) {
			found = true;
			break;
		}
	}

	//move tables
	for (int i = tableIndex2; i < tableNo; ++i)
	{
		for (int j = first[i]; j < first[i]; ++j)
		{
			element[j] = element[j + 1];
		}
		--last[i];
		--first[i];
	}
	//move for insert
	for (int j = first[tableNo]; j <= first[tableNo] + k + 1; ++j)
	{
		element[j] = element[j + 1];
	}
	//insert
	element[first[tableNo] + k] = x;
	--first[tableNo];
}

template<class T>
T& ArrayList<T>::get(int tableNo, int k) const
{
	if (k < 0 || k > size(tableNo))
	{
		cout << "bad k:" << k << endl;
		return false;
	}

	return  element[first[tableNo] + k];
}

template<class T>
void ArrayList<T>::erase(int tableNo, int k)
{
	if (k<1 || k>size(tableNo))
	{
		cout << "bad k:" << k << endl;
		return;
	}

	if (TotalLength() - 1 < arrayLength / 4) {
		T* old = element;
		element = new T[arrayLength / 2]{ 0 };
		for (int i = 1; i <= tableCount; ++i) {
			int oldfirst = first[i], length = last[i] - oldfirst;
			first[i] /= 2;
			last[i] = first[i] + length;
			for (int j = 1; j <= last[i] - first[i]; j++)
				element[first[i] + j] = old[oldfirst + j];
		}
		arrayLength /= 2;
		first[tableCount + 1] = last[tableCount + 1] = arrayLength - 1;
		delete[]old;
	}

	//move for insert
	for (int j = first[tableNo] + k; j < last[tableNo]; ++j)
	{
		element[j] = element[j + 1];
	}

	--last[tableNo];

}

template<class T>
void ArrayList<T>::output(ostream& out) const
{
	for (int i = 1; i <= tableCount; ++i)
	{
		out << "table " << i << ": ";
		for (int j = first[i] + 1; j <= last[i]; ++j)
			out << element[j] << " ";
		out << "\n";
	}
	out << endl;
}

template<class T>
ostream& operator<<(ostream& out, const ArrayList<T>& l)
{
	l.output(out);
	return out;
}


#endif