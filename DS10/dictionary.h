#pragma once
#ifndef _DICTIONARY_H
#define _DICTIONARY_H
#include <utility>
#include <string>

template<class K, class E>
class dictionary {
public:
	virtual ~dictionary() {}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual std::pair<K, E>* find(const K& key) const = 0;
	virtual void erase(const K& key) = 0;
	virtual void insert(const std::pair<K, E>& p) = 0;
};

int stringToInt(const std::string& s);

int doubleToInt(double d);

#endif
