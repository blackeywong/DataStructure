#ifndef _INDEXEDBINARYSEARCHTREE_H
#define _INDEXEDBINARYSEARCHTREE_H

#include "IndexedBSTree.h"
#include "../DS11/LinkedBinaryTree.h"

template<class K, class E>
struct IndexedBSTreeNode {
	int leftSize;
	std::pair<K,E> keyValue;
	IndexedBSTreeNode(const std::pair<K,E>& p):leftSize(0), keyValue(p) {}
};

template<class K, class E>
ostream& operator<<(ostream& out, const IndexedBSTreeNode<K, E>& node) { out << node.keyValue.first << ' '; return out; }

template<class K, class E>
class IndexedBinarySearchTree : public LinkedBinaryTree<IndexedBSTreeNode<K,E>>, public IndexedBSTree<K, E> {
public:
	IndexedBinarySearchTree() :LinkedBinaryTree<IndexedBSTreeNode<K,E>>() {}
	virtual ~IndexedBinarySearchTree() {}
	virtual bool empty() const  override { return LinkedBinaryTree<IndexedBSTreeNode<K,E>>::empty(); }
	virtual int size() const  override { return LinkedBinaryTree<IndexedBSTreeNode<K,E>>::size(); }
	virtual std::pair<K, E>* find(const K& theKey) const override;
	virtual void erase(const K& theKey) override;
	virtual void insert(const std::pair<K, E>& thePair) override;

	virtual void ascend() override;

	std::istream& input(std::istream& in);

	virtual std::pair<K, E>* get(int index) const override;
	virtual void deleteAt(int index) override;
	virtual int getIndex(const K& theKey);
protected:
	IndexedBSTreeNode<K, E>* get(int index, BinaryTreeNode<IndexedBSTreeNode<K, E>>* subtree) const;
	void updateLeftSize(K searchKey, bool bInsert = true);
};


template<class K, class E>
std::pair<K, E>* IndexedBinarySearchTree<K, E>::find(const K& theKey) const
{
	BinaryTreeNode<IndexedBSTreeNode<K,E>>* p = this->root;
	while (p != nullptr) {
		if (theKey < p->element.keyValue.first) {
			p = p->leftChild;
		}
		else if (theKey > p->element.keyValue.first) {
			p = p->rightChild;
		}
		else {
			return &p->element.keyValue;
		}
	}
	return nullptr;
}

template<class K, class E>
void IndexedBinarySearchTree<K, E>::erase(const K& theKey)
{
	BinaryTreeNode<IndexedBSTreeNode<K,E>>* p = this->root;
	BinaryTreeNode<IndexedBSTreeNode<K,E>>* pp = nullptr;

	//find the node of theKey
	while (p != nullptr && p->element.keyValue.first != theKey) {
		pp = p;
		if (theKey < p->element.keyValue.first) {
			p = p->leftChild;
		}
		else if (theKey > p->element.keyValue.first) {
			p = p->rightChild;
		}
		else {
			return;
		}
	}
	if (p == nullptr)
		return;//cannot find theKey

	//when p has two childs
	if (p->leftChild != nullptr && p->rightChild != nullptr) {
		//find the max in leftChild of p
		BinaryTreeNode<IndexedBSTreeNode<K,E>>* s = p->leftChild;
		BinaryTreeNode<IndexedBSTreeNode<K,E>>* ps = p;

		while (s->rightChild != nullptr) {
			ps = s;
			s = s->rightChild;
		}

		//move max from s to p
		BinaryTreeNode<IndexedBSTreeNode<K,E>>* q = new BinaryTreeNode<IndexedBSTreeNode<K,E>>(s->element, p->leftChild, p->rightChild);
		q->element.leftSize = p->element.leftSize;
		if (pp == nullptr) {
			this->root = q;
		}
		else if (p == pp->leftChild) {
			pp->leftChild = q;
		}
		else {
			pp->rightChild = q;
		}

		if (ps == p) {
			pp = q;
		}
		else {
			pp = ps;
		}
		delete p;
		p = s;
	}

	//p has one child at most
	BinaryTreeNode<IndexedBSTreeNode<K,E>>* c = nullptr;
	if (p->leftChild != nullptr) {
		c = p->leftChild;
	}
	else {
		c = p->rightChild;
	}
	if (p == this->root) {
		this->root = c;
	}
	else {
		if (p == pp->leftChild) {
			pp->leftChild = c;
		}
		else {
			pp->rightChild = c;
		}
		--this->treeSize;
		delete p;
	}

	if (pp != nullptr) {
		updateLeftSize(pp->element.keyValue.first, false);
	}
}

template<class K, class E>
void IndexedBinarySearchTree<K, E>::insert(const std::pair<K, E>& thePair)
{
	BinaryTreeNode<IndexedBSTreeNode<K,E>>* p = this->root;
	BinaryTreeNode<IndexedBSTreeNode<K,E>>* pp = nullptr;

	while (p != nullptr) {
		pp = p;
		if (thePair.first < p->element.keyValue.first) {
			p = p->leftChild;
		}
		else if (thePair.first > p->element.keyValue.first) {
			p = p->rightChild;
		}
		else {
			p->element.keyValue.second = thePair.second;
			return;
		}
	}

	BinaryTreeNode<IndexedBSTreeNode<K,E>>* newNode = new BinaryTreeNode<IndexedBSTreeNode<K,E>>(thePair);
	if (this->root != nullptr) {
		if (thePair.first < pp->element.keyValue.first) {
			pp->leftChild = newNode;
		}
		else {
			pp->rightChild = newNode;
		}
	}
	else {
		this->root = newNode;
	}
	++this->treeSize;

	updateLeftSize(thePair.first);
}

template<class K, class E>
inline void IndexedBinarySearchTree<K, E>::updateLeftSize(K searchKey, bool bInsert)
{
	if (this->treeSize == 0) {
		return;
	}

	if (this->treeSize == 1) {
		this->root->element.leftSize = 0;
		return;
	}

	BinaryTreeNode<IndexedBSTreeNode<K, E>>* p = this->root;
	BinaryTreeNode<IndexedBSTreeNode<K, E>>* pp = nullptr;

	//update leftSize from root to newNode
	while (p != nullptr) {
		pp = p;
		if (searchKey < p->element.keyValue.first) {
			if (bInsert) {
				++p->element.leftSize;
			}
			else
			{
				--p->element.leftSize;
			}
			p = p->leftChild;
		}
		else if (searchKey > p->element.keyValue.first) {
			p = p->rightChild;
		}
		else {
			if (p->leftChild == nullptr) {
				p->element.leftSize = 0;
			}
			else {
				p->element.leftSize = p->leftChild->element.leftSize + 1;
			}
			return;
		}
	}
}

template<class K, class E>
void IndexedBinarySearchTree<K, E>::ascend()
{
	LinkedBinaryTree<IndexedBSTreeNode<K,E>>::output(std::cout, TRAVERSE_ORDER::INFIX);
	std::cout << std::endl;
}

template<class K, class E>
std::istream& IndexedBinarySearchTree<K, E>::input(std::istream& in) {
	int num;
	in >> num;

	for (int i = 0; i < num; ++i) {
		K k;
		E e;
		in >> k >> e;
		std::pair<K,E> p({ k,e });
		insert(p);
	}
	return in;
}

template<class K, class E>
IndexedBSTreeNode<K, E>* IndexedBinarySearchTree<K, E>::get(int index, BinaryTreeNode<IndexedBSTreeNode<K, E>>* subtree) const
{
	BinaryTreeNode<IndexedBSTreeNode<K, E>>* p = subtree;
	BinaryTreeNode<IndexedBSTreeNode<K, E>>* pp = nullptr;

	while (p != nullptr) {
		if (p->element.leftSize == index) {
			return &p->element;
		}
		else if (p->element.leftSize < index) {
			index -= p->element.leftSize + 1;
			pp = p;
			p = p->rightChild;
		}
		else {
			pp = p;
			p = p->leftChild;
		}
	}
	return nullptr;
}

template<class K, class E>
std::pair<K, E>* IndexedBinarySearchTree<K, E>::get(int index) const
{
	IndexedBSTreeNode<K, E>* p = get(index, this->root);
	return &p->keyValue;
}

template<class K, class E>
void IndexedBinarySearchTree<K, E>::deleteAt(int index)
{
	IndexedBSTreeNode<K, E>* p = get(index, this->root);
	if (p != nullptr) {
		erase(p->keyValue.first);
	}
}

template<class K, class E>
int IndexedBinarySearchTree<K, E>::getIndex(const K& theKey)
{
	BinaryTreeNode<IndexedBSTreeNode<K, E>>* p = this->root;
	if( p == nullptr)
		return -1;

	int base = 0;
	while (p != nullptr) {
		if (p->element.keyValue.first == theKey) {
			return base + p->element.leftSize;
		}else if (theKey < p->element.keyValue.first) {
			p = p->leftChild;
			
		}
		else {
			base += p->element.leftSize + 1;
			p = p->rightChild;
		}
	}

	return -1;
}

#endif
