#pragma once
#ifndef _HASHTABLE3_H
#define _HASHTABLE3_H
#include "dictionary.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <functional>
#include <random>
#include <iostream>
#include <ctime>
#include <cstdio>

//Exercise 28, Quadratic Probing
class TestHashTable3;
template<class K, class E>
class HashTable3 : public dictionary<K, E> {
	friend class TestHashTable3;
public:
	HashTable3(int theDivisor);
	virtual ~HashTable3() { delete[] table; }
	virtual bool empty() const override { return dSize == 0; }
	virtual int size() const override { return dSize; }
	virtual std::pair<K, E>* find(const K& key) const override;
	virtual void erase(const K& key) override;
	virtual void insert(const std::pair<K, E>& p) override;
	virtual std::istream& input(std::istream& in);
	virtual std::ostream& output(std::ostream& out);

private:
	int search(const K& key) const;
	bool isEmptyOrEqual(int i, const K& Key) const;

	int dSize;
	std::pair<K, E>** table;
	std::hash<K> hash_key;
	int divisor;
};

template<class K, class E>
std::istream& operator>>(std::istream& in, HashTable3<K, E>& sal) { return sal.input(in); }

template<class K, class E>
std::ostream& operator<<(std::ostream& out, HashTable3<K, E>& sal) { return sal.output(out); }

template<class K, class E>
std::istream& HashTable3<K, E>::input(std::istream& in) {
	int key;
	E value;
	while (in >> key && in >> value) {
		insert(std::pair<int, int>(key, value));
	}
	return in;
}

template<class K, class E>
std::ostream& HashTable3<K, E>::output(std::ostream& out) {
	for (int i = 0; i < divisor; ++i) {
		if (table[i] != nullptr)
			out << table[i]->first << "," << table[i]->second << " ";
	}
	return out;
}

template<class K, class E>
HashTable3<K, E>::HashTable3(int theDivisor):divisor(theDivisor) {
	table = new std::pair<K, E> * [divisor];
	dSize = 0;
	for (int i = 0; i < divisor; ++i) {
		table[i] = nullptr;
	}
}

template<class K, class E>
bool HashTable3<K, E>::isEmptyOrEqual(int i, const K& key) const {
	return table[i] == nullptr || table[i]->first == key;
}

template<class K, class E>
int HashTable3<K, E>::search(const K& key) const {
	int i = (int)hash_key(key) % divisor;
	if (i < 0)
		i += divisor;

	if (isEmptyOrEqual(i, key))
		return i;
	
	int j = 1;
	do {
		int k = (i + j * j) % divisor;
		int l = (i - j * j) % divisor;
		if (l < 0)
			l += divisor;
		if (isEmptyOrEqual(k, key))
			return k;
		if (isEmptyOrEqual(l, key))
			return l;
		++j;
	} while (j < (divisor - 1)/2);
	return i;
}

template<class K, class E>
std::pair<K, E>* HashTable3<K, E>::find(const K& key) const {
	int b = search(key);

	if (table[b] == nullptr || table[b]->first != key)
		return nullptr;

	return table[b];
}

template<class K, class E>
void HashTable3<K, E>::erase(const K& key) {
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
//
//	int j = 1;
//	bool forward = true;
//	bool foundFirst = (i == hKey);
//
//	do {
//		int k;
//		if (forward) {
//			k = (hKey + j * j) % divisor;
//			forward = !forward;
//		}
//		else {
//			k = (hKey - j * j) % divisor;
//			 if (k < 0)
//				 k += divisor;
//			 forward = !forward;
//			 ++j;
//		}
//		if (!foundFirst && k == b)
//			foundFirst = true;
//
//		if (foundFirst && k != b) {
//			if (table[k] == nullptr) {
//				return;
//			}
//			int hNext = (int)hash_key(table[k]->first) % divisor;
//			if (hNext < 0)
//				hNext += divisor;
//			if (hNext == hKey) {
//				table[i] = table[k];
//				table[k] = nullptr;
//				i = k;
//			}
//		}
//	} while (j < (divisor - 1) / 2);
//
}

template<class K, class E>
void HashTable3<K, E>::insert(const std::pair<K, E>& p) {
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

class TestHashTable3 {
public:
	double calExpectedProbingUnsuccess(int bucket, int record) { double f = (double)record / bucket; return 1.0 / (1.0 - f); }
	double calExpectedProbingSuccess(int bucket, int record) { double f = (double)record / bucket; return -1.0 / f * std::log(1.0 - f); }

	double realProbingUnsuccess(const HashTable3<int, int>& ht, int* keys);
	double realProbingSuccess(const HashTable3<int, int>& ht, int* keys);

	void run(int loopTotal, int loopReal);
};

double TestHashTable3::realProbingUnsuccess(const HashTable3<int, int>& ht, int* keys) {
	int total = 0;
	for (int i = 0; i < ht.divisor; ++i) {
		int count = 0;

		int j = 1;
		int k = i;
		bool forward = true;
		do {
			++count;
			if (ht.table[k] == nullptr)
				break;

			if (forward) {
				k = (i + j * j) % ht.divisor;
				forward = !forward;
			}
			else {
				k = (i - j * j) % ht.divisor;
				if (k < 0)
					k += ht.divisor;
				forward = !forward;
				++j;
			}
		} while ((j < (ht.divisor - 1) / 2));
		total += count;
	}
	return (double)total / ht.divisor;
}

double TestHashTable3::realProbingSuccess(const HashTable3<int, int>& ht, int* keys) {
	int total = 0;
	for (int i = 0; i < ht.dSize; ++i) {
		int count = 0;
		int hKey = (int)ht.hash_key(keys[i]) % ht.divisor;
		if (hKey < 0)
			hKey += ht.divisor;
		int k = hKey;
		int j = 1;
		bool forward = true;
		do {
			++count;
			if (ht.table[k] == nullptr || ht.table[k]->first == keys[i])
				break;

			if (forward) {
				k = (hKey + j * j) % ht.divisor;
				forward = !forward;
			}
			else {
				k = (hKey - j * j) % ht.divisor;
				if (k < 0)
					k += ht.divisor;
				forward = !forward;
				++j;
			}
		} while ((j < (ht.divisor - 1) / 2));

		total += count;
	}
	return (double)total / ht.dSize;
}

void TestHashTable3::run(int loopTotal, int loopReal) {

	for (int i = 0; i < loopTotal; ++i) {
		//std::cin.ignore();
		std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));
		//std::default_random_engine e(std::random_device().entropy());
		std::uniform_int_distribution<int> u(23, 32765);
		//std::uniform_int_distribution<int> u(1, 5);
		int divisor = u(e);
		if (divisor < 0)
			divisor = -divisor;
		if (divisor % 2 == 0)
			divisor += 1;

		int record = u(e) % divisor;
		if (record < 0)
			record = -record;

		std::cout << "Bucket number: " << divisor << "; Record number: " << record << std::endl;
		std::cout << "\tUnsuccess\tSuccess" << std::endl;
		std::cout << "Calculated Unsuccess/Success Expected Quadratic Probling" << std::endl;;
		printf("\t%8.3f\t%8.3f\n", calExpectedProbingUnsuccess(divisor, record), calExpectedProbingSuccess(divisor, record));
		std::cout << std::endl;
		std::cout << "Real" << std::endl;
		for (int j = 0; j < loopReal; ++j) {
			int* keys = new int[record];
			HashTable3<int, int> ht(divisor);
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