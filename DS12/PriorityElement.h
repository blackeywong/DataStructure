#pragma once
#ifndef _PRIORITYELEMENT_H
#define _PRIORITYELEMENT_H
#include <iostream>
template<class T>
struct PriorityElement {
	int priority;
	T data;

	PriorityElement() {}
	PriorityElement(int thePriority, T theData) :priority(thePriority), data(theData){}
	PriorityElement(const PriorityElement& right) { priority = right.priority; data = right.data; }
	PriorityElement<T>& operator=(const PriorityElement& right) { priority = right.priority; data = right.data; return *this; }

	bool operator==(const PriorityElement& right) const { return data == right.data; }
	bool operator!=(const PriorityElement& right) const { return data != right.data; }
	bool operator<(const PriorityElement& right) const { return priority < right.priority; }
	bool operator<=(const PriorityElement& right) const { return priority <= right.priority; }
};

template<class T>
std::istream& operator>>(std::istream& in, PriorityElement<T>& e) {
	in >> e.priority >> e.data;
	return in;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const PriorityElement<T>& e) {
	out << e.priority << ':' << e.data;
	return out;
}


#endif
