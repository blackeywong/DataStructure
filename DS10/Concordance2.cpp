#include "Concordance2.h"
#include <iostream>
#include <sstream>

std::string Concordance2::getIndex(const std::string& word) const {
	std::string result;
	auto p = concord->find(word);
	if (p != nullptr) {
		auto& set = p->second;
		std::ostringstream oss(result);
		oss << set;
		//for (auto it2 = set.cbegin(); it2 != set.cend(); ++it2) {
		//	result += *it2;
		//	result += " ";
		//}
	}
	return result;
}

std::ostream& Concordance2::output(std::ostream& out) const {
	//HashChain<std::string, std::string>::iterator iter = concord->begin();
	std::set<std::string> keys = concord->getKeys();
	for (auto iter = keys.begin(); iter != keys.end(); ++iter) {
		auto p = concord->find(*iter);
		std::string lines = p->second;
		std::istringstream iss(lines);
		std::string line;
		std::set<std::string> linenos;
		while (iss >> line) {
			linenos.insert(line);
		}
		std::string lnstr;
		for (auto iter = linenos.begin(); iter != linenos.end(); ++iter) {
			lnstr += *iter + " ";
		}
		out << *iter << ", " << lnstr << std::endl;
	}

	//for (auto iter = concord->begin(); iter != concord->end(); ++iter) {
	//	out << (*iter).first << ", " << (*iter).second << std::endl;
	//}
	return out;
	//return concord->output(out);
}

void Concordance2::readFile(std::ifstream& in) {
	std::string s;
	while (std::getline(in, s)) {
		text.push_back(s);
	}
}

void Concordance2::constructIndex() {
	concord = new HashChain<std::string, std::string>(65537, 0.6);
	//concord = new HashChain<std::string, std::set<int>>(65537, 0.6);

	for (unsigned int i = 0; i < text.size(); ++i) {
		std::string line = text[i];
		std::istringstream iss(line);
		std::string word;
		while (iss >> word) {
			auto p = concord->find(word);
			if (p != nullptr) {
				std::string str = p->second;
				str += " ";
				str += std::to_string(i + 1);
				concord->insert({ word, str });
			}
			else {
				concord->insert({ word, std::to_string(i + 1) });
				//std::set<int> st{ i + 1 };
				//concord->insert({ word, st });
			}
		}
	}
}