#pragma once
#ifndef _LIST_H
#define _LIST_H
#include <iostream>
#include "exceptions.h"
using namespace std;

//数据结构算法与应用-C++语言描述 第三章
//习题 1， 2-8，2-8采用1中的要求

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
	friend LinearList<T> & Reverse(LinearList<T> & l);
public:
	LinearList();
	LinearList(LinearList<T>&l);
	~LinearList() { delete[]element; };
	bool IsEmpty() { return length == 0; }
	int Length() const{ return length; }
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
	int length;
	int MaxSize;
	T* element;
	int current;
};

template<class T>
LinearList<T>::LinearList()
{
	MaxSize = 1;
	element = new T[MaxSize]{0};
	length = 0;
	Reset();
};

template<class T>
LinearList<T>::LinearList(LinearList<T> & l)
{
	MaxSize = l.MaxSize;
	length = l.length;
	element = new T[MaxSize]{ 0 };
	for (int i = 0; i < length; ++i)
	{
		element[i] = l.element[i];
	}
	Reset();
};

template<class T>
LinearList<T>& LinearList<T>::Insert(int k, const T& x)
{
	if (k<0 || k>length)
	{
		cout << "bad k:" << k << endl;
		return *this;
	}
	if (length == MaxSize) {
		MaxSize *= 2;
		T* old = element;
		element = new T[MaxSize]{0};
		for (int i = 0; i < length; i++) {
			element[i] = old[i];
		}
	}

	for (int i = length; i > k; i--) {
		element[i] = element[i - 1];
	}
	element[k] = x;
	length++;

	return *this;
}


template<class T>
bool LinearList<T>::Find(int k, T& x) const
{
	if (k < 0 || k >= length)
	{
		cout << "bad k:" << k << endl;
		return false;
	}

	x = element[k];
	return true;
}

template<class T>
LinearList<T>& LinearList<T>::Delete(int k, T& x)
{
	if (! Find(k,x))
		return *this;

	for (int i = k; i < length; i++)
		element[i] = element[i + 1];

	length--;

	if (length < MaxSize / 4)
	{
		T* old = element;
		MaxSize /= 2;
		element = new T[MaxSize]{ 0 };
		for (int i = 0; i < length; i++)
			element[i] = old[i];
		delete[]old;
	}

	return *this;
}


template<class T>
int LinearList<T>::Search(const T& x) const
{
	for (int i = 0; i < length; i++)
	{
		if (element[i] == x)
			return i;
	}
	return -1;
}

template<class T>
LinearList<T>& LinearList<T>::Reverse()
{
	for (int i = 0; i < length / 2; i++)
	{
		Swap<T>(element[i], element[length - i-1]);
	}

	return *this;
}

template<class T>
LinearList<T>& LinearList<T>::Half()
{
	length = (length + 1) / 2;
	for (int i = 1; i < length; ++i)
	{
		element[i] = element[i*2];
	}


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
	return element[current];
}

template<class T>
bool LinearList<T>::End()
{
	return (current == length -1 );
}

template<class T>
bool LinearList<T>::Front()
{
	return current == 0;
}

template<class T>
bool LinearList<T>::Next()
{
	if (current != length - 1)
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
LinearList<T>& LinearList<T>::Alternate(const LinearList<T>& a, const LinearList<T>& b) const
{
	LinearList<T> * x = new  LinearList<T>();
	x->length = a.length + b.length;

	while (x->length > x->MaxSize)
		x->MaxSize *= 2;

	delete[]x->element;
	x->element = new T[x->MaxSize]{ 0 };

	int minlen = a.length < b.length ? a.length : b.length;

	T * bigger = a.length > b.length ? a.element : b.element;

	for (int i = 0; i < minlen * 2; ++i)
	{
		if (i % 2 == 0)
			x->element[i] = a.element[i / 2];
		else
			x->element[i] = b.element[(i-1) / 2];
	}

	for (int i = minlen * 2; i < x->length; ++i)
	{
		x->element[i] = bigger[i - minlen];
	}

	return *x;
}

template<class T>
void LinearList<T>::BubbleSort()
{
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < length - i -1; ++j)
		{
			if (element[j] > element[j + 1])
				Swap<T>(element[j], element[j + 1]);
		}
	}
}

template<class T>
LinearList<T>& LinearList<T>::Merge(const LinearList<T>& a, const LinearList<T>& b) const
{
	LinearList<T> * x = new  LinearList<T>();
	x->length = a.length + b.length;

	while (x->length > x->MaxSize)
		x->MaxSize *= 2;

	delete[]x->element;
	x->element = new T[x->MaxSize]{0};
	int i = 0, j = 0, k = 0;
	for (; i < x->length && j<a.length && k<b.length; ++i)
	{
		if (a.element[j] <= b.element[k])
		{
			x->element[i] = a.element[j];
			++j;
		}
		else
		{
			x->element[i] = b.element[k];
			++k;
		}
	}
	for (; i < x->length && j < a.length; ++i, ++j)
		x->element[i] = a.element[j];
	for (; i < x->length && k < b.length; ++i, ++k)
		x->element[i] = b.element[k];

	return *x;
}

template<class T>
void LinearList<T>::Split(LinearList<T>& a, LinearList<T>& b) const
{
	a.length = (length+1) / 2;
	b.length = length - a.length;

	while (a.length > a.MaxSize)
		a.MaxSize *= 2;
	while (b.length > b.MaxSize)
		b.MaxSize *= 2;

	delete[]a.element;
	a.element = new T[a.MaxSize]{ 0 };
	delete[]b.element;
	b.element = new T[b.MaxSize]{ 0 };

	for (int i = 0; i < length; i++)
	{
		if (i % 2 == 0)
		{
			a.element[i / 2] = element[i];
		}
		else
		{
			b.element[i / 2] = element[i];
		}
	}
}

template<class T>
ostream& operator<<(ostream& out, const LinearList<T>& l)
{
	for (int i = 0; i < l.length; i++)
		out << l.element[i] << " ";
	out << endl;
	return out;
}

template<class T>
LinearList<T> & Reverse(LinearList<T> & l)
{
	l.Reverse();
	return l;
}

#endif