#pragma once
#ifndef _CONCORDANCE_H
#define _CONCORDANCE_H

#include <map>
#include <utility>
#include <string>
#include <set>
#include <fstream>
#include <vector>
//Exercise 48
class Concordance {
public:
	using Index = std::pair<std::string, std::set<int>>;
	
	explicit Concordance(const std::string& file) {	std::ifstream in(file);	readFile(in);constructIndex();}
	inline ~Concordance() {}

	std::string getIndex(const std::string& word) const;
	std::ostream& output(std::ostream& out) const;

private:
	void readFile(std::ifstream& in);
	void constructIndex();
	
	std::vector<std::string> text;
	std::map<std::string, std::set<int>> concord;

};

#endif