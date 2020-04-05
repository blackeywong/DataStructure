#pragma once
#ifndef _EXTENDEDARRAYSTACK_H
#define _EXTENDEDARRAYSTACK_H
#include "extendedStack.h"
#include "arrayStack.h"

//Exercise 7.3
template<class T>
class extendedArrayStack : public arrayStack<T>, public extendedStack<T> {
	template<class T>
	friend std::istream& operator>>(std::istream& in, extendedArrayStack<T>& st);
	template<class T>
	friend std::ostream& operator<<(std::ostream& out, const extendedArrayStack<T>& st);
public:
	extendedArrayStack<T>(int initialCapacity = 10) : arrayStack<T>(initialCapacity) {}
	virtual bool empty() const override { return arrayStack<T>::empty(); }
	virtual int size() const override { return arrayStack<T>::size(); }
	virtual T& top() override { return arrayStack<T>::top(); }
	virtual void pop() override { arrayStack<T>::pop(); }
	virtual void push(const T& theElement) override { arrayStack<T>::push(theElement); }

	virtual std::istream& input(std::istream& in) override;
	virtual std::string toString() const override;
	virtual void split(extendedStack<T>& st1, extendedStack<T>& st2) const override;
	virtual void merge(extendedStack<T>& st2) override;

	std::ostream& output(std::ostream& out) const { out << toString(); return out; }
};

template<class T>
std::istream& extendedArrayStack<T>::input(std::istream& in) {
	T t;
	while (in >> t) {
		push(t);
	}
	return in;
}

template<class T>
std::istream& operator>>(std::istream& in, extendedArrayStack<T>& st) { st.input(in); return in; }
template<class T>
std::ostream& operator<<(std::ostream& out, const extendedArrayStack<T>& st) { st.output(out); return out; }


template<class T>
std::string extendedArrayStack<T>::toString() const {
	std::string s = "";
	for (int i = 0; i < size(); i++) {
		s += std::to_string(arrayStack<T>::stack[i]);
		s += " ";
	}
	return s;
}

template<class T>
void extendedArrayStack<T>::split(extendedStack<T>& st1, extendedStack<T>& st2) const {
	auto& st1_t = dynamic_cast<extendedArrayStack<T>&>(st1);
	auto& st2_t = dynamic_cast<extendedArrayStack<T>&>(st2);
	int i = 0;
	for (; i < size() / 2; i++) {
		st1_t.push(arrayStack<T>::stack[i]);
	}
	for (; i < size(); i++) {
		st2_t.push(arrayStack<T>::stack[i]);
	}
}

template<class T>
void extendedArrayStack<T>::merge(extendedStack<T>& st2) {
	auto& st_t = dynamic_cast<extendedArrayStack<T>&>(st2);
	for (int i = 0; i < st_t.size(); i++) {
		push(arrayStack<T>::stack[i]);
	}
}

#endif