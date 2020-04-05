#pragma once
#ifndef _HASHCHAINSWITHVECTOR_H
#define _HASHCHAINSWITHVECTOR_H
#include "dictionary.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <functional>
#include <random>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <list>
#include "sortedChain.h"

//Exercise 38
class TestHashChain;

template<class K, class E>
class HashChainsWithVector : public dictionary<K, E> {
	friend class TestHashChain;
public:
	HashChainsWithVector(int theDivisor);
	virtual ~HashChainsWithVector() { for (int i = 0; i < divisor; ++i) delete table[i]; }
	virtual bool empty() const override { return dSize == 0; }
	virtual int size() const override { return dSize; }
	virtual std::pair<K, E>* find(const K& key) const override;
	virtual void erase(const K& key) override;
	virtual void insert(const std::pair<K, E>& p) override;
	virtual std::istream& input(std::istream& in);
	virtual std::ostream& output(std::ostream& out);

private:
	int dSize;
	std::vector<sortedChain<K, E>*> table;
	std::hash<K> hash_key;
	int divisor;

};

template<class K, class E>
std::istream& operator>>(std::istream& in, HashChainsWithVector<K, E>& sal) { return sal.input(in); }

template<class K, class E>
std::ostream& operator<<(std::ostream& out, HashChainsWithVector<K, E>& sal) { return sal.output(out); }

template<class K, class E>
std::istream& HashChainsWithVector<K, E>::input(std::istream& in) {
	int key;
	E value;
	while (in >> key && in >> value) {
		insert(std::pair<int, int>(key, value));
	}
	return in;
}

template<class K, class E>
std::ostream& HashChainsWithVector<K, E>::output(std::ostream& out) {
	for (int i = 0; i < divisor; ++i) {
		out << *table[i];
	}
	return out;
}

template<class K, class E>
HashChainsWithVector<K, E>::HashChainsWithVector(int theDivisor) :divisor(theDivisor) {
	for (int i = 0; i < divisor; ++i) {
		table.push_back(new sortedChain<K, E>);
	}
	dSize = 0;
}

template<class K, class E>
std::pair<K, E>* HashChainsWithVector<K, E>::find(const K& key) const {
	int index = (int)hash_key(key) % divisor;
	if (index < 0)
		index += divisor;
	return table[index]->find(key);
}

template<class K, class E>
void HashChainsWithVector<K, E>::erase(const K& key) {
	int index = (int)hash_key(key) % divisor;
	if (index < 0)
		index += divisor;
	int sz = table[index]->size();
	table[index]->erase(key);
	if (table[index]->size() < sz) {
		--dSize;
	}
}

template<class K, class E>
void HashChainsWithVector<K, E>::insert(const std::pair<K, E>& p) {
	int index = (int)hash_key(p.first) % divisor;
	if (index < 0)
		index += divisor;
	int sz = table[index]->size();
	table[index]->insert(p);
	if (table[index]->size() > sz) {
		++dSize;
	}
}

#endif