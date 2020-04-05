#pragma once
#ifndef _SIMSPACE_H
#define _SIMSPACE_H

#include <iostream>
#include "exceptions.h"
using namespace std;

//数据结构算法与应用-C++语言描述 第三章
//Exercise 68

template<class T> class SimSpace;
template<class T> class SimChain;
template<class T> class SimIterator;
template<class T> class XorChain;

template<class T>
class SimNode {
	friend class SimSpace<T>;
	friend class SimChain<T>;
	friend class SimIterator<T>;
	friend class XorChain<T>;
private:
	T data;
	int link;
};

template<class T>
class SimSpace {
	friend class SimChain<T>;
	friend class SimIterator<T>;
	friend class XorChain<T>;
public:
	SimSpace(int MaxSpaceSize = 100);
	~SimSpace() { delete[]node; }
	int Allocate();
	void Deallocate(int&i);
private:
	int NumberOfNodes, first1, first2;
	SimNode<T>* node;
};

template<class T>
SimSpace<T>::SimSpace(int MaxSpaceSize) {
	NumberOfNodes = MaxSpaceSize;
	node = new SimNode<T>[NumberOfNodes];
	first1 = 0;
	first2 = -1;
}

template<class T>
int SimSpace<T>::Allocate() {
	if (first2 != -1) {
		int res = first2;
		first2 = node[first2].link;
		return res;
	}
	else if (first1 != NumberOfNodes) {
	return first1++;
	}
	else return -1;
}

template<class T>
void SimSpace<T>::Deallocate(int& i) {
	node[i].link = first2;
	first2 = i;
	i = -1;
}

template<class T> class SimIterator;

template<class T>
class SimIterator{//Exercise 67
public:
	SimIterator(const SimChain<T>& c):list(c) {
		location = c.first;
	}

	T* Next() {
		if(location == -1) return nullptr;
		int res = location;
		location = list.S.node[location].link;
		return &list.S.node[res].data;
	}
private:
	int location;
	const SimChain<T>& list;
};


#endif