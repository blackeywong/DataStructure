#pragma once
#ifndef _PAIRNODE_H
#define _PAIRNODE_H
#include <utility>

template<class K, class E>
struct pairNode {
	std::pair<K, E> element;
	pairNode<K, E>* next;

	pairNode() {}
	pairNode(const std::pair<K, E>& theElement, pairNode<K, E>* theNext = nullptr) {
		this->element = theElement;
		this->next = next;
	}

	pairNode<const K, E>& operator=(const pairNode<K, E>& theNode) {
		this->element = theNode->element;
		return *this;
	}

	bool operator!=(const pairNode<const K, E>& right) const { return element != right.element; }
	bool operator==(const pairNode<const K, E>& right) const { return element == right.element; }

};

#endif
