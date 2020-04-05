#pragma once
#ifndef _EQUIVALENTCLASSINLIST_H
#define _EQUIVALENTCLASSINLIST_H
#include <iostream>
using namespace std;
//数据结构算法与应用-C++语言描述 第六章
//Exercise 76
class EquivalentClassInList {
public:
	EquivalentClassInList(int numberOfElements);
	void unite(int classA, int classB);
	int find(int theElement) const;
	void output(ostream& out) const;

protected:
	int* equivClass;
	int n;
};

ostream& operator<<(ostream& out, EquivalentClassInList& ec);

#endif
