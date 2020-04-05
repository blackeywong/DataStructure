#ifndef _FULLLOSERRTREE_H
#define _FULLLOSERRTREE_H

#include<cmath>
#include<functional>

#include "FullWinnerTree.h"
//Exercise 19
template<class T>
class FullLoserTree : public FullWinnerTree<T> {
public:
	//FullLoserTree() = default;
	FullLoserTree(T* thePlayer, int theNumberOfPlayers, bool theSmallerWin = true) { this->smallerWin = theSmallerWin; this->init();  initialize(thePlayer, theNumberOfPlayers); }
	virtual void initialize(T* thePlayer, int theNumberOfPlayers) override;
	virtual T winner() const override;
	virtual void rePlay(int thePlayer = 0) override;

	virtual int root() const override;
protected:
	int setLoser(int parent);
	int getLeftPlayer(int parent);
	int getRightPlayer(int parent);
	void play();
};

template<class T>
T FullLoserTree<T>::winner() const {
	return this->player[this->tree[0]];
}

template<class T>
int FullLoserTree<T>::root() const {
	return this->tree[0];
}

template<class T>
void FullLoserTree<T>::rePlay(int) {
	int theOriginWinner = this->root();
	int theOriginLoser = this->tree[1];
	int thePlayer = theOriginWinner;
	int parent = this->getParentForExt(thePlayer);
	int originLoser;

	while (parent >= 1) {
		originLoser = this->tree[parent];
		if (!this->compFunc(this->player[thePlayer], this->player[originLoser])) {
			this->tree[parent] = thePlayer;
			thePlayer = originLoser;
		}
		parent /= 2;
	} 

	this->tree[0] = thePlayer;
}

template<class T>
int FullLoserTree<T>::getLeftPlayer(int parent) {
	if (parent == 0) return 1;

	if (parent <= this->getParentForExt(this->lowExt) / 2) {
		return this->tree[parent * 2];
	}
	else {
		return this->n - (this->offset - parent * 2);
	}
}

template<class T>
int FullLoserTree<T>::getRightPlayer(int parent) {
	if (parent == 0) return 0;

	if (parent <= this->getParentForExt(this->lowExt) / 2) {
		return this->tree[parent * 2 + 1];
	}
	else {
		return this->n - (this->offset - parent * 2) + 1;
	}
}

template<class T>
int FullLoserTree<T>::setLoser(int parent) {
	int leftPlayer = getLeftPlayer(parent);
	int rightPlayer = getRightPlayer(parent);

	if (this->compFunc(this->player[leftPlayer], this->player[rightPlayer])) {
		this->tree[parent] = rightPlayer;
		return leftPlayer;
	}
	else {
		this->tree[parent] = leftPlayer;
		return rightPlayer;
	}
}


template<class T>
void FullLoserTree<T>::initialize(T* thePlayer, int theNumberOfPlayers) {
	CompleteWinnerTree<T>::initialize(thePlayer, theNumberOfPlayers);
	this->tree[0] = this->tree[1];

	play();
}

template<class T>
void FullLoserTree<T>::play() {
	int i = 1;
	for (; i <= this->n - 1; ++i) {
		setLoser(i);
	}
}

#endif
