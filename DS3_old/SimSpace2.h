#pragma once
#ifndef _SIMSPACE2_H
#define _SIMSPACE2_H

#include <iostream>
#include "exceptions.h"
using namespace std;

//数据结构算法与应用-C++语言描述 第三章
//Exercise 68

template<class T> class SimSpace;
template<class T> class SimChain;

template<class T>
class SimNode {
	friend class SimSpace<T>;
	friend class SimChain<T>;
private:
	T data;
	int link;
};

template<class T>
class SimSpace {
	friend class SimChain<T>;
public:
	SimSpace(int MaxSpaceSize = 100);
	~SimSpace() { delete[]node; }
	SimNode<T>* Allocate();
	void Deallocate(SimNode<T>*n);
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
SimNode<T>* SimSpace<T>::Allocate() {
	if (first2 != -1) {
		int res = first2;
		first2 = node[first2].link;
		return &node[res];
	}
	else if (first1 != NumberOfNodes) {
	return &node[first1++];
	}
	else return nullptr;
}

template<class T>
void SimSpace<T>::Deallocate(SimNode<T>*n) {
	(*n).link = first2;
	int i = n-&node[0];
	first2 = i;
}

#endif