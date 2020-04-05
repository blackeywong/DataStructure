#pragma once
#ifndef _CHAIN_H
#define _CHAIN_H

#include <iostream>
#include "list.h"
#include "exceptions.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第三章
//Exercise 22 -34, 58-59


template<class T>class Chain;
template<class T>class ChainIterator;

template<class T>
class ChainNode {
	friend class Chain<T>;
	friend class ChainIterator<T>;
private:
	T data;
	ChainNode<T>* link;
};


template<class T>
class ChainIterator {
public:
	T* Initialize(const Chain<T>& c) {
		location = c.first;
		if (location) return &location->data;
		return nullptr;
	}

	T* Next() {
		if (!location) return nullptr;
		location = location->link;
		if (location) return &location->data;
		return nullptr;
	}
private:
	ChainNode<T>* location;
};

template<class T>
class Chain {
	template<class T>
	friend ostream& operator<<(ostream&out, const Chain<T>& c);
	//friend Chain<T>& operator=(Chain<T>& c, const Chain<T>&x);
	friend class ChainIterator<T>;
	template<class T>
	friend void Reverse(Chain<T>& c, Chain<T>& d);//Execise. 28
public:
	Chain() { first = last = nullptr; }
	~Chain() { Erase();  };
	Chain(const Chain<T>& c); //Execise. 22
	
	Chain(const LinearList<T>& l); //Execise. 23
	Chain<T>& FromList(const LinearList<T>& l);//Execise. 25
	LinearList<T>& ToList(); //Execise. 25
	LinearList<T>& ToList2(); //Execise. 25

	bool IsEmpty() { return first == nullptr; };
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(T&x) const;
	void Output(ostream & out) const;

	void Erase();

	Chain<T>& Insert(int k, const T&x);
	Chain<T>& Delete(int k, T& x);
	Chain<T>& Append(const T& x);

	Chain<T>& Reverse();//Execise. 27
	Chain<T>& Alternate(const Chain<T> &b) const; //Execise. 29
	Chain<T>& Alternate(Chain<T>& a, Chain<T>& b); //Execise. 30

	//void Swap(ChainNode<T>* p, ChainNode<T> * q);
	//int Max(int len) const;

	Chain<T>& InsertionSort(); //Execise. 58
	Chain<T>& BubbleSort(); //Execise. 59
	Chain<T>& SelectionSort(); //Execise. 59
	void Rank(int rank[]);
	Chain<T>& RankSort(); //Execise. 59

	Chain<T>& Merge(const Chain<T>& b); //Execise. 31
	Chain<T>& Merge(Chain<T>& a, Chain<T>& b); //Execise. 32

	Chain<T>& Split(Chain<T>& a, Chain<T>& b, Chain<T> &c); //Execise. 34
	Chain<T>& Split(Chain<T>& a, Chain<T>& b); //Execise. 33
private:
	ChainNode<T>* first;
	ChainNode<T>* last;
};

template<class T>
Chain<T>::Chain(const Chain<T>& c)
{
	ChainNode<T>* current = c.first;

	ChainNode<T>* preNode = nullptr;
	ChainNode<T>* newNode = nullptr;
	while (current)
	{
		newNode = new ChainNode<T>;
		if (current == c.first) first = newNode;//first node, need to set first
		newNode->data = current->data;
		if (preNode) preNode->link = newNode;
		preNode = newNode;
		current = current->link;
	}
	last = newNode;
	if (newNode) newNode->link = nullptr;
}

template<class T>
Chain<T>::Chain(const LinearList<T>& l)
{
	this->Chain<T>::Chain();

	for (int i = 0; i < l.Length(); ++i)
	{
		T x;
		l.Find(i, x);
		Insert(i, x);
	}
}

template<class T>
Chain<T>& Chain<T>::FromList(const LinearList<T>& l)
{
	Chain<T>* c = new Chain<T>(l);
	return *c;
}

template<class T>
LinearList<T>& Chain<T>::ToList()
{
	LinearList<T>* t = new LinearList<T>;

	int length = Length();

	for (int i = 0; i< length;++i)
	{
		T x;
		Find(i + 1, x);
		t->Insert(i, x);
	}

	return *t;
}

template<class T>
LinearList<T>& Chain<T>::ToList2()
{
	LinearList<T>* l = new LinearList<T>;

	ChainIterator<T> ci;
	T* x = ci.Initialize(*this);
	if (x) l->Insert(0, *x);
	int i = 1;
	while ((x=ci.Next()))	l->Insert(i++, *x);

	return *l;
}

template<class T>
int Chain<T>::Length() const
{
	ChainNode<T>* current = first;
	int len = 0;
	while (current) {
		++len;
		current = current->link;
	}

	return len;
}

template<class T>
void Chain<T>::Erase()
{
	ChainNode<T>* current = first;
	while (current) {
		ChainNode<T>* next = current->link;
		delete current;
		current = next;
	}
}

template<class T>
bool Chain<T>::Find(int k, T& x) const
{
	if (k<1)// || k>Lenth()), no need to do an extra traverse
		return false;

	ChainNode<T>* current = first;
	int i = 1;//1 means now it's already the first node
	while (i<k && current)
	{
		++i;
		current = current->link;
	}

	if (current) {
		x = current->data;
		return true;
	}
	return false;
}

template<class T>
int Chain<T>::Search(T& x) const
{
	ChainNode<T>* current = first;
	int i = 1;
	while (current && x != current->data)//add the judgement in condition
	{
		current = current->link;
		++i;
	}

	if (current) return i;
	return -1;
}

template<class T>
void Chain<T>::Output(ostream& out) const
{
	ChainNode<T>* current = first;
	while (current)
	{
		out << current->data << " ";
		current = current->link;
	}
	out << endl;
}

template<class T>
Chain<T>& Chain<T>::Insert(int k, const T& x)
{
	if (k < 0)	throw OutOfBounds();

	ChainNode<T>* c = new ChainNode<T>;
	c->data = x;


	ChainNode<T>* current = first;
	int i = 1;
	while (i < k && current)
	{
		current = current->link;
		++i;
	}

	if (k>0 && !current) throw OutOfBounds();

	if (!current || !current->link) last = c;

	if (k == 0)
	{
		c->link = first;
		first = c;
	}
	else
	{
		ChainNode<T>* d = current->link;
		current->link = c;
		c->link = d;
	}
	return *this;
}

template<class T>
Chain<T>& Chain<T>::Delete(int k, T& x)
{
	if (k < 0 || !first)	throw OutOfBounds();

	ChainNode<T>* current = first;
	int i = 1;
	while (i < k-1 && current)
	{
		current = current->link;
		++i;
	}

	if (k > 1 && (!current || !current->link)) throw OutOfBounds();

	ChainNode<T>* next = current->link;

	if (!current || !current->link) last = current;

	if (k == 1)
	{
		x = current->data;
		first = current->link;
		delete current;
	}
	else
	{
		x = next->data;
		current->link = next->link;
		delete next;
	}

	return *this;
}

template<class T>
Chain<T>& Chain<T>::Append(const T& x)
{
	ChainNode<T> *c = new ChainNode<T>;
	c->data = x;
	c->link = nullptr;
	if (first)
		last->link = c;
	else
		first = c;
	last = c;

	return *this;
}

template<class T>
Chain<T>& Chain<T>::Reverse()
{
	if (first == nullptr || first == last) return *this; //empty or 1 node only
	last = first;

	ChainNode<T>* p=nullptr, * q=first, *r = first->link;

	while (r)
	{
		q ->link = p;
		p = q;
		q = r;
		r= r->link;
	}
	first = q;
	q->link = p;

	return *this;
}

template<class T>
Chain<T>& Chain<T>::Alternate(const Chain<T>& b) const
{
	Chain<T>* c = new Chain<T>;
	ChainNode<T>* curA = first;
	ChainNode<T>* curB = b.first;
	ChainNode<T>* tailC = nullptr;

	while (curA && curB)
	{
		ChainNode<T> *newNode1 = new ChainNode<T>();
		newNode1->data = curA->data;
		ChainNode<T> *newNode2 = new ChainNode<T>();
		newNode2->data = curB->data;
		if (!c->first) c->first = newNode1;
		else if (tailC) tailC->link = newNode1;
		newNode1->link = newNode2;
		tailC = newNode2;
		c->last = newNode2;
		tailC->link = nullptr;
		curA = curA->link;
		curB = curB->link;
	}

	ChainNode<T>* left = curA != nullptr ? curA : curB;
	while (left)
	{
		ChainNode<T>* newNode = new ChainNode<T>();
		newNode->data = left->data;
		newNode->link = nullptr;
		if (!c->first) c->first = newNode;
		else if (tailC) tailC->link = newNode;
		tailC = newNode;
		c->last = newNode;
		tailC->link = nullptr;
		left = left->link;
	}
	return *c;
}

template<class T>
Chain<T>& Chain<T>::Alternate(Chain<T>& a, Chain<T>& b)
{
	ChainNode<T>* curA = a.first;
	ChainNode<T>* curB = b.first;
	ChainNode<T>* tailC = nullptr;

	while (curA && curB)
	{
		ChainNode<T>* nextA = curA->link;
		ChainNode<T>* nextB = curB->link;
		if (!first) first = curA;
		else if (tailC) tailC->link = curA;
		curA->link = curB;
		tailC = curB;
		last = curB;
		curA = nextA;
		curB = nextB;
	}

	ChainNode<T>* left = curA != nullptr ? curA : curB;
	while (left)
	{
		ChainNode<T>* next = left->link;
		if (!first) first = left;
		else if (tailC) tailC->link = left;
		tailC = left;
		last = left;
		left = next;
	}

	a.first = a.last = b.first = b.last = nullptr;
	return *this;
}

template<class T>
Chain<T>& Chain<T>::Merge(const Chain<T>& b)
{
	Chain<T>* c = new Chain<T>;
	ChainNode<T>* curA = first;
	ChainNode<T>* curB = b.first;

	ChainNode<T>* newNode = nullptr;
	while (curA || curB)
	{
		newNode = new ChainNode<T>();
		newNode->link = nullptr;

		if (curA == nullptr || curB != nullptr && curA->data > curB->data)
		{
			newNode->data = curB->data;
			curB = curB->link;
		}
		else if (curB == nullptr || curA != nullptr && curA->data <= curB->data) 
		{
			newNode->data = curA->data;
			curA = curA->link;
		}
		if (!c->first) c->first = newNode;
		else last->link = newNode;
		last = newNode;
	}

	return *c;

}

template<class T>
Chain<T>& Chain<T>::Merge(Chain<T>& a, Chain<T>& b)
{
	ChainNode<T>* curA = a.first;
	ChainNode<T>* curB = b.first;
	while (curA || curB)
	{
		if (curA == nullptr || curB != nullptr && curA->data > curB->data)
		{
			if (!first) first = curB;
			else last->link = curB;
			last = curB;
			curB = curB->link;
		}
		else if (curB == nullptr || curA !=nullptr && curA->data <= curB->data)
		{
			if (!first) first = curA;
			else last->link = curA;
			last = curA;
			curA = curA->link;
		}
	}

	a.first = a.last = nullptr;
	b.first = b.last = nullptr;

	return *this;
}

template<class T>
Chain<T>& Chain<T>::Split(Chain<T>& a, Chain<T>& b, Chain<T>& c)
{
	int len = c.Length();

	ChainNode<T>* cur = c.first;

	for (int i = 1; i <= len&&cur; ++i)
	{
		if (i % 2 == 1)
		{
			if (i == 1)	a.first = cur;
			else a.last->link = cur;
			a.last = cur;
		}else {
			if (i == 2)	b.first = cur;
			else b.last->link = cur;
			b.last = cur;
		}
		cur = cur->link;

		if (a.last) a.last->link = nullptr;
		if (b.last) b.last->link = nullptr;
	}
	c.first = c.last = nullptr;

	return *this;
}

template<class T>
Chain<T>& Chain<T>::Split(Chain<T>& a, Chain<T>& b)
{
	int len = Length();

	ChainNode<T>* cur = first;

	for (int i = 1; i <= len && cur; ++i)
	{
		ChainNode<T>* newNode = new ChainNode<T>;
		newNode->data = cur->data;
		newNode->link = nullptr;
		if (i % 2 == 1)
		{

			if (i == 1)	a.first = newNode;
			else a.last->link = newNode;
			a.last = newNode;
		}
		else {
			if (i == 2)	b.first = newNode;
			else b.last->link = newNode;
			b.last = newNode;
		}

		cur = cur->link;
	}

	return *this;
}


//template<class T>
//void Chain<T>::Swap(ChainNode<T>* p, ChainNode<T>* q)
//{
//	T tmp = p->data;
//	p->data = q->data;
//	q->data = tmp;
//}

//template<class T>
//int Chain<T>::Max(int len) const
//{
//	ChainNode<T>* current = nullptr, *maxNode = first;
//	int max = 1;
//	if (len <=1) return len;
//	current = first->link;
//
//	for (int i = 2; i <= len; ++i)
//	{
//		if (current->data > maxNode->data)
//		{
//			max = i;
//			maxNode = current;
//		}
//		current = current->link;
//	}
//	return max;
//}

template<class T>
Chain<T>& Chain<T>::InsertionSort()
{
	int len = Length();
	if (len <= 1) return *this;

	for (int i = 2; i <= len; ++i)
	{
		//found to insert
		ChainNode<T>* toInsert = first, * toInsertPrev = nullptr;
		for (int j = 1; j < i; ++j)
		{
			toInsertPrev = toInsert;
			toInsert = toInsert->link;
		}

		//find max
		ChainNode<T>* cur = first, * curPrev = nullptr;
		for (int j = 1; j < i && cur->data < toInsert->data; ++j)
		{
			curPrev = cur;
			cur = cur->link;
		}

		//found location. insert toInsert among cur and curPrev;
		if (cur == toInsert) continue;
		if (!toInsertPrev) first = toInsert->link;
		else toInsertPrev->link = toInsert->link;
		if (!curPrev) first = toInsert;
		else curPrev->link = toInsert;
		toInsert->link = cur;
		last = toInsert;
	}

	return *this;
}

template<class T>
Chain<T>& Chain<T>::BubbleSort()
{
	int len = Length();
	if (len <= 1) return *this;

	for (int i = len; i >= 2; --i)
	{
		ChainNode<T>* p = nullptr, *q = first, * r = q->link;
		while (r)
		{
			if (q->data > r->data)
			{
				if (!p) first = r;
				else p->link = r;
				q->link = r->link;
				r->link = q;
			}
			p = q;
			q = r;
			r = r->link;
		}
		if(i==len) last = q;
	}
	return *this;
}

template<class T>
Chain<T>& Chain<T>::SelectionSort()
{
	int len = Length();
	if (len <= 1) return *this;

	//for (int i = len; i > 1;--i)
	//{
	//	int max = Max(i);
	//	T x;
	//	Delete(max, x);
	//	Insert(i-1,x);
	//}

	for (int i = len; i >= 2; --i)
	{
		//find max
		ChainNode<T>* p = first, * q = p->link;
		ChainNode<T>* max = p, * maxPrev = nullptr;
		for (int j = 2; j <= i; ++j)
		{
			if (q->data > max->data)
			{
				max = q;
				maxPrev = p;
			}
			p = q;
			q = q->link;
		}

		//found max, and p is the last node
		//move max to be after p, if p is not the last node
		if (p == max) continue;
		if (!maxPrev) first = max->link;
		else maxPrev->link = max->link;
		p->link = max;
		if(i==len) last = max;
		max->link = q;
	}

	return *this;
}

template<class T>
void Chain<T>::Rank(int rank[])
{
	int len = Length();

	ChainNode<T>* p = nullptr;
	for (int i = 0; i < len - 1; ++i)
	{
		if (i == 0) p = first;
		else p = p->link;
		ChainNode<T>* q = p;
		for (int j = i+1; j < len; ++j)
		{
			 q = q->link;
			if (p->data > q->data) ++rank[i];
			else ++rank[j];
		}
	}
}

template<class T>
Chain<T>& Chain<T>::RankSort()
{
	int len = Length();
	if (len <= 1) return *this;

	int* rank = new int[len] {0};

	Rank(rank);
//	cout << rank << endl;
	for (int i = 0; i < len; ++i)
	{
		while (rank[i] != i) 
		{
			ChainNode<T>* p1 = nullptr, * q1 = first, * r1 = first->link,
				        * p2 = nullptr, * q2 = first, * r2 = first->link;

			for (int j = 1; j <= i; ++j)
			{
				p1 = q1;
				q1 = r1;
				r1 = r1->link;
			}
			for (int j = 1; j <= rank[i]; ++j)
			{
				p2 = q2;
				q2 = r2;
				r2 = r2->link;
			}

			//swap q1 and q2

			if (!p1) first = q2;
			else p1->link = q2;
			if (!p2) first = q1;
			else p2->link = q1;
			if (q1 == p2)
			{
				q2->link = p2;
				p2->link = r2;
			}
			else if (q2 == p1)
			{
				q1->link = p1;
				p1->link = r1;

			}
			else
			{
				q2->link = r1;
				q1->link = r2;
			}
			if (!r1) last = q2;
			if (!r2) last = q1;


			//swap content of rank[i] and rank[rank[i]]
			int temp = rank[i];
			rank[i] = rank[temp];
			rank[temp] = temp;

		}
	}

	delete[] rank;
}


template<class T>
void Reverse(Chain<T>& c, Chain<T>& d)
{
	c.Reverse();
	d.first = c.first;
	d.last = c.last;
	c.first = nullptr;
	c.last = nullptr;

}

template<class T>
ostream& operator<<(ostream& out, const Chain<T>& c)
{
	c.Output(out);
	return out;
}

#endif
