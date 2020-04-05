#pragma once
#ifndef _LZWCOMPRESS2_H
#define _LZWCOMPRESS2_H
#include <string>
#include <fstream>
#include "HashChain.h"
//Exercise 46
class LZWCompress2 {
	const int	DIVISOR = 131,
		MAX_CODES = 128,
		BYTE_SIZE = 8,
		ALPHA = 45,
		MASK = 255;
	typedef std::pair<short, char> pairTypeCompress;

public:
	LZWCompress2(std::string theInFile, std::string theOutFile);
	~LZWCompress2();
	void compress();
private:
	void output(short pcode);
	void initDict(HashChain<short,char>* dict);

	std::ifstream in;
	std::ofstream out;
};

class LZWUnCompress2 {
	const int	DIVISOR = 131,
		MAX_CODES = 128,
		BYTE_SIZE = 8,
		ALPHA = 45,
		MASK = 255;
	typedef std::pair<char, char> pairTypeUncompress;
public:
	LZWUnCompress2(std::string theInFile, std::string theOutFile);
	~LZWUnCompress2();
	void uncompress();
private:
	void output(char code);
	bool getCode(char& code);
	void initDict(std::pair<char, char>* dict);

	std::ifstream in;
	std::ofstream out;

	pairTypeUncompress* ht;
	char* s;
	int size;
};

#endif