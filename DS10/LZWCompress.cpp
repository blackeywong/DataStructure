#include "LZWCompress.h"
#include "HashChain.h"
#include "sortedChain.h"
#include "HashTable.h"
#include <map>


LZWCompress::LZWCompress(std::string theInFile, std::string theOutFile) {
	bitsLeftOver = false;
	in.open(theInFile, std::ifstream::in | std::ifstream::binary);
	out.open(theOutFile, std::ifstream::out | std::ifstream::binary);
}

LZWCompress::~LZWCompress(){
}

void LZWCompress::output(long pcode) {
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

void LZWCompress::compress() {
	HashChain<long, short> h(DIVISOR);
	//sortedChain<long, short> h;
	//HashTable<long, short> h(DIVISOR);
	//std::map<long, short> h;
	for (int i = 0; i < ALPHA; ++i){
		h.insert(pairTypeCompress(i, i));
	}
	int codeUsed = ALPHA;

	int c = in.get();
	if (c != EOF) {
		long pcode = c;
		while ((c = in.get()) != EOF) {
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
		}

		output(pcode);
		if (bitsLeftOver) {
			out.put(leftOver << EXCESS);
		}
	}
	in.close();
	out.close();

}



LZWUnCompress::LZWUnCompress(std::string theInFile, std::string theOutFile) {
	bitsLeftOver = false;
	in.open(theInFile, std::ifstream::in | std::ifstream::binary);
	out.open(theOutFile, std::ifstream::out | std::ifstream::binary);

	ht = new pairTypeUncompress[MAX_CODES];
	s = new char[MAX_CODES];
}

LZWUnCompress::~LZWUnCompress() {
	delete ht;
	delete s;
}

void LZWUnCompress::output(short code) {
	size = -1;
	while (code >= ALPHA) {
		s[++size] = ht[code].second;
		code = ht[code].first;
	}
	s[++size] = (char)code;

	for (int i = size; i >= 0; --i) {
		out.put(s[i]);
	}
}

bool LZWUnCompress::getCode(short& code) {
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

void LZWUnCompress::uncompress() {
	//for (int i = 0; i < ALPHA; ++i) {
	//	ht[i].second = i;
	//}
	int codeUsed = ALPHA;

	short pcode, ccode;
	if (getCode(pcode)) {
		s[0] = (char)pcode;
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
