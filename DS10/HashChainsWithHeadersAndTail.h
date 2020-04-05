#pragma once
#ifndef _HASHCHAINSWITHHEADERSANDTAIL_H
#define _HASHCHAINSWITHHEADERSANDTAIL_H
#include "dictionary.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include "pairNode.h"
//Exercise 36
template<class K, class E>
class HashChainsWithHeadersAndTail : public dictionary<K, E> {
public:
	HashChainsWithHeadersAndTail(int theDivisor);
	virtual ~HashChainsWithHeadersAndTail() { clear(); }
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
	pairNode<K, E>* firstNodes;
	pairNode<K, E>* lastNodes;
	std::hash<K> hash_key;
	int divisor;
};

template<class K, class E>
std::istream& operator>>(std::istream& in, HashChainsWithHeadersAndTail<K, E>& sal) { return sal.input(in); }

template<class K, class E>
std::ostream& operator<<(std::ostream& out, HashChainsWithHeadersAndTail<K, E>& sal) { return sal.output(out); }

template<class K, class E>
std::istream& HashChainsWithHeadersAndTail<K, E>::input(std::istream& in) {
	K key;
	E value;
	while (in >> key && in >> value) {
		insert({ key, value });
	}
	return in;
}

template<class K, class E>
std::ostream& HashChainsWithHeadersAndTail<K, E>::output(std::ostream& out) {
	for (int i = 0; i < divisor; ++i) {
		pairNode<K, E>* cur = firstNodes[i].next;
		while (cur != &lastNodes[i]) {
			out << cur->element.first << "," << cur->element.second << " ";
			cur = cur->next;
		}
	}
	return out;
}

template<class K, class E>
HashChainsWithHeadersAndTail<K, E>::HashChainsWithHeadersAndTail(int theDivisor) :divisor(theDivisor), dSize(0) {
	firstNodes = new pairNode<K, E>[divisor];
	lastNodes = new pairNode<K, E>[divisor];
	for (int i = 0; i < divisor; ++i) {
		firstNodes[i].next = &lastNodes[i];
		lastNodes[i].next = nullptr;
	}
}

template<class K, class E>
void HashChainsWithHeadersAndTail<K, E>::clear() {
	for (int i = 0; i < divisor; ++i) {
		pairNode<K, E>* cur = firstNodes[i].next;
		while (cur != &lastNodes[i]) {
			pairNode<K, E>* next = cur->next;
			delete cur;
			cur = next;
		}
	}
	delete[] firstNodes;
	delete[] lastNodes;
	firstNodes = nullptr;
	lastNodes = nullptr;
	dSize = 0;
}

template<class K, class E>
pairNode<K, E>* HashChainsWithHeadersAndTail<K, E>::findPrev(const K& key) const {
	//if exists, return prev one; if not, return the one to insert after; if empty or smaller then first, return nullptr
	int i = (int)hash_key(key) % divisor;
	if (i < 0)
		i += divisor;

	lastNodes[i].element = std::make_pair(key, 0);
	pairNode<K, E>* prev = &firstNodes[i];
	pairNode<K, E>* cur = firstNodes[i].next;
	while (cur) {
		if (key <= cur->element.first)
			break;
		prev = cur;
		cur = cur->next;
	}
	return prev;
}

template<class K, class E>
std::pair<K, E>* HashChainsWithHeadersAndTail<K, E>::find(const K& key) const {
	int i = (int)hash_key(key) % divisor;
	if (i < 0)
		i += divisor;

	pairNode<K, E>* prev = findPrev(key);
	if (prev->next != &lastNodes[i] && prev->next->element.first == key)
		return &prev->next->element;
	else
		return nullptr;
}

template<class K, class E>
void HashChainsWithHeadersAndTail<K, E>::erase(const K& key) {
	int i = (int)hash_key(key) % divisor;
	if (i < 0)
		i += divisor;

	pairNode<K, E>* prev = findPrev(key);
	if (prev->next != &lastNodes[i] && prev->next->element.first == key) {
		pairNode<K, E>* toDel = prev->next;
		prev->next = toDel->next;
		delete toDel;
		--dSize;
	}
}

template<class K, class E>
void HashChainsWithHeadersAndTail<K, E>::insert(const std::pair<K, E>& p) {
	int i = (int)hash_key(p.first) % divisor;
	if (i < 0)
		i += divisor;

	pairNode<K, E>* prev = findPrev(p.first);
	if (prev->next != &lastNodes[i] && prev->next->element.first == p.first) {
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