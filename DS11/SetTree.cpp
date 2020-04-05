#include "SetTree.h"

void SetTree::init() {
	nodes = new UnionFindNode[size + 2];//not use the first two nodes
}

void SetTree::clear() {
	delete[] nodes;
	nodes = nullptr;
	size = 0;
}

std::istream& SetTree::input(std::istream& in) {
	clear();
	in >> size;
	init();
	int num, p;
	while (in >> num >> p) {
		nodes[num].parent = p;
		nodes[num].root = false;
	}
	return in;
}
std::ostream& SetTree::output(std::ostream& out) {
	out << size << '\t';
	for (int i = 2; i <= size+1; ++i) {
		if (!nodes[i].root) {
			out << i << ':' << nodes[i].parent << ' ';
		}
	}
	return out;
}

int SetTree::find(int theElement, FIND_RULE rule) {
	int theRoot = theElement;
	while (!nodes[theRoot].root) {
		theRoot = nodes[theRoot].parent;
	}

	if (rule == PATH_COMPACTION) {
		int curNode = theElement;
		while (curNode != theRoot) {
			int parentNode = nodes[curNode].parent;
			nodes[curNode].parent = theRoot;
			curNode = parentNode;
		}
	}else if (rule == PATH_SPLITTING) {//Exercise 64
		int curNode = theElement;
		if (curNode != theRoot) {
			int parentNode = nodes[curNode].parent;
			while (parentNode != theRoot) {
				int grandNode = nodes[parentNode].parent;
				nodes[curNode].parent = grandNode;
				curNode = parentNode;
				parentNode = grandNode;
			}
		}
	}else if (rule == PATH_HALVING) {//Exercise 65
		int curNode = theElement;
		int parentNode = nodes[curNode].parent;
		while (curNode != theRoot && parentNode != theRoot) {
			int grandNode = nodes[parentNode].parent;
			nodes[curNode].parent = grandNode;
			curNode = grandNode;
			parentNode =  nodes[grandNode].parent;
		}
	}
	return theRoot;
}

void SetTree::unite(int rootA, int rootB, UNITE_RULE rule) {
	if (rule == NO_UNITE_RULE) {
		nodes[rootB].root = false;
		nodes[rootB].parent = rootA;
	}
	else if (rule == WEIGHT) {
		if (nodes[rootA].parent < nodes[rootB].parent) {
			nodes[rootB].parent += nodes[rootA].parent;
			nodes[rootA].root = false;
			nodes[rootA].parent = rootB;
		}
		else {
			nodes[rootA].parent += nodes[rootB].parent;
			nodes[rootB].root = false;
			nodes[rootB].parent = rootA;
		}
	}else if(rule == HEIGHT) {//Exercise 60
		if (nodes[rootA].parent < nodes[rootB].parent) {
			nodes[rootA].root = false;
			nodes[rootA].parent = rootB;
		}
		else {
			nodes[rootB].root = false;
			nodes[rootB].parent = rootA;
			if (nodes[rootA].parent == nodes[rootB].parent) {
				++nodes[rootA].parent;
			}
		}
	}
}