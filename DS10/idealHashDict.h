#pragma once
#ifndef _IDEALHASHDICT_H
#define _IDEALHASHDICT_H
#include "dictionary.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>
//Exercise 10
template<class E>
class IdealHashDict : public dictionary<int, E> {
public:
	IdealHashDict(int theMaxKey);
	virtual ~IdealHashDict() { delete[] list; }
	virtual bool empty() const override { return dSize == 0; }
	virtual int size() const override { return dSize; }
	virtual std::pair<int, E>* find(const int& key) const override;
	virtual void erase(const int& key) override;
	virtual void insert(const std::pair<int, E>& p) override;
	virtual std::istream& input(std::istream& in);
	virtual std::ostream& output(std::ostream& out);

private:
	int dSize;
	std::pair<int, E>** list;
	int maxKey;
};

template<class E>
std::istream& operator>>(std::istream& in, IdealHashDict<E>& sal) { return sal.input(in); }

template<class E>
std::ostream& operator<<(std::ostream& out, IdealHashDict<E>& sal) { return sal.output(out); }

template<class E>
std::istream& IdealHashDict<E>::input(std::istream& in) {
	int key;
	E value;
	while (in >> key && in >> value) {
		list[key] = new std::pair<int, E>({ key, value });
		++dSize;
	}
	return in;
}

template<class E>
std::ostream& IdealHashDict<E>::output(std::ostream& out) {
	for (int i = 0; i <= maxKey; ++i) {
		if(list[i] != nullptr)
			out << list[i]->first << "," << list[i]->second << " ";
	}
	return out;
}

template<class E>
IdealHashDict<E>::IdealHashDict(int theMaxKey):maxKey(theMaxKey) {
	if (maxKey <= 0)
		throw std::invalid_argument("maxKey should be > 0");

	list = new std::pair<int, E>* [maxKey+1];
	dSize = 0;
	for (int i = 0; i <= maxKey; ++i) {
		list[i] = nullptr;
	}
}

template<class E>
std::pair<int, E>* IdealHashDict<E>::find(const int& key) const {
	if (key < 0 || key > maxKey || list[key] == nullptr)
		return nullptr;

	return list[key];
}

template<class E>
void IdealHashDict<E>::erase(const int& key) {
	if (key < 0 || key > maxKey || list[key] == nullptr)
		return;

	delete list[key];
	list[key] = nullptr;
	--dSize;
}

template<class E>
void IdealHashDict<E>::insert(const std::pair<int, E>& p) {
	if (p.first < 0 || p.first > maxKey)
		return;

	if (list[p.first] != nullptr){
		list[p.first]->second = p.second;
	}
	else {
		list[p.first] = new std::pair<int, E>(p);
		++dSize;
	}
}

#endif