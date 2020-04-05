#pragma once
#ifndef _SIMCHAIN2_H
#define _SIMCHAIN2_H

#include <iostream>
#include "exceptions.h"
#include "SimSpace2.h"
using namespace std;

//数据结构算法与应用-C++语言描述 第三章
//Exercise 68, 70 - 73

template<class T>
class SimChain {
	template<class T>
	friend ostream& operator<<(ostream& out, SimChain<T>& c);
public:
	SimChain() { first = nullptr; }
	~SimChain() { SCDestroy(); }
	void SCDestroy();
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(T& x) const;
	SimChain<T>& Insert(int k, const T& x);
	SimChain<T>& Delete(int k, T& x);
	void Output(ostream& out) const;

	SimChain<T>& InsertionSort(); //Execise. 70
	SimChain<T>& BubbleSort(); //Execise. 72
	SimChain<T>& SelectionSort(); //Execise. 71
	void Rank(int rank[]);
	SimChain<T>& RankSort(); //Execise. 73
private:
	SimNode<T> * first;
	static SimSpace<T> S;
};

template<class T>
void SimChain<T>::SCDestroy() {
	SimNode<T>* next;
	while (first) {
		if(first->link!=-1)
			next= &S.node[first->link];
		else
			next = nullptr;
		S.Deallocate(first);
		first = next;
	}
}

template<class T>
int SimChain<T>::Length() const
{
	int len = 0;
	SimNode<T>* cur = first;
	while (cur)
	{
		++len;
		if(cur->link == -1)
			cur = nullptr;
		else
			cur = &S.node[cur->link];
	}
	return len;
}

template<class T>
bool SimChain<T>::Find(int k, T& x) const {
	if (k<1) throw OutOfBounds();
	SimNode<T>* cur = first;
	for (int i = 1; i < k && cur;++i) {
		if(cur->link == -1)
			cur = nullptr;
		else
			cur = &S.node[cur->link];
	}

	if (!cur)  throw OutOfBounds();
	x = cur->data;
	return true;
}

template<class T>
int SimChain<T>::Search(T& x) const {
	SimNode<T>* cur = first;
	int i = 0;
	for (;cur&&x!=cur->data; ++i) {
		if(cur->link == -1)
			cur = nullptr;
		else
			cur = &S.node[cur->link];
	}

	if (!cur) return -1;
	return i+1;
}

template<class T>
SimChain<T>& SimChain<T>::Insert(int k, const T& x) {
	if (k < 0) throw OutOfBounds();

	if (k == 0) {
		SimNode<T>*n = S.Allocate();
		n->data = x;
		if(first)
			n->link = first-&S.node[0];
		else
			n->link = -1;
		first = n;
		return *this;
	}

	SimNode<T>* cur = first;
	for (int i = 1; i < k && cur; ++i) {
		if(cur->link == -1)
			cur = nullptr;
		else
			cur = &S.node[cur->link];
	}

	if (!cur) throw OutOfBounds();

	SimNode<T>* n = S.Allocate();
	n->data = x;
	n->link = cur->link;
	cur->link = n-&S.node[0];

	return *this;
}

template<class T>
SimChain<T>& SimChain<T>::Delete(int k, T& x) {
	if (k < 1 || !first) throw OutOfBounds();

	if (k == 1) {
		x = first->data;
		SimNode<T>* tmp = first;
		if(first->link == -1)
			first = nullptr;
		else
			first =&S.node[first->link];
		S.Deallocate(tmp);
		return *this;
	}

	SimNode<T>* cur = first;
	for (int i = 1; i < k-1 && cur; ++i) {
		if(cur->link == -1)
			cur = nullptr;
		else
			cur = &S.node[cur->link];
	}

	if (cur == nullptr || cur->link == -1) throw OutOfBounds();
	SimNode<T>* prev = cur;
	cur = &S.node[cur->link];
	x = cur->data;
	prev->link = cur->link;
	S.Deallocate(cur);

	return *this;
}

template<class T>
void SimChain<T>::Output(ostream& out) const
{
	SimNode<T>* cur = first;
	while (cur) {
		out << cur->data << " ";
		if(cur->link != -1)
			cur = &S.node[cur->link];
		else
			break;
	}
	out << endl;
}

template<class T>
ostream& operator<<(ostream& out, SimChain<T>& c) {
	c.Output(out);
	return out;
}


template<class T>
SimChain<T>& SimChain<T>::InsertionSort()
{
	int len = Length();
	if (len <= 1) return *this;

	for (int i = 2; i <= len; ++i)
	{
		//found to insert
		SimNode<T>* toInsert = first, * toInsertPrev = nullptr;
		for (int j = 1; j < i; ++j)
		{
			toInsertPrev = toInsert;
			toInsert = &S.node[toInsert->link];
		}

		//find max
		SimNode<T>* cur = first, * curPrev = nullptr;
		for (int j = 1; j < i && cur->data < toInsert->data; ++j)
		{
			curPrev = cur;
			cur = &S.node[cur->link];
		}

		//found location. insert toInsert among cur and curPrev;
		if (cur == toInsert) continue;
		if (!toInsertPrev) first = &S.node[toInsert->link];
		else toInsertPrev->link = toInsert->link;
		if (!curPrev) first = toInsert;
		else curPrev->link = toInsert-&S.node[0];
		toInsert->link = cur-&S.node[0];
	}

	return *this;
}

template<class T>
SimChain<T>& SimChain<T>::BubbleSort()
{
	int len = Length();
	if (len <= 1) return *this;

	for (int i = len; i >= 2; --i)
	{
		SimNode<T>* p = nullptr, *q = first, * r = &S.node[q->link];
		while (r)
		{
			if (q->data > r->data)
			{
				if (!p) first = r;
				else p->link = r-&S.node[0];
				q->link = r->link;
				r->link = q-&S.node[0];
			}
			p = q;
			q = r;
			if(r->link == -1)
				r = nullptr;
			else
				r = &S.node[r->link];
		}
	}
	return *this;
}

template<class T>
SimChain<T>& SimChain<T>::SelectionSort()
{
	int len = Length();
	if (len <= 1) return *this;

	for (int i = len; i >= 2; --i)
	{
		//find max
		SimNode<T>* p = first, * q = &S.node[p->link];
		SimNode<T>* max = p, * maxPrev = nullptr;
		for (int j = 2; j <= i; ++j)
		{
			if (q->data > max->data)
			{
				max = q;
				maxPrev = p;
			}
			p = q;
			q = &S.node[q->link];
		}

		//found max, and p is the last node
		//move max to be after p, if p is not the last node
		if (p == max) continue;
		if (!maxPrev) first = &S.node[max->link];
		else maxPrev->link = max->link;
		p->link = max-&S.node[0];
		max->link = q-&S.node[0];;
	}

	return *this;
}

template<class T>
void SimChain<T>::Rank(int rank[])
{
	int len = Length();

	SimNode<T>* p = nullptr;
	for (int i = 0; i < len - 1; ++i)
	{
		if (i == 0) p = first;
		else p = &S.node[p->link];
		SimNode<T>* q = p;
		for (int j = i+1; j < len; ++j)
		{
			 q = &S.node[q->link];
			if (p->data > q->data) ++rank[i];
			else ++rank[j];
		}
	}
}

template<class T>
SimChain<T>& SimChain<T>::RankSort()
{
	int len = Length();
	if (len <= 1) return *this;

	int* rank = new int[len];
	for(int i=0;i<len;i++)
		rank[i]=0;
	

	Rank(rank);
//	cout << rank << endl;
	for (int i = 0; i < len; ++i)
	{
		while (rank[i] != i) 
		{
			SimNode<T>* p1 = nullptr, * q1 = first, * r1 = &S.node[first->link],
				        * p2 = nullptr, * q2 = first, * r2 = &S.node[first->link];

			for (int j = 1; j <= i; ++j)
			{
				p1 = q1;
				q1 = r1;
				r1 = &S.node[r1->link];
			}
			for (int j = 1; j <= rank[i]; ++j)
			{
				p2 = q2;
				q2 = r2;
				r2 = &S.node[r2->link];
			}

			//swap q1 and q2

			if (!p1) first = q2;
			else p1->link = q2-&S.node[0];
			if (!p2) first = q1;
			else p2->link = q1-&S.node[0];
			if (q1 == p2)
			{
				q2->link = p2-&S.node[0];
				p2->link = r2-&S.node[0];
			}
			else if (q2 == p1)
			{
				q1->link = p1-&S.node[0];
				p1->link = r1-&S.node[0];

			}
			else
			{
				q2->link = r1-&S.node[0];
				q1->link = r2-&S.node[0];
			}

			//swap content of rank[i] and rank[rank[i]]
			int temp = rank[i];
			rank[i] = rank[temp];
			rank[temp] = temp;

		}
	}

	delete[] rank;
}


#endif