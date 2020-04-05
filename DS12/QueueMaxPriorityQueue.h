#pragma once
#ifndef _QUEUEMAXPRIORTYQUEUE_HSortedChainMaxPriorityQueue
#define _QUEUEMAXPRIORTYQUEUE_H

#include "MaxPriorityQueue.h"
#include "../DS9/extendedLinkedQueue.h"

template<class T>
class QueueMaxPriorityQueue : virtual public MaxPriorityQueue<T> {
	template<class T> friend std::ostream& operator<<(std::ostream& out, const QueueMaxPriorityQueue<T>& qmpq);
public:
	explicit QueueMaxPriorityQueue(int theMaxPriority);
	virtual ~QueueMaxPriorityQueue() { delete[]queues; pqSize = 0; }
	virtual bool empty() const override { return pqSize == 0; }
	virtual int size() const override { return pqSize; }
	virtual const T& top() override;
	virtual void pop() override;
	virtual void push(const T& theElement) override;
private:
	extendedLinkedQueue<T>* queues;
	int pqSize;
	int maxPriority;
	int curMaxPriority;
};

template<class T>
std::ostream& operator<<(std::ostream& out, const QueueMaxPriorityQueue<T>& qmpq) {
	for (int i = 1; i <= qmpq.maxPriority; ++i) {
		out << "Priority " << i << ": ";
		qmpq.queues[i].output(out);
		out << std::endl;
	}
	return out;
}

template<class T>
QueueMaxPriorityQueue<T>::QueueMaxPriorityQueue(int theMaxPriority):maxPriority(theMaxPriority),pqSize(0), curMaxPriority(0){
	queues = new extendedLinkedQueue<T>[maxPriority+1];
}

template<class T>
const T& QueueMaxPriorityQueue<T>::top() {
	if (empty())
		throw std::out_of_range("Empty queue");

		return queues[curMaxPriority].front();
}

template<class T>
void QueueMaxPriorityQueue<T>::pop() {
	if (empty())
		throw std::out_of_range("Empty queue");

	queues[curMaxPriority].pop();
	--pqSize;
}

template<class T>
void QueueMaxPriorityQueue<T>::push(const T& theElement) {
	queues[theElement.priority].push(theElement);
	++pqSize;
	if (theElement.priority > curMaxPriority)
		curMaxPriority = theElement.priority;
}

#endif