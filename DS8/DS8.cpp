// DS8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include "derivedArrayStack.h"
#include "arrayStack.h"
#include "extendedDerivedArrayStack.h"
#include "extendedArrayStack.h"
#include "stackWithArrayList.h"
#include "twoStacks.h"
#include "derivedLinkedStack.h"
#include "linkedStack.h"
#include "extendedLinkedStack.h"
#include "applications.h"
#include "drawing.h"
#include <thread>
#include <chrono>
#include "maze.h"
#include <iterator>


void lastAsBig(int data[], int result[], int size) {
	arrayStack<int> stack;

	result[0] = -1;
	stack.push(0);

	for (int i = 1; i < 6; ++i) {
		if (data[i-1] > data[i]) {
			result[i] = i-1;
			stack.push(i-1);
			continue;
		}
		while (stack.size() > 0) {
			int top = stack.top();
			if (data[top] > data[i]) {
				result[i] = top;
				break;
			}
			else {
				stack.pop();
			}
		}
		if(stack.size() == 0) {
			result[i] = -1;
			stack.push(i);
		}
	}
}

int main()
{
	//std::cout << "Array Stack" << std::endl;
	//derivedArrayStack<int> st;
	////arrayStack<int> st;
	//st.push(5);
	//st.push(6);
	//std::cout << st.top() << std::endl;
	//st.pop();
	//std::cout << st.top() << std::endl;

	//std::cout << "Exercise 7.3" << std::endl;
	////extendedDerivedArrayStack<int> st3, st4, st5;
	//extendedArrayStack<int> st3, st4, st5;
	//st3.push(5);
	//st3.push(6);
	//std::cout << st3.top() << std::endl;
	//st3.pop();
	//std::cout << st3.top() << std::endl;
	//std::string s3("1 3 5 8");
	//std::istringstream iss3(s3);
	//iss3 >> st3;
	//std::cout << st3 << std::endl;

	//st3.split(st4, st5);
	//std::cout << st4 << std::endl;
	//std::cout << st5 << std::endl;
	//st5.merge(st4);
	//std::cout << st5 << std::endl;

	//std::cout << "Exercise 10" << std::endl;
	//stackWithArrayList<int> st6;
	//st6.push(5);
	//st6.push(6);
	//std::cout << st6.top() << std::endl;
	//st6.pop();
	//std::cout << st6.top() << std::endl;

	//std::cout << "Exercise 11" << std::endl;
	//twoStacks<int> st7(2);
	//st7.push1(4);
	//st7.push1(5);
	//st7.push1(6);
	//std::cout << st7.top1() << std::endl;
	//st7.pop1();
	//std::cout << st7.top1() << std::endl;
	//st7.push2(7);
	//st7.push2(8);
	//st7.push2(9);
	//std::cout << st7.top2() << std::endl;
	//st7.pop1();
	//st7.pop2();
	//st7.pop2();
	//st7.pop2();
	//std::cout << st7.top1() << std::endl;
	////std::cout << st7.top2() << std::endl;

	//std::cout << "Linked Stack" << std::endl;
	////derivedLinkedStack<int> st8;
	//linkedStack<int> st8;

	//st8.push(5);
	//st8.push(6);
	//std::cout << st8.top() << std::endl;
	//st8.pop();
	//std::cout << st8.top() << std::endl;

	//std::cout << "Exercise 12" << std::endl;
	//ChainNode<int>* node1 = new ChainNode<int>(7, nullptr);
	//st8.pushNode(node1);
	//std::cout << st8.top() << std::endl;
	//node1 = st8.popNode();
	//std::cout << st8.top() << std::endl;

	//std::cout << "Exercise 12.3" << std::endl;
	//clock_t start, finish;
	//int n = 1.0000000;
	//start = clock();
	//for(int i=0;i<n;i++){
	//	st8.push(6);
	//	st8.pop();
	//}
	//finish = clock();
	//cout << n << " push/pop " << start<< " "<< finish  << " " << (double)(finish - start) / CLK_TCK << endl;

	//start = clock();
	//for (int i = 0; i < n; i++) {
	//	st8.pushNode(node1);
	//	node1 = st8.popNode();
	//}
	//finish = clock();
	//cout << n << " pushNode/popNode " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << endl;

	//delete node1;

	//std::cout << "Exercise 13" << std::endl;
	//extendedLinkedStack<int> st9, st10, st11;
	//st9.push(5);
	//st9.push(6);
	//std::cout << st9.top() << std::endl;
	//st9.pop();
	//std::cout << st9.top() << std::endl;
	//std::string s4("1 3 5 8");
	//std::istringstream iss4(s4);
	//iss4 >> st9;
	//std::cout << st9 << std::endl;

	//st9.split(st10, st11);
	//std::cout << st10 << std::endl;
	//std::cout << st11 << std::endl;
	//st11.merge(st10);
	//std::cout << st11 << std::endl;

	//std::cout << "Exercise 14" << std::endl;
	//n = 1.0000000;
	//start = clock();
	//for (int i = 0; i < n; i++) {
	//	st.push(6);
	//	st.pop();
	//}
	//finish = clock();
	//cout << n << " push/pop of DerivedArrayStack " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << endl;

	//derivedLinkedStack<int> st12;
	//start = clock();
	//for (int i = 0; i < n; i++) {
	//	st12.push(6);
	//	st12.pop();
	//}
	//finish = clock();
	//cout << n << " push/pop of DerivedLinkedStack " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << endl;

	//start = clock();
	//for (int i = 0; i < n; i++) {
	//	st9.push(6);
	//	st9.pop();
	//}
	//finish = clock();
	//cout << n << " push/pop of extendedLinkedStack " << start << " " << finish << " " << (double)(finish - start) / CLK_TCK << endl;

	//std::cout << "Exercise 15" << std::endl;
	////std::string s15 = "(a*(b+c)+d)";
	////std::string s15 = "(a(*(b+c)+(d)";
	//std::string s15 = ")e)(a(*(b+c)+(d)";
	////std::cout << unmatchedParen(s15) << std::endl;
	//printMatchedParensNoStack(s15);
	////printMatchedPairs(s15);

	//std::cout << "Exercise 16" << std::endl;
	//std::string s16 = ")e](a*([b]+c)+[(d])";
	//printMatchedPairs2(s16);

	//std::cout << "Exercise 17" << std::endl;
	//std::string s17 = "f)e]g}(a[h{i*{([b]+c)+j}+[{(d])}";
	//printMatchedPairs3(s17);

	//std::cout << "Tower of Hanoi" << std::endl;
	////towersOfHanoi(3, 1, 2, 3);
	//std::cout << "Exercise 20" << std::endl;
	//towersOfHanoi(5);

	////Exercise 21
	//HanoiTower<5, 3> ht;
	//ht.move();
	//std::cin.ignore();

	////Exercise 22
	//HaHaTower<7, 3> hht;
	//hht.move();
	//std::cin.ignore();

	////Exercise 23
	//HanoiTower<11, 5> ht;
	//ht.move();
	//std::cin.ignore();

	//std::cout << "Train Track Rearrangement" << std::endl;
	//int input[10] = {0,3,6,9,2,4,7,1,8,5};
	////railroad(input, 9, 3);

	//std::cout << "Exercise 27" << std::endl;
	////Exercise 27
	//int input2[9] = { 0,4,5,8,2,7,6,1,3 };
	//int trackSize[4] = {0,2,1,3};
	//railroad(input2, 8, 3, trackSize);

	//std::cout << "Switch Box Routing" << std::endl;
	//int net[8] = { 1,2,2,1,3,3,4,4 };
	//int net2[14] = { 1,2,3,3,2,1,4,5,5,4,6,7,7,6 };
	//int net3[8] = { 1,2,2,1,3,4,3,4 };
	//checkBox(net, 8);
	//checkBox(net2, 14);
	//checkBox(net3, 8);

	//std::cout << "Offline Equivalence Class" << std::endl;
	//int n = 9;
	//std::string relations = "(1,5), (1,6), (3,7), (4,8), (5,2), (6,5), (4,9), (9,7), (7,8), (3,4), (6,2)";
	//offlineEquivClass(relations, n);

	//std::cout << "Exercise 32" << std::endl;
	//std::string relations2 = "(1,3), (4,2), (3,8), (6,7), (5,8), (6,2), (1,5), (4,7), (9,7)";
	//offlineEquivClass2(relations2, n);

	std::cout << "Exercise 33" << std::endl;
	std::string maze_str = " 0 1 1 1 1 1 0 0 0 0 " \
						   " 0 0 0 0 0 1 0 1 0 0 " \
						   " 0 0 0 1 0 1 0 0 0 0 " \
						   " 0 1 0 1 0 1 0 1 1 0 " \
						   " 0 1 0 1 0 1 0 1 0 0 " \
						   " 0 1 1 1 0 1 0 1 0 1 " \
						   " 0 1 0 0 0 1 0 1 0 1 " \
						   " 0 1 0 1 1 1 0 1 0 0 " \
						   " 1 0 0 0 0 0 0 1 0 0 " \
						   " 0 0 0 0 1 1 1 1 0 0 ";
	Maze<10> maze(maze_str);
	if (maze.findPath())
	//Exercise 36
	//if (maze.findPath2(position(1,1), 0))
		maze.showPath();
	else
		std::cout << "No path." << std::endl;

	//Exercise 38
	int data[6] = { 6, 2, 3, 1, 7, 5 };
	int result[6];
	lastAsBig(data, result, 6);
	copy(result, result + 6, std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;



}



