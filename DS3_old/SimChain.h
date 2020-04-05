#pragma once
#ifndef _SIMCHAIN_H
#define _SIMCHAIN_H

#include <iostream>
#include "exceptions.h"
#include "SimSpace2.h"
using namespace std;

//数据结构算法与应用-C++语言描述 第三章
//Exercise 67

template<class T>
class SimChain {
	template<class T>
	friend ostream& operator<<(ostream& out, SimChain<T>& c);
	friend class SimIterator<T>;
public:
	SimChain() { first = -1; }
	~SimChain() { SCDestroy(); }
	void SCDestroy();
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(T& x) const;
	SimChain<T>& Insert(int k, const T& x);
	SimChain<T>& Delete(int k, T& x);
	void Output(ostream& out) const;

private:
	int first;
	static SimSpace<T> S;
};

template<class T>
void SimChain<T>::SCDestroy() {
	int next;
	while (first != -1) {
		next= S.node[first].link;
		S.Deallocate(first);
		first = next;
	}
}

template<class T>
int SimChain<T>::Length() const
{
	int len = 0;
	int cur = first;
	while (cur != -1)
	{
		++len;
		cur = S.node[cur].link;
	}
	return len;
}

template<class T>
bool SimChain<T>::Find(int k, T& x) const {
	if (k<1) throw OutOfBounds();
	int cur = first;
	for (int i = 1; i < k && cur != -1;++i) {
		cur = S.node[cur].link;
	}

	if (cur == -1)  throw OutOfBounds();
	x = S.node[cur].data;
	return true;
}

template<class T>
int SimChain<T>::Search(T& x) const {
	int cur = first;
	int i = 0;
	for (;cur != -1&&x!=S.node[cur].data; ++i) {
		cur = S.node[cur].link;
	}

	if (cur == -1) return -1;
	return i+1;
}

template<class T>
SimChain<T>& SimChain<T>::Insert(int k, const T& x) {
	if (k < 0) throw OutOfBounds();

	if (k == 0) {
		int n = S.Allocate();
		S.node[n].data = x;
		S.node[n].link = first;
		first = n;
		return *this;
	}

	int cur = first;
	for (int i = 1; i < k && cur != -1; ++i) {
		cur = S.node[cur].link;
	}

	if (cur == -1) throw OutOfBounds();

	int n = S.Allocate();
	S.node[n].data = x;
	S.node[n].link = S.node[cur].link;
	S.node[cur].link = n;

	return *this;
}

template<class T>
SimChain<T>& SimChain<T>::Delete(int k, T& x) {
	if (k < 1 || first == -1) throw OutOfBounds();

	if (k == 1) {
		x = S.node[first].data;
		int tmp = first;
		first = S.node[first].link;
		S.Deallocate(tmp);
		return *this;
	}

	int cur = first;
	for (int i = 1; i < k-1 && cur != -1; ++i) {
		cur = S.node[cur].link;
	}

	if (cur == -1 || S.node[cur].link == -1) throw OutOfBounds();
	int prev = cur;
	cur = S.node[cur].link;
	x = S.node[cur].data;
	S.node[prev].link = S.node[cur].link;
	S.Deallocate(cur);

	return *this;
}

template<class T>
void SimChain<T>::Output(ostream& out) const
{
	int cur = first;
	while (cur != -1) {
		out << S.node[cur].data << " ";
		cur = S.node[cur].link;
	}
	out << endl;
}

template<class T>
ostream& operator<<(ostream& out, SimChain<T>& c) {
	c.Output(out);
	return out;
}

#endif