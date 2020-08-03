#ifndef _DS14_APPLICATION_H
#define _DS14_APPLICATION_H

#include<ctime>
#include<random>

#include "../DS12/DS12_Application.h"
#include "../DS13/DS13_Application.h"
#include "BinarySearchTree.h"
#include "../DS12/Heap.h"
#include "../DS10/HashChain.h"


///////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void BSTSort(T* arr, int size) {//Exercise 10
	BinarySearchTree<int, int> bst;
	for (int i = 0; i < size; ++i) {
		bst.insert(std::pair<int, T>(arr[i], arr[i]));
	}

	int i = 0;
	auto func = [&arr, &i](BinaryTreeNode<std::pair<int, T>>* node) {arr[i++] = node->element.first; };
	bst.inOrder(func);
}

template<class T>
void bubbleSort(T* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		bool swapped = false;
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1]) {
				using std::swap;
				swap<T>(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
	}
}

template<class T>
void insertionSort(T* arr, int size) {
	for (int i = 1; i < size; ++i) {
		T t = arr[i];
		int j;
		for (j = i - 1; j >= 0 && t < arr[j]; --j) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = t;
	}
}

template<class T>
void selectionSort(T* arr, int size) {
	bool sorted = false;
	for (int i = size; !sorted && (i > 1); --i) {
		int indexOfMax = 0;
		sorted = true;
		for (int j = 1; j < i; ++j) {
			if (arr[indexOfMax] <= arr[j]) {
				indexOfMax = j;
			}
			else {
				sorted = false;
			}
			using std::swap;
			swap(arr[indexOfMax], arr[i - 1]);
		}
	}
}

template<class T>
void rankSort(T arr[], int n) {
	int* rank = new int[n];
	for (int i = 0; i < n; ++i) {
		rank[i] = 0;
	}
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (arr[j] <= arr[i]) {
				++rank[i];
			}
			else {
				++rank[j];
			}

		}
	}

	for (int i = 0; i < n; ++i) {
		while (rank[i] != i) {
			int t = rank[i];
			using std::swap;
			swap(arr[i], arr[t]);
			swap(rank[i], rank[t]);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum SORTING_METHOD { INSERTION_SORT, SELECTION_SORT, RANK_SORT, BUBBLE_SORT, HEAP_SORT, WT_SORT, BST_SORT };
template<class T>
class TestSorting {
public:
	TestSorting(int theSize);
	~TestSorting() { delete[]objects; size = 0; }
	void testSort(SORTING_METHOD method);
private:
	T* objects;
	int size;
};

template<class T>
TestSorting<T>::TestSorting(int theSize)
{
	size = theSize;
	int lowBound = 1;
	int highBound = size +1;
	std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));
	std::uniform_int_distribution<int> u(lowBound, highBound);

	objects = new T[size+1];
	for (int i = 0; i < size+1; ++i) {
		objects[i] = i+1;
	}
	for (int i = 0; i < size+1; ++i) {
		int pos1 = u(e);
		int pos2 = u(e);
		using std::swap;
		swap(objects[pos1 - 1],objects[pos2 - 1]);
	}
}

template<class T>
void TestSorting<T>::testSort(SORTING_METHOD method)
{
	clock_t start, finish;
	double insertTime = 0.0;

	T* toSort = new T[size+1];
	std::copy(objects, objects + size+1, toSort);

	start = clock();
	switch (method) {
	case INSERTION_SORT: insertionSort(toSort, size); break;
	case SELECTION_SORT: selectionSort(toSort, size); break;
	case RANK_SORT: rankSort(toSort, size); break;
	case BUBBLE_SORT: bubbleSort(toSort, size); break;
	case HEAP_SORT: heapSort(toSort, size); break;
	case WT_SORT: winnerTreeSort(toSort, size); break;//Winner Tree
	case BST_SORT: BSTSort(toSort, size); break;//Binary Search Tree
	}
	finish = clock();
	std::cout << size << " Time cost: " << (double)(finish - start) / CLK_TCK << std::endl;
}

//insertion sort          1000 Time cost : 0.001
//selection sort          1000 Time cost : 0.067
//rank sort               1000 Time cost : 0.003
//Bubble sort             1000 Time cost : 0.029
//heap sort               1000 Time cost : 0.001
//winner tree sort        1000 Time cost : 0.008
//binary search tree sort 1000 Time cost : 0.002
//insertion sort          10000 Time cost : 0.076
//selection sort          10000 Time cost : 6.984
//rank sort               10000 Time cost : 0.278
//Bubble sort             10000 Time cost : 3.508
//heap sort               10000 Time cost : 0.019
//winner tree sort        10000 Time cost : 0.134
//binary search tree sort 10000 Time cost : 0.023
//insertion sort          100000 Time cost : 7.609
//selection sort          100000 Time cost : 647.456
//rank sort               100000 Time cost : 27.544
//Bubble sort             100000 Time cost : 306.994
//heap sort               100000 Time cost : 0.23
//winner tree sort        100000 Time cost : 1.474
//binary search tree sort 100000 Time cost : 0.239
//insertion sort          1000000 Time cost : 777.796
//heap sort               1000000 Time cost : 3.112
//winner tree sort        1000000 Time cost : 20.1
//binary search tree sort 1000000 Time cost : 3.664
//heap sort               10000000 Time cost : 36.448
//winner tree sort        10000000 Time cost : 224.975
//binary search tree sort 10000000 Time cost : 45.448
//heap sort               100000000 Time cost : 472.85
//binary search tree sort 100000000 Time cost : 692.736

////////////////////////////////////////////////////////////////////////////////

void averageHeight(int n);//Exercise 13
//n is: 100; average height: 12; goal: 14
//n is: 500; average height: 20.28; goal: 18
//n is: 1000; average height: 25; goal: 20
//n is: 10000; average height: 44.77; goal: 28
//n is: 20000; average height: 57.09; goal: 30
//n is: 50000; average height: 69.54; goal: 32


////////////////////////////////////////////////////////////////////////////////////
enum STORE_TYPE { MAX_HEAP, BINARY_SEARCH_TREE };
//Exercise 15-2
template<class K, class E>
class TestInsertEraseMax {
public:
	explicit TestInsertEraseMax(int theSize);
	~TestInsertEraseMax() { delete[]keys; delete[]values; delete[]operations; size = 0; }
	void testInsertEraseMax(STORE_TYPE type);
private:
	K* keys;
	E* values;
	int* operations;
	int size;
	int ops;
};

template<class K, class E>
TestInsertEraseMax<K, E>::TestInsertEraseMax(int theSize) :size(theSize) {
	ops = 1000000;
	int lowBound = 1;
	int highBound = theSize;
	std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));
	std::uniform_int_distribution<int> u(lowBound, highBound);

	keys = new K[size + 1];
	values = new E[size + 1];
	operations = new int[ops + 1];
	for (int k = 1; k <= size; ++k) {
		keys[k] = u(e);
		values[k] = keys[k];
	}

	for (int k = 1; k <= ops; ++k) {
		operations[k] = u(e);
	}
}

template<class K, class E>
void TestInsertEraseMax<K, E>::testInsertEraseMax(STORE_TYPE type) {
	clock_t start, finish;
	double insertTime = 0.0;
	if (type == MAX_HEAP) {
		Heap<E> heap(size, true);
		for (int i = 1; i <= size; ++i) {
			heap.push(values[i]);
		}
		start = clock();
		for (int i = 1; i <= ops; ++i) {
			if (operations[i] % 2 == 0) {
				heap.push(operations[i]);
			}
			else {
				heap.pop();
			}
		}
		finish = clock();
	}
	else if (type == BINARY_SEARCH_TREE) {
		BinarySearchTree<K, E> bst;
		for (int i = 1; i <= size; ++i) {
			bst.insert(std::pair<K, E>(keys[i], values[i]));
		}
		start = clock();
		for (int i = 1; i <= ops; ++i) {
			if (operations[i] % 2 == 0) {
				bst.insert(std::pair<K, E>(operations[i], operations[i]));
			}
			else {
				bst.eraseMax();
			}
		}
		finish = clock();
	}

	std::cout << size << " Time cost: " << (double)(finish - start) / CLK_TCK << std::endl;
}
//Exercise 15_2, 1000000 operations
//100 Time cost : 5.996
//100 Time cost : 0.341
//1000 Time cost : 10.034
//1000 Time cost : 0.404
//10000 Time cost : 13.26
//10000 Time cost : 0.392
//100000 Time cost : 15.136
//100000 Time cost : 0.427
//1000000 Time cost : 15.363
//1000000 Time cost : 0.918
//10000000 Time cost : 15.415
//10000000 Time cost : 1.671
//100000000 Time cost : 18.264
//100000000 Time cost : 2.519
//1000000000 Time cost : 25.58(heap)

//Exercise 23
template<class T>
void arrayHistogramming(T* arr, int n) {
	sort(arr, arr + n);
	std::cout << "\tkey\t\tcount" << std::endl;
	T ele = arr[0];
	int count = 1;
	for (int i = 1; i < n; ++i) {
		if (arr[i] == ele) {
			++count;
		}
		else {
			std::cout << "\t" << ele << "\t\t" << count << std::endl;
			ele = arr[i];
			count = 1;
		}
	}
	std::cout << "\t" << ele << "\t\t" << count << std::endl;
}


template<class T>
void hashHistogramming(T* arr, int n) {
	HashChain<T, int> hc(23);
	for (int i = 0; i < n; ++i) {
		auto p = hc.find(arr[i]);
		if (p) {
			++p->second;
		}
		else {
			hc.insert({arr[i],1});
		}
	}

	hc.output(std::cout);
	std::cout << std::endl;
}

template<class T>
void bstHistogramming(T* arr, int n) {
	BinarySearchTree<T, int> bst;
	for (int i = 0; i < n; ++i) {
		auto p = bst.find(arr[i]);
		if (p) {
			++p->second;
		}
		else {
			bst.insert({ arr[i],1 });
		}
	}

	bst.output(std::cout);
	std::cout << std::endl;
}

void bestFitPack(int* objectSize, int numberOfObjects, int binCapacity);
void bestFitPack2(int* objectSize, int numberOfObjects, int binCapacity);//Exercise 25.2

void crossingDistribution(int theC[], int n);
void setK(int theC[], int k[], int n);

//Exercise28
void crossingDistribution2(int theC[], int n);
void setK2(int theC[], int k[], int n);

//Exercise29
void indexText(const std::string& inFile, const std::string& outFile);
std::ostream& operator<<(std::ostream& out, std::set<int>& v);
std::ostream& operator<<(std::ostream& out, std::pair<std::string, std::set<int>>& p);
#endif