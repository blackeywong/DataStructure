#pragma once
#ifndef _SKIPLIST_H
#define _SKIPLIST_H
#include "dictionary.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include "skipNode.h"

template<class K, class E>
class skipList : public dictionary<K, E> {
public:
	skipList(K largeKey, int maxPairs, float prob);
	virtual ~skipList() { clear(); }
	virtual bool empty() const override { return dSize == 0; }
	virtual int size() const override { return dSize; }
	virtual std::pair<K, E>* find(const K& key) const override;
	virtual void erase(const K& key) override;
	virtual void insert(const std::pair<K, E>& p) override;
	virtual std::istream& input(std::istream& in);
	virtual std::ostream& output(std::ostream& out);
	//Exercise 9
	void removeSmallest();
	void removeLargest();

protected:
	skipNode<K, E>* findPrev(const K& key) const;
	void clear();
	int level() const;

	float cutOff;
	int levels;
	int dSize;
	int maxLevel;
	K tailKey;
	skipNode<K, E>* headerNode, * tailNode;
	skipNode<K, E>** last;
};

template<class K, class E>
std::istream& operator>>(std::istream& in, skipList<K, E>& sl) { return sl.input(in); }

template<class K, class E>
std::ostream& operator<<(std::ostream& out, skipList<K, E>& sl) { return sl.output(out); }

template<class K, class E>
std::istream& skipList<K, E>::input(std::istream& in) {
	K key;
	E value;
	while (in >> key && in >> value) {
		insert({ key, value });
	}
	return in;
}

template<class K, class E>
std::ostream& skipList<K, E>::output(std::ostream& out) {
	skipNode<K, E>* cur = headerNode->next[0];
	while (cur != tailNode) {
		out << cur->element.first << "," << cur->element.second << " ";
		cur = cur->next[0];
	}
	return out;
}

template<class K, class E>
skipList<K, E>::skipList(K largeKey, int maxPairs, float prob) :tailKey(largeKey), dSize(0), levels(0) {
	cutOff = prob * RAND_MAX;
	maxLevel = (int)ceil(log((float)maxPairs) / log(1 / prob)) - 1;

	std::pair<K, E> tailPair(tailKey, 0);
	headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);
	tailNode = new skipNode<K, E>(tailPair, 0);
	last = new skipNode<K, E>*[maxLevel + 1];
	
	for (int i = 0; i <= maxLevel; ++i) {
		headerNode->next[i] = tailNode;
	}
}

template<class K, class E>
void skipList<K, E>::clear() {
	while (headerNode != tailNode) {
		skipNode<K, E>* nextNode = headerNode->next[0];
		delete headerNode;
		headerNode = nextNode;
	}
	delete headerNode;
}

template<class K, class E>
int skipList<K, E>::level() const {
	int lev = 0;
	//while (rand() <= cutOff)
	//	lev++;
	
	//Exercise 7
	int rnum = rand();
	float probR = (float)RAND_MAX / cutOff;
	float seg = (float)RAND_MAX / probR;
	while (rnum < seg) {
		++lev;
		seg /= probR;
	}


	return (lev <= maxLevel) ? lev : maxLevel;
}

template<class K, class E>
skipNode<K, E>* skipList<K, E>::findPrev(const K& key) const {
	skipNode<K, E>* prev = headerNode;
	for (int i = levels; i >= 0; --i) {
		while (prev->next[i]->element.first < key) {
			prev = prev->next[i];
		}
		last[i] = prev;
	}
	return prev;
}

template<class K, class E>
std::pair<K, E>* skipList<K, E>::find(const K& key) const {
	if (key >= tailKey)
		return nullptr;

	skipNode<K, E>* prev = findPrev(key);
	if (prev->next[0] != tailNode && prev->next[0]->element.first == key)
		return &prev->next[0]->element;
	else
		return nullptr;
}

template<class K, class E>
void skipList<K, E>::erase(const K& key) {
	if (key >= tailKey)
		return;

	skipNode<K, E>* prev = findPrev(key);
	skipNode<K, E>* theNode = prev->next[0];
	if (key < theNode->element.first)
		return;

	for (int i = 0; i <= levels && last[i]->next[i] == theNode; ++i) {
		last[i]->next[i] = theNode->next[i];
	}

	while (levels > 0 && headerNode->next[levels] == tailNode) {
		--levels;
	}

	delete theNode;
	--dSize;
}

template<class K, class E>
void skipList<K, E>::insert(const std::pair<K, E>& p) {
	if (p.first >= tailKey)
		throw std::invalid_argument("key is too large to insert");

	skipNode<K, E>* prev = findPrev(p.first);
	skipNode<K, E>* theNode = prev->next[0];
	//Exercise 8
	//if (theNode->element.first == p.first) {
	//	theNode->element.second = p.second;
	//	return;
	//}

	int theLevel = level();
	if (theLevel > levels) {
		theLevel = ++levels;
		last[theLevel] = headerNode;
	}
	//std::cout << "insert " << p.first << " at level " << theLevel << std::endl;
	skipNode<K, E>* newNode = new skipNode<K, E>(p, theLevel + 1);
	for (int i = 0; i <= theLevel; ++i) {
		newNode->next[i] = last[i]->next[i];
		last[i]->next[i] = newNode;
	}
	++dSize;
}


template<class K, class E>
void skipList<K, E>::removeSmallest() {
	if (size() == 0)
		return;

	skipNode<K, E>* theNode = headerNode->next[0];
	for (int i = 0; i <= levels && headerNode->next[i] == theNode; ++i) {
		headerNode->next[i] = theNode->next[i];
	}

	while (levels > 0 && headerNode->next[levels] == tailNode) {
		--levels;
	}

	delete theNode;
	--dSize;
}

template<class K, class E>
void skipList<K, E>::removeLargest() {
	if (size() == 0)
		return;

	skipNode<K, E>* theNode = headerNode;
	for (int i = levels; i >= 0; --i) {
		while (theNode->next[i] != tailNode && theNode->next[i]->next[i] != tailNode) {
			theNode = theNode->next[i];
		}
		last[i] = theNode;
	}
	theNode = theNode->next[0];

	for (int i = 0; i <= levels && last[i]->next[i] == theNode; ++i) {
		last[i]->next[i] = theNode->next[i];
	}

	while (levels > 0 && headerNode->next[levels] == tailNode) {
		--levels;
	}

	delete theNode;
	--dSize;
}

#endif