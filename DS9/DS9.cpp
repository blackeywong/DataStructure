// DS9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "arrayQueue.h"
#include "extendedQueue.h"
#include <sstream>
#include "slowArrayQueue.h"
#include <ctime>
#include "arrayQueue2.h"
#include "arrayQueue3.h"
#include "arrayDeque.h"
#include "dequeStack.h"
#include "dequeQueue.h"
#include "linkedQueue.h"
#include "linkedQueueFromExtendedChain.h"
#include "extendedLinkedQueue.h"
#include "doublyLinkedQueue.h"
#include "linkedDeque.h"
#include "circularDeque.h"
#include "applications.h"
#include "grid.h"
#include "imageComponent.h"
#include "machineShopSimulator.h"

int main()
{
    std::cout << "arrayQueue" << std::endl;
	arrayQueue<int> aq1;

	std::cout << aq1.empty() << std::endl;
	std::cout << aq1.size() << std::endl;
	aq1.push(1);
	std::cout << aq1.empty() << std::endl;
	std::cout << aq1.size() << std::endl;
	std::cout << aq1.front() << std::endl;
	std::cout << aq1.back() << std::endl;
	aq1.push(2);
	std::cout << aq1.front() << std::endl;
	std::cout << aq1.back() << std::endl;
	aq1.pop();
	std::cout << aq1.front() << std::endl;
	std::cout << aq1.back() << std::endl;
	aq1.pop();
	std::cout << aq1.size() << std::endl;

	arrayQueue<int> aq2(2);
	aq2.push(3);
	aq2.push(4);
	aq2.push(5);
	aq2.pop();
	aq2.pop();

	std::cout << "Exercise 5.2" << std::endl;
	std::string s5 = "1 3 5 7 9";
	std::istringstream iss5(s5);
	extendedQueue<int> eq5;
	iss5 >> eq5;
	std::cout << eq5 << std::endl;

	std::string s6 = "2 4 6 8 10";
	std::istringstream iss6(s6);
	extendedQueue<int> eq6;
	iss6 >> eq6;
	extendedQueue<int> eq7;
	eq7.merge(eq5, eq6);
	std::cout << eq7 << std::endl;
	std::cout << eq5 << std::endl;
	std::cout << eq6 << std::endl;
	eq7.split(eq5, eq6);
	std::cout << eq7 << std::endl;
	std::cout << eq5 << std::endl;
	std::cout << eq6 << std::endl;

	std::cout << "Exercise 6" << std::endl;
	slowArrayQueue<int> saq6;

	std::cout << saq6.empty() << std::endl;
	std::cout << saq6.size() << std::endl;
	saq6.push(1);
	std::cout << saq6.empty() << std::endl;
	std::cout << saq6.size() << std::endl;
	std::cout << saq6.front() << std::endl;
	std::cout << saq6.back() << std::endl;
	saq6.push(2);
	std::cout << saq6.front() << std::endl;
	std::cout << saq6.back() << std::endl;
	saq6.pop();
	std::cout << saq6.front() << std::endl;
	std::cout << saq6.back() << std::endl;
	saq6.pop();
	std::cout << saq6.size() << std::endl;
	saq6.push(3);
	saq6.push(4);
	saq6.push(5);

	clock_t start, finish;
	int n = 1.0000000;
	start = clock();
	for(int i=0;i<n;i++){
		saq6.push(6);
		saq6.pop();
	}
	finish = clock();
	std::cout << n << " push/pop of slowArrayQueue " << start<< " "<< finish  << " " << (double)(finish - start) / CLK_TCK << std::endl;

	start = clock();
	for (int i = 0; i < n; i++) {
		aq2.push(6);
		aq2.pop();
	}
	finish = clock();
	std::cout << n << " push/pop of slowArrayQueue " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;

	std::cout << "Exercise 7" << std::endl;
	arrayQueue2<int> aqq1;

	std::cout << aqq1.empty() << std::endl;
	std::cout << aqq1.size() << std::endl;
	aqq1.push(1);
	std::cout << aqq1.empty() << std::endl;
	std::cout << aqq1.size() << std::endl;
	std::cout << aqq1.front() << std::endl;
	std::cout << aqq1.back() << std::endl;
	aqq1.push(2);
	std::cout << aqq1.front() << std::endl;
	std::cout << aqq1.back() << std::endl;
	aqq1.pop();
	std::cout << aqq1.front() << std::endl;
	std::cout << aqq1.back() << std::endl;
	aqq1.pop();
	std::cout << aqq1.size() << std::endl;
	aqq1.push(3);
	aqq1.push(4);
	aqq1.pop();
	aqq1.push(5);
	aqq1.push(6);

	std::cout << "Exercise 8" << std::endl;
	arrayQueue3<int> aqq2;

	std::cout << aqq2.empty() << std::endl;
	std::cout << aqq2.size() << std::endl;
	aqq2.push(1);
	std::cout << aqq2.empty() << std::endl;
	std::cout << aqq2.size() << std::endl;
	std::cout << aqq2.front() << std::endl;
	std::cout << aqq2.back() << std::endl;
	aqq2.push(2);
	std::cout << aqq2.front() << std::endl;
	std::cout << aqq2.back() << std::endl;
	aqq2.pop();
	std::cout << aqq2.front() << std::endl;
	std::cout << aqq2.back() << std::endl;
	aqq2.pop();
	std::cout << aqq2.size() << std::endl;
	aqq2.push(3);
	aqq2.push(4);
	aqq2.pop();
	aqq2.push(5);
	aqq2.push(6);

	std::cout << "Exercise 9" << std::endl;
	arrayDeque<int> ad1;

	std::cout << ad1.empty() << std::endl;
	std::cout << ad1.size() << std::endl;
	ad1.push_back(1);
	std::cout << ad1.empty() << std::endl;
	std::cout << ad1.size() << std::endl;
	std::cout << ad1.front() << std::endl;
	std::cout << ad1.back() << std::endl;
	ad1.push_front(2);
	std::cout << ad1.front() << std::endl;
	std::cout << ad1.back() << std::endl;
	ad1.pop_front();
	std::cout << ad1.front() << std::endl;
	std::cout << ad1.back() << std::endl;
	ad1.pop_back();
	std::cout << ad1.size() << std::endl;
	ad1.push_back(3);
	ad1.push_back(4);
	ad1.pop_front();
	ad1.push_back(5);
	ad1.push_back(6);
	ad1.push_back(7);

	std::cout << "Exercise 10" << std::endl;
	dequeStack<int> ds;
	
	ds.push(5);
	ds.push(6);
	std::cout << ds.top() << std::endl;
	ds.pop();
	std::cout << ds.top() << std::endl;


	std::cout << "Exercise 11" << std::endl;
	dequeQueue<int> dq;

	std::cout << dq.empty() << std::endl;
	std::cout << dq.size() << std::endl;
	dq.push(1);
	std::cout << dq.empty() << std::endl;
	std::cout << dq.size() << std::endl;
	std::cout << dq.front() << std::endl;
	std::cout << dq.back() << std::endl;
	dq.push(2);
	std::cout << dq.front() << std::endl;
	std::cout << dq.back() << std::endl;
	dq.pop();
	std::cout << dq.front() << std::endl;
	std::cout << dq.back() << std::endl;
	dq.pop();
	std::cout << dq.size() << std::endl;
	dq.push(3);
	dq.push(4);
	dq.pop();
	dq.push(5);
	dq.push(6);

	std::cout << "LinkedQueue" << std::endl;
	linkedQueue<int> lq;

	std::cout << lq.empty() << std::endl;
	std::cout << lq.size() << std::endl;
	lq.push(1);
	std::cout << lq.empty() << std::endl;
	std::cout << lq.size() << std::endl;
	std::cout << lq.front() << std::endl;
	std::cout << lq.back() << std::endl;
	lq.push(2);
	std::cout << lq.front() << std::endl;
	std::cout << lq.back() << std::endl;
	lq.pop();
	std::cout << lq.front() << std::endl;
	std::cout << lq.back() << std::endl;
	lq.pop();
	std::cout << lq.size() << std::endl;
	lq.push(3);
	lq.push(4);
	lq.pop();
	lq.push(5);
	lq.push(6);

	std::cout << "Exercise 12" << std::endl;
	linkedQueueFromExtendedChain<int> lqfec;

	std::cout << lqfec.empty() << std::endl;
	std::cout << lqfec.size() << std::endl;
	lqfec.push(1);
	std::cout << lqfec.empty() << std::endl;
	std::cout << lqfec.size() << std::endl;
	std::cout << lqfec.front() << std::endl;
	std::cout << lqfec.back() << std::endl;
	lqfec.push(2);
	std::cout << lqfec.front() << std::endl;
	std::cout << lqfec.back() << std::endl;
	lqfec.pop();
	std::cout << lqfec.front() << std::endl;
	std::cout << lqfec.back() << std::endl;
	lqfec.pop();
	std::cout << lqfec.size() << std::endl;
	lqfec.push(3);
	lqfec.push(4);
	lqfec.pop();
	lqfec.push(5);
	lqfec.push(6);

	std::cout << "Exercise 13" << std::endl;
	std::string s13 = "1 3 5 7 9";
	std::istringstream iss13(s13);
	extendedLinkedQueue<int> elq13;
	iss13 >> elq13;
	std::cout << elq13 << std::endl;

	std::string s14 = "2 4 6 8 10";
	std::istringstream iss14(s14);
	extendedLinkedQueue<int> elq14;
	iss14 >> elq14;
	extendedLinkedQueue<int> elq15;
	elq15.merge(elq13, elq14);
	std::cout << elq15 << std::endl;
	std::cout << elq13 << std::endl;
	std::cout << elq14 << std::endl;
	elq15.split(elq13, elq14);
	std::cout << elq15 << std::endl;
	std::cout << elq13 << std::endl;
	std::cout << elq14 << std::endl;

	std::cout << "Exercise 14" << std::endl;
	arrayQueue<int> aq14;
	linkedQueue<int> lq14;
	n = 1.0000000;
	start = clock();
	for (int i = 0; i < n; i++) {
		aq14.push(1);
	}
	for (int i = 0; i < n; i++) {
		aq14.pop();
	}
	finish = clock();
	std::cout << n << " push/pop of arrayQueue " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;

	start = clock();
	for (int i = 0; i < n; i++) {
		lq14.push(1);
	}
	for (int i = 0; i < n; i++) {
		lq14.pop();
	}
	finish = clock();
	std::cout << n << " push/pop of linkedQueue " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;

	std::cout << "Exercise 15" << std::endl;
	std::string s15 = "1 3 5 7 9";
	std::istringstream iss15(s15);
	iss15 >> elq15;
	std::cout << elq15 << std::endl;
	ChainNode<int>* n1 = elq15.popNode();
	std::cout << elq15 << std::endl;
	elq15.pushNode(n1);
	std::cout << elq15 << std::endl;

	ChainNode<int>** cnlist = new  ChainNode<int>*[n];
	for (int i = 0; i < n; i++) {
		cnlist[i] = new ChainNode<int>;
	}
	extendedLinkedQueue<int> elq15_1;
	start = clock();
	for (int i = 0; i < n; i++) {
		elq15_1.pushNode(cnlist[i]);
	}
	for (int i = 0; i < n; i++) {
		cnlist[i] = elq15_1.popNode();
	}
	finish = clock();
	std::cout << n << " pushNode/popNode of extendedLinkedQueue " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << std::endl;
	for (int i = 0; i < n; i++) {
		delete cnlist[i];
	}
	delete[] cnlist;

	std::cout << "Exercise 16" << std::endl;
	doublyLinkedDeque<int> dld1;

	std::cout << dld1.empty() << std::endl;
	std::cout << dld1.size() << std::endl;
	dld1.push_back(1);
	std::cout << dld1.empty() << std::endl;
	std::cout << dld1.size() << std::endl;
	std::cout << dld1.front() << std::endl;
	std::cout << dld1.back() << std::endl;
	dld1.push_front(2);
	std::cout << dld1.front() << std::endl;
	std::cout << dld1.back() << std::endl;
	dld1.pop_front();
	std::cout << dld1.front() << std::endl;
	std::cout << dld1.back() << std::endl;
	dld1.pop_back();
	std::cout << dld1.size() << std::endl;
	dld1.push_back(3);
	dld1.push_back(4);
	dld1.pop_front();
	dld1.push_back(5);
	dld1.push_back(6);
	dld1.push_back(7);

	std::cout << "Exercise 17" << std::endl;
	linkedDeque<int> ld1;

	std::cout << ld1.empty() << std::endl;
	std::cout << ld1.size() << std::endl;
	ld1.push_back(1);
	std::cout << ld1.empty() << std::endl;
	std::cout << ld1.size() << std::endl;
	std::cout << ld1.front() << std::endl;
	std::cout << ld1.back() << std::endl;
	ld1.push_front(2);
	std::cout << ld1.front() << std::endl;
	std::cout << ld1.back() << std::endl;
	ld1.pop_front();
	std::cout << ld1.front() << std::endl;
	std::cout << ld1.back() << std::endl;
	ld1.pop_back();
	std::cout << ld1.size() << std::endl;
	ld1.push_back(3);
	ld1.push_back(4);
	ld1.pop_front();
	ld1.push_back(5);
	ld1.push_back(6);
	ld1.push_back(7);

	std::cout << "Exercise 18" << std::endl;
	circularDeque<int> cd1;

	std::cout << cd1.empty() << std::endl;
	std::cout << cd1.size() << std::endl;
	cd1.push_back(1);
	std::cout << cd1.empty() << std::endl;
	std::cout << cd1.size() << std::endl;
	std::cout << cd1.front() << std::endl;
	std::cout << cd1.back() << std::endl;
	cd1.push_front(2);
	std::cout << cd1.front() << std::endl;
	std::cout << cd1.back() << std::endl;
	cd1.pop_front();
	std::cout << cd1.front() << std::endl;
	std::cout << cd1.back() << std::endl;
	cd1.pop_back();
	std::cout << cd1.size() << std::endl;
	cd1.push_back(3);
	cd1.push_back(4);
	cd1.pop_front();
	cd1.push_back(5);
	cd1.push_back(6);
	cd1.push_back(7);

	std::cout << "Train Track Rearrangement" << std::endl;
	int input[10] = {0,3,6,9,2,4,7,1,8,5};
	railroad(input, 9, 3);

	std::cout << "Exercise 22" << std::endl;
	int trackSize[4] = {0, 3,1, 4};
	railroad(input, 9, 3, trackSize);

	std::cout << "Exercise 23" << std::endl;
	railroadWithNoQueues(input, 9, 3);

	std::cout << "Exercise 24" << std::endl;
	railroadWithNoStacks(input, 9, 3);

	std::cout << "Exercise 26" << std::endl;
	std::string grid_str = \
		" 0 0 1 0 0 0 0 " \
		" 0 0 1 1 0 0 0 " \
		" 0 0 0 0 1 0 0 " \
		" 0 0 0 1 1 0 0 " \
		" 1 0 0 0 1 0 0 " \
		" 1 1 1 0 0 0 0 " \
		" 1 1 1 0 0 0 0 ";
	Grid<7> grid(grid_str);
	if (grid.findPath(position(3,2),position(4,6)))
		grid.showPath();
	else
		std::cout << "No path." << std::endl;

	std::cout << "Exercise 27" << std::endl;
	grid.clearPath(position(3, 2), position(4, 6));
	if (grid.findPath(position(7, 4), position(5, 7)))
		grid.showPath();
	else
		std::cout << "No path." << std::endl;

	std::cout << "Exercise 28" << std::endl;
	std::string pixel_str = \
		" 0 0 1 0 0 0 0 " \
		" 0 0 1 1 0 0 0 " \
		" 0 0 0 0 1 0 0 " \
		" 0 0 0 1 1 0 0 " \
		" 0 1 0 0 1 0 1 " \
		" 1 1 1 0 0 0 1 " \
		" 1 1 1 0 0 1 1 ";
	ImageComponent<7> image(pixel_str);
	image.labelComponent();
	image.showImage();

	std::cout << "Machine Shop Simulation" << std::endl;
	//machineShopSimulator mss(3, 4);
	std::string strChangeTime = "2 3 1";
	//std::string strTasks = "3 1 2 2 4 1 1 2 3 4 1 2 2 1 4 2 4 2 3 1 2 3";
	//Exercise 34
	//std::string strTasks = "3 1 2 0 2 4 1 1 1 2 2 3 4 0 1 2 1 2 1 4 0 2 4 2 2 3 1 0 2 3 3";
	//std::string strTasks = "3 1 2 0 2 4 0 1 1 0 2 3 4 0 1 2 0 2 1 4 0 2 4 0 2 3 1 0 2 3 0";
	//Exercise 35
	machineShopSimulator mss(3, 4, 15);
	std::string strTasks = "3 0 1 2 0 2 4 1 1 1 2 2 0 3 4 0 1 2 1 2 3 1 4 0 2 4 2 2 6 3 1 0 2 3 3";
	//machineShopSimulator mss(3, 2, 15);
	//std::string strTasks = "3 0 1 2 0 2 4 1 1 1 2 2 1 3 4 0 1 2 1";
	mss.inputData(strChangeTime, strTasks);
	mss.startShop();
	mss.simulate();
	mss.outputStatistics();
}
