#pragma once
#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include "dictionary.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <functional>
#include <random>
#include <iostream>
#include <ctime>
#include <cstdio>

//Exercise 20
class TestHashTable;

//Exercise 10
template<class K, class E>
class HashTable : public dictionary<K, E> {
	friend class TestHashTable;
public:
	HashTable(int theDivisor, bool isRandomProbing = false, double theLoadFactor = -1.0);
	virtual ~HashTable() { delete[] table; }
	virtual bool empty() const override { return dSize == 0; }
	virtual int size() const override { return dSize; }
	virtual std::pair<K, E>* find(const K& key) const override;
	virtual void erase(const K& key) override;
	virtual void insert(const std::pair<K, E>& p) override;
	virtual std::istream& input(std::istream& in);
	virtual std::ostream& output(std::ostream& out);

private:
	int search(const K& key) const;
	void shuffleAdder();

	int dSize;
	std::pair<K, E>** table;
	std::hash<K> hash_key;
	int divisor;
	//for random probing
	int* adder;
	bool randomProbing;
	//Exercise 25
	double loadFactor;
};

template<class K, class E>
std::istream& operator>>(std::istream& in, HashTable<K, E>& sal) { return sal.input(in); }

template<class K, class E>
std::ostream& operator<<(std::ostream& out, HashTable<K, E>& sal) { return sal.output(out); }

template<class K, class E>
std::istream& HashTable<K, E>::input(std::istream& in) {
	int key;
	E value;
	while (in >> key && in >> value) {
		insert(std::pair<int, int>(key, value));
	}
	return in;
}

template<class K, class E>
std::ostream& HashTable<K, E>::output(std::ostream& out) {
	for (int i = 0; i < divisor; ++i) {
		if (table[i] != nullptr)
			out << table[i]->first << "," << table[i]->second << " ";
	}
	return out;
}

template<class K, class E>
HashTable<K, E>::HashTable(int theDivisor, bool isRandomProbing, double theLoadFactor)
	:divisor(theDivisor), randomProbing(isRandomProbing), loadFactor(theLoadFactor){
	table = new std::pair<K, E> * [divisor];
	dSize = 0;
	for (int i = 0; i < divisor; ++i) {
		table[i] = nullptr;
	}

	if (randomProbing) {
		adder = new int[divisor];
		for (int i = 0; i < divisor; ++i)
			adder[i] = i;

		shuffleAdder();
	}
}

template<class K, class E>
void HashTable<K, E>::shuffleAdder() {
	std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));
	std::uniform_int_distribution<int> u(1, divisor - 1);
	for (int i = 1; i < divisor; ++i)
		std::swap(adder[i], adder[u(e)]);

	//std::copy(adder, adder + divisor, std::ostream_iterator<int>(std::cout, " "));
	//std::cout << std::endl;
	//searchRandom(1);
}

template<class K, class E>
int HashTable<K, E>::search(const K& key) const {
	int i = (int)hash_key(key) % divisor;
	if (i < 0)
		i += divisor;
	int j = i;
	int k = 1;
	do{
		if (table[j] == nullptr || table[j]->first == key) {
			return j;
		}
		if (randomProbing) {
			j = (i + adder[k]) % divisor;
			++k;
		}
		else {
			j = (j + 1) % divisor;
		}
		//std::cout << j << " ";
	}while(k < divisor);
	//std::cout << std::endl;
	return j;
}

template<class K, class E>
std::pair<K, E>* HashTable<K, E>::find(const K& key) const {
	int b = search(key);

	if (table[b] == nullptr || table[b]->first != key)
		return nullptr;

	return table[b];
}
//Exercise 26
template<class K, class E>
void HashTable<K, E>::erase(const K& key) {
	int b = search(key);
	//std::cout << "1\n";
	if (table[b] == nullptr || table[b]->first != key)
		return;

	delete table[b];
	table[b] = nullptr;
	--dSize;

	//move the pair after pos 'b', if hash(p.first) equals hash(key)
	int hKey = (int)hash_key(key) % divisor; //for comparation
	if (hKey < 0)
		hKey += divisor;
	int i = b; //to record the dest to copy to, current is nullptr
	int j = i+1; //for loop
	if (randomProbing) {
		j = (i + adder[1]) % divisor;
	}
	int k = 1;
	//std::cout << "2\n";
	do {
		if (table[j] == nullptr) {
			return;
		}
		//std::cout << "3\n";
		//std::cout << table[j] << "\n";
		int hNext = (int)hash_key(table[j]->first) % divisor;
		//std::cout << "4\n";
		if (hNext < 0)
			hNext += divisor;
		if (hNext == hKey) {
			table[i] = table[j];
			table[j] = nullptr;
			i = j;
		}
		
		if (randomProbing) {
			j = (i + adder[k]) % divisor;
			++k;
		}
		else {
			j = (j + 1) % divisor;
		}
		//std::cout << "5\n";
	} while (k < divisor);
	
}

template<class K, class E>
void HashTable<K, E>::insert(const std::pair<K, E>& p) {
	int b = search(p.first);

	if (table[b] == nullptr) {
		table[b] = new std::pair<K, E>(p);
		++dSize;
	}
	else {
		if (table[b]->first == p.first) {
			table[b]->second = p.second;
		}
		else {
			throw std::invalid_argument("hash table is full");
		}
	}
	//Exercise 25
	if (loadFactor >= 0.0 && loadFactor < (double)dSize / divisor) {
		int olddivisor = divisor;
		divisor = divisor * 2 + 1;
		std::pair<K, E>** oldTable = table;
		table = new std::pair<K, E> * [divisor];
		for (int i = 0; i < divisor; ++i)
			table[i] = nullptr;
		int oldSize = dSize;
		dSize = 0;

		for (int i = 0; i < olddivisor; ++i) {
			if (oldTable[i] != nullptr) {
				insert(*oldTable[i]);
			}
		}

		delete[] oldTable;
	}
}

//////////////////////////////////////////////////////////////////////

class TestHashTable {
public:
	double calLinearProbingUnsuccess(int bucket, int record) { double f = (double)record / bucket; return 0.5 * (1.0 + 1.0 / (1.0 - f)/(1.0 -f)); }
	double calLinearProbingSuccess(int bucket, int record) { double f = (double)record / bucket; return 0.5 * (1.0 + 1.0 / (1.0 - f)); }
	double calRandomProbingUnsuccess(int bucket, int record) { double f = (double)record / bucket; return 1.0 / (1.0 - f); }
	double calRandomProbingSuccess(int bucket, int record) { double f = (double)record / bucket; return -1.0 / f * std::log (1.0 - f); }

	double realProbingUnsuccess(const HashTable<int, int>& ht, int* keys);
	double realProbingSuccess(const HashTable<int, int>& ht, int* keys);

	void run(int loopTotal, int loopReal);
	//Exercise 22
	void listValues();
};

#endif