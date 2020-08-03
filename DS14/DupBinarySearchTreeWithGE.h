#ifndef _DUPBINARYSEARCHTREEWITHGE_H
#define _DUPBINARYSEARCHTREEWITHGE_H
#include "DupBinarySearchTree.h"

template<class K, class E>
class DupBinarySearchTreeWithGE : public DupBinarySearchTree<K, E> {
public:
	DupBinarySearchTreeWithGE() :DupBinarySearchTree<K, E>() {}
	virtual ~DupBinarySearchTreeWithGE() {}
	virtual std::pair<K, E>* findGE(const K& theKey) const;
	virtual std::pair<K, E> eraseGE(const K& theKey);//Exercise 25
};


template<class K, class E>
std::pair<K, E>* DupBinarySearchTreeWithGE<K, E>::findGE(const K& theKey) const
{
	BinaryTreeNode<std::pair<K, E>>* currentNode = LinkedBinaryTree<std::pair<K,E>>::root;
	std::pair<K, E>* bestElement = nullptr;

	while (currentNode != nullptr) {
		if (currentNode->element.first >= theKey) {
			bestElement = &currentNode->element;
			currentNode = currentNode->leftChild;
		}
		else {
			currentNode = currentNode->rightChild;
		}
	}
	return bestElement;
}

template<class K, class E>
std::pair<K, E> DupBinarySearchTreeWithGE<K, E>::eraseGE(const K& theKey)
{
	BinaryTreeNode<std::pair<K, E>>* currentNode = LinkedBinaryTree<std::pair<K, E>>::root;
	std::pair<K, E> bestElement(-1, -1);

	while (currentNode != nullptr) {
		if (currentNode->element.first >= theKey) {
			bestElement = currentNode->element;
			currentNode = currentNode->leftChild;
		}
		else {
			currentNode = currentNode->rightChild;
		}
	}
	if (bestElement.first != -1) {
		DupBinarySearchTree<K,E>::erase(bestElement.first);
	}
	return bestElement;
}


#endif
