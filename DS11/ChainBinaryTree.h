#pragma once
#ifndef _CHAINBINARYTREE_H
#define _CHAINBINARYTREE_H

#include <utility>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

#include "BinaryTreeNode.h"
#include "TraverseOrder.h"

//Exercise 26
template<class T>
class ChainBinaryTree {
public:
	ChainBinaryTree() { root = new BinaryTreeNode<T>; root->leftChild = root->rightChild = nullptr; }
	~ChainBinaryTree() { clear(root); }
	explicit ChainBinaryTree(const ChainBinaryTree<T>& right, TRAVERSE_ORDER order = PREFIX);//Exercise 25

	std::istream& input(std::istream& in);
	std::ostream& output(std::ostream& out, TRAVERSE_ORDER order = INFIX) const;

	void preOrder(BinaryTreeNode<T>* node, std::ostream& out = std::cout) const;
	void inOrder(BinaryTreeNode<T>* node, std::ostream& out = std::cout) const;
	void postOrder(BinaryTreeNode<T>* node, std::ostream& out = std::cout) const;
	void levelOrder(std::ostream& out = std::cout) const;
	void visit(BinaryTreeNode<T>* node, std::ostream& out = std::cout) const { if (node) out << node->element << " "; }

	int Height() const { return heightSubtree(root); }//Exercise 27
	int countNode() const { return countNodesubtree(root); }//Exercise 28
	int levelWithMostnodes() const;//Exercise 29

	template <class Pred> void inOrderNoRecursive(Pred func) const; //Exercise 30
	template <class Pred> void preOrderNoRecursive(Pred func) const; //Exercise 31
	template <class Pred> void postOrderNoRecursive(Pred func) const; //Exercise 32

	void createTreePreAndInOrder(const std::string& preStr, const std::string& inStr);//Exercise 33
	void createTreePreAndPostOrder(const std::string& preStr, const std::string& postStr);//Exercise 34
	void createTreePostAndInOrder(const std::string& postStr, const std::string& inStr);//Exercise 35
protected:
	void clear(BinaryTreeNode<T>* node);
	void copySubtreePreOrder(BinaryTreeNode<T>* node, const BinaryTreeNode<T>* rightNode);
	BinaryTreeNode<T>* copySubtreePostOrder(const BinaryTreeNode<T>* rightNode);
	int heightSubtree(BinaryTreeNode<T>* node) const;
	int countNodesubtree(BinaryTreeNode<T>* node) const;
	BinaryTreeNode<T>* createSubtreePreAndInOrder(BinaryTreeNode<T>* node, const std::string& preStr, const std::string& inStr);//Exercise 33
	BinaryTreeNode<T>* createSubreePreAndPostOrder(const std::string& preStr, const std::string& postStr);//Exercise 34
	BinaryTreeNode<T>* createSubreePostAndInOrder(BinaryTreeNode<T>* node, const std::string& postStr, const std::string& inStr);//Exercise 35
	bool splitStr(const std::string& c, const std::string& inStr, std::string& outStr1, std::string& outStr2);

	BinaryTreeNode<T>* root;
};

template<class T>
void ChainBinaryTree<T>::clear(BinaryTreeNode<T> * node) {
	if (node != nullptr) {
		clear(node->leftChild);
		clear(node->rightChild);
		delete node;
	}
}

template<class T>
void ChainBinaryTree<T>::copySubtreePreOrder(BinaryTreeNode<T>* node, const BinaryTreeNode<T>* rightNode) {
	node->element = rightNode->element;
	if (rightNode->leftChild) {
		node->leftChild = new BinaryTreeNode<T>;
		copySubtreePreOrder(node->leftChild, rightNode->leftChild);
	}
	if (rightNode->rightChild) {
		node->rightChild = new BinaryTreeNode<T>;
		copySubtreePreOrder(node->rightChild, rightNode->rightChild);
	}
}


template<class T>
BinaryTreeNode<T>* ChainBinaryTree<T>::copySubtreePostOrder(const BinaryTreeNode<T>* rightNode) {
	BinaryTreeNode<T>* left = nullptr;
	BinaryTreeNode<T>* right = nullptr;
	if (rightNode->leftChild) {
		left = copySubtreePostOrder(rightNode->leftChild);
	}
	if (rightNode->rightChild) {
		right = copySubtreePostOrder(rightNode->rightChild);
	}

	return new BinaryTreeNode<T>(rightNode->element, left, right);
}

template<class T>
ChainBinaryTree<T>::ChainBinaryTree(const ChainBinaryTree<T>& right, TRAVERSE_ORDER order) {
	clear(root);
	if (order == TRAVERSE_ORDER::PREFIX) {
		root = new BinaryTreeNode<T>;
		copySubtreePreOrder(root, right.root);
	}
	else { 
		root = copySubtreePostOrder(right.root); 
	}
}

template<class T>
std::istream& ChainBinaryTree<T>::input(std::istream& in) {
	int num;
	T t;
	std::queue<BinaryTreeNode<T>*> q;
	while (in >> num >> t) {
		if (num == 1) {
			root->seq_num = 1;
			root->element = t;
			q.push(root);
			continue;
		}
		BinaryTreeNode<T>* node = new BinaryTreeNode<T>(t);
		node->seq_num = num;
		q.push(node);

		while (q.size() > 0) {
			BinaryTreeNode<T>* top = q.front();
			if (top->seq_num * 2 == num) {
				top->leftChild = node;
				break;
			}else if (top->seq_num * 2 + 1 == num) {
				top->rightChild = node;
				q.pop();
				break;
			}
			else {
				q.pop();
				continue;
			}
		}
	}
	return in;
}

template<class T>
std::ostream& ChainBinaryTree<T>::output(std::ostream& out, TRAVERSE_ORDER order) const {
	switch (order) {
	case TRAVERSE_ORDER::PREFIX: preOrder(root, out); break;
	case TRAVERSE_ORDER::INFIX: inOrder(root, out); break;
	case TRAVERSE_ORDER::POSTFIX: postOrder(root, out); break;
	case TRAVERSE_ORDER::LEVEL: levelOrder(out); break;
	}
	return out;
}

template<class T>
void ChainBinaryTree<T>::preOrder(BinaryTreeNode<T>* node, std::ostream& out) const {
	if (node !=nullptr) {
		visit(node, out);
		preOrder(node->leftChild, out);
		preOrder(node->rightChild, out);
	}
}

template<class T>
void ChainBinaryTree<T>::inOrder(BinaryTreeNode<T>* node, std::ostream& out) const {
	if (node != nullptr) {
		inOrder(node->leftChild, out);
		visit(node, out);
		inOrder(node->rightChild, out);
	}
}

template<class T>
void ChainBinaryTree<T>::postOrder(BinaryTreeNode<T>* node, std::ostream& out) const {
	if (node != nullptr) {
		postOrder(node->leftChild, out);
		postOrder(node->rightChild, out);
		visit(node, out);
	}
}

template<class T>
void ChainBinaryTree<T>::levelOrder(std::ostream& out) const {
	std::queue<BinaryTreeNode<T>*> q;
	q.push(root);
	while (q.size() > 0) {
		BinaryTreeNode<T>* node = q.front();
		q.pop();
		out << node->element << " ";
		if (node->leftChild != nullptr)
			q.push(node->leftChild);
		if (node->rightChild != nullptr)
			q.push(node->rightChild);
	}
}

template<class T>
int ChainBinaryTree<T>::heightSubtree(BinaryTreeNode<T>* node) const {
	static int height = 1;
	static int curlevel = 1;

	if (node == nullptr) {
		return height;
	}

	if(node->leftChild != nullptr)
	{
		++curlevel;
		if (curlevel > height)
			height = curlevel;
		heightSubtree(node->leftChild);
		--curlevel;
	}

	if (node->rightChild != nullptr)
	{
		++curlevel;
		if (curlevel > height)
			height = curlevel;
		heightSubtree(node->rightChild);
		--curlevel;
	}

	return height;
}

template<class T>
int ChainBinaryTree<T>::countNodesubtree(BinaryTreeNode<T>* node) const {
	static int count = 1;

	if (node == nullptr) {
		return count;
	}

	if (node->leftChild != nullptr)
	{
		++count;
		countNodesubtree(node->leftChild);
	}

	if (node->rightChild != nullptr)
	{
		++count;
		countNodesubtree(node->rightChild);
	}

	return count;
}

template<class T>
int ChainBinaryTree<T>::levelWithMostnodes() const {
	int maxnodes = 1;
	int maxlevel = 1;

	std::queue<BinaryTreeNode<T>*>* q = new std::queue<BinaryTreeNode<T>*>;
	q->push(root);

	std::queue<BinaryTreeNode<T>*>* q2 = nullptr;
	int count = 0;
	while (q->size() > 0) {
		if (q2 == nullptr){
			q2 = new std::queue<BinaryTreeNode<T>*>;
			count = 0;
		}
		
		BinaryTreeNode<T>* node = q->front();
		q->pop();
		if (node->leftChild) {
			++count;
			q2->push(node->leftChild);
		}
		if (node->rightChild) {
			++count;
			q2->push(node->rightChild);
		}
		if (q->size() == 0) {
			if (count > maxnodes) {
				++maxlevel;
				maxnodes = count;
			}
			delete q;
			q = q2;
			q2 = nullptr;
		}
	}
	delete q;
	return maxlevel;
}

template<class T>
template <class Pred> void ChainBinaryTree<T>::inOrderNoRecursive(Pred func) const {
	std::stack<BinaryTreeNode<T>*> st;

	st.push(root);
	BinaryTreeNode<T>* node = root->leftChild;
	while (node || !st.empty()) {
		while (node) {
			st.push(node);
			node = node->leftChild;
		}
		node = st.top();
		st.pop();

		func(node->element);
		node = node->rightChild;
	}
}

template<class T>
template <class Pred> void ChainBinaryTree<T>::preOrderNoRecursive(Pred func) const {
	std::stack<BinaryTreeNode<T>*> st;

	BinaryTreeNode<T>* node = root;
	while (node || !st.empty()) {
		if (node) {
			func(node->element);
			if (node->rightChild)
				st.push(node->rightChild);
			if (node)
				node = node->leftChild;
		}
		else {
			node = st.top();
			st.pop();
		}
	}
}

template<class T>
template <class Pred> void ChainBinaryTree<T>::postOrderNoRecursive(Pred func) const {
	std::stack<BinaryTreeNode<T>*> st;

	BinaryTreeNode<T>* node = root;
	BinaryTreeNode<T>* tmp = nullptr;
	while (node || !st.empty()) {
		if (node) {
			st.push(node);
			node = node->leftChild;
		}
		else {
			node = st.top();
			if (node->rightChild && node->rightChild != tmp) {
				node = node->rightChild;
			}
			else {
				func(node->element);
				st.pop();
				tmp = node;
				node = nullptr;
			}
		}
	}
}

template<class T>
bool ChainBinaryTree<T>::splitStr(const std::string& c, const std::string& inStr, std::string& outStr1, std::string& outStr2) {
	auto pos = inStr.find(c);
	if (std::string::npos == pos)
		return false;

	outStr1 = inStr.substr(0, pos);
	if(pos +1 < inStr.size())
		outStr2 = inStr.substr(pos+1);
	return true;
}

template<class T>
void ChainBinaryTree<T>::createTreePreAndInOrder(const std::string& preStr, const std::string& inStr) {
	std::string c = preStr.substr(0, 1);
	root->element = c;
	std::string strLeft, strRight;
	if (splitStr(c, inStr, strLeft, strRight)) {
		if (strLeft != "") {
			root->leftChild = createSubtreePreAndInOrder(root, preStr.substr(1, strLeft.size()), strLeft);
		}
		if (strRight != "") {
			root->rightChild = createSubtreePreAndInOrder(root, preStr.substr(1 + strLeft.size()), strRight);
		}
	}
}

template<class T>
void ChainBinaryTree<T>::createTreePreAndPostOrder(const std::string& preStr, const std::string& postStr) {
	std::string c = preStr.substr(0, 1);
	root->element = c;
	if (preStr.size() == 1)
		return;
	c = preStr.substr(1, 1);
	std::string strLeft, strRight;
	if (splitStr(c, postStr.substr(0, postStr.size() - 1), strLeft, strRight)) {
		strLeft += c;
		root->leftChild = createSubreePreAndPostOrder(preStr.substr(1, strLeft.size()), strLeft);
		if (strRight != "") {
			root->rightChild = createSubreePreAndPostOrder(preStr.substr(1 + strLeft.size()), strRight);
		}
	}
}

template<class T>
void ChainBinaryTree<T>::createTreePostAndInOrder(const std::string& postStr, const std::string& inStr) {
	std::string c = postStr.substr(postStr.size()-1, 1);
	root->element = c;
	std::string strLeft, strRight;
	if (splitStr(c, inStr, strLeft, strRight)) {
		if (strLeft != "") {
			root->leftChild = createSubreePostAndInOrder(root, postStr.substr(0, strLeft.size()), strLeft);
		}
		if (strRight != "") {
			root->rightChild = createSubreePostAndInOrder(root, postStr.substr(strLeft.size(), strRight.size()), strRight);
		}
	}
}


template<class T>
BinaryTreeNode<T>* ChainBinaryTree<T>::createSubtreePreAndInOrder(BinaryTreeNode<T>* node, const std::string& preStr, const std::string& inStr) {
	std::string c = preStr.substr(0, 1);
	std::string strLeft, strRight;
	if (splitStr(c, inStr, strLeft, strRight)) {
		BinaryTreeNode<T>* left = nullptr;
		BinaryTreeNode<T>* right = nullptr;
		if (strLeft != "") {
			left = createSubtreePreAndInOrder(node, preStr.substr(1, strLeft.size()), strLeft);
		}
		if (strRight != "") {
			right = createSubtreePreAndInOrder(node, preStr.substr(1+ strLeft.size()), strRight);
		}
		return new BinaryTreeNode<T>(std::string(c), left, right);
	}
	return nullptr;
}

template<class T>
BinaryTreeNode<T>* ChainBinaryTree<T>::createSubreePreAndPostOrder(const std::string& preStr, const std::string& postStr) {
	std::string c = preStr.substr(0, 1);
	BinaryTreeNode<T>* node = new BinaryTreeNode<T>(std::string(c));
	if (preStr.size() != 1) {
		c = preStr.substr(1, 1);
		std::string strLeft, strRight;
		if (splitStr(c, postStr.substr(0, postStr.size() - 1), strLeft, strRight)) {
			strLeft += c;
			node->leftChild = createSubreePreAndPostOrder(preStr.substr(1, strLeft.size()), strLeft);
			if (strRight != "") {
				node->rightChild = createSubreePreAndPostOrder(preStr.substr(1 + strLeft.size()), strRight);
			}
		}
	}
	return node;
}

template<class T>
BinaryTreeNode<T>* ChainBinaryTree<T>::createSubreePostAndInOrder(BinaryTreeNode<T>* node, const std::string& postStr, const std::string& inStr) {
	std::string c = postStr.substr(postStr.size()-1, 1);
	std::string strLeft, strRight;
	if (splitStr(c, inStr, strLeft, strRight)) {
		BinaryTreeNode<T>* left = nullptr;
		BinaryTreeNode<T>* right = nullptr;
		if (strLeft != "") {
			left = createSubreePostAndInOrder(node, postStr.substr(0, strLeft.size()), strLeft);
		}
		if (strRight != "") {
			right = createSubreePostAndInOrder(node, postStr.substr(strLeft.size(), strRight.size()), strRight);
		}
		return new BinaryTreeNode<T>(std::string(c), left, right);
	}
	return nullptr;
}
#endif
