#pragma once
#ifndef _HASHTABLE4_H
#define _HASHTABLE4_H
#include "dictionary.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <functional>
#include <random>
#include <iostream>
#include <ctime>
#include <cstdio>

//Exercise 29, Double Hashing
class TestHashTable4;
template<class K, class E>
class HashTable4 : public dictionary<K, E> {
	friend class TestHashTable4;
public:
	HashTable4(int theDivisor, int thePrime);
	virtual ~HashTable4() { delete[] table; }
	virtual bool empty() const override { return dSize == 0; }
	virtual int size() const override { return dSize; }
	virtual std::pair<K, E>* find(const K& key) const override;
	virtual void erase(const K& key) override;
	virtual void insert(const std::pair<K, E>& p) override;
	virtual std::istream& input(std::istream& in);
	virtual std::ostream& output(std::ostream& out);

private:
	int search(const K& key) const;
	int hash_key2(int k) const { return prime - (k % prime); }

	int dSize;
	std::pair<K, E>** table;
	std::hash<K> hash_key;
	int divisor;
	int prime;
};

template<class K, class E>
std::istream& operator>>(std::istream& in, HashTable4<K, E>& sal) { return sal.input(in); }

template<class K, class E>
std::ostream& operator<<(std::ostream& out, HashTable4<K, E>& sal) { return sal.output(out); }

template<class K, class E>
std::istream& HashTable4<K, E>::input(std::istream& in) {
	int key;
	E value;
	while (in >> key && in >> value) {
		insert(std::pair<int, int>(key, value));
	}
	return in;
}

template<class K, class E>
std::ostream& HashTable4<K, E>::output(std::ostream& out) {
	for (int i = 0; i < divisor; ++i) {
		if (table[i] != nullptr)
			out << table[i]->first << "," << table[i]->second << " ";
	}
	return out;
}

template<class K, class E>
HashTable4<K, E>::HashTable4(int theDivisor, int thePrime) :divisor(theDivisor), prime(thePrime) {
	table = new std::pair<K, E> * [divisor];
	dSize = 0;
	for (int i = 0; i < divisor; ++i) {
		table[i] = nullptr;
	}
}

template<class K, class E>
int HashTable4<K, E>::search(const K& key) const {
	int i = (int)hash_key(key) % divisor;
	if (i < 0)
		i += divisor;

	int j = i;
	int stride = hash_key2(i);
	int k = 1;
	do {
		if (table[j] == nullptr || table[j]->first == key) {
			return j;
		}
		j = (i + k * stride) % divisor;
		++k;
	} while (k < divisor);
	return i;
}

template<class K, class E>
std::pair<K, E>* HashTable4<K, E>::find(const K& key) const {
	int b = search(key);

	if (table[b] == nullptr || table[b]->first != key)
		return nullptr;

	return table[b];
}

template<class K, class E>
void HashTable4<K, E>::erase(const K& key) {
//	int b = search(key);
//
//	if (table[b] == nullptr || table[b]->first != key)
//		return;
//
//	delete table[b];
//	table[b] = nullptr;
//	--dSize;
//
//	//move the pair after pos 'b', if hash(p.first) equals hash(key)
//	int hKey = (int)hash_key(key) % divisor; //for comparation
//	if (hKey < 0)
//		hKey += divisor;
//	int i = b; //to record the dest to copy to, current is nullptr
//	int stride = hash_key2(i);
//	int j = (i + stride) % divisor; //for loop
//
//	int k = 2;
//	do {
//		if (table[j] == nullptr) {
//			return;
//		}
//
//		int hNext = (int)hash_key(table[j]->first) % divisor;
//		if (hNext < 0)
//			hNext += divisor;
//		if (hNext == hKey) {
//			table[i] = table[j];
//			table[j] = nullptr;
//			i = j;
//		}
//
//		j = (i + k * stride) % divisor;
//		++k;
//		} while (k < divisor);
//
}

template<class K, class E>
void HashTable4<K, E>::insert(const std::pair<K, E>& p) {
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
}

//////////////////////////////////////////////////////////////////////

class TestHashTable4 {
public:
	double calExpectedProbingUnsuccess(int bucket, int record) { double f = (double)record / bucket; return 1.0 / (1.0 - f); }
	double calExpectedProbingSuccess(int bucket, int record) { double f = (double)record / bucket; return -1.0 / f * std::log(1.0 - f); }

	double realProbingUnsuccess(const HashTable4<int, int>& ht, int* keys);
	double realProbingSuccess(const HashTable4<int, int>& ht, int* keys);

	void run(int loopTotal, int loopReal);
};

double TestHashTable4::realProbingUnsuccess(const HashTable4<int, int>& ht, int* keys) {
	int total = 0;
	for (int i = 0; i < ht.divisor; ++i) {
		int count = 0;
		int stride = ht.hash_key2(i);
		int j = (i + stride) % ht.divisor;
		int k = 2;
		do {
			++count;
			if (ht.table[j] == nullptr)
				break;

			j = (i + k * stride) % ht.divisor;
			++k;
		} while (k < ht.divisor);
		total += count;
	}
	return (double)total / ht.divisor;
}

double TestHashTable4::realProbingSuccess(const HashTable4<int, int>& ht, int* keys) {
	int total = 0;
	for (int i = 0; i < ht.dSize; ++i) {
		int count = 0;
		int hKey = (int)ht.hash_key(keys[i]) % ht.divisor;
		if (hKey < 0)
			hKey += ht.divisor;
		int stride = ht.hash_key2(hKey);
		int j = hKey;
		int k = 1;
		do {
			++count;
			if (ht.table[j] == nullptr || ht.table[j]->first == keys[i])
				break;

			j = (hKey + k * stride) % ht.divisor;
			++k;
		} while (k < ht.divisor);
		total += count;
	}
	return (double)total / ht.dSize;
}

void TestHashTable4::run(int loopTotal, int loopReal) {

	for (int i = 0; i < loopTotal; ++i) {
		//std::cin.ignore(); 
		std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));
		std::uniform_int_distribution<int> u(23, 32765);
		//std::uniform_int_distribution<int> u(1, 5);
		int divisor = u(e);
		if (divisor < 0)
			divisor = -divisor;
		if (divisor % 2 == 0)
			divisor += 1;
		int prime = u(e);
		if (prime < 0)
			prime = -prime;
		if (prime % 2 == 0)
			prime += 1;
		int record = u(e) % divisor;
		if (record < 0)
			record = -record;

		std::cout << "Bucket number: " << divisor << "; Record number: " << record << std::endl;
		std::cout << "Calculated Unsuccess/Success Expected Quadratic Probling" << std::endl;;
		printf("\t%8.3f\t%8.3f\n", calExpectedProbingUnsuccess(divisor, record), calExpectedProbingSuccess(divisor, record));
		std::cout << std::endl;
		std::cout << "\tUnsuccess\tSuccess" << std::endl;
		std::cout << "Real" << std::endl;
		for (int j = 0; j < loopReal; ++j) {
			int* keys = new int[record];
			HashTable4<int, int> ht(divisor, prime);
			for (int k = 0; k < record; ++k) {
				keys[k] = u(e) % divisor;
				if (keys[k] < 0)
					keys[k] = -keys[k];
				ht.insert({ keys[k], k });
			}
			printf("\t%8.3f\t%8.3f\n", realProbingUnsuccess(ht, keys), realProbingSuccess(ht, keys));
			delete keys;
		}
	}
}

#endif