#ifndef _COMPLETELOSERRTREE_H
#define _COMPLETELOSERRTREE_H

#include<cmath>
#include<functional>

#include "CompleteWinnerTree.h"
//Exercise 19
template<class T>
class CompleteLoserTree : public CompleteWinnerTree<T> {
public:
	CompleteLoserTree() = default;
	CompleteLoserTree(T* thePlayer, int theNumberOfPlayers, bool theSmallerWin = true) { this->smallerWin = theSmallerWin; this->init();  initialize(thePlayer, theNumberOfPlayers); }
	virtual void initialize(T* thePlayer, int theNumberOfPlayers) override;
	virtual T winner() const override;
	virtual void rePlay(int thePlayer = 0) override;

	virtual int root() const override;
protected:
	int setLoser(int parent);
	void setLoserBottomUp(int parent);
	int getLeftPlayer(int parent);
	int getRightPlayer(int parent);
	void play();
	void playRecursive(int parent);//Exercise 19.3
};



template<class T>
T CompleteLoserTree<T>::winner() const {
	return this->player[this->tree[0]];
}

template<class T>
int CompleteLoserTree<T>::root() const {
	return this->tree[0];
}

template<class T>
void CompleteLoserTree<T>::rePlay(int) {
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
int CompleteLoserTree<T>::getLeftPlayer(int parent) {
	if (parent == 0) return 1;

	if (parent <= this->getParentForExt(this->lowExt) / 2) {
		return this->tree[parent * 2];
	}
	else if(parent * 2 > this->offset){
		return parent * 2 - this->offset;
	}
	else {
		return this->n - (this->offset - parent * 2);
	}
}

template<class T>
int CompleteLoserTree<T>::getRightPlayer(int parent) {
	if (parent == 0) return 0;

	if (this->n % 2 == 0 && parent <= this->getParentForExt(this->lowExt) / 2
		|| this->n %2 ==1 && parent <= this->getParentForExt(this->lowExt) / 2 - 1) {
		return this->tree[parent * 2 + 1];
	}
	else if (parent * 2 > this->offset) {
		return parent * 2 - this->offset + 1;
	}
	else {
		return this->n - (this->offset - parent * 2) + 1;
	}
}

template<class T>
int CompleteLoserTree<T>::setLoser(int parent) {
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
void CompleteLoserTree<T>::initialize(T* thePlayer, int theNumberOfPlayers) {
	CompleteWinnerTree<T>::initialize(thePlayer, theNumberOfPlayers);
	this->tree[0] = this->tree[1];

	//play();
	playRecursive(1);
}

template<class T>
void CompleteLoserTree<T>::play() {
	int i = 1;
	for (; i <= this->n - 1; ++i) {
		setLoser(i);
	}
}

template<class T>
void CompleteLoserTree<T>::playRecursive(int parent) {
	setLoser(parent);

	if (parent <= this->getParentForExt(this->lowExt) / 2) {
		playRecursive(parent * 2);
	}
	if (this->n % 2 == 0 && parent <= this->getParentForExt(this->lowExt) / 2
		|| this->n % 2 == 1 && parent <= this->getParentForExt(this->lowExt) / 2 - 1) {
		playRecursive(parent * 2 + 1);
	}
}

//Exercise 19.4, I think this algorithm is not correct. No method to play when the winner is in left sub-tree, when current bottom-up is from right sub-tree.
//template<class T>
//void CompleteLoserTree<T>::initialize(T* thePlayer, int theNumberOfPlayers) {
//	this->clear();
//
//	this->n = theNumberOfPlayers;
//	this->player = thePlayer;
//	this->tree = new int[this->n]{ 0 };
//
//	this->s = (int)pow(2, (int)(log(this->n - 1) / log(2)));
//	this->offset = 2 * this->s - 1;
//	this->lowExt = (this->n - this->s) * 2;
//
//	int i = this->s;
//	for (; i <= this->n - 1; ++i) {
//		setLoserBottomUp(i);
//	}
//
//	i = this->getParentForExt(this->lowExt + 1);
//	if (i % 2 == 1) {
//		++i;
//	}
//	for (; i < this->s;++i) {
//		setLoserBottomUp(i);
//	}
//}

template<class T>
void CompleteLoserTree<T>::setLoserBottomUp(int parent) {
	int thePlayer = setLoser(parent);
	parent /= 2;
	while (parent > 1) {
		if (getRightPlayer(parent) == 0) {
			this->tree[parent] = thePlayer;
		}
		else {
			int originLoser = this->tree[parent];
			if (this->compFunc(this->player[originLoser], this->player[thePlayer])) {
				this->tree[parent] = thePlayer;
				thePlayer = originLoser;
			}
		}
		parent /= 2;
	}
	if (this->tree[0] == 0) {
		this->tree[1] = thePlayer;
		this->tree[0] = thePlayer;
	}
	else {
		if (this->compFunc(this->player[this->tree[0]], this->player[thePlayer])) {
			this->tree[1] = thePlayer;
		}
		else {
			this->tree[1] = this->tree[0];
			this->tree[0] = thePlayer;
		}
	}
}


#endif