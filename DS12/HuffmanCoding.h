#pragma once
#ifndef _HUFFMANCODING_H
#define _HUFFMANCODING_H
#include<map>
#include<iostream>

#include "HuffmanTree.h"

struct CodeBit {
	unsigned long long code;
	unsigned int len;
};

class HuffmanCoding {
public:
	HuffmanCoding(unsigned int theWeight[], unsigned int n, unsigned int* theElements = nullptr);
	virtual ~HuffmanCoding() {}
	void output(std::ostream& out) const;
	void store(std::istream& in, std::ostream& out) const;
	void read(std::istream& in, std::ostream& out) const;
protected:
	virtual unsigned int readPlaintext(std::istream& in) const;
	virtual void writePlaintext(std::ostream& out, unsigned int n) const;

	CodeBit* codes;
	unsigned int codeCount;
	unsigned int* weight;
	unsigned int* elements;
	HuffmanTree<unsigned int>* ht;
};

int getInt(std::istream& in);
void putInt(std::ostream& out, unsigned int n);

//Exercise 44
class HuffmanCoding512 : public HuffmanCoding {
public:
	HuffmanCoding512(unsigned int theWeight[], unsigned int n, unsigned int* theElements = nullptr) :HuffmanCoding(theWeight, n, theElements){}
	virtual ~HuffmanCoding512() {}

protected:
	virtual unsigned int readPlaintext(std::istream& in) const override;
	virtual void writePlaintext(std::ostream& out, unsigned int n) const override;
};

#endif