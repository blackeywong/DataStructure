#pragma once
#ifndef _EQUIVALENTCLASCHAIN_H
#define _EQUIVALENTCLASCHAIN_H
#include <iostream>
#include <vector>
using namespace std;
//数据结构算法与应用-C++语言描述 第六章
//Exercise 77

struct equivNode {
	int equivClass;
	int size;
	equivNode* next;
};

class EquivalentClassInChain {
public:
	EquivalentClassInChain(int numberOfElements);
	void unite(int classA, int classB);
	int find(int theElement) const;
	void output(ostream& out) const;

protected:
	vector<equivNode*> node;
	int n;
};

ostream& operator<<(ostream& out, EquivalentClassInChain& ec);

#endif
