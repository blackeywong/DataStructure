#ifndef _DS13_APPLICATIONS_H
#define _DS13_APPLICATIONS_H

#include <iostream>
#include <random>
#include <ctime>

#include "CompleteWinnerTree.h"
#include "CompleteLoserTree.h"
#include "../DS12/DS12_Application.h"


//Exercise 8
template<class T>
void winnerTreeSort(T* thePlayer, int theNumberOfPlayers) {
	CompleteWinnerTree<T> cwt(thePlayer, theNumberOfPlayers);

	for (int i = 1; i <= theNumberOfPlayers; ++i) {
		std::cout << cwt.winner() << ' ';
		thePlayer[cwt.winnerNum()] = INT_MAX;
		cwt.rePlay(cwt.winnerNum());
	}
	std::cout << std::endl;
}

//Exercise 22
template<class T>
void loserTreeSort(T* thePlayer, int theNumberOfPlayers) {
	CompleteLoserTree<T> clt(thePlayer, theNumberOfPlayers);

	for (int i = 1; i <= theNumberOfPlayers; ++i) {
		std::cout << clt.winner() << ' ';
		thePlayer[clt.winnerNum()] = INT_MAX;
		clt.rePlay(clt.winnerNum());
	}
	std::cout << std::endl;
}

struct BinType {
	int unusedCapacity;
	//BinType(int capacity) :unusedCapacity(capacity) {}
	bool operator<=(const BinType& right) const { return unusedCapacity <= right.unusedCapacity; }
	bool operator>=(const BinType& right) const { return unusedCapacity >= right.unusedCapacity; }
};

bool greater_equal(const BinType& bt1, const BinType& bt2);
bool less_equal(const BinType& bt1, const BinType& bt2);

void firstFitPack(int* objectSize, int numberOfObjects, int binCapacity);
void firstFitPack2(int* objectSize, int numberOfObjects, int binCapacity);//Excecise 25
void firstFitPack3(int* objectSize, int numberOfObjects, int binCapacity);//Excecise 26
void firstFitDecreasingPack(int* objectSize, int numberOfObjects, int binCapacity);//Excecise 28
void worstFitPack(int* objectSize, int numberOfObjects, int binCapacity);//Excecise 28
void nextFitPack(int* objectSize, int numberOfObjects, int binCapacity);//Excecise 28
void lastFitPack(int* objectSize, int numberOfObjects, int binCapacity);//Excecise 30

enum PACK_METHOD { FIRST_FIT, FIRST_FIT2, FIRST_FIT_DECREASING, WORST_FIT,  NEXT_FIT, LAST_FIT};


class TestPacking {
public:
	explicit TestPacking(int theSize);
	~TestPacking() { delete[]objects; size = 0; }
	void test(PACK_METHOD method);
private:
	int* objects;
	int size;
};
//Exercise 25
//First Fit : 1000 Time cost : 0.008
//First Fit2 : 1000 Time cost : 0.009
//First Fit: 10000 Time cost: 0.131
//First Fit2 : 10000 Time cost : 0.111
//First Fit : 100000 Time cost : 1.539
//First Fit2 : 100000 Time cost : 1.392
//First Fit : 1000000 Time cost : 17.081
//First Fit2 : 1000000 Time cost : 16.624
//First Fit : 10000000 Time cost : 172.126
//First Fit2 : 10000000 Time cost : 176.43

#endif
