#pragma once
#ifndef _LIST3_H
#define _LIST3_H
#include <iostream>
using namespace std;

//数据结构算法与应用-C++语言描述 第三章
//习题 19, 20, 21

template<class T>
void Swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template<class T>
class LinearList {
	template<class T>
	friend ostream& operator<<(ostream& out, const LinearList<T>& l);
public:
	LinearList(int size, int count);
	~LinearList() { delete[]element; delete[]first; delete[]last; };
	bool IsEmpty(int tableNo) { return last[tableNo] > first[tableNo]; }
	int Length(int tableNo) const;
	bool Find(int tableNo, int k, T& x) const;
	LinearList<T>& Delete(int tableNo, int k, T& x);
	LinearList<T>& Insert(int tableNo, int k, const T& x);

private:
	int TotalLength() const;

private:
	int* first;
	int* last;
	int tableCount;
	int MaxSize;
	T* element;
};

template<class T>
LinearList<T>::LinearList(int size, int count)
{
	MaxSize = size;
	tableCount = count;
	element = new T[MaxSize]{ 0 };
	first = new int[tableCount + 2]{ 0 };
	last = new int[tableCount + 2]{ 0 };
	first[0] = last[0] = -1;
	first[tableCount + 1] = last[tableCount+1] = MaxSize - 1;
	int interval = MaxSize / tableCount;
	first[1] = 0;
	last[1] = 0;
	for (int i = 2; i <= tableCount; ++i)
	{
		first[i] = first[i - 1] + interval;
		last[i] = last[i - 1] + interval;
	}
};

template<class T>
int LinearList<T>::Length(int tableNo) const
{
	return last[tableNo] - first[tableNo];
}

template<class T>
int LinearList<T>::TotalLength() const
{
	int res = 0;

	for (int i = 1; i <= tableCount; i++) {
		res += Length(i);
	}

	return res;

}

template<class T>
LinearList<T>& LinearList<T>::Insert(int tableNo, int k, const T& x)
{
	if (k<0 || k>Length(tableNo)+1)
	{
		cout << "bad k:" << k << endl;
		return *this;
	}
	if (TotalLength() == MaxSize - 1) {
		T* old = element;
		element = new T[MaxSize * 2]{ 0 };
		for (int i = 0; i < MaxSize; ++i) {
			element[i] = old[i];
		}
		MaxSize *= 2;
		first[tableCount + 1] = last[tableCount + 1] = MaxSize - 1;
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
	if(found)
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
		for (int j = last[tableNo]; j >= first[tableNo] + k+1; --j)
		{
			element[j + 1] = element[j];
		}
		//insert
		element[first[tableNo] + k+1] = x;
		++last[tableNo];

		return *this;
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
			element[j] = element[j+1];
		}
		--last[i];
		--first[i];
	}
	//move for insert
	for (int j = first[tableNo]; j <= first[tableNo] + k+1; ++j)
	{
		element[j] = element[j+1];
	}
	//insert
	element[first[tableNo] + k] = x;
	--first[tableNo];

	return *this;
}


template<class T>
bool LinearList<T>::Find(int tableNo, int k, T& x) const
{
	if (k < 0 || k > Length(tableNo))
	{
		cout << "bad k:" << k << endl;
		return false;
	}

	x = element[first[tableNo] + k];
	return true;
}

template<class T>
LinearList<T>& LinearList<T>::Delete(int tableNo, int k, T& x)
{
	if (k<1 || k>Length(tableNo))
	{
		cout << "bad k:" << k << endl;
		return *this;
	}

	x = element[first[tableNo] + k + 1];

	if (TotalLength() - 1 < MaxSize / 4) {
		T* old = element;
		element = new T[MaxSize / 2]{ 0 };
		for (int i = 1; i <= tableCount; ++i) {
			int oldfirst = first[i], length = last[i] - oldfirst;
			first[i] /= 2;
			last[i] = first[i] + length;
			for(int j=1;j<=last[i] - first[i];j++)
				element[first[i] + j] = old[oldfirst + j];
		}
		MaxSize /= 2;
		first[tableCount + 1] = last[tableCount + 1] = MaxSize - 1;
		delete[]old;
	}

	//move for insert
	for (int j = first[tableNo] + k; j < last[tableNo]; ++j)
	{
		element[j] = element[j+1];
	}

	--last[tableNo];

	return *this;
}


template<class T>
ostream& operator<<(ostream & out, const LinearList<T> & l)
{
	for (int i = 1; i <= l.tableCount; ++i)
	{
		out << "table " << i << ": ";
		for(int j=l.first[i]+1 ;j<=l.last[i];++j)
			out << l.element[j] << " ";
		out << "\n";
	}
	out << endl;
	return out;
}


#endif