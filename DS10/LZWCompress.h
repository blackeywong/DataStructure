#pragma once
#ifndef _LZWCOMPRESS_H
#define _LZWCOMPRESS_H
#include <string>
#include <fstream>

class LZWCompress {
	const int	DIVISOR = 4099,
		MAX_CODES = 4096,
		BYTE_SIZE = 8,
		EXCESS = 4,
		ALPHA = 256,
		MASK1 = 255,
		MASK2 = 15;

	typedef std::pair<long, short> pairTypeCompress;
public:
	LZWCompress(std::string theInFile, std::string theOutFile);
	~LZWCompress();
	void compress();
private:
	void output(long pcode);
	
	std::ifstream in;
	std::ofstream out;

	int leftOver;
	bool bitsLeftOver;

};

class LZWUnCompress {
	const int	DIVISOR = 4099,
		MAX_CODES = 4096,
		BYTE_SIZE = 8,
		EXCESS = 4,
		ALPHA = 256,
		MASK1 = 255,
		MASK2 = 15;
	typedef std::pair<short, char> pairTypeUncompress;

public:
	LZWUnCompress(std::string theInFile, std::string theOutFile);
	~LZWUnCompress();
	void uncompress();
private:
	void output(short code);
	bool getCode(short& code);

	std::ifstream in;
	std::ofstream out;

	int size;
	int leftOver;
	bool bitsLeftOver;

	pairTypeUncompress* ht;
	char* s;

};

#endif