#include "Concordance.h"
#include <iostream>
#include <sstream>

std::string Concordance::getIndex(const std::string& word) const {
	std::string result;
	auto iter = concord.find(word);
	if (iter != concord.end()) {
		auto& set = iter->second;
		for (auto it2 = set.cbegin(); it2 != set.cend(); ++it2) {
			result+= *it2;
			result += " ";
		}
	}
	return result;
}

std::ostream& Concordance::output(std::ostream& out) const {
	for (auto it = concord.cbegin(); it != concord.cend(); ++it) {
		out << it->first << ":\t";
		for (auto it2 = it->second.cbegin(); it2 != it->second.cend(); ++it2) {
			out << *it2 << " ";
		}
		out << std::endl;
	}
	return out;
}

void Concordance::readFile(std::ifstream& in) {
	std::string s;
	while (std::getline(in, s)) {
		text.push_back(s);
	}
}

void Concordance::constructIndex() {
	for (int i = 0; i < text.size(); ++i) {
		std::string line = text[i];
		std::istringstream iss(line);
		std::string word;
		while (iss >> word) {
			auto it = concord.find(word);
			if (it != concord.end()) {
				it->second.insert(i + 1);
			}
			else {
				std::set<int> st{i+1};
				concord.insert({ word, st });
			}
		}
	}
}