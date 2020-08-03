#ifndef _INDEXEDBSTREE_H
#define _INDEXEDBSTREE_H

#include "BSTree.h"

template<class K, class E>
class IndexedBSTree : public  BSTree<K, E> {
public:
	virtual std::pair<K, E>* get(int) const = 0;
	virtual void deleteAt(int) = 0;
};

#endif