#include <algorithm>
#include <vector>
#include <string>
#include "EquivalentClassInSimChain.h"

using namespace std;
//数据结构算法与应用-C++语言描述 第六章
//Exercise 73
EquivalentClassInSimChain::EquivalentClassInSimChain(int numberOfElements) {
	n = numberOfElements;
	node = new equivNode[n + 1];
	for (int e = 1; e <= n; e++) {
		node[e].equivClass = e;
		node[e].size = 1;
		node[e].next = 0;
	}
}

void EquivalentClassInSimChain::unite(int classA, int classB) {//suppose class != classB, and classA and classB are firstNode in chain
	if (node[classA].size > node[classB].size) {
		swap(classA, classB);
	}

	int k;

	for (k = classA; node[k].next != 0; k = node[k].next) {
		node[k].equivClass = classB;
	}
	node[k].equivClass = classB;

	//insert classA after firstnode of classB
	node[classB].size += node[classA].size;
	node[k].next = node[classB].next;
	node[classB].next = classA;
}

int EquivalentClassInSimChain::find(int theElement) const{
	return node[theElement].equivClass;
}

void EquivalentClassInSimChain::output(ostream& out) const{
	vector<string> v;
	for(int i=0;i<=n;i++){
		v.push_back("");
	}
	
	for(int i=1;i<=n;i++){
		v[node[i].equivClass].append(to_string(i));
		v[node[i].equivClass].append(", ");
	}

	for(int i=1;i<=n;i++){
		if(v[i] != ""){
			v[i].pop_back();v[i].pop_back();//remove the last ", "
			out << "class " << i << " : {" << v[i] <<"} ";
		}
	}
}

ostream& operator<<(ostream& out, EquivalentClassInSimChain& ec){
	ec.output(out);
	return out;
}