#ifndef _COMPLETEWINNERTREE4_H
#define _COMPLETEWINNERTREE4_H

#include<cmath>
#include<functional>
#include<exception>

#include "CompleteWinnerTree.h"
//Exercise 13
template<class T>
class CompleteWinnerTree4 : public CompleteWinnerTree<T> {
public:
	CompleteWinnerTree4(T* thePlayer, int theNumberOfPlayers, bool theSmallerWin = true) { this->smallerWin = theSmallerWin; this->init(); initialize(thePlayer, theNumberOfPlayers); }
	virtual ~CompleteWinnerTree4() { this->clear(); }
	virtual void initialize(T* thePlayer, int theNumberOfPlayers) override;

protected:
	virtual int getParentForExt(int i) const override;
	void play(int parent, int leftChild, int rightChild);
	virtual bool isRightChild(int player, bool isExt) const const override;
	virtual int getSiblingPlayer(int i, bool isExt) const const override;

	int m;
};

template<class T>
int CompleteWinnerTree4<T>::getParentForExt(int i) const {
	if (i <= this->lowExt)
		return (i + this->offset) / 2;
	return (i - this->lowExt + this->m - 1) / 2;
}

template<class T>
void CompleteWinnerTree4<T>::initialize(T* thePlayer, int theNumberOfPlayers) {
	this->clear();

	this->n = theNumberOfPlayers;
	this->player = thePlayer;
	this->s = (int)pow(2, (int)(log(this->n - 1) / log(2)));
	this->offset = 2 * this->s - 1;
	if (this->n % 2 == 0) {
		m = this->n;
	}
	else {
		m = this->n + 1;
	}
	this->lowExt = (this->m - this->s) * 2;
	this->tree = new int[this->m];

	int p = 2;
	for (; p <= this->n; p += 2) {
		play(getParentForExt(p), p - 1, p);
	}
	if (this->n % 2 == 1) {
		play(getParentForExt(p), p - 1, 1);
		p += 2;
	}
}

template<class T>
bool CompleteWinnerTree4<T>::isRightChild(int i, bool isExt) const {
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
int CompleteWinnerTree4<T>::getSiblingPlayer(int i, bool isExt) const {
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
void CompleteWinnerTree4<T>::play(int parent, int leftChild, int rightChild) {
	this->tree[parent] = this->compFunc(this->player[leftChild], this->player[rightChild]) ? leftChild : rightChild;

	while (parent % 2 == 1 && parent != 1) {
		int p = parent;
		parent /= 2;
		this->tree[parent] = this->compFunc(this->player[this->tree[p - 1]], this->player[this->tree[p]]) ? this->tree[p - 1] : this->tree[p];
	}
}


#endif
