#pragma once
#ifndef _MAXDHEAP_H
#define _MAXDHEAP_H

#include <algorithm>
#include <xutility>

#include "../DS5/changelength.h"
#include "MaxPriorityQueue.h"

//Exercise 17
template<class T>
class MaxDHeap :public MaxPriorityQueue<T> {
	template <class T> friend std::istream& operator>>(std::istream& in, const MaxDHeap<T>& mh);
	template <class T> friend std::ostream& operator<<(std::ostream& out, const MaxDHeap<T>& mh);
public:
	explicit MaxDHeap(int theDegree, int theCapacity = 10) :degree(theDegree), arrayLength(theCapacity + 1), heapSize(0) { init(); }
	virtual ~MaxDHeap() { clear(); }

	virtual bool empty() const override { return heapSize == 0; }
	virtual int size() const override { return heapSize; }
	virtual const T& top() override;
	virtual void pop() override;
	virtual void push(const T& theElement) override;

	void input(std::istream& in);
	void output(std::ostream& out) const;

	void changeMax(const T& newElement);//Exercise 18
private:
	void init();
	void initialize();
	void clear();
	void bubbleOrArrange(int node);
	void arrange(int root);//arrange a subtree, move its root to a proper position
	void bubble(int node);
	int maxChild(int node);

	T* heap;
	int arrayLength;
	int heapSize;
	int degree;
};

template <class T>
std::istream& operator>>(std::istream& in, MaxDHeap<T>& mh) {
	mh.input(in);
	return(in);
}

template <class T>
std::ostream& operator<<(std::ostream& out, const MaxDHeap<T>& mh) {
	mh.output(out);
	return out;
}
template<class T>
const T& MaxDHeap<T>::top()
{
	if (heapSize == 0)
		throw std::out_of_range("emtpy heap");

	return heap[1];
}

template<class T>
void MaxDHeap<T>::pop()
{
	if (heapSize == 0)
		throw std::out_of_range("emtpy heap");

	heap[1].~T();

	heap[1] = heap[heapSize--];

	arrange(1);
}

template<class T>
void MaxDHeap<T>::push(const T& theElement)
{
	if (heapSize == arrayLength - 1) {
		changeLength1D(heap, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	heap[++heapSize] = theElement;
	bubble(heapSize);
}

template<class T>
void MaxDHeap<T>::input(std::istream& in) {
	T t;
	while (heapSize < arrayLength && in >> t) {
		heap[++heapSize] = t;
	}
	initialize();
}

template<class T>
void MaxDHeap<T>::output(std::ostream& out) const {
	for (int i = 1; i <= heapSize; ++i) {
		out << heap[i] << ' ';
	}
}

template<class T>
void MaxDHeap<T>::changeMax(const T& newElement)
{
	heap[1] = newElement;
	arrange(1);
}
template<class T>
void MaxDHeap<T>::init()
{
	heap = new T[arrayLength];
}


template<class T>
void MaxDHeap<T>::initialize()
{
	for (int root = heapSize / degree; root >= 1; --root) {
		arrange(root);
	}
}

template<class T>
void MaxDHeap<T>::clear()
{
	delete[]heap;
	heap = nullptr;
	arrayLength = 0;
	heapSize = 0;
}

template<class T>
void MaxDHeap<T>::bubbleOrArrange(int node) {
	if (node == 1) {
		arrange(node);
		return;
	}

	if (heap[node] > heap[(node + (degree - 2)) / degree])
		bubble(node);
	else
		arrange(node);
}

template<class T>
void MaxDHeap<T>::arrange(int root) {
	T rootElement = heap[root];

	int child = degree * (root - 1) + 2;
	int maxchild = maxChild(root);
	while (rootElement < heap[maxchild]) {
		heap[root] = heap[maxchild];
		root = maxchild;
		child = degree * (root - 1) + 2;
		if (child > heapSize)
			break;

		maxchild = maxChild(root);
	}
	heap[root] = rootElement;
}

template<class T>
void MaxDHeap<T>::bubble(int node) {
	int currentNode = node;
	T theElement = heap[node];
	int parent = (currentNode + (degree - 2)) / degree;
	while (currentNode != 1 && heap[parent] < theElement) {
		heap[currentNode] = heap[parent];
		currentNode = parent;
		parent = (currentNode + (degree - 2)) / degree;
	}
	heap[currentNode] = theElement;
}

template<class T>
int MaxDHeap<T>::maxChild(int node) {
	int firstchild = degree * (node - 1) + 2;
	int result = firstchild;
	for (int i = 1; i < degree; ++i) {
		if (firstchild + i <= heapSize && heap[result] < heap[firstchild + i])
			result = firstchild + i;
	}
	return result;
}

#endif
