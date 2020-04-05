#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "studentrecord.h"

ostream& operator<<(ostream& out, const StudentRecord& x)
{out << x.score << ' ' <<x.name<<endl; return out;}

Chain<StudentRecord>& constructStudentRecordChain(string filename){
	Chain<StudentRecord>* chain = new Chain<StudentRecord>();
	vector<string> v;
	string s;
	ifstream file(filename);
	while(getline(file,s)){
		v.push_back(s);
	}
	file.close();
	stringstream ss;
	for(string str: v){
		ss.str(str);
		string name, score;
		ss >> name >> score;
		StudentRecord * rec = new StudentRecord(name, score);
		ss.clear();
		chain->insert(0,*rec);
	}


	return *chain;
}

int getStudentScore(ChainNode<StudentRecord>* node) {
	return node->element.score;
}

int getNumForRadixSort(ChainNode<StudentRecord>* node, int r, int d, int i) {
	int num = node->element;
	for (int k = 0; k < i; k++)
		num /= r;
	num %= r;
	return num;
}
