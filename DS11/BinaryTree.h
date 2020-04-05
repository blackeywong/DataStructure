#ifndef _BINARYTREE_H
#define _BINARYTREE_H
#include <functional>

template<class T>
class BinaryTree {
public:
	virtual ~BinaryTree() {}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	//virtual void preOrder(void(*)(T*)) = 0;
	//virtual void inOrder(void(*)(T*)) = 0;
	//virtual void postOrder(void(*)(T*)) = 0;
	//virtual void levelOrder(void(*)(T*)) = 0;
	virtual void preOrder(std::function<void(T*)>) = 0;
	virtual void inOrder(std::function<void(T*)>) = 0;
	virtual void postOrder(std::function<void(T*)>) = 0;
	virtual void levelOrder(std::function<void(T*)>) = 0;
};

#endif
