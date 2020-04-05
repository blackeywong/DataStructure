#pragma once
#ifndef _TESTSETTREE_H
#define _TESTSETTREE_H
#include <random>
#include <ctime>
#include <iostream>
#include "SetTree.h"
/*
Exercise 63
Set Tree No Find rule, No Unite rule
10000 Time cost: 796 809 0.013
Set Tree Weight and Path Compaction
10000 Time cost: 825 827 0.002
Exercise 66
Set Tree Weight and Path Splitting
10000 Time cost: 834 835 0.001
Set Tree Weight and Path Splitting
10000 Time cost: 840 841 0.001
Set Tree Height and Path Compaction
10000 Time cost: 848 850 0.002
Set Tree Height and Path Splitting
10000 Time cost: 854 855 0.001
Set Tree Height and Path Splitting
10000 Time cost: 860 861 0.001

Exercise 63
Set Tree No Find rule, No Unite rule
100000 Time cost: 1020 4170 3.15
Set Tree Weight and Path Compaction
100000 Time cost: 4181 4197 0.016
Exercise 66
Set Tree Weight and Path Splitting
100000 Time cost: 4209 4227 0.018
Set Tree Weight and Path Splitting
100000 Time cost: 4237 4254 0.017
Set Tree Height and Path Compaction
100000 Time cost: 4264 4279 0.015
Set Tree Height and Path Splitting
100000 Time cost: 4290 4309 0.019
Set Tree Height and Path Splitting
100000 Time cost: 4318 4334 0.016

Exercise 63
Set Tree No Find rule, No Unite rule
1000000 Time cost: 1950 549449 547.499
Set Tree Weight and Path Compaction
1000000 Time cost: 549517 549762 0.245
Exercise 66
Set Tree Weight and Path Splitting
1000000 Time cost: 549828 550061 0.233
Set Tree Weight and Path Splitting
1000000 Time cost: 550124 550345 0.221
Set Tree Height and Path Compaction
1000000 Time cost: 550414 550681 0.267
Set Tree Height and Path Splitting
1000000 Time cost: 550761 551057 0.296
Set Tree Height and Path Splitting
1000000 Time cost: 551118 551329 0.211

Exercise 63
Set Tree Weight and Path Compaction
10000000 Time cost: 12978 17821 4.843
Exercise 66
Set Tree Weight and Path Splitting
10000000 Time cost: 18408 23203 4.795
Set Tree Weight and Path Splitting
10000000 Time cost: 23791 28661 4.87
Set Tree Height and Path Compaction
10000000 Time cost: 29247 33976 4.729
Set Tree Height and Path Splitting
10000000 Time cost: 34586 39392 4.806
Set Tree Height and Path Splitting
10000000 Time cost: 39973 44876 4.903

Exercise 63
Set Tree Weight and Path Compaction
100000000 Time cost: 119042 174990 55.948
Exercise 66
Set Tree Weight and Path Splitting
100000000 Time cost: 178506 234684 56.178
Set Tree Weight and Path Halving
100000000 Time cost: 237918 299043 61.125
Set Tree Height and Path Compaction
100000000 Time cost: 302522 362836 60.314
Set Tree Height and Path Splitting
100000000 Time cost: 366357 426403 60.046
Set Tree Height and Path Halving
100000000 Time cost: 429867 491213 61.346

Exercise 63
Set Tree Weight and Path Compaction
1000000000 Time cost: 1231540 1929888 698.348
Exercise 66
Set Tree Weight and Path Splitting
1000000000 Time cost: 1964162 2653858 689.696
Set Tree Weight and Path Halving
1000000000 Time cost: 2688448 3395122 706.674
Set Tree Height and Path Compaction
1000000000 Time cost: 3429456 4114014 684.558
Set Tree Height and Path Splitting
1000000000 Time cost: 4148103 4840698 692.595
Set Tree Height and Path Halving
1000000000 Time cost: 4875083 5584531 709.448
*/
struct Couple {
	int i;
	int j;
	Couple() {}
	Couple(int theI, int theJ) :i(theI), j(theJ) {}
};

class TestSetTree {
public:
	explicit TestSetTree(int theSize);
	~TestSetTree() { delete[]couples; size = 0; }
	void test(SetTree& t, SetTree::FIND_RULE find_rule, SetTree::UNITE_RULE unite_rule);
private:
	Couple* couples;
	int size;
};

TestSetTree::TestSetTree(int theSize) :size(theSize) {
	int lowBound = 2;
	int highBound = theSize + 1;
	std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));
	std::uniform_int_distribution<int> u(lowBound, highBound);

	couples = new Couple[size];
	for (int k = 0; k < size; ++k) {
		couples[k].i = u(e);
		couples[k].j = u(e);
	}
}

void TestSetTree::test(SetTree& t, SetTree::FIND_RULE find_rule, SetTree::UNITE_RULE unite_rule) {
	clock_t start, finish;
	double insertTime = 0.0;
	start = clock();
	for (int k = 0; k < size; ++k) {
		int rootA = t.find(couples[k].i, find_rule);
		int rootB = t.find(couples[k].j, find_rule);
		if (rootA != rootB) {
			t.unite(rootA, rootB, unite_rule);
		}
	}
	finish = clock();
	std::cout << size << " Time cost: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;
}

#endif