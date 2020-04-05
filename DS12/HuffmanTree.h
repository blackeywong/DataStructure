#ifndef _HUFFMANTREE_H
#define _HUFFMANTREE_H

#include "../DS11/LinkedBinaryTree.h"
#include "Heap.h"

template<class T>
struct HuffmanNode {
	LinkedBinaryTree<unsigned int>* tree;
	T weight;
	T element;
	HuffmanNode():tree(nullptr),weight(0),element(0) {}
	operator T() const { return weight; }
};

class HuffmanCoding;
template<class T>
class HuffmanTree : public LinkedBinaryTree<T> {
	friend class HuffmanCoding;
public:
	HuffmanTree(T weight[], unsigned int n, T* elements = nullptr) { initialize(weight, n, elements); }
	virtual ~HuffmanTree() { delete[]hNode; }
protected:
	void initialize(T weight[], unsigned int n, T* elements);

	HuffmanNode<T>* hNode;
};



template<class T>
void HuffmanTree<T>::initialize(T weight[], unsigned int n, T* elements)
{
	unsigned int nonZero = 0;
	for (unsigned int i = 0; i < n; ++i) {
		if (weight[i] != 0) {
			++nonZero;
		}
	}
	hNode = new HuffmanNode<T>[nonZero + 1];
	LinkedBinaryTree<unsigned int> emptyTree;

	for (unsigned int i = 1, j=1; i <= nonZero; ++i, ++j) {
		while (j <= n && weight[j-1] == 0) {
			++j;
		}
		if (j > n) {
			break;
		}
		hNode[i].weight = weight[j-1];
		if (elements == nullptr) {
			hNode[i].element = j - 1;
		}
		else {
			hNode[i].element = elements[j-1];
		}
		hNode[i].tree = new LinkedBinaryTree<unsigned int>;
		//hNode[i].tree->makeTree(weight[i-1], &emptyTree, &emptyTree);
		hNode[i].tree->makeTree(hNode[i].element, &emptyTree, &emptyTree);
	}

	Heap<HuffmanNode<T>> heap(hNode, nonZero, false);

	HuffmanNode<T> w, x, y;
	LinkedBinaryTree<unsigned int>* z;
	if (nonZero == 1) {
		x = heap.top(); heap.pop();
		z = new LinkedBinaryTree<unsigned int>;
		z->makeTree(0, x.tree, &emptyTree);
		w.weight = x.weight;
		w.tree = z;
		heap.push(w);
		delete x.tree;
	}else {
		for (unsigned int i = 1; i < nonZero; ++i) {
			x = heap.top(); heap.pop();
			y = heap.top(); heap.pop();

			z = new LinkedBinaryTree<unsigned int>;
			z->makeTree(0, x.tree, y.tree);
			w.weight = x.weight + y.weight;
			w.tree = z;
			heap.push(w);
			delete x.tree;
			delete y.tree;
		}
	}
	if (!heap.empty()) {
		this->root = heap.top().tree->root;
		this->treeSize = heap.top().tree->treeSize;
	}
	else {
		this->root = nullptr;
		this->treeSize = 0;
	}
	
}


#endif

