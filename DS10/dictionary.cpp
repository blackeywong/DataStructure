#include "dictionary.h"
#include <string>

int stringToInt(const std::string& s) {
	int length = (int)s.length();
	int answer = 0;
	for (int i = 0, j = 0; i < length; ++i) {
		j = i % 4;
		answer += s.at(i) << (j * 8);
	}

	return (answer < 0) ? -answer : answer;
}

int doubleToInt(double d) {
	unsigned long* plong = reinterpret_cast<unsigned long*>(&d);
	int answer = plong[0] + plong[1];
	
	return (answer < 0) ? -answer : answer;
}