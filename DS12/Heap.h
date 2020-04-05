#pragma once
#ifndef _HEAP_H
#define _HEAP_H

#include <algorithm>
#include <xutility>
#include <functional>

#include "../DS5/changelength.h"
#include "MaxPriorityQueue.h"

template<class T>
class Heap:public MaxPriorityQueue<T> {
	template <class T> friend std::istream& operator>>(std::istream& in, const Heap<T>& mh);
	template <class T> friend std::ostream& operator<<(std::ostream& out, const Heap<T>& mh);
public:
	explicit Heap(int theCapacity = 10, bool isMaxHeap = true):arrayLength(theCapacity + 1), maxHeap(isMaxHeap), heapSize(0) { init(); }
	Heap(T* array, int theArrayLength, bool isMaxHeap = true) :arrayLength(theArrayLength), maxHeap(isMaxHeap), heapSize(theArrayLength) {//for Huffman tree
		init(); 
		std::copy(array + 1, array + arrayLength + 1, heap + 1);
		initialize();
	}
	virtual ~Heap() { clear(); }

	Heap(const Heap<T>& right);//Exercise 11

	virtual bool empty() const override { return heapSize == 0; }
	virtual int size() const override { return heapSize;}
	virtual const T& top() override;
	virtual void pop() override;
	virtual void push(const T& theElement) override;

	void input(std::istream& in);
	void output(std::ostream& out) const;

	void changeTop(const T& newElement);//Exercise 12, Exercise 33
	T remove(int node);//Exercise 13
public:
	class Iterator;//Exercise 14
	friend class Iterator;
	Iterator begin() { return Iterator(*this); }
	Iterator end() { return Iterator(); }

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

	bool maxHeap;
	//bool (*compFunc)(const T& t1, const T& t2);
	std::function<bool(const T&, const T&)> compFunc;
};

template <class T> 
std::istream& operator>>(std::istream& in, Heap<T>& mh) {
	mh.input(in);
	return(in);
}

template <class T> 
std::ostream& operator<<(std::ostream& out, const Heap<T>& mh) {
	mh.output(out);
	return out;
}

template <class T>
Heap<T>::Heap(const Heap<T>& right):arrayLength(right.arrayLength), heapSize(right.heapSize) {
	init();
	std::copy(right.heap+1, right.heap+1+heapSize, heap+1);
}

template<class T>
const T& Heap<T>::top()
{
	if (heapSize == 0)
		throw std::out_of_range("emtpy heap");

	return heap[1];
}

template<class T>
void Heap<T>::pop()
{
	if (heapSize == 0)
		throw std::out_of_range("emtpy heap");

	heap[1].~T();

	heap[1] = heap[heapSize--];

	arrange(1);
}

template<class T>
void Heap<T>::push(const T& theElement)
{
	if (heapSize == arrayLength - 1) {
		changeLength1D(heap, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	heap[++heapSize] = theElement;
	bubble(heapSize);
}

template<class T>
void Heap<T>::input(std::istream& in) {
	T t;
	while (heapSize < arrayLength && in >> t) {
		heap[++heapSize] = t;
	}
	initialize();
}

template<class T>
void Heap<T>::output(std::ostream& out) const{
	for (int i = 1; i <= heapSize; ++i) {
		out << heap[i] << ' ';
	}
}

template<class T>
void Heap<T>::changeTop(const T& newElement)
{
	int root = 1, child = 2;
	while (child <= heapSize) {
		if (child < heapSize && compFunc(heap[child], heap[child + 1])) {
			++child;
		}

		if (! compFunc(newElement, heap[child]))
			break;


		heap[root] = heap[child];
		root = child;
		child *= 2;
	}
	heap[child / 2] = newElement;
}

template<class T>
T Heap<T>::remove(int node) {
	T removeElement = heap[node];

	heap[node] = heap[heapSize--];
	bubbleOrArrange(node);

	return removeElement;
}

template<class T>
void Heap<T>::init()
{
	heap = new T[arrayLength+1];
	if (maxHeap) {
		compFunc = std::less<T>();
	}
	else {
		compFunc = std::greater<T>();
	}
}


template<class T>
void Heap<T>::initialize()
{
	for (int root = heapSize / 2; root >= 1; --root) {
		arrange(root);
	}
}

template<class T>
void Heap<T>::clear()
{
	delete[]heap;
	heap = nullptr;
	arrayLength = 0;
	heapSize = 0;
}

template<class T>
void Heap<T>::bubbleOrArrange(int node) {
	if (node == 1) {
		arrange(node);
		return;
	}

	if (compFunc(heap[node / 2], heap[node]))
		bubble(node);
	else
		arrange(node);

}

template<class T>
void Heap<T>::arrange(int root) {
	T rootElement = heap[root];

	int child = 2 * root;
	while (child <= heapSize) {
		if (child < heapSize && compFunc(heap[child], heap[child + 1])) {
			++child;
		}

		if (! compFunc(rootElement, heap[child]))
			break;

		heap[child / 2] = heap[child];
		child *= 2;
	}
	heap[child / 2] = rootElement;
}

template<class T>
void Heap<T>::bubble(int node) {
	int currentNode = node;
	T theElement = heap[node];
	while (currentNode != 1 && compFunc(heap[currentNode / 2], theElement)) {
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}

	heap[currentNode] = theElement;
}

template<class T>
class Heap<T>::Iterator {
public:
	typedef std::forward_iterator_tag iterator_capacity;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;

	Iterator() { mh = nullptr; node = 0; }
	explicit Iterator(Heap<T>& h) { mh = &h; node = 1; }
	Iterator(const Iterator& it) { mh = it.mh; node = it.node; }

	T& operator*() const { return mh->heap[node]; }
	T* operator->() const { return &mh->heap[node]; }

	Iterator& operator++() { 
		if (node == mh->heapSize)
			node = 0;
		else
			++node;
		return *this;
	}
	Iterator operator++(int) { Iterator old = *this; operator++(); return old; }

	bool operator!=(const Iterator& right) const { return node != right.node; }
	bool operator==(const Iterator& right) const { return node == right.node; }
	
	void swap(Iterator& right) { using std::swap; swap(heap[node], right.heap[right.node]); }
private:
	Heap<T>* mh;
	int node;

};

template<class T> 
void swap(typename Heap<T>::Iterator& it1, typename Heap<T>::Iterator& it2) { it1.swap(it2); }


#endif
