#ifndef _COMPLETEWINNERTREE_H
#define _COMPLETEWINNERTREE_H

#include<cmath>
#include<functional>

#include "WinnerTree.h"
//#include "DS13_Applications.h"

void firstFitPack2(int* objectSize, int numberOfObjects, int binCapacity);
void firstFitDecreasingPack(int* objectSize, int numberOfObjects, int binCapacity);
void nextFitPack(int* objectSize, int numberOfObjects, int binCapacity);
void rightFitPack(int* objectSize, int numberOfObjects, int binCapacity);

template<class T>
class CompleteWinnerTree: public WinnerTree<T> {
	friend void firstFitPack2(int* objectSize, int numberOfObjects, int binCapacity);
	friend void firstFitDecreasingPack(int* objectSize, int numberOfObjects, int binCapacity);
	friend void nextFitPack(int* objectSize, int numberOfObjects, int binCapacity);
	friend void rightFitPack(int* objectSize, int numberOfObjects, int binCapacity);
public:
	CompleteWinnerTree() = default;
	CompleteWinnerTree(T* thePlayer, int theNumberOfPlayers, bool theSmallerWin = true):smallerWin(theSmallerWin) { init();  initialize(thePlayer, theNumberOfPlayers); }
	virtual ~CompleteWinnerTree() { clear(); }
	virtual void initialize(T* thePlayer, int theNumberOfPlayers) override;
	virtual T winner() const override;
	virtual void rePlay(int thePlayer) override;
	virtual int winnerNum() const;

	//Exercise 26
	virtual int root() const;
	virtual int leftChild(int i) const;
	virtual int rightChild(int i) const;

	int winner(int i) const { return i < n ? tree[i] : 0; }
	int getCommonAncestor(int p1, int p2, bool isExt);
protected:
	void init();
	void clear();
	virtual int getParentForExt(int i) const;
	void play(int parent, int leftChild, int rightChild);
	void playRecursive(int parent, int leftChild, int rightChild);
	virtual bool isRightChild(int player, bool isExt) const;
	virtual int getSiblingPlayer(int i, bool isExt) const;
	bool compareSibling(int thePlayer, bool isExt) const;//always compare left to right

	int s;//first node of lowest internal nodes
	int offset;
	int lowExt;
	std::function<bool(const T&, const T&)> compFunc;

	bool smallerWin;
	int n;//playerNumber
	T* player;
	int* tree;

};

template<class T>
void CompleteWinnerTree<T>::init() {
	player = nullptr;
	tree = nullptr;
	if (smallerWin) {
		//compFunc = std::less<T>();
		compFunc = std::less_equal<T>();
	}
	else {
		//compFunc = std::greater<T>();
		compFunc = std::greater_equal<T>();
	}
}

template<class T>
void CompleteWinnerTree<T>::clear() {
	delete[] tree;
	player = nullptr;
	tree = nullptr;
}

template<class T>
int CompleteWinnerTree<T>::getParentForExt(int i)  const {
	if (i <= lowExt)
		return (i + offset) / 2;
	return (i - lowExt + n - 1) / 2;
}

template<class T>
int CompleteWinnerTree<T>::getCommonAncestor(int p1, int p2, bool isExt) {
	if (p1 == p2)
		return p1;

	if (isExt) {
		p1 = getParentForExt(p1);
		p2 = getParentForExt(p2);
	}

	while (p1 != p2) {
		p1 /= 2;
		if (p1 == p2)
			return p1;
		p2 /= 2;
	}

	return p1;
}

template<class T>
void CompleteWinnerTree<T>::initialize(T* thePlayer, int theNumberOfPlayers) {
	clear();

	n = theNumberOfPlayers;
	player = thePlayer;
	tree = new int[n] {0};

	s = (int)pow(2, (int)(log(n - 1)/log(2)));
	offset = 2 * s - 1;
	lowExt = (n - s) * 2;

	//Exercise 9
	//if (n >= 2) {
	//	playRecursive(1, 2, 3);
	//}

	int p = 2;
	for (; p <= lowExt; p += 2) {
		play(getParentForExt(p), p-1, p);
	}

	if (n % 2 == 1) {
		play((n-1) / 2, tree[n-1], lowExt + 1);
		++p;
	}

	for (; p <= n; p += 2) {
		play(getParentForExt(p), p - 1, p);
	}
}

template<class T>
T CompleteWinnerTree<T>::winner() const {
	return player[tree[1]];
}


template<class T>
int CompleteWinnerTree<T>::winnerNum() const {
	return tree[1];
}

template<class T>
int CompleteWinnerTree<T>::root() const {
	return 1;
}

template<class T>
int CompleteWinnerTree<T>::leftChild(int i) const {
	if (i == 0) return 1;

	if (i <= getParentForExt(lowExt) / 2) {
		return i * 2;
	}
	else {
		return 0;
	}
}

template<class T>
int CompleteWinnerTree<T>::rightChild(int i) const {
	if (i == 0) return 0;

	if (n % 2 == 0 && i <= getParentForExt(lowExt) / 2
		|| n % 2 == 1 && i <= getParentForExt(lowExt) / 2 - 1) {
		return i * 2 + 1;
	}
	else {
		return 0;
	}
}

template<class T>
bool CompleteWinnerTree<T>::isRightChild(int i, bool isExt) const {
	if (isExt) {
		if (n % 2 == 0) {
			if (i % 2 == 0)
				return true;
			return false;
		}
		else {
			if (i <= lowExt) {
				if (i % 2 == 0)
					return true;
				return false;
			}
			else {
				if (i % 2 == 0)
					return false;
				return true;
			}
		}
	}
	if (i % 2 == 0 || i == 1)
		return false;
	return true;
}

template<class T>
int CompleteWinnerTree<T>::getSiblingPlayer(int i, bool isExt) const {
	if (isRightChild(i, isExt)) {
		if (isExt) {
			if (i == lowExt + 1 && i % 2 != 0)
				return tree[n - 1];
			return i - 1;
		}
		return tree[i - 1];
	}
	else {
		if (isExt) {
			return i + 1;
		}
		if (i == n - 1)
			return lowExt + 1;
		return tree[i + 1];
	}
}

template<class T>
bool CompleteWinnerTree<T>::compareSibling(int thePlayer, bool isExt) const {
	int siblingPlayer = getSiblingPlayer(thePlayer, isExt);
	if (isExt) {
		if (n % 2 == 1 && thePlayer == lowExt + 1) {
			return !compFunc(player[siblingPlayer], player[thePlayer]);
		}
		else {
			if (!isRightChild(thePlayer, true)) {
				return compFunc(player[thePlayer], player[siblingPlayer]);
			}
			else {
				return !compFunc(player[siblingPlayer], player[thePlayer]);
			}
		}
	}
	else {
		if (n % 2 == 1 && thePlayer == n - 1) {
			return compFunc(player[tree[thePlayer]], player[siblingPlayer]);
		}
		else {
			if (!isRightChild(thePlayer, false)) {
				return compFunc(player[tree[thePlayer]], player[siblingPlayer]);
			}
			else {
				return !compFunc(player[siblingPlayer], player[tree[thePlayer]]);
			}
		}
	}
}

template<class T>
void CompleteWinnerTree<T>::rePlay(int thePlayer) {
	int parent = getParentForExt(thePlayer);
	int originWinner = tree[parent];
	if (compareSibling(thePlayer, true)) {
		tree[parent] = thePlayer;
	}
	else {
		tree[parent] = getSiblingPlayer(thePlayer, true);
	}
	if (originWinner == tree[parent] && originWinner != thePlayer)
		return;

	while (parent != 1) {
		int q = parent;
		parent /= 2;
		originWinner = tree[parent];
		if (compareSibling(q, false)) {
			tree[parent] = tree[q];
		}
		else {
			if (n %2 == 1 && q == n - 1 && s * 2 != n/*is not full*/) {
				tree[parent] = lowExt + 1;
			}
			else {
				tree[parent] = getSiblingPlayer(q, false);
			}
		}
		if (originWinner == tree[parent] && originWinner != thePlayer)//Exercise 7
			return;
	}
}

template<class T>
void CompleteWinnerTree<T>::play(int parent, int leftChild, int rightChild) {
	tree[parent] = compFunc(player[leftChild], player[rightChild]) ? leftChild: rightChild;

	while (parent %2 == 1 && parent != 1) {
		int p = parent;
		parent /= 2;
		tree[parent] = compFunc(player[tree[p - 1]], player[tree[p]]) ? tree[p - 1]: tree[p];
	}
}
template<class T>
void CompleteWinnerTree<T>::playRecursive(int parent, int leftChild, int rightChild) {
	if (parent < n / 2) {
		playRecursive(leftChild, leftChild * 2, leftChild * 2 + 1);
		playRecursive(rightChild, rightChild * 2, rightChild * 2 + 1);
		tree[parent] = compFunc(player[tree[leftChild]], player[tree[rightChild]]) ? tree[leftChild] : tree[rightChild];
	}
	else if (n % 2 == 1 && rightChild == n) {
		playRecursive(leftChild, leftChild * 2, leftChild * 2 + 1);
		tree[parent] = compFunc(player[tree[leftChild]], player[lowExt + 1]) ? tree[leftChild] : lowExt + 1;
	}
	else {
		if (leftChild > offset) {
			tree[parent] = compFunc(player[leftChild - offset], player[rightChild - offset]) ? leftChild - offset : rightChild - offset;
		}
		else if (rightChild <= offset) {
			tree[parent] = compFunc(player[parent * 2 - (n - 1) + lowExt], player[parent * 2 - (n - 1) + lowExt + 1]) ? parent * 2 - (n - 1) + lowExt : parent * 2 - (n - 1) + lowExt + 1;
		}
	}
}


//template<class T>
//void CompleteWinnerTree<T>::initialize(T* thePlayer, int theNumberOfPlayers) {
//	clear();
//
//	n = theNumberOfPlayers;
//	player = thePlayer;
//	tree = new int[n];
//
//	s = (int)pow(2, (int)(log(n - 1) / log(2)));
//	offset = 2 * s - 1;
//	lowExt = (n - s) * 2;
//
//	for (int p = 2; p <= n; ++p) {
//		int q = p;
//		if (isRightChild(q, true)) {
//			int parent = getParentForExt(q);
//			int leftPlayer = getSiblingPlayer(q, true);
//			if (compFunc(player[leftPlayer], player[q])) {
//				tree[parent] = leftPlayer;
//			}
//			else {
//				tree[parent] = q;
//			}
//			q = parent;
//			while (isRightChild(q, false)) {
//				int parent = q / 2;
//				int leftPlayer = getSiblingPlayer(q, false);
//				if (compFunc(player[leftPlayer], player[tree[q]])) {
//					tree[parent] = leftPlayer;
//				}
//				else {
//					tree[parent] = tree[q];
//				}
//				q = parent;
//			}
//		}
//
//	}
//}


#endif
