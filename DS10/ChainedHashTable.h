#pragma once
#ifndef _CHAINEDHASHTABLE_H
#define _CHAINEDHASHTABLE_H
#include "dictionary.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include "pairNode.h"
//Exercise 36
template<class K, class E>
class ChainedHashTable : public dictionary<K, E> {
public:
	ChainedHashTable(int theDivisor);
	virtual ~ChainedHashTable() { clear(); }
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
	pairNode<K, E>** firstNodes;
	std::hash<K> hash_key;
	int divisor;
};

template<class K, class E>
std::istream& operator>>(std::istream& in, ChainedHashTable<K, E>& sal) { return sal.input(in); }

template<class K, class E>
std::ostream& operator<<(std::ostream& out, ChainedHashTable<K, E>& sal) { return sal.output(out); }

template<class K, class E>
std::istream& ChainedHashTable<K, E>::input(std::istream& in) {
	K key;
	E value;
	while (in >> key && in >> value) {
		insert({ key, value });
	}
	return in;
}

template<class K, class E>
std::ostream& ChainedHashTable<K, E>::output(std::ostream& out) {
	for (int i = 0; i < divisor; ++i) {
		pairNode<K, E>* cur = firstNodes[i];
		while (cur != nullptr) {
			out << cur->element.first << "," << cur->element.second << " ";
			cur = cur->next;
		}
	}
	return out;
}

template<class K, class E>
ChainedHashTable<K, E>::ChainedHashTable(int theDivisor) :divisor(theDivisor), dSize(0) {
	firstNodes = new pairNode<K, E>*[divisor];
	for (int i = 0; i < divisor; ++i) {
		firstNodes[i] = nullptr;
	}
}

template<class K, class E>
void ChainedHashTable<K, E>::clear() {
	for (int i = 0; i < divisor; ++i) {
		pairNode<K, E>* cur = firstNodes[i];
		while (cur != nullptr) {
			pairNode<K, E>* next = cur->next;
			delete cur;
			cur = next;
		}
	}
	delete[] firstNodes;
	firstNodes = nullptr;
	dSize = 0;
}

template<class K, class E>
pairNode<K, E>* ChainedHashTable<K, E>::findPrev(const K& key) const {
	//if exists, return prev one; if not, return the one to insert after; if empty or smaller then first, return nullptr
	int i = (int)hash_key(key) % divisor;
	if (i < 0)
		i += divisor;

	pairNode<K, E>* prev = nullptr;
	pairNode<K, E>* cur = firstNodes[i];
	while (cur) {
		if (key <= cur->element.first)
			break;
		prev = cur;
		cur = cur->next;
	}
	return prev;
}

template<class K, class E>
std::pair<K, E>* ChainedHashTable<K, E>::find(const K& key) const {
	int i = (int)hash_key(key) % divisor;
	if (i < 0)
		i += divisor;

	if (firstNodes[i] == nullptr)
		return  nullptr;

	pairNode<K, E>* prev = findPrev(key);
	if (prev == nullptr && firstNodes[i]->element.first == key)
		return &firstNodes[i]->element;
	else if (prev->next != nullptr && prev->next->element.first == key)
		return &prev->next->element;
	else
		return nullptr;
}

template<class K, class E>
void ChainedHashTable<K, E>::erase(const K& key) {
	int i = (int)hash_key(key) % divisor;
	if (i < 0)
		i += divisor;

	if (firstNodes[i] == nullptr)
		return;

	pairNode<K, E>* prev = findPrev(key);
	if (prev == nullptr && firstNodes[i]->element.first == key) {
		pairNode<K, E>* toDel = firstNodes[i];
		firstNodes[i] = toDel->next;
		delete toDel;
		--dSize;
	}else if (prev->next != nullptr && prev->next->element.first == key) {
		pairNode<K, E>* toDel = prev->next;
		prev->next = toDel->next;
		delete toDel;
		--dSize;
	}
}

template<class K, class E>
void ChainedHashTable<K, E>::insert(const std::pair<K, E>& p) {
	int i = (int)hash_key(p.first) % divisor;
	if (i < 0)
		i += divisor;

	pairNode<K, E>* prev = findPrev(p.first);
	if (prev == nullptr && firstNodes[i] != nullptr && firstNodes[i]->element.first == p.first) {
		firstNodes[i]->element.second = p.second;
	}else if (prev == nullptr && (firstNodes[i] == nullptr || firstNodes[i]->element.first != p.first)) {
		pairNode<K, E>* newNode = new pairNode<K, E>(p);
		newNode->next = firstNodes[i];
		firstNodes[i] = newNode;
		++dSize;
	}else if (prev->next != nullptr && prev->next->element.first == p.first) {
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