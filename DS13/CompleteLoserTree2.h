#ifndef _COMPLETELOSERRTREE2_H
#define _COMPLETELOSERRTREE2_H

#include<cmath>
#include<functional>

#include "CompleteWinnerTree3.h"
//Exercise 21
template<class T>
class CompleteLoserTree2 : public CompleteWinnerTree3<T> {
public:
	CompleteLoserTree2() = default;
	CompleteLoserTree2(T* thePlayer, int theNumberOfPlayers, bool theSmallerWin = true) { this->smallerWin = theSmallerWin; this->init();  initialize(thePlayer, theNumberOfPlayers); }
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
T CompleteLoserTree2<T>::winner() const {
	return this->player[this->tree[0]];
}

template<class T>
int CompleteLoserTree2<T>::root() const {
	return this->tree[0];
}

template<class T>
void CompleteLoserTree2<T>::rePlay(int) {
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
int CompleteLoserTree2<T>::getLeftPlayer(int parent) {
	if (parent == 0) return 1;

	return this->tree[parent * 2];
}

template<class T>
int CompleteLoserTree2<T>::getRightPlayer(int parent) {
	if (parent == 0) return 0;

	return this->tree[parent * 2 + 1];
}

template<class T>
int CompleteLoserTree2<T>::setLoser(int parent) {
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
void CompleteLoserTree2<T>::initialize(T* thePlayer, int theNumberOfPlayers) {
	CompleteWinnerTree3<T>::initialize(thePlayer, theNumberOfPlayers);
	this->tree[0] = this->tree[1];

	play();
}

template<class T>
void CompleteLoserTree2<T>::play() {
	int i = 1;
	for (; i <= this->n - 1; ++i) {
		setLoser(i);
	}
}

#endif