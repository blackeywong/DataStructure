#pragma once
#ifndef _SORTEDARRAYLIST_H
#define _SORTEDARRAYLIST_H
#include "dictionary.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>

template<class K, class E>
class sortedArrayList: public dictionary<K, E>{
public:
	sortedArrayList(int initialCapacity = 10);
	virtual ~sortedArrayList() { delete[] list; }
	virtual bool empty() const override { return listSize == 0; }
	virtual int size() const override { return listSize; }
	virtual std::pair<K, E>* find(const K& key) const override;
	virtual void erase(const K& key) override;
	virtual void insert(const std::pair<K, E>& p) override;
	virtual std::istream& input(std::istream& in);
	virtual std::ostream& output(std::ostream& out) const;

protected:
	int findIndex(const K& key) const;

	int listSize;
	int arrayLength;
	std::pair<K, E>* list;
};

template<class K, class E>
std::istream& operator>>(std::istream& in, sortedArrayList<K, E>& sal) { return sal.input(in); }

template<class K, class E>
std::ostream& operator<<(std::ostream& out, sortedArrayList<K, E>& sal) { return sal.output(out); }

template<class K, class E>
std::istream& sortedArrayList<K, E>::input(std::istream& in) {
	K key;
	E value;
	while (in >> key && in >> value) {
		list[listSize++] = { key, value };
	}
	return in;
}

template<class K, class E>
std::ostream& sortedArrayList<K, E>::output(std::ostream& out) const{
	for (int i = 0; i < size(); ++i) {
		out << list[i].first << "," << list[i].second << " ";
	}
	return out;
}

template<class K, class E>
sortedArrayList<K,E>::sortedArrayList(int initialCapacity) {
	if (initialCapacity <= 0)
		throw std::invalid_argument("capcity should be > 0");

	list = new std::pair<K, E>[initialCapacity];
	listSize = 0;
	arrayLength = initialCapacity;
}

template<class K, class E>
int sortedArrayList<K, E>::findIndex(const K& key) const {
	//if key does not exist, index is the one just smaller than key
	if (size() == 0)
		return -1;

	int small = 0, large = size()-1;
	int index = 0;
	while (small <= large) {
		index = (small + large) / 2;
		if (list[index].first == key)
			return index;
		else if ((list[index].first < key))
			small = index+1;
		else
			large = index-1;
	}

	if (key < list[index].first)
		--index;
	return index;
}

template<class K, class E>
std::pair<K, E>* sortedArrayList<K, E>::find(const K& key) const {
	if (size() == 0)
		return nullptr;

	int index = findIndex(key);
	if(list[index].first != key)
		return nullptr;
	else
		return &list[index];
}

template<class K, class E>
void sortedArrayList<K, E>::erase(const K& key) {
	int index = findIndex(key);
	if (list[index].first != key)
		return;

	if (listSize + 1 < arrayLength / 4 && arrayLength >= 4) {
		std::pair<K, E>* old = list;
		list = new std::pair<K, E>[arrayLength/2];
		std::copy(old, old + index, list);
		std::copy(old + index + 1, old + listSize, list + index);
		arrayLength /= 2;
		delete[] old;
	}
	else {
		list[index].~pair<K, E>();
		std::copy(list + index + 1, list + listSize, list + index);
	}
	--listSize;
}

template<class K, class E>
void sortedArrayList<K, E>::insert(const std::pair<K, E>& p) {
	int index = findIndex(p.first);
	if (index != -1 && list[index].first == p.first) {
		list[index].second = p.second;
		return;
	}

	if (listSize + 1 == arrayLength) {
		std::pair<K, E>* old = list;
		list = new std::pair<K, E>[arrayLength * 2];
		std::reverse_copy(old, old + index, list);
		std::copy(old + index + 1, old + listSize, list + index);
		arrayLength *= 2;
		delete[] old;
	}
	else {
		std::copy(std::reverse_iterator<std::pair<K, E>*>(list + listSize),
			std::reverse_iterator<std::pair<K, E>*>(list + index),
			std::reverse_iterator<std::pair<K, E>*>(list + listSize+1));
	}
	list[index+1] = p;
	++listSize;

}

#endif