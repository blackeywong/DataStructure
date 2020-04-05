#pragma once
#ifndef _EXTENDEDDEFRIVEDARRAYSTACK_H
#define _EXTENDEDDEFRIVEDARRAYSTACK_H
#include "../DS5/arraylist.h"
#include "extendedStack.h"

//Exercise 7.3
//template<class T> std::istream& operator>>(std::istream& in, extendedDerivedArrayStack<T>& st);
//template<class T> std::ostream& operator<<(std::ostream& out, const extendedDerivedArrayStack<T>& st);

template<class T>
class extendedDerivedArrayStack : private ArrayList<T>, public extendedStack<T> {
	template<class T>
	friend std::istream& operator>>(std::istream& in, extendedDerivedArrayStack<T>& st);
	template<class T>
	friend std::ostream& operator<<(std::ostream& out, const extendedDerivedArrayStack<T>& st);
public:
	extendedDerivedArrayStack<T>(int initialCapacity = 10) : ArrayList<T>::ArrayList(initialCapacity) {}
	virtual bool empty() const override { return ArrayList<T>::empty(); }
	virtual int size() const override { return ArrayList<T>::size(); }

	virtual T& top() override {
		if (empty()) { throw OutOfBounds(); }

		return ArrayList<T>::get(size() - 1);
	}

	virtual void pop() override {
		if (empty()) { throw OutOfBounds(); }

		ArrayList<T>::erase(size() - 1);
	}

	virtual void push(const T& theElement) override {
		ArrayList<T>::insert(size(), theElement);
	}

	virtual std::istream& input(std::istream& in) override;
	virtual std::string toString() const override;
	virtual void split(extendedStack<T>& st1, extendedStack<T>& st2) const override;
	virtual void merge(extendedStack<T>& st2) override;

	std::ostream& output(std::ostream& out) const { out << toString(); return out; }
};

template<class T>
std::istream& extendedDerivedArrayStack<T>::input(std::istream& in) {
	T t;
	while (in >> t) {
		push(t);
	}
	return in;
}

template<class T>
std::istream& operator>>(std::istream& in, extendedDerivedArrayStack<T>& st) { st.input(in); return in; }
template<class T>
std::ostream& operator<<(std::ostream& out, const extendedDerivedArrayStack<T>& st) { st.output(out); return out; }


template<class T>
std::string extendedDerivedArrayStack<T>::toString() const {
	std::string s = "";
	for (int i = 0; i < size(); i++) {
		s += std::to_string(ArrayList<T>::get(i));
		s += " ";
	}
	return s;
}

template<class T>
void extendedDerivedArrayStack<T>::split(extendedStack<T>& st1, extendedStack<T>& st2) const{
	int i = 0;
	for (; i < size() / 2; i++) {
		st1.push(ArrayList<T>::get(i));
	}
	for (; i < size(); i++) {
		st2.push(ArrayList<T>::get(i));
	}
}

template<class T>
void extendedDerivedArrayStack<T>::merge(extendedStack<T>& st2) {
	auto& st_t = dynamic_cast<extendedDerivedArrayStack<T>&>(st2);
	for (int i=0; i < st_t.size(); i++) {
		push(st_t.ArrayList<T>::get(i));
	}
}

#endif