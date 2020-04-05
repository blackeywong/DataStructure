#pragma once
#ifndef _TESTTIMEPERF_H
#define _TESTTIMEPERF_H

#include "dictionary.h"
#include <ctime>
#include <iostream>
#include <random>
#include <map>

class TestTimePerf {
public:
	enum TEST_TYPE { INSERT_ONLY, FIND_ONLY, ERASE_ONLY, ALL };//ALL: insert, find, and erase
	TestTimePerf(int theCount, TEST_TYPE theType);
	~TestTimePerf() { delete[] keys; }
	void test(dictionary<int, int>& dict);
	void test(std::map<int, int>& dict);

private:
	int count;
	TEST_TYPE test_type;
	int* keys;
};

TestTimePerf::TestTimePerf(int theCount, TEST_TYPE theType)
	:count(theCount), test_type(theType){
	int lowBound = count;
	int highBound = count * 2;

	std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));
	std::uniform_int_distribution<int> u(lowBound, highBound);
	//std::uniform_int_distribution<int> u(1, 5);

	keys = new int[count];
	for (int i = 0; i < count; ++i) {
		keys[i] = u(e) % count;
		if (keys[i] < 0)
			keys[i] = -keys[i];
	}
}


void TestTimePerf::test(dictionary<int, int>& dict) {
	clock_t start, finish;
	double insertTime = 0.0;
	if (test_type == TEST_TYPE::INSERT_ONLY) {
		start = clock();
		for (int i = 0; i < count; ++i) {
			dict.insert({ keys[i], i });
			//std::cout << i << "," << keys[i] << std::endl;
		}

		finish = clock();
		std::cout << count << " insert: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;
	}
	else if (test_type == TEST_TYPE::FIND_ONLY) {
		for (int i = 0; i < count; ++i) {
			dict.insert({ keys[i], i });
		}
		start = clock();
		for (int i = 0; i < count; ++i) {
			dict.find(keys[i]);
		}
		finish = clock();
		std::cout << count << " find: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;
	}
	else if (test_type == TEST_TYPE::ERASE_ONLY) {
		for (int i = 0; i < count; ++i) {
			dict.insert({ keys[i], i });
		}
		start = clock();
		for (int i = 0; i < count; ++i) {
			dict.erase(keys[i]);
		}
		finish = clock();
		std::cout << count << " erase: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;
	}
	else if (test_type == TEST_TYPE::ALL) {
		start = clock();
		for (int i = 0; i < count; ++i) {
			dict.insert({ keys[i], i });
		}
		for (int i = 0; i < count; ++i) {
			dict.find(keys[i]);
		}
		for (int i = 0; i < count; ++i) {
			dict.erase(keys[i]);
		}
		finish = clock();
		std::cout << count * 3 << " insert, find and erase: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;
	}
}

void TestTimePerf::test(std::map<int, int>& dict) {
	clock_t start, finish;
	double insertTime = 0.0;
	if (test_type == TEST_TYPE::INSERT_ONLY) {
		start = clock();
		for (int i = 0; i < count; ++i) {
			dict.insert({ keys[i], i });
			//std::cout << i << "," << keys[i] << std::endl;
		}

		finish = clock();
		std::cout << count << " insert: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;
	}
	else if (test_type == TEST_TYPE::FIND_ONLY) {
		for (int i = 0; i < count; ++i) {
			dict.insert({ keys[i], i });
		}
		start = clock();
		for (int i = 0; i < count; ++i) {
			dict.find(keys[i]);
		}
		finish = clock();
		std::cout << count << " find: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;
	}
	else if (test_type == TEST_TYPE::ERASE_ONLY) {
		for (int i = 0; i < count; ++i) {
			dict.insert({ keys[i], i });
		}
		start = clock();
		for (int i = 0; i < count; ++i) {
			dict.erase(keys[i]);
		}
		finish = clock();
		std::cout << count << " erase: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;
	}
	else if (test_type == TEST_TYPE::ALL) {
		start = clock();
		for (int i = 0; i < count; ++i) {
			dict.insert({ keys[i], i });
		}
		for (int i = 0; i < count; ++i) {
			dict.find(keys[i]);
		}
		for (int i = 0; i < count; ++i) {
			dict.erase(keys[i]);
		}
		finish = clock();
		std::cout << count * 3 << " insert, find and erase: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;
	}
}

#endif