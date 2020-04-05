#ifndef _LINKEDQUEUEFROMEXTENDEDCHAIN_H
#define _LINKEDQUEUEFROMEXTENDEDCHAIN_H

#include "queue_adt.h"
#include "../DS6/extendedchain.h"

template<class T>
class linkedQueueFromExtendedChain : virtual public queue_adt<T>, virtual private ExtendedChain<T> {
public:
	linkedQueueFromExtendedChain() :ExtendedChain<T>() {}

	virtual ~linkedQueueFromExtendedChain() {}
	virtual bool empty() const override { return ExtendedChain<T>::empty(); }
	virtual int size() const override { return ExtendedChain<T>::size(); }
	virtual T& front() override { return ExtendedChain<T>::get(0); }
	virtual T& back() override { return ExtendedChain<T>::get(size()-1); }
	virtual void pop() override { ExtendedChain<T>::erase(0); }
	virtual void push(const T& theElement) override { ExtendedChain<T>::push_back(theElement); }
};

#endif