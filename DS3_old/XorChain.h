#pragma once
#ifndef _XORCHAIN_H
#define _XORCHAIN_H
#include <iostream>
#include "SimSpace.h"
using namespace std;

template<class T>
class XorChain {
	template<class T>
	friend ostream& operator<<(ostream& out, XorChain<T>& c);
public:
	XorChain() {
		first = last = 0;
		S.node[0].link = 0;
	}
	~XorChain() { SCDestroy(); }
	void SCDestroy();
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(T& x) const;
	XorChain<T>& Insert(int k, const T& x);
	XorChain<T>& Delete(int k, T& x);
	void Output(ostream& out) const;
	void ROutput(ostream& out) const;

private:
	int first, last;
	static SimSpace<T> S;
};


template<class T>
void XorChain<T>::SCDestroy() {
	int next;
	while (first != -1) {
		next = S.node[first].link;
		S.Deallocate(first);
		first = next;
	}
}

template<class T>
int XorChain<T>::Length() const
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
bool XorChain<T>::Find(int k, T& x) const {
	if (k < 1) throw OutOfBounds();
	int cur = first;
	for (int i = 1; i < k && cur != -1; ++i) {
		cur = S.node[cur].link;
	}

	if (cur == -1)  throw OutOfBounds();
	x = S.node[cur].data;
	return true;
}

template<class T>
int XorChain<T>::Search(T& x) const {
	int cur = first;
	int i = 0;
	for (; cur != -1 && x != S.node[cur].data; ++i) {
		cur = S.node[cur].link;
	}

	if (cur == -1) return -1;
	return i + 1;
}

template<class T>
XorChain<T>& XorChain<T>::Insert(int k, const T& x) {
	if (k < 0) throw OutOfBounds();

	int n = S.Allocate();
	if (n == 0) n = S.Allocate();//abandon node[0]
	S.node[n].data = x;

	if (first == 0) //empty chain
	{
		first = last = n;
		S.node[n].link = 0;
		return *this;
	}

	int prev = 0;
	int cur = first;
	int next = S.node[first].link; //it is the index of second node
	if (next == 0) //only 1 node
	{
		if (k == 0) {
			last = first;
			first = n;
		}
		else {
			last = n;
		}
		S.node[first].link = last;
		S.node[last].link = first;
		return *this;
	}

	for (int i = 1; i < k && cur!=last; ++i) {
		prev = cur;
		cur = next;
		next = prev ^ S.node[next].link;
	}

	if (k>0 && prev == last) throw OutOfBounds();

	if (k == 0)
	{
		S.node[first].link = S.node[first].link ^ n;
		S.node[n].link = first;
		first = n;
		return *this;
	}

	if (cur == last)
	{
		S.node[cur].link = prev ^ n;
		S.node[n].link = last;
		last = n;
		return *this;
	}
	
	S.node[n].link = cur ^ next; //suppose original it's a->b->d->e, to insert c between b and d
	S.node[cur].link = prev ^ n;// b->link = (b ^ d) ^ b ^ c
	S.node[next].link = S.node[next].link ^ cur ^ n;// d->link = (d ^ e) ^ d ^ c
	return *this;
}

template<class T>
XorChain<T>& XorChain<T>::Delete(int k, T& x) {
	if (k < 1 || first == 0) throw OutOfBounds();

	int prev = 0;
	int cur = first;
	int next = S.node[first].link; //it is the index of second node

	if (k == 1) {
		x = S.node[first].data;
		if (next == 0) //only one node
		{
			first = last = 0;
		}
		else {
			S.node[next].link ^= cur;
			first = next;
		}
		
		S.Deallocate(cur);
		return *this;
	}

	for (int i = 1; i < k && cur != last; ++i) {
		prev = cur;
		cur = next;
		next = prev ^ S.node[next].link;
	}


	if (k > 0 && prev == last) throw OutOfBounds();

	if (cur == last)
	{
		x = S.node[cur].data;
		S.node[prev].link = S.node[prev].link ^ cur;
		last = prev;
		return *this;
	}
	x = S.node[cur].data;
	S.node[prev].link = S.node[prev].link ^ cur ^ next; //supporse a->b->c->d->e, delete c. b->link should be a^d: (a^c) ^ c ^ d
	S.node[next].link = S.node[next].link ^ cur ^ prev; //d->link should be b^e: (c^e) ^ c ^ b

	S.Deallocate(cur);
	return *this;
}

template<class T>
void XorChain<T>::Output(ostream& out) const
{
	int prev = 0;
	int cur = first;
	int next = S.node[first].link;

	while (cur != 0) {
		out << S.node[cur].data << " ";
		prev = cur;
		cur = next;
		next = prev ^ S.node[next].link;
	}
	out << endl;
}

template<class T>
void XorChain<T>::ROutput(ostream& out) const
{
	int prev = 0;
	int cur = last;
	int next = S.node[last].link;

	while (cur != 0) {
		out << S.node[cur].data << " ";
		prev = cur;
		cur = next;
		next = prev ^ S.node[next].link;
	}
	out << endl;
}

template<class T>
ostream& operator<<(ostream& out, XorChain<T>& c) {
	c.Output(out);
	return out;
}


#endif


