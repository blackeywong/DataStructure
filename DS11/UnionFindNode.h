#pragma once
#ifndef _UNIONFINDNODE_H
#define _UNIONFINDNODE_H

struct UnionFindNode {
	int parent;//For root node: number of nodes for Weight rule, while height for Height rule
	bool root;

	UnionFindNode() :parent(1), root(true) {}

};

#endif