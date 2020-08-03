#ifndef _BSTREE_H
#define _BSTREE_H

#include "../DS10/dictionary.h"

template<class K, class E>
class BSTree : public  dictionary<K, E>{
public:
	virtual void ascend() = 0;
};

#endif