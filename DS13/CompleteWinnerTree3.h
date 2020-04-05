#ifndef _COMPLETEWINNERTREE3_H
#define _COMPLETEWINNERTREE3_H

#include<cmath>
#include<functional>
#include<exception>

#include "CompleteWinnerTree.h"
//Exercise 12
template<class T>
class CompleteWinnerTree3 : public CompleteWinnerTree<T> {
public:
	CompleteWinnerTree3() = default;
	CompleteWinnerTree3(T* thePlayer, int theNumberOfPlayers, bool theSmallerWin = true) { this->smallerWin = theSmallerWin; this->init(); initialize(thePlayer, theNumberOfPlayers); }
	virtual ~CompleteWinnerTree3() { this->clear(); }
	virtual void initialize(T* thePlayer, int theNumberOfPlayers) override;
	virtual void rePlay(int thePlayer) override;

protected:
	virtual int getParentForExt(int i) const override;
	void play(int parent);
	virtual bool isRightChild(int player, bool isExt) const override;
	virtual int getSiblingPlayer(int i, bool isExt) const override;
};

template<class T>
int CompleteWinnerTree3<T>::getParentForExt(int i) const {
	if (i <= this->lowExt)
		return i + this->offset;
	return i - this->lowExt + this->n - 1;
}

template<class T>
void CompleteWinnerTree3<T>::initialize(T* thePlayer, int theNumberOfPlayers) {
	this->clear();

	this->n = theNumberOfPlayers;
	this->player = thePlayer;
	this->s = (int)pow(2, (int)(log(this->n - 1) / log(2)));
	this->offset = 2 * this->s - 1;
	this->lowExt = (this->n - this->s) * 2;
	this->tree = new int[2 * this->n];

	int i = 1;
	for (; i <= this->n; ++i) {
		this->tree[getParentForExt(i)] = i;
	}

	for (i = 2; i <= this->lowExt; i += 2) {
		play(getParentForExt(i) / 2);
	}
	if (this->n % 2 == 1) {
		play(this->n / 2);
		++i;
	}
	for (; i <= this->n; i += 2) {
		play(getParentForExt(i) / 2);
	}
}

template<class T>
bool CompleteWinnerTree3<T>::isRightChild(int i, bool isExt) const {
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
int CompleteWinnerTree3<T>::getSiblingPlayer(int i, bool isExt) const {
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
void CompleteWinnerTree3<T>::play(int parent) {
	int p;
	do{
		this->tree[parent] = this->compFunc(this->player[this->tree[parent * 2]], this->player[this->tree[parent * 2 + 1]]) ? this->tree[parent * 2] : this->tree[parent * 2 + 1];
		p = parent;
		parent /= 2;
	 } while (p % 2 == 1 && p != 1);
}

template<class T>
void CompleteWinnerTree3<T>::rePlay(int thePlayer) {
	int parent = getParentForExt(thePlayer);

	while (parent != 1) {
		int q = parent;
		parent /= 2;
		int originWinner = this->tree[parent];
		int siblingPlayer = getSiblingPlayer(q, false);
		if (this->compFunc(this->player[siblingPlayer], this->player[this->tree[q]])) {
			this->tree[parent] = siblingPlayer;
		}
		else {
			this->tree[parent] = this->tree[q];
		}
		if (originWinner == this->tree[parent] && originWinner != thePlayer)
			return;
	}
}


#endif
