#ifndef _EXTENDEDCHAIN_H
#define _EXTENDEDCHAIN_H
#include<iostream>
#include "chain.h"
#include "chainnode.h"
//数据结构算法与应用-C++语言描述 第六章
//Exercise 24，25
template<class T>
class ExtendedChain : public Chain<T>
{
	template<class T>
	friend void meld(const ExtendedChain<T>& a, const ExtendedChain<T>& b, ExtendedChain<T>& c);//Ecercise 17
	template<class T>
	friend void merge(const ExtendedChain<T>& a, const ExtendedChain<T>& b, ExtendedChain<T>& c);//Ecercise 19
	template<class T>
	friend void split(const ExtendedChain<T>& c, ExtendedChain<T>& a, ExtendedChain<T>& b); //Execise 21
public:
	ExtendedChain():Chain<T>(){lastNode=nullptr;}

	ExtendedChain(const Chain<T>& t) : Chain<T>(t){}

	ExtendedChain<T>& operator=(const ExtendedChain<T>& right);

	void clear();
	void push_back(const T& theElement);

	
	ExtendedChain<T>& circularShift(int index);//Exercise 23
	void zero() { this->firstNode = lastNode = nullptr; this->listSize = 0; }//chapter 7, linkedMatrix

protected:
	ChainNode<T> * lastNode;
};

template<class T>
void ExtendedChain<T>::clear(){
	while(this->firstNode){
		ChainNode<T>* next = this->firstNode->next;
		delete this->firstNode;
		this->firstNode = next;
	}
	this->listSize = 0;
	lastNode = nullptr;
}

template<class T>
void ExtendedChain<T>::push_back(const T& theElement){
	ChainNode<T> * newNode = new ChainNode<T>(theElement, nullptr);
	if(this->firstNode == nullptr){
		this->firstNode = lastNode = newNode;
	}else{
		lastNode->next = newNode;
		lastNode = newNode;
	}
	this->listSize++;
}


template<class T>
ExtendedChain<T>& ExtendedChain<T>::operator=(const ExtendedChain<T>& right) {
	if (!right.firstNode) return *this;
	clear();
	ChainNode<T>* current = right.firstNode;
	while (current) {
		push_back(current->element);
		current = current->next;
	}
	return *this;
}

template<class T>
void meld(const ExtendedChain<T>& a, const ExtendedChain<T>& b, ExtendedChain<T>& c){//Exercise 17
	int smallsize = a.size() <= b.size() ? a.size() : b.size();
	ChainNode<T>* cur1 = a.firstNode;
	ChainNode<T>* cur2 = b.firstNode;
	for(int i=0;i<smallsize;i++){
		c.push_back(cur1->element);
		c.push_back(cur2->element);
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	while(cur1){
		c.push_back(cur1->element);
		cur1 = cur1->next;
	}
	while(cur2){
		c.push_back(cur2->element);
		cur2 = cur2->next;
	}
}

template<class T>
void merge(const ExtendedChain<T>& a, const ExtendedChain<T>& b, ExtendedChain<T>& c){ //Execise 19
	ChainNode<T>* cur1 = a.firstNode;
	ChainNode<T>* cur2 = b.firstNode;
	while(cur1&&cur2){
		if(cur1->element <= cur2->element){
			c.push_back(cur1->element);
			cur1 = cur1->next;
		}else{
			c.push_back(cur2->element);
			cur2 = cur2->next;
		}
	}
	while(cur1){
		c.push_back(cur1->element);
		cur1 = cur1->next;
	}
	while(cur2){
		c.push_back(cur2->element);
		cur2 = cur2->next;
	}
}

template<class T>
void split(const ExtendedChain<T>& c, ExtendedChain<T>& a, ExtendedChain<T>& b) { //Execise 21
	ChainNode<T>* cur = c.firstNode;
	for (int i = 0; i < c.listSize && cur->next; i += 2) {
		a.push_back(cur->element);
		cur = cur->next;
		b.push_back(cur->element);
		cur = cur->next;
	}
	if (cur) a.push_back(cur->element);
}

template<class T>
ExtendedChain<T>& ExtendedChain<T>::circularShift(int index) {//Exercise 23
	if (this->listSize <= 1) return *this;
	for (int i = 0; i < index; i++) {
		this->lastNode->next = this->firstNode;
		this->lastNode = this->firstNode;
		this->firstNode = this->firstNode->next;
		this->lastNode->next = nullptr;
	}

	return *this;
}
#endif