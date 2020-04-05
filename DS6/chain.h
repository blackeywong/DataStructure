#pragma once
#ifndef _CHAIN_H
#define _CHAIN_H

#include <iostream>
#include <functional>
#include "../DS5/linearlist.h"
#include "../DS5/arraylist.h"
#include "../DS5/exceptions.h"
#include "chainnode.h"

using namespace std;
using namespace std::placeholders;
//数据结构算法与应用-C++语言描述 第六章
//Exercise 2-16，18，20，22，26, 63, 64

template<class T>
class Chain : public LinearList<T> {
public:
	Chain(int initialCapacity = 10);
	Chain(const Chain<T>& c);
	~Chain();

	bool empty() const { return listSize == 0; }
	int size() const {return listSize;}
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void insert(int theIndex, const T& theElement);
	void erase(int theIndex);
	void output(ostream & out) const;

	void setSize(int theSize);// Exercise 2
	void set(int theIndex, const T& theElement); //Exercise 3
	void removeRange(int fromIndex, int toIndex); //Exercise 4
	int lastIndexOf(const T& theElement) const; //Exercise 5

	ChainNode<T>& operator[](int theIndex);//Exercise 6
	bool operator==(const Chain<T>& theChain) const;//Exercise 7
	bool operator!=(const Chain<T>& theChain) const;//Exercise 8
	bool operator<(const Chain<T>& theChain) const;//Exercise 9

	void swap(Chain<T>& theChain);//Exercise 10
	void fromList(const ArrayList<T>& theList);//Ecercise 13
	void toList(ArrayList<T>& theList) const;//Ecercise 13
	void leftShift(int i); //Exercise 14

	Chain<T>& reverse();//Execise 15
	Chain<T>& meld(Chain<T>& a, Chain<T>& b);//Exercise 18

	Chain<T>& insertionSort(); //Execise. 26
	Chain<T>& bubbleSort(); //Execise. 27
	Chain<T>& selectionSort(); //Execise. 27
	void rank(int rank[]);
	Chain<T>& rankSort(); //Execise. 27

	//Chain<T>& binSort(int range);//Execise 63
	Chain<T>& binSort(int range, int (*func)(ChainNode<T>*) = nullptr);//Execise 65
	Chain<T>& radixSort(int r, int d);//Execise 64
	int getNumForRadixSort(ChainNode<T>* node, int r, int d, int i);
	Chain<T>& radixSort2(int r, int d);

	Chain<T>& merge(Chain<T>& a, Chain<T>& b); //Execise 20

	Chain<T>& split(Chain<T>& a, Chain<T>& b); //Execise 22

public:
	class iterator;
	iterator begin(){return iterator(firstNode);}
	iterator end(){return iterator(nullptr);}
	iterator last() { 
		if (listSize <= 1) return iterator(firstNode);
		ChainNode<T>* cur = firstNode;
		for (int i = 0; i < listSize -1 ; i++)
			cur = cur->next;
		return iterator(cur);
	}
	int iteratorToIndex(iterator iter) {
		int i = 0;
		for (iterator b = begin(); b != iter; b++)
			i++;
		return i;
	}
	iterator previous(iterator iter) {
		int index = iteratorToIndex(iter);
		if (index == 0) index = listSize - 1;
		else index--;
		ChainNode<T>* cur= firstNode;
		for (int i = 0; i < index; i++)
			cur = cur->next;

		return iterator(cur);
	}
protected:
	void checkIndex(int theIndex) const;

	ChainNode<T>* firstNode;
	int listSize;
};


template<class T>
class Chain<T>::iterator {
public:
	typedef forward_iterator_tag iterator_capacity;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;

	iterator(ChainNode<T>* theNode = nullptr) { node = theNode;}

	T& operator*() const { return node->element;}
	T* operator->() const { return &node->element;}

	iterator& operator++() { node = node->next; return * this;}
	iterator operator++(int) {iterator old = *this; node = node->next; return old; }

	bool operator!=(const iterator right) const {return node != right.node;}
	bool operator==(const iterator right) const {return node == right.node;}

	iterator operator+(const ptrdiff_t diff) const {
			ChainNode<T>* p = node;
			for (int i = 0; i < diff; i++) p = p->next;
			return iterator(p);
		}

protected:
	ChainNode<T>* node;
};

template<class T>
Chain<T>::Chain(int initialCapacity){
	if(initialCapacity < 1){
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " must be > 0.";
		throw IllegalParameterValue(s.str());
	}
	firstNode = nullptr;
	listSize = 0;
}

template<class T>
Chain<T>::Chain(const Chain<T>& c) {
	firstNode = nullptr;
	listSize = c.listSize;
	ChainNode<T>* cur = nullptr;
	ChainNode<T>* ccur = c.firstNode;

	while(ccur){
		ChainNode<T>* newNode = new ChainNode<T>(ccur->element);
		if(!firstNode){
			firstNode = newNode;
		}else{
			cur->next = newNode;
		}
		newNode->next = nullptr;
		cur = newNode;
		ccur = ccur->next;
	}
}


template<class T>
Chain<T>::~Chain(){
	while(firstNode){
		ChainNode<T> * next = firstNode->next;
		firstNode->element.~T();
		delete firstNode;
		firstNode = next;
	}
}

template<class T>
void Chain<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize) {
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw IllegalIndex(s.str());
	}
}

template<class T>
void Chain<T>::setSize(int theSize) {
	if (listSize == 0 || theSize >= listSize) return;


	ChainNode<T>* cur = firstNode;
	for (int i = 1; i < theSize; i++)
		cur = cur->next;

	ChainNode<T>* prev = cur;
	if (theSize == 0) firstNode = nullptr;
	else {
		cur = cur->next;
		prev->next = nullptr;
	}
	for (int i = theSize; i < listSize; i++)
	{
		prev = cur;
		cur = cur->next;
		delete prev;
	}
	listSize = theSize;
}

template<class T>
void Chain<T>::set(int theIndex, const T& theElement)
{
	checkIndex(theIndex);

	if (theIndex == 0) {
		firstNode->element = theElement;
		return;
	}

	ChainNode<T>* cur = firstNode;
	for (int i = 0; i < theIndex; i++)
		cur = cur->next;
	cur->element = theElement;
}

template<class T>
void Chain<T>::removeRange(int fromIndex, int toIndex)
{
	checkIndex(fromIndex);
	checkIndex(toIndex);
	if (fromIndex > toIndex) return;

	ChainNode<T>* cur = firstNode;
	for (int i = 1; i < fromIndex; i++)
		cur = cur->next;
	ChainNode<T>* beforeDel = cur;
	for (int i = fromIndex; i <= toIndex; i++)
	{
		if (fromIndex == 0) {
			firstNode = cur->next;
			delete cur;
			cur = firstNode;
		}
		else {
			cur = beforeDel->next;
			beforeDel->next = cur->next;
			delete cur;
		}
	}

	listSize = listSize - (toIndex - fromIndex + 1);
}

template<class T>
int Chain<T>::lastIndexOf(const T& theElement) const
{
	if (listSize < 1) return -1;

	int result = -1;
	ChainNode<T>* cur = firstNode;
	for (int i = 0; i < listSize; i++) {
		if (cur->element == theElement)
			result = i;
		cur = cur->next;
	}
	return result;
}

template<class T>
ChainNode<T>& Chain<T>::operator[](int theIndex)
{
	checkIndex(theIndex);

	if (theIndex == 0){
		return *firstNode;
	}

	ChainNode<T>* cur = firstNode;
	for (int i = 1; i <= theIndex; i++)
		cur = cur->next;
	return *cur;
}

template<class T>
bool Chain<T>::operator==(const Chain<T>& right) const
{
	if(listSize == 0 && right.listSize == 0) return true;
	if(listSize != right.listSize) return false;

	ChainNode<T>* cur1 = firstNode;
	ChainNode<T>* cur2 = right.firstNode;

	for (int i = 0; i < listSize; i++){
		if(cur1->element != cur2->element) return false;
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return true;
}

template<class T>
bool Chain<T>::operator!=(const Chain<T>& right) const
{
	if(listSize == 0 && right.listSize == 0) return false;
	if(listSize != right.listSize) return true;

	ChainNode<T>* cur1 = firstNode;
	ChainNode<T>* cur2 = right.firstNode;

	for (int i = 0; i < listSize; i++){
		if(cur1->element != cur2->element) return true;
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return false;
}

template<class T>
bool Chain<T>::operator<(const Chain<T>& right) const
{
	if(listSize == 0 && right.listSize > 0) return true;
	if(listSize > 0 && right.listSize == 0) return false;
	int small = listSize <= right.listSize ? listSize : right.listSize;

	ChainNode<T>* cur1 = firstNode;
	ChainNode<T>* cur2 = right.firstNode;

	for (int i = 0; i < small; i++){
		if(cur1->element < cur2->element) return true;
		if (cur1->element > cur2->element) return false;
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	if(cur2 != nullptr) return true;

	return false;
}

template<class T>
void Chain<T>::swap(Chain<T>& theChain)
{
	ChainNode<T>* old = firstNode;
	firstNode = theChain.firstNode;
	theChain.firstNode = old;

	int temp = listSize;
	listSize = theChain.listSize;
	theChain.listSize = temp;
}

template<class T>
void Chain<T>::fromList(const ArrayList<T>& theList)
{
	if(theList.size() == 0) return;
	for (int i = 0; i< theList.size();++i)
	{
		insert(i, theList.get(i));
	}
}

template<class T>
void Chain<T>::toList(ArrayList<T>& theList) const
{
	if(listSize == 0) return;
	ChainNode<T>* cur = firstNode;
	for (int i = 0; i< listSize;++i)
	{
		theList.insert(i, cur->element);
		cur=cur->next;
	}
}

template<class T>
void Chain<T>::leftShift(int i){
		if(i < 0 || i>listSize){
		ostringstream s;
		s << "Index = " << i << " must be >= 0 and <= listSize.";
		throw IllegalParameterValue(s.str());
	}
	if(i==0) return;
	if(i>listSize) i=listSize;

	ChainNode<T>* cur = firstNode;
	for(int j=0;j<i;j++){
		firstNode = cur->next;
		delete cur;
		cur = firstNode;
		listSize--;
	}
}

template<class T>
T& Chain<T>::get(int theIndex) const
{
	checkIndex(theIndex);

	ChainNode<T>* current = firstNode;
	int i = 0;//1 means now it's already the firstNode node
	while (i< theIndex && current)
	{
		++i;
		current = current->next;
	}
	return current->element;
}

template<class T>
int Chain<T>::indexOf(const T& theElement) const
{
	ChainNode<T>* current = firstNode;
	int i = 0;
	while (current && theElement != current->element)//add the judgement in condition
	{
		current = current->next;
		++i;
	}

	if (current) return i;
	return -1;
}

template<class T>
void Chain<T>::output(ostream& out) const
{
	ChainNode<T>* current = firstNode;
	while (current)
	{
		out << current->element << " ";
		current = current->next;
	}
	out << endl;
}

template<class T>
void Chain<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize)	throw OutOfBounds();

	ChainNode<T>* c = new ChainNode<T>;
	c->element = theElement;


	ChainNode<T>* current = firstNode;
	int i = 1;
	while (i < theIndex && current)
	{
		current = current->next;
		++i;
	}

	if (theIndex == 0)
	{
		c->next = firstNode;
		firstNode = c;
	}
	else
	{
		ChainNode<T>* d = current->next;
		current->next = c;
		c->next = d;
	}
	listSize++;
}

template<class T>
void Chain<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	ChainNode<T>* current = firstNode;
	int i = 0;
	while (i < theIndex-1 && current)
	{
		current = current->next;
		++i;
	}

	ChainNode<T>* next = current->next;


	if (theIndex == 0)
	{
		firstNode = current->next;
		delete current;
	}
	else
	{
		current->next = next->next;
		delete next;
	}
	listSize--;
}

template<class T>
Chain<T>& Chain<T>::reverse()
{
	if (listSize <=1) return *this;

	ChainNode<T>* p=nullptr, * q=firstNode, *r = firstNode->next;

	while (r)
	{
		q ->next = p;
		p = q;
		q = r;
		r= r->next;
	}
	firstNode = q;
	q->next = p;

	return *this;
}

template<class T>
Chain<T>& Chain<T>::meld(Chain<T>& a, Chain<T>& b)
{
	ChainNode<T>* curA = a.firstNode;
	ChainNode<T>* curB = b.firstNode;
	ChainNode<T>* tailC = nullptr;

	while (curA && curB)
	{
		ChainNode<T>* nextA = curA->next;
		ChainNode<T>* nextB = curB->next;
		if (!firstNode) firstNode = curA;
		else if (tailC) tailC->next = curA;
		curA->next = curB;
		tailC = curB;
		curA = nextA;
		curB = nextB;
	}

	ChainNode<T>* left = curA != nullptr ? curA : curB;
	while (left)
	{
		ChainNode<T>* next = left->next;
		if (!firstNode) firstNode = left;
		else if (tailC) tailC->next = left;
		tailC = left;
		left = next;
	}

	a.firstNode =b.firstNode = nullptr;
	return *this;
}

template<class T>
Chain<T>& Chain<T>::merge(Chain<T>& a, Chain<T>& b)
{
	ChainNode<T>* curA = a.firstNode;
	ChainNode<T>* curB = b.firstNode;
	ChainNode<T>* curC = firstNode;
	while (curA || curB)
	{
		if (curA == nullptr || curB != nullptr && curA->element > curB->element)
		{
			if (!firstNode) {
				firstNode = curB;
				curC=firstNode;
			}else{
				curC->next=curB;
				curC=curB;
			}
			curB = curB->next;
		}
		else if (curB == nullptr || curA !=nullptr && curA->element <= curB->element)
		{
			if (!firstNode) {
				firstNode = curA;
				curC=firstNode;
			}else{
				curC->next=curA;
				curC=curA;
			}
			curA = curA->next;
		}
	}

	listSize = a.listSize + b.listSize;
	a.firstNode = b.firstNode = nullptr;
	a.listSize = b.listSize = 0;

	return *this;
}

template<class T>
Chain<T>& Chain<T>::split(Chain<T>& a, Chain<T>& b)
{
	ChainNode<T>* cur = firstNode;
	ChainNode<T>* next = nullptr;
	ChainNode<T>* curA = nullptr;
	ChainNode<T>* curB = nullptr;

	for (int i = 0; i < listSize && cur; ++i)
	{
		next = cur->next;
		if (i % 2 == 0)
		{
			if (i == 0) {
				a.firstNode = cur;
				curA = cur;
			}
			else {
				curA->next = cur;
				curA = cur;
				curA->next = nullptr;
			}
			a.listSize++;
		}
		else {
				if (i == 1) {
					b.firstNode = cur;
					curB = cur;
				}
				else {
				curB->next = cur;
				curB = cur;
				curB->next = nullptr;
			}
			b.listSize++;
		}
		cur = next;
	}
	firstNode = nullptr;
	listSize = 0;

	return *this;
}

template<class T>
Chain<T>& Chain<T>::insertionSort()
{
	int len = listSize;
	if (len <= 1) return *this;

	for (int i = 2; i <= len; ++i)
	{
		//found to insert
		ChainNode<T>* toInsert = firstNode, * toInsertPrev = nullptr;
		for (int j = 1; j < i; ++j)
		{
			toInsertPrev = toInsert;
			toInsert = toInsert->next;
		}

		//find max
		ChainNode<T>* cur = firstNode, * curPrev = nullptr;
		for (int j = 1; j < i && cur->element < toInsert->element; ++j)
		{
			curPrev = cur;
			cur = cur->next;
		}

		//found location. insert toInsert among cur and curPrev;
		if (cur == toInsert) continue;
		if (!toInsertPrev) firstNode = toInsert->next;
		else toInsertPrev->next = toInsert->next;
		if (!curPrev) firstNode = toInsert;
		else curPrev->next = toInsert;
		toInsert->next = cur;
	}

	return *this;
}

template<class T>
Chain<T>& Chain<T>::bubbleSort()
{
	int len = listSize;
	if (len <= 1) return *this;

	for (int i = len; i >= 2; --i)
	{
		ChainNode<T>* p = nullptr, *q = firstNode, * r = q->next;
		while (r)
		{
			if (q->element > r->element)
			{
				if (!p) firstNode = r;
				else p->next = r;
				q->next = r->next;
				r->next = q;
			}
			p = q;
			q = r;
			r = r->next;
		}
	}
	return *this;
}

template<class T>
Chain<T>& Chain<T>::selectionSort()
{
	int len = listSize;
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
		ChainNode<T>* p = firstNode, * q = p->next;
		ChainNode<T>* max = p, * maxPrev = nullptr;
		for (int j = 2; j <= i; ++j)
		{
			if (q->element > max->element)
			{
				max = q;
				maxPrev = p;
			}
			p = q;
			q = q->next;
		}

		//found max, and p is the lastNode node
		//move max to be after p, if p is not the lastNode node
		if (p == max) continue;
		if (!maxPrev) firstNode = max->next;
		else maxPrev->next = max->next;
		p->next = max;
		max->next = q;
	}

	return *this;
}

template<class T>
void Chain<T>::rank(int rank[])
{
	int len = listSize;

	ChainNode<T>* p = nullptr;
	for (int i = 0; i < len - 1; ++i)
	{
		if (i == 0) p = firstNode;
		else p = p->next;
		ChainNode<T>* q = p;
		for (int j = i+1; j < len; ++j)
		{
			 q = q->next;
			if (p->element > q->element) ++rank[i];
			else ++rank[j];
		}
	}
}

template<class T>
Chain<T>& Chain<T>::rankSort()
{
	int len = listSize;
	if (len <= 1) return *this;

	int* r = new int[len];
	for(int i=0;i<len;i++)
		r[i] = 0;

	rank(r);
//	cout << rank << endl;
	for (int i = 0; i < len; ++i)
	{
		while (r[i] != i)
		{
			ChainNode<T>* p1 = nullptr, * q1 = firstNode, * r1 = firstNode->next,
				        * p2 = nullptr, * q2 = firstNode, * r2 = firstNode->next;

			for (int j = 1; j <= i; ++j)
			{
				p1 = q1;
				q1 = r1;
				r1 = r1->next;
			}
			for (int j = 1; j <= r[i]; ++j)
			{
				p2 = q2;
				q2 = r2;
				r2 = r2->next;
			}

			//swap q1 and q2

			if (!p1) firstNode = q2;
			else p1->next = q2;
			if (!p2) firstNode = q1;
			else p2->next = q1;
			if (q1 == p2)
			{
				q2->next = p2;
				p2->next = r2;
			}
			else if (q2 == p1)
			{
				q1->next = p1;
				p1->next = r1;

			}
			else
			{
				q2->next = r1;
				q1->next = r2;
			}

			//swap content of rank[i] and rank[rank[i]]
			int temp = r[i];
			r[i] = r[temp];
			r[temp] = temp;

		}
	}

	delete[] r;
}

template<class T>
Chain<T>& Chain<T>::binSort(int range, int (*func)(ChainNode<T>*)) {
	ChainNode<T>** top = nullptr;
	ChainNode<T>** bottom = nullptr;

	top = new ChainNode<T> * [range + 1];
	bottom = new ChainNode<T> * [range + 1];

	for (int i = 0; i <= range; i++)
		bottom[i] = nullptr;

	while (firstNode) {
		int binNum;
		if (!func) {
			//binNum = static_cast<int>(firstNode->element);
			binNum =firstNode->element;
		}
		else {
			binNum = func(firstNode);
		}

		if (bottom[binNum] == nullptr) {
			bottom[binNum] = top[binNum] = firstNode;
		}
		else {
			top[binNum]->next = firstNode;
			top[binNum] = firstNode;
		}
		firstNode = firstNode->next;
	}

	ChainNode<T>* tail = nullptr;
	for (int i = 0; i <= range; i++) {
		if (bottom[i] == nullptr)
			continue;
		if (tail == nullptr) {
			firstNode = bottom[i];
		}
		else {
			tail->next = bottom[i];
		}
		tail = top[i];
	}
	if (tail) tail->next = nullptr;

	delete[] bottom;
	delete[] top;

	return *this;
}

template<class T>
int Chain<T>::getNumForRadixSort(ChainNode<T>* node, int r, int d, int i) {
	int num = node->element;
	for (int k = 0; k < i; k++)
		num /= r;
	num %= r;
	return num;
}

template<class T>
Chain<T>& Chain<T>::radixSort2(int r, int d){//, int (*func)(ChainNode<T>*)) {
	if (firstNode == nullptr) return *this;
	for (int i = 0; i < d; i++) {
		//auto func = [r, d, i](ChainNode<T>* node)->int {return getNumForRadixSort(node, r, d, i);};
		//auto func = bind(&Chain<T>::getNumForRadixSort, _1, _2, r, d, i);
		//binSort(10, func);
	}
	return *this;
}

template<class T>
Chain<T>& Chain<T>::radixSort(int r, int d) {
	ChainNode<T>** bottom = nullptr;
	ChainNode<T>** top = nullptr;
	bottom = new ChainNode<T> * [r + 1];
	top = new ChainNode<T> * [r + 1];

	for (int i = 0; i < d; i++) {
		for (int j = 0; j <= r; j++)
			bottom[j] = nullptr;

		while (firstNode) {
			int num = firstNode->element;
			for (int k = 0; k < i; k++)
				num /= r;
			num %= r;
		
			if (bottom[num] == nullptr) {
				bottom[num] = top[num] = firstNode;
			}
			else {
				top[num]->next = firstNode;
				top[num] = firstNode;
			}
		
			firstNode = firstNode->next;
		}

		ChainNode<T>* end = nullptr;
		for (int j = 0; j <= r; j++) {
			if (bottom[j] == nullptr)
				continue;

			if (end == nullptr) {
				firstNode = bottom[j];
			}
			else {
				end->next = bottom[j];
			}
			end = top[j];
		}
		if (end != nullptr)
			end->next = nullptr;	
	}
	delete[] bottom;
	delete[] top;
	return *this;
}

template<class T>
ostream& operator<<(ostream& out, const Chain<T>& c)
{
	c.output(out);
	return out;
}

template<class T>
void listToChain(ArrayList<T>& l, Chain<T>& c){//Exercise 11
	for(int i=0;i<l.size();i++)
		c.insert(i,l.get(i));
}

template<class T>
void chainToList(Chain<T>& c, ArrayList<T>& l){//Exercise 12
	for(int i=0;i<c.size();i++)
		l.insert(i,c.get(i));
}

template<class T>
void chainToList2(Chain<T>& c, ArrayList<T>& l){//Exercise 12
	Chain<int>::iterator b = c.begin();
	for(int i=0;b!=c.end();i++){
		l.insert(i,*b++);
	}
}

template<class T>
void reverse(Chain<T>& c, Chain<T>& d)//Execise 16
{
	for(int i=0;i<c.size();i++)
		d.insert(0, c.get(i));
}
#endif
