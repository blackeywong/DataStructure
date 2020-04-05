#pragma once
#ifndef _TESTPRIORITYQUEUE_H
#define _TESTPRIORITYQUEUE_H
#include <random>
#include <ctime>
#include <iostream>
#include "MaxPriorityQueue.h"
/*
Performance
Max Heap
10000 Time cost: 11 15 0.004
Max Heap 2
10000 Time cost: 19 22 0.003
Max DHeap degree = 2
10000 Time cost: 25 38 0.013
Max DHeap degree = 3
10000 Time cost: 41 48 0.007
Max DHeap degree = 4
10000 Time cost: 51 57 0.006
Max Height-biased Leftiest Tree
10000 Time cost: 82 136 0.054
Max Weight-biased Leftiest Tree
10000 Time cost: 159 204 0.045
Max Height-biased Leftiest Tree With Remove Node
10000 Time cost: 219 264 0.045
Max Height-biased Leftiest Tree With Min Element
10000 Time cost: 281 325 0.044

Max Heap
100000 Time cost: 65 108 0.043
Max Heap 2
100000 Time cost: 118 161 0.043
Max DHeap degree = 2
100000 Time cost: 164 276 0.112
Max DHeap degree = 3
100000 Time cost: 282 368 0.086
Max DHeap degree = 4
100000 Time cost: 379 457 0.078
Max Height-biased Leftiest Tree
100000 Time cost: 671 1306 0.635
Max Weight-biased Leftiest Tree
100000 Time cost: 1446 2066 0.62
Max Height-biased Leftiest Tree With Remove Node
100000 Time cost: 2203 2871 0.668
Max Height-biased Leftiest Tree With Min Element
100000 Time cost: 3013 3663 0.65

Max Heap
1000000 Time cost: 649 1160 0.511
Max Heap 2
1000000 Time cost: 1188 1722 0.534
Max DHeap degree = 2
1000000 Time cost: 1735 3098 1.363
Max DHeap degree = 3
1000000 Time cost: 3113 4149 1.036
Max DHeap degree = 4
1000000 Time cost: 4164 5113 0.949
Max Height-biased Leftiest Tree
1000000 Time cost: 7261 16506 9.245
Max Weight-biased Leftiest Tree
1000000 Time cost: 17920 27196 9.276
Max Height-biased Leftiest Tree With Remove Node
1000000 Time cost: 28957 38258 9.301
Max Height-biased Leftiest Tree With Min Element
1000000 Time cost: 39985 49378 9.393

Max Heap
10000000 Time cost: 6030 13598 7.568
Max Heap 2
10000000 Time cost: 13636 21216 7.58
Max DHeap degree = 2
10000000 Time cost: 21233 41432 20.199
Max DHeap degree = 3
10000000 Time cost: 41454 55839 14.385
Max DHeap degree = 4
10000000 Time cost: 55859 68842 12.983
Max Height-biased Leftiest Tree
10000000 Time cost: 81703 199938 118.235
Max Weight-biased Leftiest Tree
10000000 Time cost: 212487 321994 109.507
Max Height-biased Leftiest Tree With Remove Node
10000000 Time cost: 334856 456624 121.768
Max Height-biased Leftiest Tree With Min Element
10000000 Time cost: 469568 589601 120.033
*/
template<class T>
class TestPriorityQueue {
public:
	explicit TestPriorityQueue<T>(int theSize);
	~TestPriorityQueue<T>() { delete[]values; size = 0; }
	void test(MaxPriorityQueue<T>& heap);

	T* getValues() { return values; }
private:
	T* values;
	int size;
};

template<class T>
TestPriorityQueue<T>::TestPriorityQueue(int theSize) :size(theSize) {
	int lowBound = 1;
	int highBound = INT_MAX - 1;
	std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));
	std::uniform_int_distribution<int> u(lowBound, highBound);

	values = new T[size];
	for (int k = 0; k < size; ++k) {
		values[k] = u(e);
	}
}

template<class T>
void TestPriorityQueue<T>::test(MaxPriorityQueue<T>& heap) {
	clock_t start, finish;
	double insertTime = 0.0;
	start = clock();
	for (int k = 0; k < size; ++k) {
		heap.push(values[k]);
	}
	for (int k = 0; k < size; ++k) {
		if (values[k] % 2 == 0)
			heap.top();
		heap.pop();
	}
	finish = clock();
	std::cout << size << " Time cost: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;
}

#endif