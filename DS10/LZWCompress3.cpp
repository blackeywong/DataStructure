#include "LZWCompress3.h"
#include "HashChain.h"
#include "sortedChain.h"
#include "HashTable.h"
#include <map>
//Exercise 47
const int RESET_BASE = 1024;
const int RESET_RATE = 50;
//compress a 152KB file:
//0:	98KB
//10:	102KB
//20:	98KB
//30:	97KB
//40:	95KB
//50:	97KB

LZWCompress3::LZWCompress3(std::string theInFile, std::string theOutFile) {
	bitsLeftOver = false;
	in.open(theInFile, std::ifstream::in | std::ifstream::binary);
	out.open(theOutFile, std::ifstream::out | std::ifstream::binary);
}

LZWCompress3::~LZWCompress3() {
}

void LZWCompress3::output(long pcode) {
	short c, d;
	if (bitsLeftOver) {
		d = short(pcode & MASK1);
		c = short((leftOver << EXCESS) | (pcode >> BYTE_SIZE));
		out.put(c);
		out.put(d);
		bitsLeftOver = false;
	}
	else {
		leftOver = pcode & MASK2;
		c = short(pcode >> EXCESS);
		out.put(c);
		bitsLeftOver = true;
	}
}

void LZWCompress3::compress() {
	HashChain<long, short> h(DIVISOR);
	//sortedChain<long, short> h;
	//HashTable<long, short> h(DIVISOR);
	//std::map<long, short> h;
	int count = 0;

	while (true) {
		h.reset();
		int codeUsed = ALPHA;
		bitsLeftOver = false;
		leftOver = 0;
		int c = in.get();
		++count;
		if (c != EOF) {
			long pcode = c;
			while ((c = in.get()) != EOF) {
				//Exercise 47
				++count;
				long theKey = (pcode << BYTE_SIZE) + c;
				pairTypeCompress* thePair = h.find(theKey);
				//auto p = h.find(theKey);
				if (thePair == nullptr) {
					//if (p == h.end()) {
					output(pcode);
					if (codeUsed < MAX_CODES) {
						h.insert(pairTypeCompress((pcode << BYTE_SIZE) | c, codeUsed++));
					}
					pcode = c;
				}
				else {
					pcode = thePair->second;
					//pcode = p->second;
				}
				//std::cout << count << " " << count % (RESET_BASE * RESET_RATE) << std::endl;
				if (count % (RESET_BASE * RESET_RATE) == 0) {
					break;
				}
			}
			output(pcode);
			if (bitsLeftOver) {
				out.put(leftOver << EXCESS);
			}
			if (c == EOF)
				break;
		}
		else
			break;
	}
	in.close();
	out.close();
}



LZWUnCompress3::LZWUnCompress3(std::string theInFile, std::string theOutFile) {
	bitsLeftOver = false;
	in.open(theInFile, std::ifstream::in | std::ifstream::binary);
	out.open(theOutFile, std::ifstream::out | std::ifstream::binary);

	ht = new pairTypeUncompress[MAX_CODES];
	s = new char[MAX_CODES];
}

LZWUnCompress3::~LZWUnCompress3() {
	delete ht;
	delete s;
}

void LZWUnCompress3::output(short code) {
	size = -1;
	while (code >= ALPHA) {
		s[++size] = ht[code].second;
		code = ht[code].first;
	}
	s[++size] = (char)code;

	for (int i = size; i >= 0; --i) {
		out.put(s[i]);
		++count;
	}
}

bool LZWUnCompress3::getCode(short& code) {
	short c, d;
	if ((c = in.get()) == EOF) {
		return false;
	}

	if (bitsLeftOver) {
		code = (leftOver << BYTE_SIZE) | c;
	}
	else {
		d = in.get();
		code = (c << EXCESS) | (d >> EXCESS);
		leftOver = d & MASK2;
	}
	bitsLeftOver = !bitsLeftOver;
	return true;
}

void LZWUnCompress3::uncompress() {
	count = 0;
	short pcode, ccode;
	while (true) {
		delete ht;
		ht = new pairTypeUncompress[MAX_CODES];
		int codeUsed = ALPHA;
		bitsLeftOver = false;
		leftOver = 0;
		if (getCode(pcode)) {
			s[0] = (char)pcode;
			out.put(s[0]);
			++count;
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
				//Exercise 47
				//std::cout << count << " " << count % (RESET_BASE * RESET_RATE) << std::endl;
				if (count % (RESET_BASE * RESET_RATE) == 0) {
					break;
				}
			}
			if ((ccode = in.get()) == EOF)
				break;
			else
				in.putback((char)ccode);
		}
		else
			break;
	}
	in.close();
	out.close();
}
