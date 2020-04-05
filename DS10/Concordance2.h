#pragma once
#ifndef _CONCORDANCE2_H
#define _CONCORDANCE2_H

#include "HashChain.h"
#include "sortedChain.h"
#include <utility>
#include <string>
#include <fstream>
#include <vector>
#include <set>
//Exercise 48
class Concordance2 {
public:
	explicit Concordance2(const std::string& file) { std::ifstream in(file);	readFile(in); constructIndex(); }
	inline ~Concordance2() { delete concord; }

	std::string getIndex(const std::string& word) const;
	std::ostream& output(std::ostream& out) const;

private:
	void readFile(std::ifstream& in);
	void constructIndex();

	std::vector<std::string> text;
	//HashChain<std::string, std::set<int>>* concord;
	HashChain<std::string, std::string>* concord;

};

#endif