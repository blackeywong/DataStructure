#include "LZWCompress2.h"
#include "HashChain.h"
#include "sortedChain.h"
#include "HashTable.h"
#include <map>

LZWCompress2::LZWCompress2(std::string theInFile, std::string theOutFile) {
	in.open(theInFile, std::ifstream::in | std::ifstream::binary);
	out.open(theOutFile, std::ifstream::out | std::ifstream::binary);
}

LZWCompress2::~LZWCompress2() {
}

void LZWCompress2::output(short pcode) {
	char c = (char) (pcode & MASK);
	out.put(c);
}

void LZWCompress2::initDict(HashChain<short, char>* dict) {
	char c = 'a';
	short i = 0;
	dict->insert(pairTypeCompress{ '\0', i++ });
	for (; i < 27; ++i) {
		dict->insert(pairTypeCompress{ c++, i });
	}
	c = '0';
	for (; i < 37; ++i) {
		dict->insert(pairTypeCompress{ c++, i });
	}
	dict->insert(pairTypeCompress{ ' ', i++ });//37
	dict->insert(pairTypeCompress{ '\t', i++ });
	dict->insert(pairTypeCompress{ '\r', i++ });
	dict->insert(pairTypeCompress{ '\n', i++ });
	dict->insert(pairTypeCompress{ '.', i++ });
	dict->insert(pairTypeCompress{ ',', i++ });
	dict->insert(pairTypeCompress{ ';', i++ });
	dict->insert(pairTypeCompress{ ':', i++ });//44

	//c = 'A';
	//for (; i < 70; ++i) {
	//	dict->insert(pairTypeCompress{ c++, i });
	//}
	//dict->insert(pairTypeCompress{ '`', i++ });//70
	//dict->insert(pairTypeCompress{ '~', i++ });
	//dict->insert(pairTypeCompress{ '!', i++ });
	//dict->insert(pairTypeCompress{ '@', i++ });
	//dict->insert(pairTypeCompress{ '#', i++ });
	//dict->insert(pairTypeCompress{ '$', i++ });
	//dict->insert(pairTypeCompress{ '%', i++ });
	//dict->insert(pairTypeCompress{ '^', i++ });
	//dict->insert(pairTypeCompress{ '&', i++ });
	//dict->insert(pairTypeCompress{ '*', i++ });
	//dict->insert(pairTypeCompress{ '(', i++ });
	//dict->insert(pairTypeCompress{ ')', i++ });
	//dict->insert(pairTypeCompress{ '-', i++ });
	//dict->insert(pairTypeCompress{ '_', i++ });
	//dict->insert(pairTypeCompress{ '=', i++ });
	//dict->insert(pairTypeCompress{ '+', i++ });
	//dict->insert(pairTypeCompress{ '[', i++ });
	//dict->insert(pairTypeCompress{ ']', i++ });
	//dict->insert(pairTypeCompress{ '{', i++ });
	//dict->insert(pairTypeCompress{ '}', i++ });
	//dict->insert(pairTypeCompress{ '\\', i++ });
	//dict->insert(pairTypeCompress{ '|', i++ });
	//dict->insert(pairTypeCompress{ '\'', i++ });
	//dict->insert(pairTypeCompress{ '"', i++ });
	//dict->insert(pairTypeCompress{ '<', i++ });
	//dict->insert(pairTypeCompress{ '>', i++ });
	//dict->insert(pairTypeCompress{ '/', i++ });
	//dict->insert(pairTypeCompress{ '?', i++ });
	//dict->insert(pairTypeCompress{ '\v', i++ });//98
}


void LZWCompress2::compress() {
	HashChain<short, char> h(DIVISOR);
	initDict(&h);

	int codeUsed = ALPHA;

	int c = in.get();
	if (c != EOF) {
		short theKey = c;
		pairTypeCompress* thePair = h.find(theKey);
		if (thePair == nullptr) {
			return;
		}
		short pcode = thePair->second;
		//output(pcode);
		while ((c = in.get()) != EOF) {
			//std::cout << (char)c;
			theKey = (pcode << BYTE_SIZE) + c;
			thePair = h.find(theKey);
			if (thePair == nullptr) {
				output(pcode);
				if (codeUsed < MAX_CODES) {
					h.insert(pairTypeCompress((pcode << BYTE_SIZE) | c, codeUsed++));
				}
				pcode = h.find(c)->second;
			}
			else {
				pcode = thePair->second;
			}
		}
		output(pcode);
	}
	in.close();
	out.close();
}




LZWUnCompress2::LZWUnCompress2(std::string theInFile, std::string theOutFile) {
	in.open(theInFile, std::ifstream::in | std::ifstream::binary);
	out.open(theOutFile, std::ifstream::out | std::ifstream::binary);

	ht = new pairTypeUncompress[MAX_CODES];
	s = new char[MAX_CODES];
}

LZWUnCompress2::~LZWUnCompress2() {
	delete ht;
	delete s;
}

void LZWUnCompress2::output(char code) {
	size = -1;
	while (code >= ALPHA) {
		s[++size] = ht[code].second;
		code = ht[code].first;
	}
	s[++size] = ht[code].second;

	for (int i = size; i >= 0; --i) {
		//std::cout << s[i];
		out.put(s[i]);
	}
}

void LZWUnCompress2::initDict(std::pair<char, char>* dict) {
	char c = 'a';
	short i = 0;
	dict[i++] = {'\0', '\0'};
	for (; i < 27; ++i) {
		dict[i] = { i, c++ };
	}
	c = '0';
	for (; i < 37; ++i) {
		dict[i] = { i, c++ };
	}
	dict[i++] = { 37, ' ' };//37
	dict[i++] = { 38, '\t' };
	dict[i++] = { 39, '\r' };
	dict[i++] = { 40, '\n' };
	dict[i++] = { 41, '.' };
	dict[i++] = { 42, ',' };
	dict[i++] = { 43, ';' };
	dict[i++] = { 44, ':' };//44

	//c = 'A';
	//for (; i < 70; ++i) {
	//	dict[i] = { i, c++ };
	//}
	//dict[i++] = { 70, '`' };//70
	//dict[i++] = { 71, '~' };
	//dict[i++] = { 72, '!' };
	//dict[i++] = { 73, '@' };
	//dict[i++] = { 74, '#' };
	//dict[i++] = { 75, '$' };
	//dict[i++] = { 76, '%' };
	//dict[i++] = { 77, '^' };
	//dict[i++] = { 78, '&' };
	//dict[i++] = { 79, '*' };
	//dict[i++] = { 80, '(' };
	//dict[i++] = { 81, ')' };
	//dict[i++] = { 82, '-' };
	//dict[i++] = { 83, '_' };
	//dict[i++] = { 84, '=' };
	//dict[i++] = { 85, '+' };
	//dict[i++] = { 86, '[' };
	//dict[i++] = { 87, ']' };
	//dict[i++] = { 88, '{' };
	//dict[i++] = { 89, '}' };
	//dict[i++] = { 90, '\\' };
	//dict[i++] = { 91, '|' };
	//dict[i++] = { 92, '\'' };
	//dict[i++] = { 93, '"' };
	//dict[i++] = { 94, '<' };
	//dict[i++] = { 95, '>' };
	//dict[i++] = { 96, '/' };
	//dict[i++] = { 97, '?' };
	//dict[i++] = { 98, '\v' };//98
}

bool LZWUnCompress2::getCode(char& code) {
	int c;
	if ((c = in.get()) == EOF) {
		return false;
	}

	code = c;
	return true;
}

void LZWUnCompress2::uncompress() {
	initDict(ht);
	int codeUsed = ALPHA;

	char pcode, ccode;
	if (getCode(pcode)) {
		s[0] = ht[pcode].second;
		out.put(s[0]);
		size = 0;

		while (getCode(ccode)) {
			if (ccode < codeUsed) {
				output(ccode);
				if (codeUsed < MAX_CODES) {
					ht[codeUsed].first = pcode;
					ht[codeUsed++].second = s[size];
				}
			}
			else {
				ht[codeUsed].first = pcode;
				ht[codeUsed++].second = s[size];
				output(ccode);
			}
			pcode = ccode;
		}
	}

	in.close();
	out.close();
}
