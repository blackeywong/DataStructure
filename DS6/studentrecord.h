#ifndef _STUDENTRECORD_H
#define _STUDENTRECORD_H
#include <iostream>
#include <string>
#include "chain.h"
using namespace std;

struct StudentRecord{
	int score;
	string name;

	StudentRecord(){}
	StudentRecord(const string name, const int score){this->name = name; this->score = score;}
	StudentRecord(const string name, const string score){
		this->name = name;
		this->score = stoi(score);
	}
	StudentRecord(const StudentRecord& rec){name=rec.name;score=rec.score;}

	StudentRecord& operator=(const StudentRecord& rec){name=rec.name;score=rec.score;return *this;}
	bool operator!=(const StudentRecord& x) const
	{return score != x.score;}
	operator int() const {return score;}
};
ostream& operator<<(ostream& out, const StudentRecord& x);
Chain<StudentRecord>& constructStudentRecordChain(string filename);

int getStudentScore(ChainNode<StudentRecord>* node);

#endif