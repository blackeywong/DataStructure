// DS10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "sortedArrayList.h"
#include "pairNode.h"
#include <sstream>
#include "sortedChain.h"
#include "sortedChain2.h"
#include "skipList.h"
#include "idealHashDict.h"
#include "HashTable.h"
#include "HashTable2.h"
#include "HashTable3.h"
#include "HashTable4.h"
#include "HashChain.h"
#include "sortedChainWithTail.h"
#include "TestTimePerf.h"
#include "ChainedHashTable.h"
#include "HashChainsWithTail.h"
#include "HashChainsWithTails.h"
#include "HashChainsWithHeadersAndTail.h"
#include "HashChainsWithVector.h"
#include "TestHashChain.h"
#include <map>
#include "LZWCompress.h"
#include "LZWCompress2.h"
#include "LZWCompress3.h"
#include "Concordance.h"
#include "Concordance2.h"

int main()
{
	std::cout << "Exercise 5" << std::endl;
	sortedArrayList<int, int> sal1;
	std::string s1 = "1 2 23 3 33 4";
	std::istringstream iss1(s1);
	iss1 >> sal1;
	std::cout << sal1 << std::endl;

	sal1.insert(std::make_pair(44, 22));
	std::cout << sal1 << std::endl;
	sal1.insert(std::make_pair(-1, -1));
	std::cout << sal1 << std::endl;
	sal1.insert(std::make_pair(0, 5));
	std::cout << sal1 << std::endl;
	sal1.insert(std::make_pair(40, 8));
	std::cout << sal1 << std::endl;
	sal1.insert(std::make_pair(30, 30));
	std::cout << sal1 << std::endl;

	auto p1 = sal1.find(45);
	if (p1 != nullptr)
		std::cout << p1->first << "," << p1->second << std::endl;
	p1 = sal1.find(44);
	if (p1 != nullptr)
		std::cout << p1->first << "," << p1->second << std::endl;

	sal1.erase(31);
	std::cout << sal1 << std::endl;
	sal1.erase(-68);
	std::cout << sal1 << std::endl;
	sal1.erase(88);
	std::cout << sal1 << std::endl;
	sal1.erase(0);
	std::cout << sal1 << std::endl;
	sal1.erase(30);
	std::cout << sal1 << std::endl;
	sal1.erase(40);
	std::cout << sal1 << std::endl;
	sal1.erase(-1);
	std::cout << sal1 << std::endl;
	sal1.erase(44);
	std::cout << sal1 << std::endl;

	std::cout << "Exercise 6" << std::endl;
	sortedChain2<int, int> sc2;
	std::string s3 = s1;
	std::istringstream iss3(s3);
	iss3 >> sc2;
	std::cout << sc2 << std::endl;

	sc2.insert(std::make_pair(44, 22));
	std::cout << sc2 << std::endl;
	sc2.insert(std::make_pair(-1, -1));
	std::cout << sc2 << std::endl;
	sc2.insert(std::make_pair(0, 5));
	std::cout << sc2 << std::endl;
	sc2.insert(std::make_pair(40, 8));
	std::cout << sc2 << std::endl;
	sc2.insert(std::make_pair(30, 30));
	std::cout << sc2 << std::endl;

	auto p3 = sc2.find(45);
	if (p3 != nullptr)
		std::cout << p3->first << "," << p3->second << std::endl;
	p3 = sc2.find(44);
	if (p3 != nullptr)
		std::cout << p3->first << "," << p3->second << std::endl;

	sc2.erase(31);
	std::cout << sc2 << std::endl;
	sc2.erase(-68);
	std::cout << sc2 << std::endl;
	sc2.erase(88);
	std::cout << sc2 << std::endl;
	sc2.erase(0);
	std::cout << sc2 << std::endl;
	sc2.erase(30);
	std::cout << sc2 << std::endl;
	sc2.erase(40);
	std::cout << sc2 << std::endl;
	sc2.erase(-1);
	std::cout << sc2 << std::endl;
	sc2.erase(44);
	std::cout << sc2 << std::endl;

	std::cout << "Skip List" << std::endl;
	skipList<int, int> sl4(1000, 10, 0.5);
	std::string s4 = s1;
	std::istringstream iss4(s4);
	iss4 >> sl4;
	std::cout << sl4 << std::endl;

	sl4.insert(std::make_pair(44, 22));
	std::cout << sl4 << std::endl;
	sl4.insert(std::make_pair(-1, -1));
	std::cout << sl4 << std::endl;
	sl4.insert(std::make_pair(0, 5));
	std::cout << sl4 << std::endl;
	sl4.insert(std::make_pair(40, 8));
	std::cout << sl4 << std::endl;
	sl4.insert(std::make_pair(30, 30));
	std::cout << sl4 << std::endl;
	//sl4.insert(std::make_pair(13, 30));
	//sl4.insert(std::make_pair(15, 30));
	//sl4.insert(std::make_pair(18, 30));
	//sl4.insert(std::make_pair(19, 30));
	//sl4.insert(std::make_pair(20, 30));
	//sl4.insert(std::make_pair(21, 30));
	//sl4.insert(std::make_pair(22, 30));
	//sl4.insert(std::make_pair(24, 30));
	//sl4.insert(std::make_pair(25, 30));
	//sl4.insert(std::make_pair(26, 30));
	//sl4.insert(std::make_pair(27, 31));
	//sl4.insert(std::make_pair(28, 32));
	std::cout << sl4 << std::endl;

	auto p4 = sl4.find(45);
	if (p4 != nullptr)
		std::cout << p4->first << "," << p4->second << std::endl;
	p4 = sl4.find(44);
	if (p4 != nullptr)
		std::cout << p4->first << "," << p4->second << std::endl;

	sl4.erase(31);
	std::cout << sl4 << std::endl;
	sl4.erase(-68);
	std::cout << sl4 << std::endl;
	sl4.erase(88);
	std::cout << sl4 << std::endl;
	sl4.erase(0);
	std::cout << sl4 << std::endl;
	sl4.erase(30);
	std::cout << sl4 << std::endl;
	sl4.erase(40);
	std::cout << sl4 << std::endl;
	sl4.erase(-1);
	std::cout << sl4 << std::endl;
	sl4.erase(44);
	std::cout << sl4 << std::endl;

	std::cout << "Exercise 8" << std::endl;
	sl4.insert(std::make_pair(1, 1));
	std::cout << sl4 << std::endl;
	sl4.insert(std::make_pair(33, 44));
	std::cout << sl4 << std::endl;
	p4 = sl4.find(1);
	if (p4 != nullptr)
		std::cout << p4->first << "," << p4->second << std::endl;
	sl4.erase(1);
	std::cout << sl4 << std::endl;
	sl4.erase(33);
	std::cout << sl4 << std::endl;

	std::cout << "Exercise 9" << std::endl;
	sl4.removeSmallest();
	std::cout << sl4 << std::endl;
	sl4.removeLargest();
	std::cout << sl4 << std::endl;
	std::cout << std::endl;

	std::cout << "Exercise 10" << std::endl;
	IdealHashDict<int> ihd1(100);
	std::string s10 = s1;
	std::istringstream iss10(s10);
	iss10 >> ihd1;
	std::cout << ihd1 << std::endl;

	ihd1.insert(std::make_pair(44, 22));
	std::cout << ihd1 << std::endl;
	ihd1.insert(std::make_pair(-1, -1));
	std::cout << ihd1 << std::endl;
	ihd1.insert(std::make_pair(0, 5));
	std::cout << ihd1 << std::endl;
	ihd1.insert(std::make_pair(40, 8));
	std::cout << ihd1 << std::endl;
	ihd1.insert(std::make_pair(30, 30));
	std::cout << ihd1 << std::endl;

	auto p10 = ihd1.find(45);
	if (p10 != nullptr)
		std::cout << p10->first << "," << p10->second << std::endl;
	p10 = ihd1.find(44);
	if (p10 != nullptr)
		std::cout << p10->first << "," << p10->second << std::endl;

	ihd1.erase(31);
	std::cout << ihd1 << std::endl;
	ihd1.erase(-68);
	std::cout << ihd1 << std::endl;
	ihd1.erase(88);
	std::cout << ihd1 << std::endl;
	ihd1.erase(0);
	std::cout << ihd1 << std::endl;
	ihd1.erase(30);
	std::cout << ihd1 << std::endl;
	ihd1.erase(40);
	std::cout << ihd1 << std::endl;
	ihd1.erase(-1);
	std::cout << ihd1 << std::endl;
	ihd1.erase(44);
	std::cout << ihd1 << std::endl;

	std::cout << "Exercise 15" << std::endl;
	std::cout << stringToInt("a") << std::endl;
	std::cout << stringToInt("ab") << std::endl;
	std::cout << stringToInt("abc") << std::endl;
	std::cout << stringToInt("abcd") << std::endl;
	std::cout << stringToInt("abcde") << std::endl;
	std::cout << stringToInt("abcdef") << std::endl;
	std::cout << stringToInt("abcdefg") << std::endl;
	std::cout << stringToInt("abcdefgh") << std::endl;

	std::cout << "Exercise 16" << std::endl;
	std::cout << doubleToInt(0) << std::endl;
	std::cout << doubleToInt(0.0) << std::endl;
	std::cout << doubleToInt(123.56) << std::endl;
	std::cout << doubleToInt(1) << std::endl;
	std::cout << doubleToInt(1.0) << std::endl;
	std::cout << doubleToInt(.3e-99) << std::endl;
	std::cout << doubleToInt(3.e88) << std::endl;
	std::cout << doubleToInt(12314356.78789898) << std::endl;

	std::cout << "Hash Table linear probing" << std::endl;
	HashTable<int, int> ht1(23, true);
	std::string s11 = s1;
	std::istringstream iss11(s11);
	iss11 >> ht1;
	std::cout << ht1 << std::endl;

	ht1.insert(std::make_pair(44, 22));
	std::cout << ht1 << std::endl;
	ht1.insert(std::make_pair(-1, -1));
	std::cout << ht1 << std::endl;
	ht1.insert(std::make_pair(0, 5));
	std::cout << ht1 << std::endl;
	ht1.insert(std::make_pair(40, 8));
	std::cout << ht1 << std::endl;
	ht1.insert(std::make_pair(30, 30));
	std::cout << ht1 << std::endl;

	auto p11 = ht1.find(45);
	if (p11 != nullptr)
		std::cout << p11->first << "," << p11->second << std::endl;
	p11 = ht1.find(44);
	if (p11 != nullptr)
		std::cout << p11->first << "," << p11->second << std::endl;

	ht1.erase(31);
	std::cout << ht1 << std::endl;
	ht1.erase(-68);
	std::cout << ht1 << std::endl;
	ht1.erase(88);
	std::cout << ht1 << std::endl;
	ht1.erase(-1);
	std::cout << ht1 << std::endl;
	ht1.erase(30);
	std::cout << ht1 << std::endl;
	ht1.erase(40);
	std::cout << ht1 << std::endl;
	ht1.erase(0);
	std::cout << ht1 << std::endl;
	ht1.erase(44);
	std::cout << ht1 << std::endl;

	std::cout << "Exercise 20" << std::endl;
	//HashTable<int, int> ht2(23);
	//ht2.searchRandom(3);
	TestHashTable tht;
	//tht.run(5, 10);

	std::cout << "Exercise 22" << std::endl;
	tht.listValues();

	std::cout << "Exercise 25" << std::endl;
	HashTable<int, int> ht25(5,false, (float)0.6);
	ht25.insert({1, 2});
	ht25.insert({ 23, 3 });
	ht25.insert({ 33, 4 });
	std::cout << ht25 << std::endl;
	ht25.insert({ 44, 22 });
	std::cout << ht25 << std::endl;
	//ht25.insert({ -1, -1 });

	std::cout << "Exercise 27" << std::endl;
	HashTable2<int, int> ht27(11);
	std::string s27 = s1;
	std::istringstream iss27(s10);
	iss27 >> ht27;
	std::cout << ht27 << std::endl;

	ht27.insert(std::make_pair(44, 22));
	std::cout << ht27 << std::endl;
	ht27.insert(std::make_pair(-1, -1));
	std::cout << ht27 << std::endl;
	ht27.insert(std::make_pair(0, 5));
	std::cout << ht27 << std::endl;
	ht27.insert(std::make_pair(40, 8));
	std::cout << ht27 << std::endl;
	ht27.insert(std::make_pair(30, 30));
	std::cout << ht27 << std::endl;

	auto p27 = ht27.find(45);
	if (p27 != nullptr)
		std::cout << p27->first << "," << p27->second << std::endl;
	p27 = ht27.find(44);
	if (p27 != nullptr)
		std::cout << p27->first << "," << p27->second << std::endl;

	ht27.erase(31);
	std::cout << ht27 << std::endl;
	ht27.erase(-68);
	std::cout << ht27 << std::endl;
	ht27.erase(88);
	std::cout << ht27 << std::endl;
	ht27.erase(-1);
	std::cout << ht27 << std::endl;
	ht27.erase(30);
	std::cout << ht27 << std::endl;
	ht27.erase(40);
	std::cout << ht27 << std::endl;
	ht27.erase(23);
	std::cout << ht27 << std::endl;
	ht27.erase(44);
	std::cout << ht27 << std::endl;

	std::cout << "Exercise 28" << std::endl;
	HashTable3<int, int> ht28(11);
	std::string s28 = s1;
	std::istringstream iss28(s28);
	iss28 >> ht28;
	std::cout << ht28 << std::endl;

	ht28.insert(std::make_pair(44, 22));
	std::cout << ht28 << std::endl;
	ht28.insert(std::make_pair(-1, -1));
	std::cout << ht28 << std::endl;
	ht28.insert(std::make_pair(0, 5));
	std::cout << ht28 << std::endl;
	ht28.insert(std::make_pair(40, 8));
	std::cout << ht28 << std::endl;
	ht28.insert(std::make_pair(30, 30));
	std::cout << ht28 << std::endl;

	auto p28 = ht28.find(45);
	if (p28 != nullptr)
		std::cout << p28->first << "," << p28->second << std::endl;
	p28 = ht28.find(44);
	if (p28 != nullptr)
		std::cout << p28->first << "," << p28->second << std::endl;

	//ht28.erase(31);
	//std::cout << ht28 << std::endl;
	//ht28.erase(-68);
	//std::cout << ht28 << std::endl;
	//ht28.erase(88);
	//std::cout << ht28 << std::endl;
	//ht28.erase(44);
	//std::cout << ht28 << std::endl;
	//ht28.erase(30);
	//std::cout << ht28 << std::endl;
	//ht28.erase(1);
	//std::cout << ht28 << std::endl;
	//ht28.erase(23);
	//std::cout << ht28 << std::endl;
	//ht28.erase(40);
	//std::cout << ht28 << std::endl;
	//TestHashTable3 tht3;
	//tht3.run(5, 10);

	std::cout << "Exercise 29" << std::endl;
	HashTable4<int, int> ht29(11, 5);
	std::string s29 = s1;
	std::istringstream iss29(s29);
	iss29 >> ht29;
	std::cout << ht29 << std::endl;

	ht29.insert(std::make_pair(44, 22));
	std::cout << ht29 << std::endl;
	ht29.insert(std::make_pair(-1, -1));
	std::cout << ht29 << std::endl;
	ht29.insert(std::make_pair(0, 5));
	std::cout << ht29 << std::endl;
	ht29.insert(std::make_pair(40, 8));
	std::cout << ht29 << std::endl;
	ht29.insert(std::make_pair(30, 30));
	std::cout << ht29 << std::endl;

	auto p29 = ht29.find(45);
	if (p29 != nullptr)
		std::cout << p29->first << "," << p29->second << std::endl;
	p29 = ht29.find(44);
	if (p29 != nullptr)
		std::cout << p29->first << "," << p29->second << std::endl;

	//ht29.erase(31);
	//std::cout << ht29 << std::endl;
	//ht29.erase(-68);
	//std::cout << ht29 << std::endl;
	//ht29.erase(88);
	//std::cout << ht29 << std::endl;
	//ht29.erase(-1);
	//std::cout << ht29 << std::endl;
	//ht29.erase(30);
	//std::cout << ht29 << std::endl;
	//ht29.erase(40);
	//std::cout << ht29 << std::endl;
	//ht29.erase(23);
	//std::cout << ht29 << std::endl;
	//ht29.erase(44);
	//std::cout << ht29 << std::endl;
	//TestHashTable4 tht4;
	//tht4.run(5, 10);

	std::cout << "Exercise 28/29 comparing perf" << std::endl;
	//int n = 10000000;
	int n = 100000;
	//TestTimePerf ttf28(n, TestTimePerf::TEST_TYPE::INSERT_ONLY);
	//TestTimePerf ttf28(n, TestTimePerf::TEST_TYPE::FIND_ONLY);
	TestTimePerf ttf28(n, TestTimePerf::TEST_TYPE::INSERT_ONLY);
	HashTable3<int, int> ht28_2(n+1);
	ttf28.test(ht28_2);

	HashTable4<int, int> ht29_2(n + 1, 251);
	ttf28.test(ht29_2);

	std::cout << "Hash Chain" << std::endl;
	HashChain<int, int> hc(11);
	std::string shc = s1;
	std::istringstream isshc(shc);
	isshc >> hc;
	std::cout << hc << std::endl;

	hc.insert(std::make_pair(44, 22));
	std::cout << hc << std::endl;
	hc.insert(std::make_pair(-1, -1));
	std::cout << hc << std::endl;
	hc.insert(std::make_pair(0, 5));
	std::cout << hc << std::endl;
	hc.insert(std::make_pair(40, 8));
	std::cout << hc << std::endl;
	hc.insert(std::make_pair(30, 30));
	std::cout << hc << std::endl;

	auto phc = hc.find(45);
	if (phc != nullptr)
		std::cout << phc->first << "," << phc->second << std::endl;
	phc = hc.find(44);
	if (phc != nullptr)
		std::cout << phc->first << "," << phc->second << std::endl;

	hc.erase(31);
	std::cout << hc << std::endl;
	hc.erase(-68);
	std::cout << hc << std::endl;
	hc.erase(88);
	std::cout << hc << std::endl;
	hc.erase(-1);
	std::cout << hc << std::endl;
	hc.erase(30);
	std::cout << hc << std::endl;
	hc.erase(40);
	std::cout << hc << std::endl;
	hc.erase(23);
	std::cout << hc << std::endl;
	hc.erase(44);
	std::cout << hc << std::endl;
	//TestHashChain thc;
	//thc.run(5, 10);

	std::cout << "Exercise 33" << std::endl;
	sortedChainWithTail<int, int> sc33;
	std::string s33_1 = s1;
	std::istringstream iss33_1(s33_1);
	iss33_1 >> sc33;
	std::cout << sc33 << std::endl;

	sc33.insert(std::make_pair(44, 22));
	std::cout << sc33 << std::endl;
	sc33.insert(std::make_pair(-1, -1));
	std::cout << sc33 << std::endl;
	sc33.insert(std::make_pair(0, 5));
	std::cout << sc33 << std::endl;
	sc33.insert(std::make_pair(40, 8));
	std::cout << sc33 << std::endl;
	sc33.insert(std::make_pair(30, 30));
	std::cout << sc33 << std::endl;

	auto p33_1 = sc33.find(45);
	if (p33_1 != nullptr)
		std::cout << p33_1->first << "," << p33_1->second << std::endl;
	p33_1 = sc33.find(44);
	if (p33_1 != nullptr)
		std::cout << p33_1->first << "," << p33_1->second << std::endl;

	sc33.erase(31);
	std::cout << sc33 << std::endl;
	sc33.erase(-68);
	std::cout << sc33 << std::endl;
	sc33.erase(88);
	std::cout << sc33 << std::endl;
	sc33.erase(0);
	std::cout << sc33 << std::endl;
	sc33.erase(30);
	std::cout << sc33 << std::endl;
	sc33.erase(40);
	std::cout << sc33 << std::endl;
	sc33.erase(-1);
	std::cout << sc33 << std::endl;
	sc33.erase(44);
	std::cout << sc33 << std::endl;
	
	std::cout << "Exercise 33 comparing perf" << std::endl;
	//TestTimePerf ttf33(10000, TestTimePerf::TEST_TYPE::INSERT_ONLY);
	//TestTimePerf ttf33(10000, TestTimePerf::TEST_TYPE::FIND_ONLY);
	TestTimePerf ttf33(10000, TestTimePerf::TEST_TYPE::ALL);
	sortedChainWithTail<int, int> sc33_2;
	ttf33.test(sc33_2);

	sortedChain<int, int> sc33_3;
	ttf33.test(sc33_3);

	std::cout << "Exercise 34" << std::endl;
	ChainedHashTable<int, int> cht(23);
	std::string s34 = s1;
	std::istringstream iss34(s34);
	iss34 >> cht;
	std::cout << cht << std::endl;

	cht.insert(std::make_pair(44, 22));
	std::cout << cht << std::endl;
	cht.insert(std::make_pair(-1, -1));
	std::cout << cht << std::endl;
	cht.insert(std::make_pair(0, 5));
	std::cout << cht << std::endl;
	cht.insert(std::make_pair(40, 8));
	std::cout << cht << std::endl;
	cht.insert(std::make_pair(30, 30));
	std::cout << cht << std::endl;

	auto p34 = cht.find(45);
	if (p34 != nullptr)
		std::cout << p34->first << "," << p34->second << std::endl;
	p34 = cht.find(44);
	if (p34 != nullptr)
		std::cout << p34->first << "," << p34->second << std::endl;

	cht.erase(31);
	std::cout << cht << std::endl;
	cht.erase(-68);
	std::cout << cht << std::endl;
	cht.erase(88);
	std::cout << cht << std::endl;
	cht.erase(0);
	std::cout << cht << std::endl;
	cht.erase(30);
	std::cout << cht << std::endl;
	cht.erase(40);
	std::cout << cht << std::endl;
	cht.erase(-1);
	std::cout << cht << std::endl;
	cht.erase(44);
	std::cout << cht << std::endl;

	std::cout << "Exercise 35" << std::endl;
	HashChainsWithTails<int, int> hcwt(23);
	std::string s35 = s1;
	std::istringstream iss35(s35);
	iss35 >> hcwt;
	std::cout << hcwt << std::endl;

	hcwt.insert(std::make_pair(44, 22));
	std::cout << hcwt << std::endl;
	hcwt.insert(std::make_pair(-1, -1));
	std::cout << hcwt << std::endl;
	hcwt.insert(std::make_pair(0, 5));
	std::cout << hcwt << std::endl;
	hcwt.insert(std::make_pair(40, 8));
	std::cout << hcwt << std::endl;
	hcwt.insert(std::make_pair(30, 30));
	std::cout << hcwt << std::endl;

	auto p35 = hcwt.find(45);
	if (p35 != nullptr)
		std::cout << p35->first << "," << p35->second << std::endl;
	p35 = hcwt.find(44);
	if (p35 != nullptr)
		std::cout << p35->first << "," << p35->second << std::endl;

	hcwt.erase(31);
	std::cout << hcwt << std::endl;
	hcwt.erase(-68);
	std::cout << hcwt << std::endl;
	hcwt.erase(88);
	std::cout << hcwt << std::endl;
	hcwt.erase(0);
	std::cout << hcwt << std::endl;
	hcwt.erase(30);
	std::cout << hcwt << std::endl;
	hcwt.erase(40);
	std::cout << hcwt << std::endl;
	hcwt.erase(-1);
	std::cout << hcwt << std::endl;
	hcwt.erase(44);
	std::cout << hcwt << std::endl;

	std::cout << "Exercise 36" << std::endl;
	HashChainsWithTail<int, int> hcw(23);
	std::string s36 = s1;
	std::istringstream iss36(s36);
	iss36 >> hcw;
	std::cout << hcw << std::endl;

	hcw.insert(std::make_pair(44, 22));
	std::cout << hcw << std::endl;
	hcw.insert(std::make_pair(-1, -1));
	std::cout << hcw << std::endl;
	hcw.insert(std::make_pair(0, 5));
	std::cout << hcw << std::endl;
	hcw.insert(std::make_pair(40, 8));
	std::cout << hcw << std::endl;
	hcw.insert(std::make_pair(30, 30));
	std::cout << hcw << std::endl;

	auto p36 = hcw.find(45);
	if (p36 != nullptr)
		std::cout << p36->first << "," << p36->second << std::endl;
	p36 = hcw.find(44);
	if (p36 != nullptr)
		std::cout << p36->first << "," << p36->second << std::endl;

	hcw.erase(31);
	std::cout << hcw << std::endl;
	hcw.erase(-68);
	std::cout << hcw << std::endl;
	hcw.erase(88);
	std::cout << hcw << std::endl;
	hcw.erase(0);
	std::cout << hcw << std::endl;
	hcw.erase(30);
	std::cout << hcw << std::endl;
	hcw.erase(40);
	std::cout << hcw << std::endl;
	hcw.erase(-1);
	std::cout << hcw << std::endl;
	hcw.erase(44);
	std::cout << hcw << std::endl;

	std::cout << "Exercise 35/36 comparing perf" << std::endl;
	n = 100000;
	TestTimePerf ttf35(n, TestTimePerf::TEST_TYPE::INSERT_ONLY);
	//TestTimePerf ttf35(n, TestTimePerf::TEST_TYPE::FIND_ONLY);
	//TestTimePerf ttf35(n, TestTimePerf::TEST_TYPE::ALL);
	HashChainsWithTail<int, int> hcw35_2(n + 1);
	ttf35.test(hcw35_2); 
	
	HashChainsWithTails<int, int> hcwt35_2(n + 1);
	ttf35.test(hcwt35_2);

	HashChain<int, int> hc35_2(n + 1);
	ttf35.test(hc35_2);

	std::cout << "Exercise 37" << std::endl;
	HashChainsWithHeadersAndTail<int, int> hcwhat(23);
	std::string s37 = s1;
	std::istringstream iss37(s37);
	iss37 >> hcwhat;
	std::cout << hcwhat << std::endl;

	hcwhat.insert(std::make_pair(44, 22));
	std::cout << hcwhat << std::endl;
	hcwhat.insert(std::make_pair(-1, -1));
	std::cout << hcwhat << std::endl;
	hcwhat.insert(std::make_pair(0, 5));
	std::cout << hcwhat << std::endl;
	hcwhat.insert(std::make_pair(40, 8));
	std::cout << hcwhat << std::endl;
	hcwhat.insert(std::make_pair(30, 30));
	std::cout << hcwhat << std::endl;

	auto p37 = hcwhat.find(45);
	if (p37 != nullptr)
		std::cout << p37->first << "," << p37->second << std::endl;
	p37 = hcwhat.find(44);
	if (p37 != nullptr)
		std::cout << p37->first << "," << p37->second << std::endl;

	hcwhat.erase(31);
	std::cout << hcwhat << std::endl;
	hcwhat.erase(-68);
	std::cout << hcwhat << std::endl;
	hcwhat.erase(88);
	std::cout << hcwhat << std::endl;
	hcwhat.erase(0);
	std::cout << hcwhat << std::endl;
	hcwhat.erase(30);
	std::cout << hcwhat << std::endl;
	hcwhat.erase(40);
	std::cout << hcwhat << std::endl;
	hcwhat.erase(-1);
	std::cout << hcwhat << std::endl;
	hcwhat.erase(44);
	std::cout << hcwhat << std::endl;

	std::cout << "Exercise 38" << std::endl;
	HashChainsWithVector<int, int> hcwv(23);
	std::string s38 = s1;
	std::istringstream iss38(s38);
	iss38 >> hcwv;
	std::cout << hcwv << std::endl;

	hcwv.insert(std::make_pair(44, 22));
	std::cout << hcwv << std::endl;
	hcwv.insert(std::make_pair(-1, -1));
	std::cout << hcwv << std::endl;
	hcwv.insert(std::make_pair(0, 5));
	std::cout << hcwv << std::endl;
	hcwv.insert(std::make_pair(40, 8));
	std::cout << hcwv << std::endl;
	hcwv.insert(std::make_pair(30, 30));
	std::cout << hcwv << std::endl;

	auto p38 = hcwv.find(45);
	if (p38 != nullptr)
		std::cout << p38->first << "," << p38->second << std::endl;
	p38 = hcwv.find(44);
	if (p38 != nullptr)
		std::cout << p38->first << "," << p38->second << std::endl;

	hcwv.erase(31);
	std::cout << hcwv << std::endl;
	hcwv.erase(-68);
	std::cout << hcwv << std::endl;
	hcwv.erase(88);
	std::cout << hcwv << std::endl;
	hcwv.erase(-1);
	std::cout << hcwv << std::endl;
	hcwv.erase(30);
	std::cout << hcwv << std::endl;
	hcwv.erase(40);
	std::cout << hcwv << std::endl;
	hcwv.erase(0);
	std::cout << hcwv << std::endl;
	hcwv.erase(44);
	std::cout << hcwv << std::endl;

	//TestHashChain thc2;
	//thc2.run(5, 10);
	std::cout << "Exercise 38 comparing perf" << std::endl;
	n = 100000;
	//TestTimePerf ttf38(n, TestTimePerf::TEST_TYPE::INSERT_ONLY);
	//TestTimePerf ttf38(n, TestTimePerf::TEST_TYPE::FIND_ONLY);
	TestTimePerf ttf38(n, TestTimePerf::TEST_TYPE::ALL);
	HashChainsWithVector<int, int> hcwv38_2(n + 1);
	ttf38.test(hcwv38_2);

	HashChain<int, int> hc38_2(n + 1);
	ttf38.test(hc38_2);

	std::cout << "Exercise 39" << std::endl;
	HashChain<int, int> hc39(11, 0.6);
	std::string s39 = "1 2 23 3 33 4 44 22 -1 -1 0 5";
	std::istringstream iss39(s39);
	iss39 >> hc39;
	std::cout << hc39 << std::endl;

	hc39.insert(std::make_pair(40, 8));
	std::cout << hc39 << std::endl;
	hc39.insert(std::make_pair(30, 30));
	std::cout << hc39 << std::endl;

	std::cout << "Exercise 40" << std::endl;
	n = 1000;
	TestTimePerf ttf40(n, TestTimePerf::TEST_TYPE::INSERT_ONLY);
	//TestTimePerf ttf40(n, TestTimePerf::TEST_TYPE::FIND_ONLY);
	//TestTimePerf ttf40(n, TestTimePerf::TEST_TYPE::ERASE_ONLY);
	//TestTimePerf ttf40(n, TestTimePerf::TEST_TYPE::ALL);
	std::cout << "sorted Chain" << std::endl;
	sortedChain<int, int> sc40;//100000 insert: 1540 107238 105.698
	ttf40.test(sc40);
	std::cout << "skip list" << std::endl;
	skipList<int, int> sl40(n * 2, n, 0.5); //10000000 insert: 7848 69221 61.373
	ttf40.test(sl40);
	std::cout << "hash table" << std::endl;
	HashTable<int, int> ht40(n+1);//100000000 insert: 59517 148421 88.904
	ttf40.test(ht40);
	std::cout << "hash chain" << std::endl;
	HashChain<int, int> hc40(n + 1);//100000000 insert: 155726 263921 108.195
	ttf40.test(hc40);
	std::cout << "hash map" << std::endl;
	std::map<int, int> map40;//10000000 insert: 89304 175629 86.325
	ttf40.test(map40);

	clock_t start, finish;
	double insertTime = 0.0;
	std::cout << "LZWCompress" << std::endl;
	LZWCompress comp("D:\\study\\C++\\DS\\DS10\\compress.input", "D:\\study\\C++\\DS\\DS10\\compress.output");
	//LZWCompress comp("D:\\study\\C++\\DS\\DS10\\test.txt", "D:\\study\\C++\\DS\\DS10\\test.out");
	start = clock();
	comp.compress();
	finish = clock();
	std::cout << "Compress: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;

	LZWUnCompress uncomp("D:\\study\\C++\\DS\\DS10\\compress.output", "D:\\study\\C++\\DS\\DS10\\compress.txt");
	//LZWUnCompress uncomp("D:\\study\\C++\\DS\\DS10\\test.out", "D:\\study\\C++\\DS\\DS10\\test2.txt");
	uncomp.uncompress();

	std::cout << "Exercise 46" << std::endl;
	LZWCompress2 comp2("D:\\study\\C++\\DS\\DS10\\comp2.input", "D:\\study\\C++\\DS\\DS10\\comp2.output");
	//LZWCompress2 comp2("D:\\study\\C++\\DS\\DS10\\test2.txt", "D:\\study\\C++\\DS\\DS10\\test2.out");
	comp2.compress();

	LZWUnCompress2 uncomp2("D:\\study\\C++\\DS\\DS10\\comp2.output", "D:\\study\\C++\\DS\\DS10\\comp2.txt");
	//LZWUnCompress2 uncomp2("D:\\study\\C++\\DS\\DS10\\test2.out", "D:\\study\\C++\\DS\\DS10\\test3.txt");
	uncomp2.uncompress();

	std::cout << "Exercise 47" << std::endl;
	LZWCompress3 comp3("D:\\study\\C++\\DS\\DS10\\compr3.txt", "D:\\study\\C++\\DS\\DS10\\compr3.output");
	//LZWCompress3 comp3("D:\\study\\C++\\DS\\DS10\\test.txt", "D:\\study\\C++\\DS\\DS10\\test.out");
	comp3.compress();

	LZWUnCompress3 uncomp3("C:\\workspace\\DS\\DS10\\compr3.output", "C:\\workspace\\DS\\DS10\\compr33.txt");
	//LZWUnCompress3 uncomp3("D:\\study\\C++\\DS\\DS10\\test.out", "D:\\study\\C++\\DS\\DS10\\test2.txt");
	uncomp3.uncompress();

	std::cout << "Exercise 48" << std::endl;
	Concordance conc("D:\\study\\C++\\DS\\DS10\\toindex.txt");
	conc.output(std::cout);

	Concordance conc2("D:\\study\\C++\\DS\\DS10\\compress.input");
	std::ofstream file("D:\\study\\C++\\DS\\DS10\\index.txt");
	conc2.output(file);

	Concordance2 conc3("D:\\study\\C++\\DS\\DS10\\toindex.txt");
	conc3.output(std::cout);

	Concordance2 conc4("D:\\study\\C++\\DS\\DS10\\compress.input");
	std::ofstream file4("D:\\study\\C++\\DS\\DS10\\index4.txt");
	conc4.output(file4);
}

