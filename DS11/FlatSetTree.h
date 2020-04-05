#pragma once
#ifndef _FLATSETTREE_H
#define _FLATSETTREE_H
#include <iostream>
class FlatSetTree {
public:
	FlatSetTree() :size(0), parent(nullptr) {}
	explicit FlatSetTree(int theSize) :size(theSize) { init(); }
	~FlatSetTree() { clear(); }

	int find(int theElement) {
		while (parent[theElement] != 0) {
			theElement = parent[theElement];
		}
		return theElement;
	}
	void unite(int rootA, int rootB) {
		parent[rootB] = rootA;
	}

	std::istream& input(std::istream& in) {
		clear();
		in >> size;
		init();
		int num, p;
		while (in >> num >> p) {
			parent[num] = p;
		}
		return in;
	}
	std::ostream& output(std::ostream& out) {
		out << size << '\t';
		for (int i = 1; i <= size; ++i) {
			if (parent[i] != 0) {
				out << i << ':' <<parent[i] << ' ';
			}
		}
		return out;
	}
private:
	void init() {
		parent = new int[size + 1];
		for (int i = 1; i <= size; ++i) {
			parent[i] = 0;
		}
	}
	void clear() {
		delete[] parent;
		parent = nullptr;
		size = 0;
	}
	int* parent;
	int size;
};

#endif