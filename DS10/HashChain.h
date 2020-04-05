#pragma once
#ifndef _HASHCHAIN_H
#define _HASHCHAIN_H
#include "dictionary.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <functional>
#include <random>
#include <iostream>
#include <ctime>
#include <cstdio>
#include "sortedChain.h"
#include <set>

//Exercise 32
class TestHashChain;

template<class K, class E>
class HashChain : public dictionary<K, E> {
	friend class TestHashChain;
public:
	HashChain(int theDivisor, double theLoadFactor = -1.0) :divisor(theDivisor), loadFactor(theLoadFactor) { init(); }
	virtual ~HashChain() { clear(); }
	virtual bool empty() const override { return dSize == 0; }
	virtual int size() const override { return dSize; }
	virtual std::pair<K, E>* find(const K& key) const override;
	virtual void erase(const K& key) override;
	virtual void insert(const std::pair<K, E>& p) override;
	virtual std::istream& input(std::istream& in);
	virtual std::ostream& output(std::ostream& out);
	void reset() { clear(); init(); }

	std::set<K> getKeys();
public:
	class iterator;
	friend class iterator;
	iterator begin() { 
		int index = 0;
		while (table[index].firstNode == nullptr && index < divisor)
			++index;

		if (index == divisor)
			return iterator(this, nullptr);

		return iterator(this, table[index].firstNode);
	}
	iterator end() { return iterator(this, nullptr); }
private:
	void init();
	void clear();
	int dSize;
	sortedChain<K, E>* table;
	std::hash<K> hash_key;
	int divisor;
	//Exercise 39
	double loadFactor;
};

template<class K, class E>
class HashChain<K, E>::iterator {
public:
	//typedef forward_iterator_tag iterator_capacity;
	typedef std::pair<K, E> value_type;
	typedef ptrdiff_t difference_type;
	typedef std::pair<K, E>* pointer;
	typedef std::pair<K, E>& reference;

	iterator(HashChain<K, E>* phc, pairNode<K, E>* theNode = nullptr) { hc = phc; node = theNode; }

	std::pair<K,E>& operator*() const { return node->element; }
	std::pair<K, E>* operator->() const { return &node->element; }

	iterator& operator++() { node = findNext(node); return *this; }
	iterator operator++(int) { iterator old = *this; node = findNext(node); return old; }

	bool operator!=(const iterator right) const { return node != right.node; }
	bool operator==(const iterator right) const { return node == right.node; }

private:
	pairNode<K, E>* findNext(const pairNode<K, E>* node) {
		if (node->next != nullptr)
			return node->next;

		int index = (int)hc->hash_key(node->element.first) % hc->divisor;
		if (index < 0)
			index += hc->divisor;
		++index;
		while (hc->table[index].firstNode == nullptr && index < hc->divisor)
			++index;

		if (index == hc->divisor)
			return nullptr;

		return hc->table[index].firstNode;

	}

	pairNode<K, E>* node;
	HashChain<K, E>* hc;
};



template<class K, class E>
std::istream& operator>>(std::istream& in, HashChain<K, E>& sal) { return sal.input(in); }

template<class K, class E>
std::ostream& operator<<(std::ostream& out, HashChain<K, E>& sal) { return sal.output(out); }

template<class K, class E>
std::istream& HashChain<K, E>::input(std::istream& in) {
	K key;
	E value;
	while (in >> key && in >> value) {
		std::pair<K, E> p( key, value );
		insert(p);
	}
	return in;
}

template<class K, class E>
std::ostream& HashChain<K, E>::output(std::ostream& out) {
	for (int i = 0; i < divisor; ++i) {
		out << table[i];
	}
	return out;
}

template<class K, class E>
void HashChain<K, E>::init() {
	table = new sortedChain<K, E>[divisor];
	dSize = 0;
}

template<class K, class E>
void HashChain<K, E>::clear() {
	delete[] table;
}

template<class K, class E>
std::pair<K, E>* HashChain<K, E>::find(const K& key) const {
	int index = (int)hash_key(key) % divisor;
	if (index < 0)
		index += divisor;
	return table[index].find(key);
}

template<class K, class E>
void HashChain<K, E>::erase(const K& key) {
	int index = (int)hash_key(key) % divisor;
	if (index < 0)
		index += divisor;
	int sz = table[index].size();
	table[index].erase(key);
	if (table[index].size() < sz) {
		--dSize;
	}	
}

template<class K, class E>
void HashChain<K, E>::insert(const std::pair<K, E>& p) {
	int index = (int)hash_key(p.first) % divisor;
	if (index < 0)
		index += divisor;
	int sz = table[index].size();
	table[index].insert(p);
	if (table[index].size() > sz) {
		++dSize;
	}

	//Exercise 39
	if (loadFactor >= 0.0 && loadFactor < (double)dSize / divisor) {
		int newdivisor = divisor * 2 + 1;
		sortedChain<K, E>* newTable = new sortedChain<K, E>[newdivisor];

		for (int i = 0; i < divisor; ++i) {
			pairNode<K, E>* cur = table[i].firstNode;
			while (cur != nullptr) {
				pairNode<K, E>* next = cur->next;
				int newkey = (int)hash_key(cur->element.first) % newdivisor;
				if (newkey < 0)
					newkey += newdivisor;

				newTable[newkey].insertNode(cur);
				cur = next;
			}
			table[i].dSize = 0;
			table[i].firstNode = nullptr;
		}

		divisor = newdivisor;
		delete[] table;
		table = newTable;
	}
}

template<class K, class E>
std::set<K> HashChain<K,E>::getKeys() {
	std::set<K> result;
	iterator iter = begin();
	while (iter != end()) {
		result.insert(iter->first);
		++iter;
	}
	return result;
}

#endif