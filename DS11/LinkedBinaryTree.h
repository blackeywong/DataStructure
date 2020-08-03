#pragma once
#ifndef _LINKEDBINARYTREE_H
#define _LINKEDBINARYTREE_H
#include <xutility>
#include <stack>
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <memory>

#include "BinaryTree.h"
#include "BinaryTreeNode.h"
#include "TraverseOrder.h"
#include "../DS8/drawing.h"

template<class E> class BaseIterator;
template<class E> class InOrderIterator;
template<class E> class PreOrderIterator;
template<class E> class PostOrderIterator;
template<class E> class LevelOrderIterator;

template<class E> class HuffmanTree;

template<class E>
class LinkedBinaryTree : public BinaryTree<BinaryTreeNode<E>> {
	template<class E> friend class InOrderIterator;
	template<class E> friend class PreOrderIterator;
	template<class E> friend class PostOrderIterator;
	template<class E> friend class LevelOrderIterator;
	template<class E> friend class HuffmanTree;
public:
	LinkedBinaryTree();
	virtual ~LinkedBinaryTree() { erase(); }
	virtual bool empty() const override { return treeSize == 0; }
	virtual int size() const override { return treeSize; }
	//virtual void preOrder(void(*theVisit)(BinaryTreeNode<E>*)) override { visit = theVisit; preOrder(root); }
	//virtual void inOrder(void(*theVisit)(BinaryTreeNode<E>*)) override { visit = theVisit; inOrder(root); }
	//virtual void postOrder(void(*theVisit)(BinaryTreeNode<E>*)) override { visit = theVisit; postOrder(root); }
	//virtual void levelOrder(void(*theVisit)(BinaryTreeNode<E>*)) override;
	virtual void preOrder(std::function<void(BinaryTreeNode<E>*)> theVisit) override { visit = theVisit; preOrder(root); }
	virtual void inOrder(std::function<void(BinaryTreeNode<E>*)> theVisit) override { visit = theVisit; inOrder(root); }
	virtual void postOrder(std::function<void(BinaryTreeNode<E>*)> theVisit) override { visit = theVisit; postOrder(root); }
	virtual void levelOrder(std::function<void(BinaryTreeNode<E>*)> theVisit) override;
	virtual void erase() { postOrder(dispose); root = nullptr; treeSize = 0; }
	int Height() const { return Height(root); }

	std::istream& input(std::istream& in);
	std::ostream& output(std::ostream& out, TRAVERSE_ORDER order = TRAVERSE_ORDER::INFIX);

	explicit LinkedBinaryTree(const LinkedBinaryTree<E>& right) { root = copySubtreePreOrder(right.root); }//Exercise 44
	bool compare(const LinkedBinaryTree<E>& right) { return compare(root, right.root); }//Exercise 45
	void swapTrees(LinkedBinaryTree<E>& right) { BinaryTreeNode<E>* temp = root; root = right.root; right.root = temp; }//Exercise 46
	int maxHeightDifferent() { return maxHeightDifferent(root); }//Exercise 47
	void makeTree(E weight, LinkedBinaryTree<E>* leftTree, LinkedBinaryTree<E>* rightTree);//for Huffman tree

	InOrderIterator<E> beginInOrder() { return InOrderIterator<E>(*this); }
	InOrderIterator<E> endInOrder() { return InOrderIterator<E>(); }
	PreOrderIterator<E> beginPreOrder() { return PreOrderIterator<E>(*this); }
	PreOrderIterator<E> endPreOrder() { return PreOrderIterator<E>(); }
	PostOrderIterator<E> beginPostOrder() { return PostOrderIterator<E>(*this); }
	PostOrderIterator<E> endPostOrder() { return PostOrderIterator<E>(); }
	LevelOrderIterator<E> beginLevelOrder() { return LevelOrderIterator<E>(*this); }
	LevelOrderIterator<E> endLevelOrder() { return LevelOrderIterator<E>(); }
public:
	void draw();
protected:
	BinaryTreeNode<E>* root;
	int treeSize;

	//void (*visit) (BinaryTreeNode<E>*);
	std::function<void(BinaryTreeNode<E>*)> visit;
	void preOrder(BinaryTreeNode<E>* t);
	void inOrder(BinaryTreeNode<E>* t);
	virtual void postOrder(BinaryTreeNode<E>* t);
	int Height(BinaryTreeNode<E>* t) const;
	BinaryTreeNode<E>* copySubtreePreOrder(BinaryTreeNode<E>* right);
	bool compare(BinaryTreeNode<E>* left, BinaryTreeNode<E>* right);
	int maxHeightDifferent(BinaryTreeNode<E>* node);

	static void dispose(BinaryTreeNode<E>* t) { delete t; }
	//static void printNode(BinaryTreeNode<E>* t) { std::cout << t->element << " "; }

protected:
	HWND myconsole;
	HDC mydc;
	int top;
	int left;
	int nodeWidth;
	int minNodeDistance;
	int levelDistance;
	//calculated from above
	int height;
	int nodeHeight;//=nodeWidth
	int levelHeight;//=nodeHeight+levelDistance

	COLORREF COLORS[10] = {
	RGB(255, 255, 255),//white
	RGB(255, 0, 0),//red
	RGB(0, 255, 0),//green
	RGB(0, 0, 255),//blue
	RGB(255, 255, 0),//yellow
	RGB(255, 0, 255),//purple
	RGB(0, 255, 255)//indigo
	};
};

template<class E>
std::ostream& operator<<(std::ostream& out, const std::pair<int, E>& p) {
	out << p.second;
	return out;
}

template<class E>
LinkedBinaryTree<E>::LinkedBinaryTree() :root(nullptr), treeSize(0) {
	myconsole = GetConsoleWindow();
	mydc = GetDC(myconsole);

	top = 115;
	left = 15;
	nodeWidth = 10;
	minNodeDistance = 10;
	levelDistance = 30;
	
	nodeHeight = nodeWidth;
	levelHeight = nodeHeight + levelDistance;
}

template<class E>
void LinkedBinaryTree<E>::draw() {
	height = Height();

	int nodeCount = (int)pow(2, height);
	BinaryTreeNode<E>** nodes = new BinaryTreeNode<E>*[nodeCount];
	for (int i = 1; i < nodeCount; ++i) {
		nodes[i] = nullptr;
	}
	
	nodes[1] = root;
	int low = 1, high = 2;
	for (int i = 1; i < height; ++i) {
		for (int j = low; j < high; ++j) {
			if (nodes[j] != nullptr) {
				if (nodes[j]->leftChild != nullptr) {
					nodes[j*2]= nodes[j]->leftChild;
				}
				if (nodes[j]->rightChild != nullptr) {
					nodes[j * 2 + 1] = nodes[j]->rightChild;
				}
			}
		}
		low *= 2;
		high *= 2;
	}

	//draw
	low = (int)pow(2, height - 1), high = 2 * low;
	int nodeDistance = nodeWidth + minNodeDistance;
	int halfNodeDistance = nodeDistance / 2;
	for (int i = height; i >= 1; --i) {
		int lowerX = left + halfNodeDistance * ((int)pow(2, height -i) - 1);
		int lowerY = top + levelHeight * (i - 1);
		int highX = left + halfNodeDistance * ((int)pow(2, height -i + 1) - 1);
		int highY = lowerY - levelDistance;
		for (int j = low, k = 0; j < high; ++j, ++k) {
			Point p1(lowerX - nodeWidth / 2, lowerY), p2(lowerX + nodeWidth / 2, lowerY + nodeHeight);
			MyRectangle rect(p1, p2, COLORS[2]);
			drawRectangle(mydc, rect);
			if (nodes[j] != nullptr) {
				std::ostringstream oss;
				oss << nodes[j]->element;
				drawText(myconsole, mydc, lowerX - nodeWidth / 2, lowerY, oss.str());
				if (i != 1) {
					drawLine(mydc, lowerX, lowerY, highX, highY, COLORS[1]);
				}
			}
			lowerX = lowerX + nodeDistance;
			if (j % 2 == 1) {
				highX = highX + nodeDistance * 2;
			}
		}
		low /= 2;
		high /= 2;
		nodeDistance *= 2;
	}

}

template<class E>
void LinkedBinaryTree<E>::preOrder(BinaryTreeNode<E>* t) {
	if (t != nullptr) {
		visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

template<class E>
void LinkedBinaryTree<E>::inOrder(BinaryTreeNode<E>* t) {
	if (t != nullptr) {
		inOrder(t->leftChild);
		visit(t);
		inOrder(t->rightChild);
	}
}

template<class E>
void LinkedBinaryTree<E>::postOrder(BinaryTreeNode<E>* t) {
	if (t != nullptr) {
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		visit(t);
	}
}

template<class E>
inline int LinkedBinaryTree<E>::Height(BinaryTreeNode<E>* t) const
{
	if (t == nullptr)
		return 0;

	int hl = Height(t->leftChild);
	int hr = Height(t->rightChild);
	if (hl > hr)
		return ++hl;
	else
		return ++hr;
}

template<class E>
//void LinkedBinaryTree<E>::levelOrder(void(*theVisit)(BinaryTreeNode<E>*))
void LinkedBinaryTree<E>::levelOrder(std::function<void(BinaryTreeNode<E>*)> theVisit)
{
	visit = theVisit;
	std::queue<BinaryTreeNode<E>*> q;
	q.push(root);
	while (q.size() > 0) {
		BinaryTreeNode<E>* node = q.front();
		q.pop();
		visit(node);
		if (node->leftChild != nullptr)
			q.push(node->leftChild);
		if (node->rightChild != nullptr)
			q.push(node->rightChild);
	}
} 

template<class E>
std::istream& LinkedBinaryTree<E>::input(std::istream& in) {
	int num;
	E e;
	std::queue<BinaryTreeNode<E>*> q;
	while (in >> num >> e) {
		BinaryTreeNode<E>* node = new BinaryTreeNode<E>(e);
		++treeSize;
		node->seq_num = num;
		q.push(node);
		if (num == 1) {
			root = node;
			continue;
		}

		while (q.size() > 0) {
			BinaryTreeNode<E>* top = q.front();
			if (top->seq_num * 2 == num) {
				top->leftChild = node;
				break;
			}
			else if (top->seq_num * 2 + 1 == num) {
				top->rightChild = node;
				q.pop();
				break;
			}
			else {
				q.pop();
				continue;
				--treeSize;
			}
		}
	}
	return in;
}

template<class E>
std::ostream& LinkedBinaryTree<E>::output(std::ostream& out, TRAVERSE_ORDER order) {
	auto func = [&out](BinaryTreeNode<E>* t) {out << t->element << " "; };
	switch (order) {
	case TRAVERSE_ORDER::PREFIX: preOrder(func); break;
	case TRAVERSE_ORDER::INFIX: inOrder(func); break;
	case TRAVERSE_ORDER::POSTFIX: postOrder(func); break;
	case TRAVERSE_ORDER::LEVEL: levelOrder(func); break;
	}
	return out;
}

template<class E>
BinaryTreeNode<E>* LinkedBinaryTree<E>::copySubtreePreOrder(BinaryTreeNode<E>* right)
{
	//auto f = [](BinaryTreeNode<E>* node) {BinaryTreeNode<E>* newNode = new BinaryTreeNode<E>(node->element); return newNode; }->BinaryTreeNode<E>*;
	BinaryTreeNode<E>* newNode = nullptr;
	if (right != nullptr) {
		newNode = new BinaryTreeNode<E>(right->element,
			copySubtreePreOrder(right->leftChild),
			copySubtreePreOrder(right->rightChild));
	}
	return newNode;
}

template<class E>
bool LinkedBinaryTree<E>::compare(BinaryTreeNode<E>* left, BinaryTreeNode<E>* right)
{
	if (left == nullptr && right == nullptr) {
		return true;
	}
	else if (left != nullptr && right != nullptr) {
		return compare(left->leftChild, right->leftChild) && compare(left->rightChild, right->rightChild);
	}else
		return false;
}

template<class E>
inline int LinkedBinaryTree<E>::maxHeightDifferent(BinaryTreeNode<E>* node)
{
	static int maxDiff = 0;
	if (node == nullptr)
		return 0;

	int diff = std::abs(Height(node->leftChild) - Height(node->rightChild));
	maxDiff = maxDiff > diff ? maxDiff : diff;
	diff = maxHeightDifferent(node->leftChild);
	maxDiff = maxDiff > diff ? maxDiff : diff;
	diff = maxHeightDifferent(node->rightChild);
	maxDiff = maxDiff > diff ? maxDiff : diff;
	return maxDiff;
}


template<class E>
void LinkedBinaryTree<E>::makeTree(E weight, LinkedBinaryTree<E>* leftTree, LinkedBinaryTree<E>* rightTree)
{
	root = new BinaryTreeNode<E>(weight);
	treeSize = 1;
	if (leftTree != nullptr && leftTree->root != nullptr) {
		root->leftChild = leftTree->root;
		treeSize += leftTree->treeSize;
		leftTree->root = nullptr;
		leftTree->treeSize = 0;
	}

	if (rightTree != nullptr && rightTree->root != nullptr) {
		root->rightChild = rightTree->root;
		treeSize += rightTree->treeSize;
		rightTree->root = nullptr;
		rightTree->treeSize = 0;
	}
}

////////////////////////////////////////////////////////////////////////////////////////

template<class E>
class BaseIterator {
public:
	typedef std::forward_iterator_tag iterator_capacity;
	typedef E value_type;
	typedef ptrdiff_t difference_type;
	typedef E* pointer;
	typedef E& reference;

	E& operator*() const { return node->element; }
	E* operator->() const { return &node->element; }

	virtual BaseIterator<E>& operator++() = 0;
	//virtual BaseIterator<E> operator++(int) { BaseIterator<E> old = *this; operator++(); return old; }

	virtual bool operator!=(const BaseIterator& right) const { return node != right.node; }
	virtual bool operator==(const BaseIterator& right) const { return node == right.node; }

	virtual void swap(BaseIterator<E>& right) { using std::swap; swap(this->node->element, right.node->element);}
protected:
	BinaryTreeNode<E>* node;
};
//Exercise 48
template<class E>
class InOrderIterator:public BaseIterator<E> {
public:
	InOrderIterator() {this->node = nullptr;}
	explicit InOrderIterator(LinkedBinaryTree<E>& t) {
		BinaryTreeNode<E>* n = nullptr;
		if (t.root)
			n = t.root;
		while (n->leftChild) { 
			stack.push(n);
			n = n->leftChild; 
		}
		this->node = n;
	}

	 InOrderIterator(const InOrderIterator<E>& t) { this->node = t.node; stack = t.stack; }

	virtual InOrderIterator<E>& operator++() override {
		if (this->node->rightChild != nullptr) {
			this->node = this->node->rightChild;
			BinaryTreeNode<E>* n = this->node;
			while (n->leftChild) {
				stack.push(n);
				n = n->leftChild;
			}
			this->node = n;
		}
		else {
			if (!stack.empty()) {
				this->node = stack.top();
				stack.pop();
			}
			else {
				this->node = nullptr;
			}
		}
		return *this;
	}

	virtual InOrderIterator<E> operator++(int) { InOrderIterator<E> old = *this; operator++(); return old; }

private:
	std::stack<BinaryTreeNode<E>*> stack;
};
//Exercise 49
template<class E>
class PreOrderIterator :public BaseIterator<E> {
public:
	PreOrderIterator() { this->node = nullptr; }
	explicit PreOrderIterator(LinkedBinaryTree<E>& t) {this->node = t.root;}

	PreOrderIterator(const PreOrderIterator<E>& t) { this->node = t.node; stack = t.stack; }

	virtual PreOrderIterator<E>& operator++() override {
		if (this->node->rightChild != nullptr) {
			stack.push(this->node->rightChild);
		}
		if(this->node->leftChild != nullptr)
		{
			this->node = this->node->leftChild;
		}
		else {
			if (!stack.empty()) {
				this->node = stack.top();
				stack.pop();
			}
			else {
				this->node = nullptr;
			}
		}
		return *this;
	}

	virtual PreOrderIterator<E> operator++(int) { PreOrderIterator<E> old = *this; operator++(); return old; }

private:
	std::stack<BinaryTreeNode<E>*> stack;
};
//Exercise 50
template<class E>
class PostOrderIterator :public BaseIterator<E> {
public:
	PostOrderIterator() { this->node = nullptr; }
	explicit PostOrderIterator(LinkedBinaryTree<E>& t) {
		this->node = getNext(t.root);
	}

	PostOrderIterator(const PostOrderIterator<E>& t) { this->node = t.node; stack = t.stack; }

	virtual PostOrderIterator<E>& operator++() override {
		if (stack.empty()) {
			this->node = nullptr;
			return *this;
		}

		BinaryTreeNode<E>* temp = this->node;
		this->node = stack.top();

		if (temp == this->node->leftChild && this->node->rightChild != nullptr) {
			this->node = getNext(this->node->rightChild);
		}
		else {
			stack.pop();
		}

		return *this;
	}

	virtual PostOrderIterator<E> operator++(int) { PostOrderIterator<E> old = *this; operator++(); return old; }

private:
	BinaryTreeNode<E>* getNext(BinaryTreeNode<E>* n) {
		if (!n)
			return nullptr;

		while (n->leftChild != nullptr || n->rightChild != nullptr) {
			while (n->leftChild) {
				stack.push(n);
				n = n->leftChild;
			}
			if (n->rightChild) {
				stack.push(n);
				n = n->rightChild;
			}
		}
		return n;
	}

	std::stack<BinaryTreeNode<E>*> stack;
};
//Exercise 51
template<class E>
class LevelOrderIterator :public BaseIterator<E> {
public:
	LevelOrderIterator() { this->node = nullptr; }
	explicit LevelOrderIterator(LinkedBinaryTree<E>& t) { this->node = t.root; }
	LevelOrderIterator(const LevelOrderIterator<E>& t) { this->node = t.node; queue = t.queue; }

	virtual LevelOrderIterator<E>& operator++() override {
		if (queue.empty() && this->node->leftChild == nullptr && this->node->rightChild == nullptr) {
			this->node = nullptr;
			return *this;
		}

		if (this->node->leftChild) {
			queue.push(this->node->leftChild);
		}
		if (this->node->rightChild) {
			queue.push(this->node->rightChild);
		}

		this->node = queue.front();
		queue.pop();
		return *this;
	}

	virtual LevelOrderIterator<E> operator++(int) { LevelOrderIterator<E> old = *this; operator++(); return old; }
private:
	std::queue<BinaryTreeNode<E>*> queue;
};
 
template<class E> void swap(BaseIterator<E>& it1, BaseIterator<E>& it2) {it1.swap(*it2);}

template<class E> void swap(InOrderIterator<E>& it1, InOrderIterator<E>& it2) {it1.swap(*it2);}

template<class E> void swap(PreOrderIterator<E>& it1, PreOrderIterator<E>& it2) {it1.swap(*it2);}

template<class E> void swap(PostOrderIterator<E>& it1, PostOrderIterator<E>& it2) {it1.swap(*it2);}

template<class E> void swap(LevelOrderIterator<E>& it1, LevelOrderIterator<E>& it2) {it1.swap(*it2);}
 
#endif 