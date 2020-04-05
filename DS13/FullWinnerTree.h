#ifndef _FULLEWINNERTREE_H
#define _FULLEWINNERTREE_H

#include<cmath>
#include<functional>
#include<exception>

#include "CompleteWinnerTree.h"
//Exercise 10, power of 2
template<class T>
class FullWinnerTree : public CompleteWinnerTree<T> {
public:
	FullWinnerTree() = default;
	FullWinnerTree(T* thePlayer, int theNumberOfPlayers, bool theSmallerWin = true){ this->smallerWin = theSmallerWin; this->init(); initialize(thePlayer,theNumberOfPlayers); }
	virtual ~FullWinnerTree() { this->clear(); }
	virtual void initialize(T* thePlayer, int theNumberOfPlayers) override;

protected:
	virtual int getParentForExt(int i) const override;
	void play(int parent, int leftChild, int rightChild);
	virtual bool isRightChild(int player, bool isExt)const override;
	virtual int getSiblingPlayer(int i, bool isExt) const override;
};

template<class T>
int FullWinnerTree<T>::getParentForExt(int i)const {
	return (i + this->offset) / 2;
}

template<class T>
void FullWinnerTree<T>::initialize(T* thePlayer, int theNumberOfPlayers) {
	this->clear();

	this->n = theNumberOfPlayers;
	this->player = thePlayer;
	this->tree = new int[this->n];

	this->s = (int)pow(2, (int)(log(this->n - 1) / log(2)));
	if (this->s * 2 != this->n) {
		throw std::invalid_argument("number of input players is not power of 2");
	}
	this->offset = 2 * this->s - 1;
	//this->lowExt = (this->n - this->s) * 2;

	for (int p = 2;p <= this->n; p += 2) {
		play(getParentForExt(p), p - 1, p);
	}
}

template<class T>
bool FullWinnerTree<T>::isRightChild(int i, bool isExt) const {
	if (isExt) {
		if (i % 2 == 0)
			return true;
		return false;
	}
	if (i % 2 == 0 || i == 1)
		return false;
	return true;
}

template<class T>
int FullWinnerTree<T>::getSiblingPlayer(int i, bool isExt) const {
	if (isRightChild(i, isExt)) {
		if (isExt) {
			return i - 1;
		}
		return this->tree[i - 1];
	}
	else {
		if (isExt) {
			return i + 1;
		}
		return this->tree[i + 1];
	}
}

template<class T>
void FullWinnerTree<T>::play(int parent, int leftChild, int rightChild) {
	this->tree[parent] = this->compFunc(this->player[leftChild], this->player[rightChild]) ? leftChild : rightChild;

	while (parent % 2 == 1 && parent != 1) {
		int p = parent;
		parent /= 2;
		this->tree[parent] = this->compFunc(this->player[this->tree[p - 1]], this->player[this->tree[p]]) ? this->tree[p - 1] : this->tree[p];
	}
}


#endif
