#pragma once
#ifndef _HASHTABLE2_H
#define _HASHTABLE2_H
#include "dictionary.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <functional>
#include <random>
#include <iostream>
#include <ctime>
#include <cstdio>
//Exercise 27

template<class K, class E>
struct bucket {
	std::pair<K, E>* pair;
	bool neverUsed;

	bucket() : pair(nullptr), neverUsed(true){}
	explicit bucket(const std::pair<K, E>& p) :pair(&p), neverUsed(false) {}
	bucket<K, E>& operator=(const bucket<K, E>& b) { pair = b.pair; neverUsed = b.neverUsed; return *this; }
};

template<class K, class E>
class HashTable2 : public dictionary<K, E> {
public:
	HashTable2(int theDivisor);
	virtual ~HashTable2() { delete[] table; }
	virtual bool empty() const override { return dSize == 0; }
	virtual int size() const override { return dSize; }
	virtual std::pair<K, E>* find(const K& key) const override;
	virtual void erase(const K& key) override;
	virtual void insert(const std::pair<K, E>& p) override;
	virtual std::istream& input(std::istream& in);
	virtual std::ostream& output(std::ostream& out);

private:
	int search(const K& key) const;

	int dSize;
	bucket<K,E>* table;
	std::hash<K> hash_key;
	int divisor;
	int usedEmpty;
};

template<class K, class E>
std::istream& operator>>(std::istream& in, HashTable2<K, E>& sal) { return sal.input(in); }

template<class K, class E>
std::ostream& operator<<(std::ostream& out, HashTable2<K, E>& sal) { return sal.output(out); }

template<class K, class E>
std::istream& HashTable2<K, E>::input(std::istream& in) {
	int key;
	E value;
	while (in >> key && in >> value) {
		insert(std::pair<int, int>(key, value));
	}
	return in;
}

template<class K, class E>
std::ostream& HashTable2<K, E>::output(std::ostream& out) {
	for (int i = 0; i < divisor; ++i) {
		if (table[i].pair != nullptr)
			out << table[i].pair->first << "," << table[i].pair->second << " ";
	}
	return out;
}

template<class K, class E>
HashTable2<K, E>::HashTable2(int theDivisor):divisor(theDivisor) {
	table = new bucket<K,E>[divisor];
	dSize = 0;
	usedEmpty = 0;
	//for (int i = 0; i < divisor; ++i) {
	//	table[i] = nullptr;
	//}
}

template<class K, class E>
int HashTable2<K, E>::search(const K& key) const {
	int i = (int)hash_key(key) % divisor;
	if (i < 0)
		i += divisor;
	int j = i;
	do {
		if (table[j].neverUsed == true ||
			table[j].pair != nullptr && table[j].pair->first == key){
			return j;
		}

		j = (j + 1) % divisor;
	} while (j != i);
	return j;
}

template<class K, class E>
std::pair<K, E>* HashTable2<K, E>::find(const K& key) const {
	int b = search(key);

	if (table[b].pair == nullptr || table[b].pair->first != key)
		return nullptr;

	return table[b].pair;
}

template<class K, class E>
void HashTable2<K, E>::erase(const K& key) {
	int b = search(key);

	if (table[b].pair == nullptr || table[b].pair->first != key)
		return;

	delete table[b].pair;
	table[b].pair = nullptr;
	--dSize;
	++usedEmpty;

	if ((float)usedEmpty / (divisor - dSize) > 0.6) {
		for (int i = 0; i < divisor; ++i) {
			if (table[i].neverUsed == true || table[i].pair != nullptr)
				continue;

			//table[i].pair == nullptr && table[i].neverUsed == false
			int k = i;
			int j = (i + 1) % divisor;
			for (; j != i; j = (j + 1) % divisor) {
				if (table[j].neverUsed == true)
					break;
				if (table[j].pair == nullptr)
					continue;

				int hNext = (int)hash_key(table[j].pair->first) % divisor;
				if (hNext < 0)
					hNext += divisor;
				if (hNext == i) {
					table[k] = table[j];
					table[j].pair = nullptr;
					k = j;
				}		
			}
			if (table[k].pair == nullptr) {
				table[k].neverUsed = true;
			}
		}
		usedEmpty = 0;
	}
}

template<class K, class E>
void HashTable2<K, E>::insert(const std::pair<K, E>& p) {
	int b = search(p.first);

	if (table[b].pair == nullptr) {
		table[b].pair = new std::pair<K, E>(p);
		++dSize;
		if (table[b].neverUsed) {
			table[b].neverUsed = false;
		}
	}
	else {
		if (table[b].pair->first == p.first) {
			table[b].pair->second = p.second;
		}
		else {
			throw std::invalid_argument("hash table is full");
		}
	}
}


#endif