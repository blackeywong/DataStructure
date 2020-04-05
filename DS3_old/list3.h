#pragma once
#ifndef _LIST3_H
#define _LIST3_H
#include <iostream>
#include "exceptions.h"
using namespace std;

//数据结构算法与应用-C++语言描述 第三章
//习题 14-18

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
	template<class T>
	friend LinearList<T>& Reverse(LinearList<T>& l);
public:
	LinearList();
	LinearList(LinearList<T>& l);
	~LinearList() { delete[]element; };
	bool IsEmpty() { return first == last; }
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(const T& x) const;
	LinearList<T>& Delete(int k, T& x);
	LinearList<T>& Insert(int k, const T& x);

	LinearList<T>& Reverse();
	LinearList<T>& Half();

	void Reset();
	T& Current();
	bool End();
	bool Front();
	bool Next();
	bool Previous();

	LinearList<T>& Alternate(const LinearList<T>& a, const LinearList<T>& b) const;

	void BubbleSort();
	LinearList<T>& Merge(const LinearList<T>& a, const LinearList<T>& b) const;

	void Split(LinearList<T>& a, LinearList<T>& b) const;

private:
	int first;
	int last;
	int MaxSize;
	T* element;
	int current;
};

template<class T>
LinearList<T>::LinearList()
{
	MaxSize = 1;
	element = new T[MaxSize]{ 0 };
	first = 0;
	last = -1;
	Reset();
};

template<class T>
LinearList<T>::LinearList(LinearList<T>& l)
{
	MaxSize = l.MaxSize;
	first = 0;
	last = l.Length() == 0 ? -1 : l.Length() - 1;
	element = new T[MaxSize]{ 0 };
	for (int i = 0; i < Length(); ++i)
	{
		element[i] = l.element[(l.first + i) % l.MaxSize];
	}
	Reset();
};

template<class T>
int LinearList<T>::Length() const
{ 
	return last == -1 ? 0 :
	last >= first ? last - first + 1 : last + MaxSize - first + 1;
}

template<class T>
LinearList<T>& LinearList<T>::Insert(int k, const T& x)
{
	if (k<0 || k>Length())
	{
		cout << "bad k:" << k << endl;
		return *this;
	}
	if (Length() == MaxSize) {
		T* old = element;
		element = new T[MaxSize * 2]{ 0 };
		for (int i = 0; i < Length(); i++) {
			element[i] = old[(first + i) % MaxSize];
		}
		last = Length() - 1;
		first = 0;
		MaxSize *= 2;
		delete[]old;
	}

	if (k > Length() / 2)//move the end
	{
		for (int i = Length(); i > k; --i) {
			element[(first +i) % MaxSize] = element[(first + i - 1 + MaxSize) % MaxSize];
		}
		element[(first +k + MaxSize) % MaxSize] = x;
		last = (last +1) % MaxSize;
	}
	else {
		for (int i = 0; i < k; ++i) {
			element[(first + i -1 + MaxSize) % MaxSize] = element[(first + i) % MaxSize];
		}
		element[(first + k - 1 + MaxSize) % MaxSize] = x;
		first = (first -1 + MaxSize)% MaxSize;
		if (last == -1)
			last = first;
	}

	return *this;
}


template<class T>
bool LinearList<T>::Find(int k, T& x) const
{
	if (k < 0 || k > Length())
	{
		cout << "bad k:" << k << endl;
		return false;
	}

	x = element[(first + k + MaxSize) % MaxSize];
	return true;
}

template<class T>
LinearList<T>& LinearList<T>::Delete(int k, T& x)
{
	if (!Find(k, x))
		return *this;

	if (k > Length() / 2)//move the end
	{
		for (int i = k; i < Length(); ++i) {
			element[(first + i -1 + MaxSize) % MaxSize] = element[(first + i) % MaxSize];
		}
		last = (last-1 +MaxSize) % MaxSize;
	}
	else {
		for (int i = k; i > 0; --i) {
			element[(first + i + MaxSize) % MaxSize] = element[(first + i - 1) % MaxSize];
		}
		first = (first+1) % MaxSize;
	}

	if (Length() < MaxSize / 4)
	{
		T* old = element;
		element = new T[MaxSize/2]{ 0 };
		for (int i = 0; i < Length(); i++)
			element[i] = old[(first + i - 1 + MaxSize) % MaxSize];
		delete[]old;
		last = Length() - 1;
		first = 0;
		MaxSize /= 2;
	}

	return *this;
}


template<class T>
int LinearList<T>::Search(const T & x) const
{
	for (int i = 0; i < Length(); i++)
	{
		if (element[(first + i -1 + MaxSize) % MaxSize] == x)
			return i;
	}
	return -1;
}

template<class T>
LinearList<T>& LinearList<T>::Reverse()
{
	for (int i = 0; i < Length() / 2; i++)
	{
		Swap<T>(element[(first + i) % MaxSize], element[(last - i + MaxSize) % MaxSize]);
	}

	return *this;
}

template<class T>
LinearList<T>& LinearList<T>::Half()
{
	for (int i = 1; i < Length(); ++i)
	{
		element[(first + i) % MaxSize] = element[(first + i * 2) % MaxSize];
	}

	last = (last - (Length() + 1) / 2 + MaxSize) % MaxSize;

	return *this;
}

template<class T>
void LinearList<T>::Reset()
{
	current = 0;
}

template<class T>
T& LinearList<T>::Current()
{
	return element[(first + current) % MaxSize];
}

template<class T>
bool LinearList<T>::End()
{
	return (current == Length() - 1);
}

template<class T>
bool LinearList<T>::Front()
{
	return current == 0;
}

template<class T>
bool LinearList<T>::Next()
{
	if (current != Length() - 1)
	{
		++current;
		return true;
	}
	else
	{
		throw NoNext();
		return false;
	}
}

template<class T>
bool LinearList<T>::Previous()
{
	if (current != 0)
	{
		--current;
		return true;
	}
	else
	{
		throw NoPrev();
		return false;
	}
}

template<class T>
LinearList<T>& LinearList<T>::Alternate(const LinearList<T> & a, const LinearList<T> & b) const
{
	LinearList<T>* x = new  LinearList<T>();
	x->last = a.Length() + b.Length() - 1;

	while (x->Length() > x->MaxSize)
		x->MaxSize *= 2;

	delete[]x->element;
	x->element = new T[x->MaxSize]{ 0 };

	int minlen = a.Length() < b.Length() ? a.Length() : b.Length();

	const LinearList<T>& bigger = a.Length() > b.Length() ? a : b;

	for (int i = 0; i < minlen * 2; ++i)
	{
		if (i % 2 == 0)
			 a.Find(i / 2, x->element[i]);
		else
			 b.Find((i - 1) / 2, x->element[i]);
	}

	for (int i = minlen * 2; i < x->Length(); ++i)
	{
		 bigger.Find(i - minlen, x->element[i]);
	}

	return *x;
}

template<class T>
void LinearList<T>::BubbleSort()
{
	for (int i = 0; i < Length(); ++i)
	{
		for (int j = 0; j < Length() - i - 1; ++j)
		{
			if (element[(first + j) % MaxSize] > element[(first + j + 1) % MaxSize])
				Swap<T>(element[(first + j) % MaxSize], element[(first + j + 1) % MaxSize]);
		}
	}
}

template<class T>
LinearList<T>& LinearList<T>::Merge(const LinearList<T> & a, const LinearList<T> & b) const
{
	LinearList<T>* x = new  LinearList<T>();
	x->last = a.Length() + b.Length() - 1;

	while (x->Length() > x->MaxSize)
		x->MaxSize *= 2;

	delete[]x->element;
	x->element = new T[x->MaxSize]{ 0 };
	int i = 0, j = 0, k = 0;
	for (; i < x->Length() && j < a.Length() && k < b.Length(); ++i)
	{
		T t1, t2;
		a.Find(j, t1);
		b.Find(k, t2);
		if (t1 <= t2)
		{
			x->element[i] = t1;
			++j;
		}
		else
		{
			x->element[i] = t2;
			++k;
		}
	}
	for (; i < x->Length() && j < a.Length(); ++i, ++j)
		a.Find(j, x->element[i]);
	for (; i < x->Length() && k < b.Length(); ++i, ++k)
		b.Find(k, x->element[i]);

	return *x;
}

template<class T>
void LinearList<T>::Split(LinearList<T> & a, LinearList<T> & b) const
{
	a.last = (Length() + 1) / 2 - 1;
	b.last = Length() - a.Length() -1;

	while (a.Length() > a.MaxSize)
		a.MaxSize *= 2;
	while (b.Length() > b.MaxSize)
		b.MaxSize *= 2;

	delete[]a.element;
	a.element = new T[a.MaxSize]{ 0 };
	delete[]b.element;
	b.element = new T[b.MaxSize]{ 0 };

	for (int i = 0; i < Length(); i++)
	{
		if (i % 2 == 0)
		{
			Find(i, a.element[i / 2]);
		}
		else
		{
			Find(i, b.element[i / 2]);
		}
	}
}

template<class T>
ostream& operator<<(ostream & out, const LinearList<T> & l)
{
	T t;
	for (int i = 0; i < l.Length(); i++)
	{
		l.Find(i, t);
		out << t << " ";
	}
	out << endl;
	return out;
}

template<class T>
LinearList<T>& Reverse(LinearList<T> & l)
{
	l.Reverse();
	return l;
}

#endif