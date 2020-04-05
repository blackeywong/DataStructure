#include <algorithm>
#include <vector>
#include <string>
#include "EquivalentClassInChain.h"

using namespace std;
//数据结构算法与应用-C++语言描述 第六章
//Exercise 77
EquivalentClassInChain::EquivalentClassInChain(int numberOfElements) {
	n = numberOfElements;
	node.push_back(nullptr);
	
	for (int e = 1; e <= n; e++) {
		equivNode* aNode = new equivNode();
		aNode->equivClass = e;
		aNode->size = 1;
		aNode->next = nullptr;
		node.push_back(aNode);
	}
}

void EquivalentClassInChain::unite(int classA, int classB) {//suppose class != classB, and classA and classB are firstNode in chain
	if (node[classA]->size > node[classB]->size) {
		swap(classA, classB);
	}

	equivNode* cur;

	for (cur = node[classA]; cur->next != nullptr; cur = cur->next) {
		cur->equivClass = classB;
	}
	cur->equivClass = classB;

	//insert classA after firstnode of classB
	node[classB]->size += node[classA]->size;
	cur->next = node[classB]->next;
	node[classB]->next = cur;
}

int EquivalentClassInChain::find(int theElement) const{
	return node[theElement]->equivClass;
}

void EquivalentClassInChain::output(ostream& out) const{
	vector<string> v;
	for(int i=0;i<=n;i++){
		v.push_back("");
	}
	
	for(int i=1;i<=n;i++){
		v[node[i]->equivClass].append(to_string(i));
		v[node[i]->equivClass].append(", ");
	}

	for(int i=1;i<=n;i++){
		if(v[i] != ""){
			v[i].pop_back();v[i].pop_back();//remove the last ", "
			out << "class " << i << " : {" << v[i] <<"} ";
		}
	}
}

ostream& operator<<(ostream& out, EquivalentClassInChain& ec){
	ec.output(out);
	return out;
}