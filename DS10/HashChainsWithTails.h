#pragma once
#ifndef _HASHCHAINSWITHTAILS_H
#define _HASHCHAINSWITHTAILS_H
#include "dictionary.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <functional>
#include <random>
#include <iostream>
#include <ctime>
#include <cstdio>
#include "sortedChainWithTail.h"

//Exercise 35

template<class K, class E>
class HashChainsWithTails : public dictionary<K, E> {
public:
	HashChainsWithTails(int theDivisor);
	virtual ~HashChainsWithTails() { delete[] table; }
	virtual bool empty() const override { return dSize == 0; }
	virtual int size() const override { return dSize; }
	virtual std::pair<K, E>* find(const K& key) const override;
	virtual void erase(const K& key) override;
	virtual void insert(const std::pair<K, E>& p) override;
	virtual std::istream& input(std::istream& in);
	virtual std::ostream& output(std::ostream& out);

private:
	int dSize;
	sortedChainWithTail<K, E>* table;
	std::hash<K> hash_key;
	int divisor;

};

template<class K, class E>
std::istream& operator>>(std::istream& in, HashChainsWithTails<K, E>& sal) { return sal.input(in); }

template<class K, class E>
std::ostream& operator<<(std::ostream& out, HashChainsWithTails<K, E>& sal) { return sal.output(out); }

template<class K, class E>
std::istream& HashChainsWithTails<K, E>::input(std::istream& in) {
	int key;
	E value;
	while (in >> key && in >> value) {
		insert(std::pair<int, int>(key, value));
	}
	return in;
}

template<class K, class E>
std::ostream& HashChainsWithTails<K, E>::output(std::ostream& out) {
	for (int i = 0; i < divisor; ++i) {
		out << table[i];
	}
	return out;
}

template<class K, class E>
HashChainsWithTails<K, E>::HashChainsWithTails(int theDivisor) :divisor(theDivisor) {
	table = new sortedChainWithTail<K, E>[divisor];
	dSize = 0;
}

template<class K, class E>
std::pair<K, E>* HashChainsWithTails<K, E>::find(const K& key) const {
	int index = (int)hash_key(key) % divisor;
	if (index < 0)
		index += divisor;
	return table[index].find(key);
}

template<class K, class E>
void HashChainsWithTails<K, E>::erase(const K& key) {
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
void HashChainsWithTails<K, E>::insert(const std::pair<K, E>& p) {
	int index = (int)hash_key(p.first) % divisor;
	if (index < 0)
		index += divisor;
	int sz = table[index].size();
	table[index].insert(p);
	if (table[index].size() > sz) {
		++dSize;
	}
}

#endif