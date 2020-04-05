#pragma once
#ifndef _SORTEDCHAIN2_H
#define _SORTEDCHAIN2_H
#include "dictionary.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include "pairNode.h"
//Chain with both head node and tail node
template<class K, class E>
class sortedChain2 : public dictionary<K, E> {
public:
	sortedChain2();
	virtual ~sortedChain2() { clear(); }
	virtual bool empty() const override { return dSize == 0; }
	virtual int size() const override { return dSize; }
	virtual std::pair<K, E>* find(const K& key) const override;
	virtual void erase(const K& key) override;
	virtual void insert(const std::pair<K, E>& p) override;
	virtual std::istream& input(std::istream& in);
	virtual std::ostream& output(std::ostream& out);

protected:
	pairNode<K, E>* findPrev(const K& key) const;
	void clear();

	int dSize;
	pairNode<K, E>* firstNode, *lastNode;
};

template<class K, class E>
std::istream& operator>>(std::istream& in, sortedChain2<K, E>& sal) { return sal.input(in); }

template<class K, class E>
std::ostream& operator<<(std::ostream& out, sortedChain2<K, E>& sal) { return sal.output(out); }

template<class K, class E>
std::istream& sortedChain2<K, E>::input(std::istream& in) {
	K key;
	E value;
	while (in >> key && in >> value) {
		insert({ key, value });
	}
	return in;
}

template<class K, class E>
std::ostream& sortedChain2<K, E>::output(std::ostream& out) {
	pairNode<K, E>* cur = firstNode->next;
	while (cur != lastNode) {
		out << cur->element.first << "," << cur->element.second << " ";
		cur = cur->next;
	}
	return out;
}

template<class K, class E>
sortedChain2<K, E>::sortedChain2():dSize(0) {
	firstNode = new pairNode<K, E>();
	lastNode = new pairNode<K, E>();
	firstNode->next = lastNode;
	lastNode->next = nullptr;
}

template<class K, class E>
void sortedChain2<K, E>::clear() {
	while (firstNode != nullptr) {
		pairNode<K, E>* next = firstNode->next;
		delete firstNode;
		firstNode = next;
	}
	firstNode = lastNode = nullptr;
	dSize = 0;
}

template<class K, class E>
pairNode<K, E>* sortedChain2<K, E>::findPrev(const K& key) const {
	//if exists, return prev one; if not, return the one to insert after; if empty or smaller then first, return nullptr
	lastNode->element = { key, 0 };
	pairNode<K, E>* prev = firstNode;
	pairNode<K, E>* cur = firstNode->next;
	while (cur) {
		if (key <= cur->element.first)
			break;
		prev = cur;
		cur = cur->next;
	}
	return prev;
}

template<class K, class E>
std::pair<K, E>* sortedChain2<K, E>::find(const K& key) const {
	pairNode<K, E>* prev = findPrev(key);
	if (prev->next != lastNode && prev->next->element.first == key)
		return &prev->next->element;
	else
		return nullptr;
}

template<class K, class E>
void sortedChain2<K, E>::erase(const K& key) {
	pairNode<K, E>* prev = findPrev(key);
	if (prev->next != lastNode && prev->next->element.first == key) {
		pairNode<K, E>* toDel = prev->next;
		prev->next = toDel->next;
		delete toDel;
		--dSize;
	}
}

template<class K, class E>
void sortedChain2<K, E>::insert(const std::pair<K, E>& p) {
	pairNode<K, E>* prev = findPrev(p.first);
	if (prev->next != lastNode && prev->next->element.first == p.first) {
		prev->next->element.second = p.second;
	}
	else {
		pairNode<K, E>* newNode = new pairNode<K, E>(p);
		newNode->next = prev->next;
		prev->next = newNode;
		++dSize;
	}
}

#endif