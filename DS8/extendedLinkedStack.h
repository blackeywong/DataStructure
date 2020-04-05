#pragma once
#ifndef _EXTENDEDLINKEDSTACK_H
#define _EXTENDEDLINKEDSTACK_H
#include "extendedStack.h"
#include "linkedStack.h"

//Exercise 13
template<class T>
class extendedLinkedStack : public linkedStack<T>, public extendedStack<T> {
	template<class T>
	friend std::istream& operator>>(std::istream& in, extendedLinkedStack<T>& st);
	template<class T>
	friend std::ostream& operator<<(std::ostream& out, const extendedLinkedStack<T>& st);
public:
	extendedLinkedStack<T>() : linkedStack<T>() {}
	virtual bool empty() const override { return linkedStack<T>::empty(); }
	virtual int size() const override { return linkedStack<T>::size(); }
	virtual T& top() override { return linkedStack<T>::top(); }
	virtual void pop() override { linkedStack<T>::pop(); }
	virtual void push(const T& theElement) override { linkedStack<T>::push(theElement); }

	virtual std::istream& input(std::istream& in) override;
	virtual std::string toString() const override;
	virtual void split(extendedStack<T>& st1, extendedStack<T>& st2) const override;
	virtual void merge(extendedStack<T>& st2) override;

	std::ostream& output(std::ostream& out) const { out << toString(); return out; }
};

template<class T>
std::istream& extendedLinkedStack<T>::input(std::istream& in) {
	T t;
	while (in >> t) {
		push(t);
	}
	return in;
}

template<class T>
std::istream& operator>>(std::istream& in, extendedLinkedStack<T>& st) { st.input(in); return in; }
template<class T>
std::ostream& operator<<(std::ostream& out, const extendedLinkedStack<T>& st) { st.output(out); return out; }


template<class T>
std::string extendedLinkedStack<T>::toString() const {
	std::string s = "";
	ChainNode<T>* node = linkedStack<T>::stackTop;
	while (node) {
		s = std::to_string(node->element) + " " + s;
		node = node->next;
	}
	return s;
}

template<class T>
void extendedLinkedStack<T>::split(extendedStack<T>& st1, extendedStack<T>& st2) const {
	auto& st1_t = dynamic_cast<extendedLinkedStack<T>&>(st1);
	auto& st2_t = dynamic_cast<extendedLinkedStack<T>&>(st2);
	std::string s = toString();
	std::istringstream iss(s);
	int i = 0;
	T t;
	for (; i < size() / 2; i++) {
		iss >> t;
		st1_t.push(t);
	}
	for (; i < size(); i++) {
		iss >> t;
		st2_t.push(t);
	}
}

template<class T>
void extendedLinkedStack<T>::merge(extendedStack<T>& st2) {
	auto& st_t = dynamic_cast<extendedLinkedStack<T>&>(st2);
	std::string s = st_t.toString();
	std::istringstream iss(s);
	T t;
	for (int i = 0; i < st_t.size(); i++) {
		iss >> t;
		push(t);
	}
}

#endif