#pragma once
#ifndef _SORTEDCHAIN_H
#define _SORTEDCHAIN_H
#include "dictionary.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include "pairNode.h"

//Exercise 39
template<class K, class E> class HashChain;
template<class K, class E>
class sortedChain : public dictionary<K, E> {
	template<class K, class E>
	friend class HashChain;
public:
	sortedChain() :dSize(0), firstNode(nullptr) {}
	virtual ~sortedChain() { clear(); }
	virtual bool empty() const override { return dSize == 0; }
	virtual int size() const override { return dSize; }
	virtual std::pair<K, E>* find(const K& key) const override;
	virtual void erase(const K& key) override;
	virtual void insert(const std::pair<K, E>& p) override;
	virtual std::istream& input(std::istream& in);
	virtual std::ostream& output(std::ostream& out);

	//Exercise 39
	pairNode<K, E>* eraseNode(const K& key);
	void insertNode(pairNode<K, E>* p);

protected:
	pairNode<K, E>* findPrev(const K& key) const;
	void clear();

	int dSize;
	pairNode<K, E>* firstNode;
};

template<class K, class E>
std::istream& operator>>(std::istream& in, sortedChain<K, E>& sal) { return sal.input(in); }

template<class K, class E>
std::ostream& operator<<(std::ostream& out, sortedChain<K, E>& sal) { return sal.output(out); }

template<class K, class E>
std::istream& sortedChain<K, E>::input(std::istream& in) {
	K key;
	E value;
	while (in >> key && in >> value) {
		insert({ key, value });
	}
	return in;
}

template<class K, class E>
std::ostream& sortedChain<K, E>::output(std::ostream& out) {
	pairNode<K, E>* cur = firstNode;
	while (cur) {
		out << cur->element.first << "," << cur->element.second << " ";
		cur = cur->next;
	}
	return out;
}

template<class K, class E>
void sortedChain<K, E>::clear() {
	while (firstNode != nullptr) {
		pairNode<K, E>* next = firstNode->next;
		delete firstNode;
		firstNode = next;
	}
	firstNode = nullptr;
}

template<class K, class E>
pairNode<K, E>* sortedChain<K, E>::findPrev(const K& key) const {
	//if exists, return prev one; if not, return the one to insert after; if empty or smaller then first, return nullptr
	if (size() == 0)
		return nullptr;

	if (key <= firstNode->element.first)
		return nullptr;

	if (size() == 1)
		return firstNode;

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
std::pair<K, E>* sortedChain<K, E>::find(const K& key) const {
	if (size() == 0)
		return nullptr;

	pairNode<K, E>* prev = findPrev(key);
	if (prev == nullptr && firstNode != nullptr && firstNode->element.first == key)
		return &firstNode->element;
	else if( prev != nullptr && prev->next != nullptr && prev->next->element.first == key)
		return &prev->next->element;
	else
		return nullptr;
}

template<class K, class E>
void sortedChain<K, E>::erase(const K& key) {
	if (size() == 0)
		return;

	pairNode<K, E>* prev = findPrev(key);
	if (prev == nullptr && firstNode->element.first != key
		|| prev != nullptr && prev->next == nullptr
		|| prev != nullptr && prev->next !=nullptr && prev->next->element.first != key)
		return;

	if (prev == nullptr) {
		pairNode<K, E>* toDel = firstNode;
		firstNode = firstNode->next;
		delete toDel;
	}
	else {
		pairNode<K, E>* toDel = prev->next;
		prev->next = toDel->next;
		delete toDel;
	}
	--dSize;
}

template<class K, class E>
void sortedChain<K, E>::insert(const std::pair<K, E>& p) {
	pairNode<K, E>* prev = findPrev(p.first);
	if (prev == nullptr && firstNode != nullptr && firstNode->element.first == p.first) {
		firstNode->element.second = p.second;
	}
	else if (prev != nullptr && prev->next !=nullptr && prev->next->element.first == p.first)
		prev->next->element.second = p.second;
	else {
		pairNode<K, E>* newNode = new pairNode<K, E>(p);
		if (prev == nullptr) {
			newNode->next = firstNode;
			firstNode = newNode;
		}
		else {
			newNode->next = prev->next;
			prev->next = newNode;
		}
		++dSize;
	}
}

//Exercise 39
template<class K, class E>
pairNode<K, E>* sortedChain<K, E>::eraseNode(const K& key) {
	if (size() == 0)
		return nullptr;

	pairNode<K, E>* prev = findPrev(key);
	if (prev == nullptr && firstNode->element.first != key
		|| prev != nullptr && prev->next == nullptr
		|| prev != nullptr && prev->next != nullptr && prev->next->element.first != key)
		return nullptr;

	if (prev == nullptr) {
		pairNode<K, E>* toDel = firstNode;
		firstNode = firstNode->next;
		--dSize;
		return toDel;
	}
	else {
		pairNode<K, E>* toDel = prev->next;
		prev->next = toDel->next;
		--dSize;
		return toDel;
	}
}

template<class K, class E>
void sortedChain<K, E>::insertNode(pairNode<K, E>* p) {
	pairNode<K, E>* prev = findPrev(p->element.first);
	if (prev == nullptr && firstNode != nullptr && firstNode->element.first == p->element.first) {
		pairNode<K, E>* toDel = firstNode;
		p->next = firstNode->next;
		firstNode = p;
		delete toDel;
	}
	else if (prev != nullptr && prev->next != nullptr && prev->next->element.first == p->element.first) {
		pairNode<K, E>* toDel = prev->next;
		p->next = prev->next->next;
		prev->next = p;
		delete toDel;
	}
	else {
		if (prev == nullptr) {
			p->next = firstNode;
			firstNode = p;
		}
		else {
			p->next = prev->next;
			prev->next = p;
		}
		++dSize;
	}
}


#endif