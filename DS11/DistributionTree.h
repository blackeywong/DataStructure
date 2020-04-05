#pragma once
#ifndef _DISTRIBUTIONTREE_H
#define _DISTRIBUTIONTREE_H

#include "LinkedBinaryTree.h"
#include "Booster.h"

void placeBoosters(BinaryTreeNode<Booster>* x);
void placeBoosters2(BinaryTreeNode<Booster>* x);//Exercise 57


class DistributionTree : public LinkedBinaryTree<Booster> {
public:
	virtual void postOrder(std::function<void(BinaryTreeNode<Booster>*)> theVisit) override { visit = theVisit; postOrder(root); }
private:
	virtual void postOrder(BinaryTreeNode<Booster>* t) override;//Exercise 57

	int tolerance;
};

#endif
