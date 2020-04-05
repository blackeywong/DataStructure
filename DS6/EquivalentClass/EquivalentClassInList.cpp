#include <string>
#include <vector>
#include "EquivalentClassInList.h"
//数据结构算法与应用-C++语言描述 第六章
//Exercise 76
EquivalentClassInList::EquivalentClassInList(int numberOfElements) {
	n = numberOfElements;
	equivClass = new int[n + 1];
	for (int e = 1; e <= n; e++) {
		equivClass[e] = e;
	}
}

void EquivalentClassInList::unite(int classA, int classB) {
	for (int k = 1; k <= n; k++) {
		if (equivClass[k] == classB) {
			equivClass[k] = classA;
		}
	}
}

int EquivalentClassInList::find(int theElement) const {
	return equivClass[theElement];
}


void EquivalentClassInList::output(ostream& out) const{
	vector<string> v;
	for(int i=0;i<=n;i++){
		v.push_back("");
	}
	
	for(int i=1;i<=n;i++){
		v[equivClass[i]].append(to_string(i));
		v[equivClass[i]].append(", ");
	}

	for(int i=1;i<=n;i++){
		if(v[i] != ""){
			v[i].pop_back();v[i].pop_back();//remove the last ", "
			out << "class " << i << " : {" << v[i] <<"} ";
		}
	}
}

ostream& operator<<(ostream& out, EquivalentClassInList& ec){
	ec.output(out);
	return out;
}