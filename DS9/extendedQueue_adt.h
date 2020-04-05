#pragma once
#ifndef _EXTENDEDQUEUE_ADT_H
#define _EXTENDEDQUEUE_ADT_H
#include "queue_adt.h"
#include <iostream>

template<class T>
class extendedQueue_adt : public queue_adt<T> {
public:
	virtual std::istream& input(std::istream& in) = 0;
	virtual std::ostream& output(std::ostream& out) = 0;
	virtual void split(extendedQueue_adt<T>& q1, extendedQueue_adt<T>& q2) = 0;
	virtual void merge(extendedQueue_adt<T>& q1, extendedQueue_adt<T>& q2) = 0;
};


#endif