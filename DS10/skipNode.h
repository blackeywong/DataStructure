#pragma once
#ifndef _SKIPNODE_H
#define _SKIPNODE_H
#include <utility>

template<class K, class E>
struct skipNode {
	typedef std::pair<K, E> pairType;
	pairType element;
	skipNode<K, E>** next;

	skipNode(const pairType& theElement, int size):element(theElement) {
		if (size == 0)
			next = nullptr;
		else
			next = new skipNode<K, E> * [size];
	}
};

#endif
