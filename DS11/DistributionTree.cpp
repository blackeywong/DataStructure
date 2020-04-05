#include "Booster.h"
#include "DistributionTree.h"


std::ostream& operator<<(std::ostream& out, const Booster& x) { x.output(out); return out; }
std::istream& operator>>(std::istream& in, Booster& x) { x.input(in); return in; }

extern int tolerance;

void placeBoosters(BinaryTreeNode<Booster>* x) {
	x->element.degradeToLeaf = 0;

	BinaryTreeNode<Booster>* y = x->leftChild;
	if (y != nullptr) {
		int degradation = y->element.degradeToLeaf + y->element.degradeFromParent;
		if (degradation > tolerance) {
			y->element.boosterHere = true;
			x->element.degradeToLeaf = y->element.degradeFromParent;
		}
		else {
			x->element.degradeToLeaf = degradation;
		}
	}

	y = x->rightChild;
	if (y != nullptr) {
		int degradation = y->element.degradeToLeaf + y->element.degradeFromParent;
		if (degradation > tolerance) {
			y->element.boosterHere = true;
			degradation = y->element.degradeFromParent;
		}
		if (x->element.degradeToLeaf < degradation) {
			x->element.degradeToLeaf = degradation;
		}
	}
}

void placeBoosters2(BinaryTreeNode<Booster>* x) {
	x->element.degradeToLeaf = 0;

	BinaryTreeNode<Booster>* y = x->leftChild;
	if (y != nullptr) {
		int degradation = y->element.degradeToLeaf + y->element.degradeFromParent;
		if (degradation > tolerance) {
			y->element.boosterHere = true;
			x->element.degradeToLeaf = y->element.degradeFromParent;
		}
		else {
			x->element.degradeToLeaf = degradation;
		}

		y = y->rightChild;
		while (y != nullptr) {
			int degradation = y->element.degradeToLeaf + y->element.degradeFromParent;
			if (degradation > tolerance) {
				y->element.boosterHere = true;
				degradation = y->element.degradeFromParent;
			}
			if (x->element.degradeToLeaf < degradation) {
				x->element.degradeToLeaf = degradation;
			}
			y = y->rightChild;
		}
	}
}


void DistributionTree::postOrder(BinaryTreeNode<Booster>* t) {
	if (t != nullptr) {
		postOrder(t->leftChild);
		if (t->leftChild) {
			BinaryTreeNode<Booster>* s = t->leftChild->rightChild;
			while (s) {
				postOrder(s);
				s = s->rightChild;
			}
		}
		visit(t);
	}
}