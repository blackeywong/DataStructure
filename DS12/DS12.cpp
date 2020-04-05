// DS12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>

#include "PriorityElement.h"
#include "ArrayListMaxPriorityQueue.h"
#include "ChainMaxPriorityQueue.h"
#include "SortedArrayListMaxPriorityQueue.h"
#include "SortedChainMaxPriorityQueue.h"
#include "QueueMaxPriorityQueue.h"
#include "Heap.h"
#include "MaxHeap2.h"
#include "TestPriorityQueue.h"
#include "MaxDHeap.h"
#include "Hblt.h"
#include "HbltWithRemoveNode.h"
#include "Wblt.h"
#include "HbltWithMinElement.h"
#include "DS12_Application.h"
#include "HuffmanTree.h"
#include "Rsebt.h"
#include "HuffmanCoding.h"

int main()
{
    //std::cout << "Exercise 1" << std::endl;
    //ArrayListMaxPriorityQueue<PriorityElement<int>> almpq;
    //almpq.push(PriorityElement<int>(1, 2));
    //almpq.push(PriorityElement<int>(3, 3));
    //almpq.push(PriorityElement<int>(2, 1));
    //std::cout << almpq << std::endl;
    //std::cout << almpq.top() << std::endl;
    //almpq.pop();
    //std::cout << almpq << std::endl;

    //std::cout << "Exercise 2" << std::endl;
    //ChainMaxPriorityQueue<PriorityElement<int>> cmpq;
    //cmpq.push(PriorityElement<int>(1, 2));
    //cmpq.push(PriorityElement<int>(3, 3));
    //cmpq.push(PriorityElement<int>(2, 1));
    //std::cout << cmpq << std::endl;
    //std::cout << cmpq.top() << std::endl;
    //cmpq.pop();
    //std::cout << cmpq << std::endl;

    //std::cout << "Exercise 3" << std::endl;
    //SortedArrayListMaxPriorityQueue<PriorityElement<int>> salmpq;
    //salmpq.push(PriorityElement<int>(1, 2));
    //salmpq.push(PriorityElement<int>(3, 3));
    //salmpq.push(PriorityElement<int>(2, 1));
    //std::cout << salmpq << std::endl;
    //std::cout << salmpq.top() << std::endl;
    //salmpq.pop();
    //std::cout << salmpq << std::endl;

    //std::cout << "Exercise 4" << std::endl;
    //SortedChainMaxPriorityQueue<PriorityElement<int>> scmpq;
    //scmpq.push(PriorityElement<int>(1, 2));
    //scmpq.push(PriorityElement<int>(3, 3));
    //scmpq.push(PriorityElement<int>(2, 1));
    //std::cout << scmpq << std::endl;
    //std::cout << scmpq.top() << std::endl;
    //scmpq.pop();
    //std::cout << scmpq << std::endl;

    //std::cout << "Exercise 5" << std::endl;
    //QueueMaxPriorityQueue<PriorityElement<int>> qmpq(5);
    //qmpq.push(PriorityElement<int>(1, 2));
    //qmpq.push(PriorityElement<int>(3, 3));
    //qmpq.push(PriorityElement<int>(2, 1));
    //std::cout << qmpq << std::endl;
    //std::cout << qmpq.top() << std::endl;
    //qmpq.pop();
    //std::cout << qmpq << std::endl;

    //std::cout << "Heap" << std::endl;
    //std::string s_mh = "10 2 7 6 5 9 12 35 22 15 1 3 4";
    //std::istringstream iss_mh(s_mh);
    //Heap<int> mh(14);
    //iss_mh >> mh;
    //std::cout << mh << std::endl;
    //mh.push(15);
    //std::cout << mh << std::endl;
    //mh.push(20);
    //std::cout << mh << std::endl;
    //mh.push(45);
    //std::cout << mh << std::endl;
    //std::cout << mh.top() << std::endl;
    //mh.pop();
    //std::cout << mh << std::endl;
    //Heap<int> mh13(mh);
    //mh.pop();
    //std::cout << mh << std::endl;
    //mh.pop();
    //std::cout << mh << std::endl;
    //mh.pop();
    //std::cout << mh << std::endl;

    //std::cout << "Exercise 11" << std::endl;
    //Heap<int> mh11(mh);
    //std::cout << mh11 << std::endl;

    //std::cout << "Exercise 12" << std::endl;
    //mh11.changeTop(20);
    //std::cout << mh11 << std::endl;
    //mh11.changeTop(11);
    //std::cout << mh11 << std::endl;
    //mh11.changeTop(2);
    //std::cout << mh11 << std::endl;

    //std::cout << "Exercise 13" << std::endl;
    //int n = mh13.remove(8);
    //std::cout << mh13 << std::endl;
    //std::cout << n << std::endl;
    //n = mh13.remove(14);
    //std::cout << mh13 << std::endl;
    //std::cout << n << std::endl;
    //n = mh13.remove(1);
    //std::cout << mh13 << std::endl;
    //std::cout << n << std::endl;
    //n = mh13.remove(3);
    //std::cout << mh13 << std::endl;
    //std::cout << n << std::endl;

    //std::cout << "Exercise 14" << std::endl;
    //std::string s_14 = "10 2 7 6 5 9 12 35 22 15 1 3 4";
    //std::istringstream iss14(s_14);
    //Heap<std::string> mh14(14);
    //iss14 >> mh14;
    //for (Heap<std::string>::Iterator it14 = mh14.begin(); it14 != mh14.end(); ++it14)
    //    std::cout << *it14 << ' ';
    //std::cout << std::endl;
    //auto it14_2 = mh14.begin();
    //auto it14_3 = it14_2++;
    //std::cout << it14_3->substr(0) << std::endl;
    //std::cout << *it14_2 << std::endl;

    //std::cout << "Exercise 16" << std::endl;
    //std::string s16 = "10 2 7 6 5 9 12 35 22 15 1 3 4";
    //std::istringstream iss16(s16);
    //MaxHeap2<int> mh16(100, 0, 13);
    //iss16 >> mh16;
    //std::cout << mh16 << std::endl;
    //mh16.push(15);
    //std::cout << mh16 << std::endl;
    //mh16.push(20);
    //std::cout << mh16 << std::endl;
    //mh16.push(45);
    //std::cout << mh16 << std::endl;
    //std::cout << mh16.top() << std::endl;
    //mh16.pop();
    //std::cout << mh16 << std::endl;
    //mh16.pop();
    //std::cout << mh16 << std::endl;
    //mh16.pop();
    //std::cout << mh16 << std::endl;
    //mh16.pop();
    //std::cout << mh16 << std::endl;

    //std::cout << "Exercise 17" << std::endl;
    //std::string s17 = "10 2 7 6 5 9 12 35 22 15 1 3 4";
    //std::istringstream iss17(s17);
    //MaxDHeap<int> mdh17(3, 13);
    //iss17 >> mdh17;
    //std::cout << mdh17 << std::endl;
    //mdh17.push(15);
    //std::cout << mdh17 << std::endl;
    //mdh17.push(20);
    //std::cout << mdh17 << std::endl;
    //mdh17.push(45);
    //std::cout << mdh17 << std::endl;
    //std::cout << mdh17.top() << std::endl;
    //mdh17.pop();
    //std::cout << mdh17 << std::endl;
    //mdh17.pop();
    //std::cout << mdh17 << std::endl;
    //mdh17.pop();
    //std::cout << mdh17 << std::endl;
    //mdh17.pop();
    //std::cout << mdh17 << std::endl;

    //std::cout << "Exercise 18" << std::endl;
    //mdh17.changeMax(20);
    //std::cout << mdh17 << std::endl;
    //mdh17.changeMax(11);
    //std::cout << mdh17 << std::endl;
    //mdh17.changeMax(2);
    //std::cout << mdh17 << std::endl;

    //int a_mhb[] = {0, 3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17};
    //std::cout << "Exercise 19" << std::endl;
    //Hblt<int> maxhb19(a_mhb, 12);
    //maxhb19.push(10);
    //maxhb19.push(18);
    //maxhb19.push(11);
    //maxhb19.push(4);
    //maxhb19.pop();
    //maxhb19.pop();
    //maxhb19.pop();

    //int a_mhb2[] = { 0, 10, 2, 7, 6, 5, 9, 12, 35, 22, 15, 1, 3, 4 };
    //std::cout << "Exercise 20" << std::endl;
    //Hblt<int> maxhb20(a_mhb2, 13);
    //maxhb20.push(10);
    //maxhb20.push(18);
    //maxhb20.push(11);
    //maxhb20.push(4);
    //maxhb20.pop();
    //maxhb20.pop();
    //maxhb20.pop();

    //std::cout << "Exercise 21" << std::endl;
    //Hblt<int> minhb21(a_mhb, 12, false);

    //std::cout << "Exercise 22" << std::endl;
    //for (auto it = minhb21.begin(); it != minhb21.end(); ++it) {
    //    std::cout << *it << ' ';
    //}
    //std::cout << std::endl;

    //std::cout << "Exercise 23" << std::endl;
    //HbltWithRemoveNode<int> hwrn23(a_mhb2, 13);
    //auto n23 = hwrn23.pushAndReturnNode(10);
    //n23 = hwrn23.pushAndReturnNode(18);
    //hwrn23.pushAndReturnNode(11);
    //hwrn23.removeElementInNode(n23);

    //std::cout << "Exercise 24" << std::endl;
    //Wblt<int> wb24(a_mhb, 12);
    //wb24.push(10);
    //wb24.push(18);
    //wb24.push(11);
    //wb24.push(4);
    //wb24.pop();
    //wb24.pop();
    //wb24.pop();

    //std::cout << "Exercise 25" << std::endl;
    //HbltWithMinElement<int> hb25(a_mhb, 12);
    //
 
    //std::cout << "Performance" << std::endl;
    //int count = 10000;
    //TestPriorityQueue<int> tpq(count);
    ////SetTree st1(count);
    ////std::cout << "Set Tree No Find rule, No Unite rule" << std::endl;
    ////tst.test(st1, SetTree::NO_FIND_RULE, SetTree::NO_UNITE_RULE);
    //Heap<int> mhp(count);
    //std::cout << "Max Heap" << std::endl;
    //tpq.test(mhp);
    //MaxHeap2<int> mhp2(INT_MAX, 0, count * 2 + 1);
    //std::cout << "Max Heap 2" << std::endl;
    //tpq.test(mhp2);
    //std::cout << "Max DHeap degree = 2" << std::endl;
    //MaxDHeap<int> mdp_2(2, count);
    //tpq.test(mdp_2);
    //std::cout << "Max DHeap degree = 3" << std::endl;
    //MaxDHeap<int> mdp_3(3, count);
    //tpq.test(mdp_3);
    //std::cout << "Max DHeap degree = 4" << std::endl;
    //MaxDHeap<int> mdp_4(4, count);
    //tpq.test(mdp_4);
    //std::cout << "Max Height-biased Leftiest Tree" << std::endl;
    //Hblt<int> hb_t(tpq.getValues(), count + 1);
    //tpq.test(hb_t);
    //std::cout << "Max Weight-biased Leftiest Tree" << std::endl;
    //Wblt<int> wb_t(tpq.getValues(), count + 1);
    //tpq.test(wb_t);
    //std::cout << "Max Height-biased Leftiest Tree With Remove Node" << std::endl;
    //Hblt<int> hbwrn_t(tpq.getValues(), count + 1);
    //tpq.test(hbwrn_t);
    //std::cout << "Max Height-biased Leftiest Tree With Min Element" << std::endl;
    //Hblt<int> hbwme_t(tpq.getValues(), count + 1);
    //tpq.test(hbwme_t);

    //std::cout << "Exercise 26" << std::endl;
    //int a26[] = {5, 7, 2, 9, 3, 8, 6, 1};
    //int c26 = sizeof(a26) / sizeof(int);
    //heapSort<int>(a26, c26);
    //std::copy(a26, a26 + c26, std::ostream_iterator<int>(std::cout, " "));
    //std::cout << std::endl;

    //std::cout << "Exercise 27" << std::endl;
    //int a27[] = { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    //int c27 = sizeof(a27) / sizeof(int);
    //heapSort<int>(a27, c27);
    //std::copy(a27, a27 + c27, std::ostream_iterator<int>(std::cout, " "));
    //std::cout << std::endl;

    //std::cout << "Exercise 28" << std::endl;
    ////int a28[] = { 5, 7, 2, 9, 3, 8, 6, 1 };
    //int a28[] = { 10, 2, 7, 6, 5, 9, 12, 35, 22, 15, 1, 3, 4 };
    //int c28 = sizeof(a28) / sizeof(int);
    //dheapSort<int>(a28, c28, 6);
    //std::copy(a28, a28 + c28, std::ostream_iterator<int>(std::cout, " "));
    //std::cout << std::endl;

    //int count28 = 10000;
    //int* a28_2 = new int[count28];
    //int* a28_3 = new int[count28];
    //int* a28_4 = new int[count28];
    //int* a28_5 = new int[count28];
    //int* a28_6 = new int[count28];
    //for (int i = 0; i <count28; ++i) {
    //    a28_2[i] = count28 - i;
    //}
    //std::copy(a28_2, a28_2 + count28, a28_3);
    //std::copy(a28_2, a28_2 + count28, a28_4);
    //std::copy(a28_2, a28_2 + count28, a28_5);
    //std::copy(a28_2, a28_2 + count28, a28_6);
    //clock_t start, finish;
    //start = clock();
    //dheapSort(a28_2, count28, 2);
    //finish = clock();
    //std::cout << count28 << " Time cost for degree 2: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;
    //start = clock();
    //dheapSort(a28_3, count28, 3);
    //finish = clock();
    //std::cout << count28 << " Time cost for degree 3: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;
    //start = clock();
    //dheapSort(a28_4, count28, 4);
    //finish = clock();
    //std::cout << count28 << " Time cost for degree 4: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;
    //start = clock();
    //dheapSort(a28_5, count28, 5);
    //finish = clock();
    //std::cout << count28 << " Time cost for degree 5: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;
    //start = clock();
    //dheapSort(a28_5, count28, 5);
    //finish = clock();
    //std::cout << count28 << " Time cost for degree 6: " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;

    //delete[] a28_2;
    //delete[] a28_3;
    //delete[] a28_4;
    //delete[] a28_5;
    //delete[] a28_6;

    //std::cout << "Exercise 31" << std::endl;
    //JobNode a31[] = { {1, 6}, {2, 5}, {3, 3}, {4, 2}, {5, 9}, {6, 7}, {7, 1}, {8, 4}, {9, 8} };
    //makeSchedule(a31, 9, 3);

    //std::cout << "Exercise 32" << std::endl;
    //JobNode a32[] = { {1, 20}, {2, 15}, {3, 10}, {4, 8}, {5, 8}, {6, 8} };
    //makeSchedule2(a32, 6, 3);

    //std::cout << "Exercise 33" << std::endl;
    ///*
    //10000 jobs schedule on machines 1000 cost: 0.174
    //10000 jobs schedule on machines 1000 cost: 0.019

    //100000 jobs schedule on machines 10000 cost: 2.39
    //100000 jobs schedule on machines 10000 cost: 0.19

    //1000000 jobs schedule on machines 100000 cost: 27.8
    //1000000 jobs schedule on machines 100000 cost: 1.761

    //10000000 jobs schedule on machines 1000000 cost: 319.57
    //10000000 jobs schedule on machines 1000000 cost: 18.371

    //100000000 jobs schedule on machines 10000000 cost: 4150.82
    //100000000 jobs schedule on machines 10000000 cost: 209.349

    //1000000000 jobs schedule on machines 100000000 cost: 45673.7
    //1000000000 jobs schedule on machines 100000000 cost: 1828.42
    //*/
    //int machineNum = 1000;
    //int jobNum = machineNum * 10;
    //int lowBound = 1;
    //int highBound = 100;
    //std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));
    //std::uniform_int_distribution<int> u(lowBound, highBound);

    //JobNode* jobs = new JobNode[jobNum];
    //JobNode* jobs2 = new JobNode[jobNum];
    //for (int k = 0; k < jobNum; ++k) {
    //    jobs[k].id = k + 1;
    //    jobs[k].time = u(e);
    //}
    //std::copy(jobs, jobs + jobNum, jobs);

    //start = clock();
    //makeSchedule(jobs, jobNum, machineNum);
    //finish = clock();
    //std::cout << jobNum << " jobs schedule on machines " << machineNum << " cost: " <<  (double)(finish - start) / CLK_TCK << std::endl;
    //start = clock();
    //makeSchedule2(jobs2, jobNum, machineNum);
    //finish = clock();
    //std::cout << jobNum << " jobs schedule on machines " << machineNum << " cost: " << (double)(finish - start) / CLK_TCK << std::endl;

    //std::cout << "Exercise 36" << std::endl;
    //ItemNode a36[] = { {1, 6}, {2, 5}, {3, 3}, {4, 2}, {5, 9}, {6, 7}, {7, 1}, {8, 4}, {9, 8} };
    //packItems(a36, 9, 3, 15);

    //std::cout << "Exercise 37" << std::endl;
    //int a37[] = { 3, 7, 9, 12, 15, 20, 25 };
    //int c37 = sizeof(a37) / sizeof(int);
    //HuffmanTree<int> ht37(a37, c37);

    //std::cout << "Exercise 38" << std::endl;
    //int a38[] = { 2, 4, 5, 7, 9, 10, 14, 17, 18, 50 };
    //int c38 = sizeof(a38) / sizeof(int);
    //HuffmanTree<int> ht38(a38, c38);

    //std::cout << "Exercise 40.3" << std::endl;
    //int a40[] = {4, 6, 7, 9, 10 };
    //int c40 = sizeof(a40) / sizeof(int);
    //Rsebt<int> rsebt40(a40, c40);
    //
    ////ht38.draw();
    ////std::cin.ignore();

    //std::cout << "Exercise 42" << std::endl;
    //HuffmanCoding hc(a37, c37);
    //hc.output(std::cout);

    std::cout << "Exercise 43" << std::endl;
    //huffmanCompress("D:\\study\\C++\\DS\\DS12\\test.txt", "D:\\study\\C++\\DS\\DS12\\test.huf");
    //huffmanUncompress("D:\\study\\C++\\DS\\DS12\\test.huf", "D:\\study\\C++\\DS\\DS12\\test.out");
    //huffmanCompress("D:\\study\\C++\\DS\\DS12\\toindex.txt", "D:\\study\\C++\\DS\\DS12\\toindex.huf");
    //huffmanUncompress("D:\\study\\C++\\DS\\DS12\\toindex.huf", "D:\\study\\C++\\DS\\DS12\\toindex.out");
    //huffmanCompress("D:\\study\\C++\\DS\\DS12\\TheStoryofMankind.txt", "D:\\study\\C++\\DS\\DS12\\TheStoryofMankind.huf");
    //huffmanUncompress("D:\\study\\C++\\DS\\DS12\\TheStoryofMankind.huf", "D:\\study\\C++\\DS\\DS12\\TheStoryofMankind.out");
    huffmanCompress("D:\\study\\C++\\DS\\DS12\\compr3.txt", "D:\\study\\C++\\DS\\DS12\\compr3.huf");
    huffmanUncompress("D:\\study\\C++\\DS\\DS12\\compr3.huf", "D:\\study\\C++\\DS\\DS12\\compr3.out");

    std::cout << "Exercise 44" << std::endl;
    huffmanCompress512("D:\\study\\C++\\DS\\DS12\\comp512.txt", "D:\\study\\C++\\DS\\DS12\\comp512.huf");
    huffmanUncompress512("D:\\study\\C++\\DS\\DS12\\comp512.huf", "D:\\study\\C++\\DS\\DS12\\comp512.out");

}
