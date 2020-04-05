#pragma once
#ifndef _EQUIVALENTCLASSIMCHAIN_H
#define _EQUIVALENTCLASSIMCHAIN_H
#include <iostream>
using namespace std;
//���ݽṹ�㷨��Ӧ��-C++�������� ������
//Exercise 73

struct equivNode {
	int equivClass,
		size,
		next;
};

class EquivalentClassInSimChain {
public:
	EquivalentClassInSimChain(int numberOfElements);
	void unite(int classA, int classB);
	int find(int theElement) const;
	void output(ostream& out) const;

protected:
	equivNode* node;
	int n;
};

ostream& operator<<(ostream& out, EquivalentClassInSimChain& ec);

#endif
