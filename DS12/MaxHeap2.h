#pragma once
#ifndef _MAXHEAP2_H
#define _MAXHEAP2_H

#include <algorithm>
#include <xutility>

#include "../DS5/changelength.h"
#include "MaxPriorityQueue.h"
//Exercise 16
template<class T>
class MaxHeap2 :public MaxPriorityQueue<T> {
	template <class T> friend std::istream& operator>>(std::istream& in, const MaxHeap2<T>& mh);
	template <class T> friend std::ostream& operator<<(std::ostream& out, const MaxHeap2<T>& mh);
public:
	MaxHeap2(T theMaxElement, T theMinElement, int theCapacity = 10) :arrayLength(theCapacity * 2 + 2), heapSize(0), maxElement(theMaxElement), minElement(theMinElement) { init(); }
	virtual ~MaxHeap2() { clear(); }

	virtual bool empty() const override { return heapSize == 0; }
	virtual int size() const override { return heapSize; }
	virtual const T& top() override;
	virtual void pop() override;
	virtual void push(const T& theElement) override;

	void input(std::istream& in);
	void output(std::ostream& out) const;

private:
	void init();
	void initialize();
	void clear();
	void bubbleOrArrange(int node);
	void arrange(int root);//arrange a subtree, move its root to a proper position
	void bubble(int node);

	T* heap;
	int arrayLength;
	int heapSize;
	T maxElement;
	T minElement;
};

template <class T>
std::istream& operator>>(std::istream& in, MaxHeap2<T>& mh) {
	mh.input(in);
	return(in);
}

template <class T>
std::ostream& operator<<(std::ostream& out, const MaxHeap2<T>& mh) {
	mh.output(out);
	return out;
}

template<class T>
const T& MaxHeap2<T>::top()
{
	if (heapSize == 0)
		throw std::out_of_range("emtpy heap");

	return heap[1];
}

template<class T>
void MaxHeap2<T>::pop()
{
	if (heapSize == 0)
		throw std::out_of_range("emtpy heap");

	heap[1].~T();

	heap[1] = heap[heapSize];
	heap[heapSize--] = minElement;
	arrange(1);
}

template<class T>
void MaxHeap2<T>::push(const T& theElement)
{
	if (heapSize == arrayLength / 2 - 1) {
		changeLength1D(heap, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	heap[++heapSize] = theElement;
	heap[2 * heapSize] = minElement;
	heap[2 * heapSize + 1] = minElement;
	bubble(heapSize);
}

template<class T>
void MaxHeap2<T>::input(std::istream& in) {
	T t;
	while (heapSize < arrayLength && in >> t) {
		heap[++heapSize] = t;
	}
	initialize();
}

template<class T>
void MaxHeap2<T>::output(std::ostream& out) const {
	for (int i = 1; i <= heapSize; ++i) {
		out << heap[i] << ' ';
	}
}

template<class T>
void MaxHeap2<T>::init()
{
	heap = new T[arrayLength];
	heap[0] = maxElement;
	for (int i = arrayLength / 2; i < arrayLength; ++i)
		heap[i] = minElement;
}


template<class T>
void MaxHeap2<T>::initialize()
{
	for (int root = heapSize / 2; root >= 1; --root) {
		arrange(root);
	}
}

template<class T>
void MaxHeap2<T>::clear()
{
	delete[]heap;
	heap = nullptr;
	arrayLength = 0;
	heapSize = 0;
}

template<class T>
void MaxHeap2<T>::bubbleOrArrange(int node) {
	if (node == 1) {
		arrange(node);
		return;
	}

	if (heap[node] > heap[node / 2])
		bubble(node);
	else
		arrange(node);
}

template<class T>
void MaxHeap2<T>::arrange(int root) {
	T rootElement = heap[root];

	int child = 2 * root;
	while (rootElement < heap[child] || rootElement < heap[child + 1]) {
		if (heap[child] < heap[child + 1]) {
			++child;
		}

		heap[child / 2] = heap[child];
		child *= 2;
	}
	heap[child / 2] = rootElement;
}

template<class T>
void MaxHeap2<T>::bubble(int node) {
	int currentNode = node;
	T theElement = heap[node];
	while (/*currentNode != 1 && */heap[currentNode / 2] < theElement) {//since heap[0] is maxElement, the loop can always stop at the root
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}
	heap[currentNode] = theElement;
}

#endif
