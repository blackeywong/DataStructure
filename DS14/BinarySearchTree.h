#ifndef _BINARYSEARCHTREE_H
#define _BINARYSEARCHTREE_H

#include<algorithm>
#include<ctime>
#include<random>

#include "BSTree.h"
#include "../DS11/LinkedBinaryTree.h"

template<class K, class E> class Iterator;
template<class K, class E>
class BinarySearchTree : public LinkedBinaryTree<std::pair<K,E>>, public BSTree<K,E>{
	template<class K, class E> friend class Iterator;
public:
	BinarySearchTree():LinkedBinaryTree<std::pair<K, E>>() {}
	virtual ~BinarySearchTree() {}
	virtual bool empty() const  override { return LinkedBinaryTree<std::pair<K, E>>::empty(); }
	virtual int size() const  override { return LinkedBinaryTree<std::pair<K, E>>::size(); }
	virtual std::pair<K, E>* find(const K& theKey) const override;
	virtual void erase(const K& theKey) override;
	virtual void insert(const std::pair<K, E>& thePair) override;

	virtual void ascend() override;

	std::istream& input(std::istream& in);

	void outputInRange(const K& theLow, const K& theHigh) const; //Exercise 8
	virtual std::pair<K, E>* find2(const K& theKey) const;//Exercise 9

	std::pair<K, E>* split(const K& theKey, BinarySearchTree<K, E>* lessThan, BinarySearchTree<K, E>* greaterThan);//Exercise 12

	//Exercise 14
	Iterator<K,E> begin() { return Iterator<K,E>(*this); }
	Iterator<K,E> end() { return Iterator<K,E>(); }

	void eraseMax();//Exercise 15

	std::ostream& output(std::ostream& out, TRAVERSE_ORDER order = TRAVERSE_ORDER::INFIX);
protected:
	void outputInRange(BinaryTreeNode<std::pair<K,E>>* node,const K& theLow, const K& theHigh) const;
};


template<class K, class E>
std::pair<K, E>* BinarySearchTree<K, E>::find(const K& theKey) const
{
	BinaryTreeNode<std::pair<K, E>>* p = this->root;
	while (p != nullptr) {
		if (theKey < p->element.first) {
			p = p->leftChild;
		}
		else if (theKey > p->element.first) {
			p = p->rightChild;
		}
		else {
			return &p->element;
		}
	}
	return nullptr;
}

template<class K, class E>
inline std::pair<K, E>* BinarySearchTree<K, E>::find2(const K& theKey) const
{
	BinaryTreeNode<std::pair<K, E>>* p = this->root;
	while (p != nullptr) {
		if(theKey == p->element.first)
			return  &p->element;

		if (theKey < p->element.first) {
			p = p->leftChild;
		}
		else {
			p = p->rightChild;
		}
	}
	return nullptr;
}

template<class K, class E>
void BinarySearchTree<K, E>::erase(const K& theKey)
{
	BinaryTreeNode<std::pair<K, E>>* p = this->root;
	BinaryTreeNode<std::pair<K, E>>* pp = nullptr;

	//find the node of theKey
	while (p != nullptr && p->element.first != theKey) {
		pp = p;
		if (theKey < p->element.first) {
			p = p->leftChild;
		}
		else if (theKey > p->element.first) {
			p = p->rightChild;
		}
		else {
			return;
		}
	}
	if (p == nullptr)
		return;//cannot find theKey

	//when p has two childs
	if (p->leftChild != nullptr && p->rightChild != nullptr) {
		//find the max in leftChild of p
		BinaryTreeNode<std::pair<K, E>>* s = p->leftChild;
		BinaryTreeNode<std::pair<K, E>>* ps = p;

		while (s->rightChild != nullptr) {
			ps = s;
			s = s->rightChild;
		}

		//move max from s to p
		BinaryTreeNode<std::pair<K, E>>* q = new BinaryTreeNode<std::pair<K, E>>(s->element, p->leftChild, p->rightChild);
		if (pp == nullptr) {
			this->root = q;
		}
		else if(p == p->leftChild){
			pp->leftChild = q;
		}
		else {
			pp->rightChild = q;
		}

		if (ps == p) {
			pp = q;
		}
		else {
			pp = ps;
		}
		delete p;
		p = s;
	}

	//p has one child at most
	BinaryTreeNode<std::pair<K, E>>* c;
	if (p->leftChild != nullptr) {
		c = p->leftChild;
	}
	else {
		c = p->rightChild;
	}
	if (p == this->root) {
		this->root = c;
	}
	else {
		if (p == pp->leftChild) {
			pp->leftChild = c;
		}
		else {
			pp->rightChild = c;
		}
	}
	delete p;
	--this->treeSize;
}

template<class K, class E>
void BinarySearchTree<K, E>::insert(const std::pair<K, E>& thePair)
{
	BinaryTreeNode<std::pair<K, E>>* p = this->root;
	BinaryTreeNode<std::pair<K, E>> * pp = nullptr;

	while (p != nullptr) {
		pp = p;
		if (thePair.first < p->element.first) {
			p = p->leftChild;
		}
		else if (thePair.first > p->element.first) {
			p = p->rightChild;
		}
		else {
			p->element.second = thePair.second;
			return;
		}
	}

	BinaryTreeNode<std::pair<K, E>>* newNode = new BinaryTreeNode<std::pair<K, E>>(thePair);
	if (this->root != nullptr) {
		if (thePair.first < pp->element.first) {
			pp->leftChild = newNode;
		}
		else {
			pp->rightChild = newNode;
		}
	}
	else {
		this->root = newNode;
	}
	++this->treeSize;
}

template<class K, class E>
void BinarySearchTree<K, E>::ascend()
{
	LinkedBinaryTree<std::pair<K, E>>::output(std::cout, TRAVERSE_ORDER::INFIX);
	std::cout << std::endl;
}

template<class K, class E>
std::istream& BinarySearchTree<K, E>::input(std::istream& in) {
	int num;
	in >> num;

	for (int i = 0; i < num; ++i) {
		K k;
		E e;
		in >> k >> e;
		std::pair<K, E> p(k, e);
		insert(p);
	}
	return in;
}

template<class K, class E>
inline void BinarySearchTree<K, E>::outputInRange(const K& theLow, const K& theHigh) const
{
	outputInRange(this->root, theLow, theHigh);
	std::cout << std::endl;
}

template<class K, class E>
inline void BinarySearchTree<K, E>::outputInRange(BinaryTreeNode<std::pair<K, E>>* node, const K& theLow, const K& theHigh) const
{
	if (node == nullptr)
		return;

	if (node->element.first > theLow && node->leftChild != nullptr) {
		outputInRange(node->leftChild, theLow, theHigh);
	}

	if(node->element.first >= theLow && node->element.first <= theHigh)
		std::cout << node->element << " ";

	if (node->element.first < theHigh && node->rightChild != nullptr) {
		outputInRange(node->rightChild, theLow, theHigh);
	}
}

template<class K, class E>
std::pair<K, E>* BinarySearchTree<K, E>::split(const K& theKey, BinarySearchTree<K, E>* lessThan, BinarySearchTree<K, E>* greaterThan)
{
	//if empty tree
	if (this->root == nullptr) {
		return nullptr;
	}
	std::pair<K, E>* result = nullptr;
	BinaryTreeNode<std::pair<K, E>>* p = nullptr;
	BinaryTreeNode<std::pair<K, E>>* pr = nullptr;//parent node of the right subtree, waiting to set leftChild
	BinaryTreeNode<std::pair<K, E>>* pl = nullptr;//parent node of the left subtree, waiting to set rightChild
	int count = 0;
	auto countFunc = [&count](BinaryTreeNode<std::pair<K, E>>* p) {if (p)++count; };
	//except its element equals theKey
	if(theKey == this->root->element.first) {	
		lessThan->root = this->root->leftChild;
		greaterThan->root = this->root->rightChild;
		lessThan->inOrder(countFunc);
		lessThan->treeSize = count;
		count = 0;
		greaterThan->inOrder(countFunc);
		greaterThan->treeSize = count;
		count = 0;
		result = new std::pair<K, E>(this->root->element);
		delete this->root;
		this->root = nullptr;
		this->treeSize = 0;
		return result;
	}

	//otherwise original root must be root of one new tree
	if (theKey < this->root->element.first) {//the splitting point is in the left tree
		greaterThan->root = this->root;//original root is the new root of the tree bigger than theKey
		p = this->root;
		while (p != nullptr && theKey < p->element.first) {//root of lessThan must be the leftiest 'arm' of left sub-tree
			pr = p;
			p = p->leftChild;
		}
		pr->leftChild = nullptr;
		if (p == nullptr && theKey <= pr->element.first) {//no node smaller than theKey
			lessThan->root = nullptr;
		}
		else {
			lessThan->root = p;
			if (theKey == p->element.first) {
				result = new std::pair<K, E>(p->element);
				pr->leftChild = p->rightChild;
				lessThan->root = p->leftChild;
				delete p;
				p = nullptr;
			}
		}
	}
	else{//theKey > this->root->element.first
		lessThan->root = this->root;//original root is the new root of the tree bigger than theKey
		p = this->root;
		while (p != nullptr && p->element.first < theKey) {//root of greaterThan must be the rightiest 'arm' of right sub-tree
			pl = p;
			p = p->rightChild;
		}
		pl->rightChild = nullptr;
		if (p == nullptr && pl->element.first <= theKey ) {//no node greater than theKey
			greaterThan->root = nullptr;
		}
		else {
			greaterThan->root = p;
			if (theKey == p->element.first) {
				result = new std::pair<K, E>(p->element);
				pl->rightChild = p->leftChild;
				greaterThan->root = p->rightChild;
				delete p;
				p = nullptr;
			}
		}
	}
	//Get lessThan->root and greaterThan->root done. Next to adjust the two trees to assure correctness
	while (p != nullptr/* && (pr != nullptr || pl != nullptr)*/) {
		if (pr != nullptr) {//pr->leftChild is waiting to be set with nodes that are larger than theKey which are on rightist 'arm' of the tree whose root is p
			while (p != nullptr && p->element.first < theKey) {//search in the rightiest 'arm' of left sub-tree
				pl = p;
				p = p->rightChild;
			}
			pl->rightChild = nullptr;
			if (p != nullptr) {//there's node greater than theKey
				pr->leftChild = p;
				if (theKey == p->element.first) {
					result = new std::pair<K, E>(p->element);
					pr->leftChild = p->rightChild;
					pl->rightChild = p->leftChild;
					delete p;
					p = nullptr;
				}
			}
		}

		if (pl != nullptr) {//pl->rightChild is waiting to be set with nodes that are smaller than theKey which are on leftist 'arm' of the tree whose root is p
			while (p != nullptr && theKey < p->element.first) {//search in the leftiest 'arm' of right sub-tree
				pr = p;
				p = p->leftChild;
			}
			pr->leftChild = nullptr; 
			if (p != nullptr) {//there's node smaller than theKey
				pl->rightChild = p;
				if (theKey == p->element.first) {
					result = new std::pair<K, E>(p->element);
					pl->rightChild = p->leftChild;
					pr->leftChild = p->rightChild;
					delete p;
					p = nullptr;
				}
			}
		}
	}

	lessThan->inOrder(countFunc);
	lessThan->treeSize = count;
	count = 0;
	greaterThan->inOrder(countFunc);
	greaterThan->treeSize = count;
	this->root = nullptr;
	this->treeSize = 0;

	return result;
}

template<class K, class E>
void BinarySearchTree<K, E>::eraseMax()
{
	BinaryTreeNode<std::pair<K, E>>* p = this->root;
	BinaryTreeNode<std::pair<K, E>>* pp = nullptr;
	while (p != nullptr) {
		if (p->rightChild != nullptr) {
			pp = p;
			p = p->rightChild;
		}
		else {
			if (pp == nullptr) {
				this->root = p->leftChild;
			}
			else {
				pp->rightChild = p->leftChild;
			}
			delete p;
			--this->treeSize;
			return;
		}
	}
}
template<class K, class E>
inline std::ostream& BinarySearchTree<K, E>::output(std::ostream& out, TRAVERSE_ORDER order)
{
	auto func = [&out](BinaryTreeNode<std::pair<K, E>>* t) {out << t->element.first << "," << t->element.second << "\t"; };
	switch (order) {
	case TRAVERSE_ORDER::PREFIX: LinkedBinaryTree<std::pair<K, E>>::preOrder(func); break;
	case TRAVERSE_ORDER::INFIX: LinkedBinaryTree<std::pair<K, E>>::inOrder(func); break;
	case TRAVERSE_ORDER::POSTFIX: LinkedBinaryTree<std::pair<K, E>>::postOrder(func); break;
	case TRAVERSE_ORDER::LEVEL: LinkedBinaryTree<std::pair<K, E>>::levelOrder(func); break;
	}
	return out;
}
//////////////////////////////////////////////////////////////////////////////////////////////

template<class K, class E>
class Iterator {
public:
	typedef std::forward_iterator_tag iterator_capacity;
	typedef std::pair<K, E> value_type;
	typedef ptrdiff_t difference_type;
	typedef std::pair<K, E>* pointer;
	typedef std::pair<K, E>& reference;

	Iterator() { this->node = nullptr; }
	explicit Iterator(BinarySearchTree<K, E>& t) {
		BinaryTreeNode<std::pair<K, E>>* n = nullptr;
		if (t.root)
			n = t.root;
		while (n->leftChild) {
			stack.push(n);
			n = n->leftChild;
		}
		this->node = n;
	}

	std::pair<K, E>& operator*() const { return node->element; }
	std::pair<K, E>* operator->() const { return &node->element; }


	Iterator<K, E>& operator++() {
		if (this->node->rightChild != nullptr) {
			this->node = this->node->rightChild;
			BinaryTreeNode<std::pair<K, E>>* n = this->node;
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

	Iterator<K,E> operator++(int) { Iterator<K, E> old = *this; operator++(); return old; }


	Iterator(const Iterator<K, E>& t) { this->node = t.node; stack = t.stack; }

	bool operator!=(const Iterator& right) const { return node != right.node; }
	bool operator==(const Iterator& right) const { return node == right.node; }

	void swap(Iterator<K, E>& right) { using std::swap; swap(this->node->element, right.node->element); }
protected:
	BinaryTreeNode<std::pair<K, E>>* node;
	std::stack<BinaryTreeNode<std::pair<K, E>>*> stack;
};

template<class K, class E> void swap(Iterator<K, E>& it1, Iterator<K, E >& it2) { it1.swap(*it2); }

////////////////////////////////////////////////////////////////////////////////////
enum FIND_METHOD { FIND1, FIND2 };

template<class K, class E>
class TestBinarySearchTree {
public:
	explicit TestBinarySearchTree(int theSize);
	~TestBinarySearchTree() { delete[]keys; delete[]values; size = 0; }
	void testFind(FIND_METHOD find);
private:
	K* keys;
	E* values;
	int size;
};

template<class K, class E>
TestBinarySearchTree<K, E>::TestBinarySearchTree(int theSize) :size(theSize) {
	int lowBound = 1;
	int highBound = theSize;
	std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));
	std::uniform_int_distribution<int> u(lowBound, highBound);

	keys = new K[size + 1];
	values = new E[size + 1];
	for (int k = 1; k <= size; ++k) {
		keys[k] = u(e);
		values[k] = keys[k];
	}
}

template<class K, class E>
void TestBinarySearchTree<K, E>::testFind(FIND_METHOD method) {
	BinarySearchTree<K, E> bst;
	for (int i = 1; i <= size; ++i) {
		bst.insert(std::pair<K, E>(keys[i], values[i]));
	}

	clock_t start, finish;
	double insertTime = 0.0;
	if (method == FIND1) {
		start = clock();
		for (int i = 1; i <= size; ++i) {
			bst.find(keys[i]);
		}
		finish = clock();
	}
	else if (method == FIND2) {
		start = clock();
		for (int i = 1; i <= size; ++i) {
			bst.find2(keys[i]);
		}
		finish = clock();
	}

	std::cout << size << " Time cost: " << (double)(finish - start) / CLK_TCK << std::endl;
}
//Exercise 9
//10000 Time cost : 0.003
//10000 Time cost : 0.002
//100000 Time cost : 0.047
//100000 Time cost : 0.052
//1000000 Time cost : 1.16
//1000000 Time cost : 1.157
//10000000 Time cost : 20.368
//10000000 Time cost : 19.314
//100000000 Time cost : 304.436
//100000000 Time cost : 313.463



#endif
