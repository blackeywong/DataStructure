#ifndef _EXTENDEDLINKEDQUEUE_H
#define _EXTENDEDLINKEDQUEUE_H

#include "extendedQueue_adt.h"
#include "linkedQueue.h"
#include <iostream>
#include <exception>
#include <algorithm>
//Exercise 13
template<class T>
class extendedLinkedQueue : virtual public linkedQueue<T>, virtual public extendedQueue_adt<T> {
public:
	extendedLinkedQueue(int initialCapacity = 10) :linkedQueue<T>() {}

	virtual bool empty() const override { return linkedQueue<T>::empty(); }
	virtual int size() const override { return linkedQueue<T>::size(); }
	virtual T& front() override { return linkedQueue<T>::front(); }
	virtual T& back() override { return linkedQueue<T>::back(); }
	virtual void pop() override { linkedQueue<T>::pop(); }
	virtual void push(const T& theElement) override { linkedQueue<T>::push(theElement); }
	
	virtual std::istream& input(std::istream& in) override;
	virtual std::ostream& output(std::ostream& out) override;
	virtual void split(extendedQueue_adt<T>& q1, extendedQueue_adt<T>& q2) override;
	virtual void merge(extendedQueue_adt<T>& q1, extendedQueue_adt<T>& q2) override;
	//Exercise 15
	ChainNode<T>* popNode();
	void pushNode(ChainNode<T>* theNode);

};

template<class T>
std::istream& operator>>(std::istream& in, extendedLinkedQueue<T>& eq) { return eq.input(in); }

template<class T>
std::ostream& operator<<(std::ostream& out, extendedLinkedQueue<T>& eq) { return eq.output(out); }

template<class T>
std::istream& extendedLinkedQueue<T>::input(std::istream& in) {
	T t;
	while (in >> t) {
		push(t);
	}
	return in;
}

template<class T>
std::ostream& extendedLinkedQueue<T>::output(std::ostream& out) {
	ChainNode<T>* cur = this->queueFront;
	while (cur) {
		out << cur->element << " ";
		cur = cur->next;
	}
	return out;
}

template<class T>
void extendedLinkedQueue<T>::split(extendedQueue_adt<T>& q1, extendedQueue_adt<T>& q2) {
	extendedLinkedQueue<T>& elq1 = dynamic_cast<extendedLinkedQueue<T>&>(q1);
	extendedLinkedQueue<T>& elq2 = dynamic_cast<extendedLinkedQueue<T>&>(q2);
	elq1.clear();
	elq2.clear();
	if (this->queueFront)	{
		elq1.queueFront = this->queueFront;
		this->queueFront = this->queueFront->next;
		elq1.queueSize++;
	}
	if (this->queueFront) {
		elq2.queueFront = this->queueFront;
		this->queueFront = this->queueFront->next;
		elq2.queueSize++;
	}

	ChainNode<T>* cur1 = elq1.queueFront;
	ChainNode<T>* cur2 = elq2.queueFront;
	while (this->queueFront) {
		cur1->next = this->queueFront;
		this->queueFront = this->queueFront->next;
		cur1 = cur1->next;
		elq1.queueSize++;
		if (this->queueFront) {
			cur2->next = this->queueFront;
			this->queueFront = this->queueFront->next;
			cur2 = cur2->next;
			elq2.queueSize++;
		}
	}
	elq1.queueBack = cur1;
	elq1.queueBack->next = nullptr;
	elq2.queueBack = cur2;
	elq2.queueBack->next = nullptr;
	this->queueFront = nullptr;
	this->queueBack = nullptr;
	this->queueSize = 0;
}

template<class T>
void extendedLinkedQueue<T>::merge(extendedQueue_adt<T>& q1, extendedQueue_adt<T>& q2) {
	extendedLinkedQueue<T>& elq1 = dynamic_cast<extendedLinkedQueue<T>&>(q1);
	extendedLinkedQueue<T>& elq2 = dynamic_cast<extendedLinkedQueue<T>&>(q2);
	this->clear();
	if (elq1.queueSize != 0) {
		this->queueFront = elq1.queueFront;
		elq1.queueFront = elq1.queueFront->next;
		++this->queueSize;
	}else if (elq2.queueSize != 0) {
		this->queueFront = elq2.queueFront;
		elq2.queueFront = elq2.queueFront->next;
		++this->queueSize;
	}
	ChainNode<T>* cur = this->queueFront;
	while (elq2.queueFront != nullptr && elq1.queueFront != nullptr) {
		cur->next = elq2.queueFront;
		elq2.queueFront = elq2.queueFront->next;
		cur = cur->next;
		++this->queueSize;
		cur->next = elq1.queueFront;
		elq1.queueFront = elq1.queueFront->next;
		cur = cur->next;
		++this->queueSize;
	}
	while (elq1.queueFront != nullptr) {
		cur->next = elq1.queueFront;
		elq1.queueFront = elq1.queueFront->next;
		cur = cur->next;
		++this->queueSize;
	}
	while (elq2.queueFront != nullptr) {
		cur->next = elq2.queueFront;
		elq2.queueFront = elq2.queueFront->next;
		cur = cur->next;
		++this->queueSize;
	}
	
	this->queueBack = cur;
	this->queueBack->next = nullptr;
	elq1.queueFront = elq1.queueBack = nullptr;
	elq1.queueSize = 0;
	elq2.queueFront = elq2.queueBack = nullptr;
	elq2.queueSize = 0;
}


template<class T>
ChainNode<T>* extendedLinkedQueue<T>::popNode() {
	ChainNode<T>* ret = this->queueFront;

	if (this->queueFront) {
		this->queueFront = this->queueFront->next;
		--this->queueSize;
		if (!this->queueFront)
			this->queueBack = nullptr;
	}

	return ret;
}

template<class T>
void extendedLinkedQueue<T>::pushNode(ChainNode<T>* theNode) {
	if (!this->queueFront) {
		this->queueFront = theNode;
	}
	else
	{
		this->queueBack->next = theNode;
	}
	++this->queueSize;
	this->queueBack = theNode;
	theNode->next = nullptr;
}


#endif