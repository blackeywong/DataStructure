#pragma once
#ifndef _DS12_APPLICATION_H
#define _DS12_APPLICATION_H
//Heap Sort
template<class T>
void arrange(T* list, int listSize, int node) {
	T top = list[node];
	int child = node * 2 + 1;
	using std::swap;
	while (child < listSize) {
		if (child < listSize - 1 && list[child] < list[child + 1]) {
			++child;
		}
		if (list[node] >= list[child])
			break;

		swap(list[node], list[child]);
		node = child;
		child = node * 2 + 1;
	}
	list[(child - 1) / 2] = top;
}

template<class T>
void heapSort(T* list, int listSize) {
	//arrange from half to the begin
	for (int i = (listSize - 2) / 2; i >= 0; --i) {
		arrange(list, listSize, i);
	}
	int treeSize = listSize;

	//then pop from the top and put at the end
	for (int i = listSize - 1; i >= 0; --i) {
		T top = list[0];
		list[0] = list[i];
		--treeSize;
		arrange(list, treeSize, 0);
		list[i] = top;
	}
}

//dHeap Sort, Exercise 28
/*
10000 Time cost for degree 2: 334 352 0.018
10000 Time cost for degree 3 : 354 366 0.012
10000 Time cost for degree 4 : 367 377 0.01
10000 Time cost for degree 5 : 377 387 0.01
10000 Time cost for degree 6 : 389 399 0.01

100000 Time cost for degree 2: 321 553 0.232
100000 Time cost for degree 3: 554 715 0.161
100000 Time cost for degree 4: 717 860 0.143
100000 Time cost for degree 5: 862 991 0.129
100000 Time cost for degree 6: 993 1125 0.132

1000000 Time cost for degree 2: 377 3545 3.168
1000000 Time cost for degree 3: 3546 5637 2.091
1000000 Time cost for degree 4: 5639 7389 1.75
1000000 Time cost for degree 5: 7391 8914 1.523
1000000 Time cost for degree 6: 8915 10443 1.528

10000000 Time cost for degree 2: 492 34692 34.2
10000000 Time cost for degree 3: 34694 57288 22.594
10000000 Time cost for degree 4: 57289 77055 19.766
10000000 Time cost for degree 5: 77056 94609 17.553
10000000 Time cost for degree 6: 94610 111676 17.066

100000000 Time cost for degree 2: 1651 381068 379.417
100000000 Time cost for degree 3: 381070 644212 263.142
100000000 Time cost for degree 4: 644237 854695 210.458
100000000 Time cost for degree 5: 854697 1048721 194.024
100000000 Time cost for degree 6: 1048722 1251483 202.761
*/
template<class T>
void dheapArrange(T* list, int listSize, int node, int degree) {
	T top = list[node];
	int child = node * degree + 1;
	using std::swap;
	while (child < listSize) {
		int maxchild = child;
		for (int i = 1; i < degree; ++i) {
			++child;
			if (child < listSize && list[maxchild] < list[child]) {
				maxchild = child;
			}
		}
		if (list[node] >= list[maxchild])
			break;

		swap(list[node], list[maxchild]);
		node = maxchild;
		child = node * degree + 1;
	}
	list[(child - 1) / degree] = top;
}

template<class T>
void dheapSort(T* list, int listSize, int degree) {
	//arrange from half to the begin
	for (int i = (listSize - 2) / degree; i >= 0; --i) {
		dheapArrange(list, listSize, i, degree);
	}
	int treeSize = listSize;

	//then pop from the top and put at the end
	for (int i = listSize - 1; i >= 0; --i) {
		T top = list[0];
		list[0] = list[i];
		--treeSize;
		dheapArrange(list, treeSize, 0, degree);
		list[i] = top;
	}
}

struct JobNode {
	int id;
	int time;
	operator int() const { return time; }
	JobNode():id(0), time(0) {}
	JobNode(int theId, int theTime) :id(theId), time(theTime) {}
};

struct MachineNode {
	int id;
	int avail;
	operator int() const { return avail; }
	MachineNode() :id(0), avail(0) {}
	MachineNode(int theId, int theAvail) :id(theId), avail(theAvail) {}
};

void makeSchedule(JobNode a[], int n, int m);
void makeSchedule2(JobNode a[], int n, int m);//Exercise 33

struct ItemNode {
	int id;
	int space;
	operator int() const { return space; }
	ItemNode() :id(0), space(0) {}
	ItemNode(int theId, int theSpace) :id(theId), space(theSpace) {}
};

struct ContainerNode {
	int id;
	int avail;
	operator int() const { return avail; }
	ContainerNode() :id(0), avail(0) {}
	ContainerNode(int theId, int theAvail) :id(theId), avail(theAvail) {}
};

bool packItems(ItemNode a[], int n, int m, int c);//Exercise 36

//Exercise 43
class HuffmanCompress {
public:
	HuffmanCompress(int theCharNum = 256) :charNum(theCharNum) { init(); }
	~HuffmanCompress() { delete[] weight; delete[]elements; }
	bool compress(const std::string& inFile, const std::string& outFile);
	bool uncompress(const std::string& inFile, const std::string& outFile);
private:
	void init();

	int charNum;
	unsigned int* weight;
	unsigned int* elements;
};

bool huffmanCompress(const std::string& inFile, const std::string& outFile);
bool huffmanUncompress(const std::string& inFile, const std::string& outFile);

//Exercise 44
bool huffmanCompress512(const std::string& inFile, const std::string& outFile);
bool huffmanUncompress512(const std::string& inFile, const std::string& outFile);
#endif