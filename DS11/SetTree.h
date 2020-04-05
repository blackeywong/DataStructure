#pragma once
#ifndef _SETTREE_H
#define _SETTREE_H
#include <iostream>
#include "UnionFindNode.h"
class TestSetTree;
class SetTree {
	friend class TestSetTree;
public:
	enum UNITE_RULE {NO_UNITE_RULE, WEIGHT, HEIGHT};
	enum FIND_RULE {NO_FIND_RULE, PATH_COMPACTION, PATH_SPLITTING, PATH_HALVING};
public:
	SetTree() :size(0), nodes(nullptr) {}
	explicit SetTree(int theSize) :size(theSize) {init();}
	~SetTree() { clear(); }

	int find(int theElement, FIND_RULE rule = NO_FIND_RULE);
	void unite(int rootA, int rootB, UNITE_RULE rule = NO_UNITE_RULE);

	std::istream& input(std::istream& in);
	std::ostream& output(std::ostream& out);
private:
	void init();
	void clear();
	UnionFindNode* nodes;
	int size;
};

#endif