#pragma once
#ifndef _SIMSPACE3_H
#define _SIMSPACE3_H

#include <iostream>
#include "exceptions.h"
using namespace std;

//数据结构算法与应用-C++语言描述 第三章
//Exercise 69

template<class T> class SimSpace;
template<class T> class Chain;

template<class T>
class SimNode {
	friend class SimSpace<T>;
	friend class Chain<T>;
	template<class T>
	friend void* operator new(unsigned int size);
	friend void operator delete(void*p);
private:
	T data;
	SimNode<T>* link;
	static SimSpace<T> S;
};

template<class T>
void* operator new(unsigned int size)
{
	return SimNode<T>::S.Allocate();
}

template<class T>
void operator delete(void *p)
{
	SimNode<T>::S.Deallocate(static_cast<SimNode<T>*>p);
}

template<class T>
class SimSpace {
	friend class Chain<T>;
public:
	SimSpace(int MaxSpaceSize = 100);
	~SimSpace() { delete[]node; }
	SimNode<T>* Allocate();
	void Deallocate(SimNode<T>*n);
private:
	int NumberOfNodes;
	SimNode<T>* first1, * first2;
	SimNode<T>* node;
};

template<class T>
SimSpace<T>::SimSpace(int MaxSpaceSize) {
	NumberOfNodes = MaxSpaceSize;
	node = new SimNode<T>[NumberOfNodes];
	first1 = node;
	first2 = nullptr;
}

template<class T>
SimNode<T>* SimSpace<T>::Allocate() {
	if (first2) {
		SimSpace<T>* res = first2;
		first2 = first2->link;
		return res;
	}
	else if (first1 != NumberOfNodes) {
		return first1++;
	}
	else return nullptr;
}

template<class T>
void SimSpace<T>::Deallocate(SimNode<T>*n) {
	(*n).link = first2;
	first2 = n;
}

#endif