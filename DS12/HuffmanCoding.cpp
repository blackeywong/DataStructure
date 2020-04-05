#include "HuffmanCoding.h"

HuffmanCoding::HuffmanCoding(unsigned int theWeight[], unsigned int n, unsigned int* theElements) :weight(theWeight), elements(theElements), codes(nullptr), codeCount(n) {
	ht = new HuffmanTree<unsigned int>(weight, n, elements);
	//ht->draw();
	int height = ht->Height();
	if (height > sizeof(unsigned long long) * 8 + 1)
		throw std::exception("max bits exceed limits.");

	if (n > 0) {
		codes = new CodeBit[n];
	}

	unsigned int* accessFlag = new unsigned int[height];//0 means not access left & right childs, 1 means accessed left but right not, 2 means both all accessed, 3 means the subtree accessed
	for (int i = 0; i < height; ++i) {
		accessFlag[i] = 0;
	}

	for (unsigned int i = 0; i < n; ++i) {
		unsigned long long code = 0;
		unsigned int codeCount = 0;

		if (weight[i] == 0)
			continue;

		BinaryTreeNode<unsigned int>* curNode = ht->root;
		int j = 0;
		for (; j < height; ++j) {
			if (accessFlag[j] != 2 && curNode->leftChild != nullptr) {
				code = code << 1;
				if (accessFlag[j] == 0) {
					accessFlag[j] = 1;
				}
				curNode = curNode->leftChild;
			}
			else if (accessFlag[j] != 1 && curNode->rightChild != nullptr) {
				code = (code << 1) | 1;
				if (accessFlag[j] == 0) {
					accessFlag[j] = 2;
				}
				curNode = curNode->rightChild;
			}
			else if (curNode->leftChild == nullptr && curNode->rightChild == nullptr) {
				codes[curNode->element].code = code;
				//codes[i].code = code;
				if (height == 1) {//only one char
					codes[i].len = 1;
				}
				else {
					codes[curNode->element].len = j;
					//codes[i].len = j;
				}
				break;
			}
		}
		//set accessFlag to point to next path
		bool endFlag = false;
		for (int k = j - 1; k >= 0; --k) {
			if (accessFlag[k] == 1) {
				accessFlag[k] = 2;
				break;
			}
			else if (accessFlag[k] == 2) {
				accessFlag[k] = 0;
				if (k == 0) {
					endFlag = true;
					break;
				}
			}
		}
		if (endFlag) {
			break;
		}

		for (int k = j; k < height - 1; ++k) {
			if (accessFlag[k] != 0) {
				accessFlag[k] = 0;
			}
		}

	}
}

void HuffmanCoding::output(std::ostream& out) const {
	for (unsigned int i = 0; i < codeCount; ++i) {
		unsigned long long bitMask = 1;
		bitMask <<= codes[i].len - 1;
		std::string s = "";
		for (unsigned int j = 0; j < codes[i].len; ++j) {
			if (bitMask & codes[i].code) {
				s += '1';
			}
			else {
				s += '0';
			}
			bitMask >>= 1;
		}
		out << "Number [" << i << "] is coded to [" << s << "]" << endl;
	}
}

void HuffmanCoding::store(std::istream& in, std::ostream& out) const {
	//store weight array for re-creating Huffman tree
	unsigned int totalChars = 0;

	putInt(out, codeCount);
	for (unsigned int i = 0; i < codeCount; ++i) {
		putInt(out, weight[i]);
		totalChars += weight[i];
		if (elements) {
			putInt(out, elements[i]);
		}
		else {
			putInt(out, i);
		}
	}

	putInt(out, totalChars);

	unsigned char c = (unsigned char)readPlaintext(in);
	unsigned char d = 0;
	unsigned int bits = 0;

	while (!in.eof()) {
		//unsigned long long code = codes[c - 97].code;
		//int len = codes[c - 97].len;
		unsigned long long code = codes[c].code;
		unsigned int len = codes[c].len;
		if (bits + len < 8) {
			d |= code << (8 - bits - len);
			bits += len;
		}
		else {
			unsigned int bitsLeft = 8 - bits;
			d |= code >> (len - bitsLeft);
			writePlaintext(out, d);
			unsigned int j = 0;
			for (; j < (len - bitsLeft) / 8; ++j) {
				d = (unsigned char)(code >> (len - bitsLeft - 8 * (j+1)) & 255);
				writePlaintext(out, d);
				d = 0;
			}
			bits = len - bitsLeft - 8 * j;
			d = code & 127 >> (7-(len - bitsLeft - 8 * j));
			d = d << (8 - bits);
		}
		c = (unsigned char)readPlaintext(in);
	}
	
	if (bits != 0) {
		writePlaintext(out, d);
	}
}

void HuffmanCoding::read(std::istream& in, std::ostream& out) const {
	unsigned int totalChars = getInt(in);

	unsigned char c = (unsigned char)readPlaintext(in);
	unsigned char d = 0;
	unsigned int bits = 0;
	unsigned int readChars = 0;

	BinaryTreeNode<unsigned int>* curNode = ht->root;
	while (!in.eof()) {
		for (int i = 7; i >= 0 && readChars < totalChars; --i) {
			int bit = c >> i & 1;
			if (ht->height != 1) {
				if (bit == 0) {
					curNode = curNode->leftChild;
				}
				else {
					curNode = curNode->rightChild;
				}
			}
			if (curNode->leftChild == nullptr && curNode->rightChild == nullptr) {
				d = curNode->element;
				out.put(d);
				++readChars;
				curNode = ht->root;
			}
		}
		c = (unsigned char)readPlaintext(in);
	}

}

unsigned int HuffmanCoding::readPlaintext(std::istream& in) const {
	unsigned char c = 0;
	if (!in.eof()) {
		c = in.get();
	}
	return c;
}

void HuffmanCoding::writePlaintext(std::ostream& out, unsigned int n) const {
	unsigned char c = (unsigned char)n;
	out.put(c);
}


int getInt(std::istream& in) {
	int sz = sizeof(int);
	unsigned char c = 0;
	unsigned int n = 0;
	for (int i = 0; i < sz; ++i) {
		c = in.get();
		n = n << 8 | c;
	}
	return n;
}

void putInt(std::ostream& out, unsigned int n) {
	int sz = sizeof(int);
	unsigned char c = 0;
	for (int i = sz-1; i >= 0; --i) {
		c = n >> i * 8;
		out.put(c);
	}
}

unsigned int HuffmanCoding512::readPlaintext(std::istream& in) const {
	unsigned int n = 0;
	std::string s;
	if (!in.eof()) {
		in >> s;
		n = (unsigned int)stoi(s);
		if (n >= 512) {
			throw out_of_range("input number should be [0, 512)");
		}
	}
	return n;
}

void HuffmanCoding512::writePlaintext(std::ostream& out, unsigned int n) const {
	if (!out.tellp() == 0) {
		out << ' ';
	}
	out << n;
}