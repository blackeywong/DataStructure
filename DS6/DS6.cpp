// DS3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include "../DS5/exceptions.h"
//#include "chain.h"
//#include "extendedchain.h"
//#include "moveleftandrightonchain.h"
//#include "circular.h"
//#include "extendedcircular.h"
//#include "double.h"
//#include "doublecircular.h"
//#include "extendeddoublecircular.h"
//#include "studentrecord.h"
//#include "card.h"
//
//#include "ConvexHull/point.h"
//#include "ConvexHull/vectorpoints.h"
//#include "ConvexHull/doublepoints.h"
//#include "ConvexHull/doublecircularpoints.h"
//#include "ConvexHull/chainpoints.h"
//#include "ConvexHull/moveleftandrightonchainpoints.h"
//
//#include "BigInteger/BigIntegerInVector.h"
//#include "BigInteger/BigIntegerInDouble.h"
//
//#include "Polynomial/PolynomialInVector.h"
//#include "Polynomial/PolynomialInCircular.h"

#include "EquivalentClass/EquivalentClassInSimChain.h"
//#include "EquivalentClass/EquivalentClassInList.h"
//#include "EquivalentClass/EquivalentClassInChain.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第六章

//Exercise 78, Example 6-5
const int NUM_OF_TASK = 4;

class SparePeriod: public EquivalentClassInSimChain{
public:
	SparePeriod(int periods) : EquivalentClassInSimChain(periods){}
	int assign(int period){//period is used, need to unite all period to period-1
		int result = near(period);
		if(result == 0){return 0;}
		int k;
		for (k = result; node[k].next != 0; k = node[k].next) {
			node[k].equivClass = near(period -1);
		}
		node[k].equivClass = near(period - 1);

		//insert classA after firstnode of classB
		node[near(period - 1)].size += node[result].size;
		node[k].next = node[near(period - 1)].next;
		node[near(period - 1)].next = result;

		return result;
	}
	int near(int period){
		return find(period);
	}
};

struct TaskNode{
	string name;
	int startTime;
	int deadline;
	int period;
	TaskNode(string theName, int theStartTime, int theDeadline):name(theName),startTime(theStartTime),deadline(theDeadline){period = 0;}
};

bool compareTaskStartByTime(TaskNode a, TaskNode b){
	return a.startTime < b.startTime;
} 

bool compareTaskByPeriod(TaskNode a, TaskNode b){
	return a.period < b.period;
} 

class Tasks{
public:
	Tasks(){initialize();}
	void scheduleTasks(){
		sortTask();

		SparePeriod sp(NUM_OF_TASK);

		for(int i=0;i<NUM_OF_TASK;i++){
			tasks[i].period = sp.assign(tasks[i].deadline);
			if(tasks[i].period == 0){
				cout << "fail to find a schedule." << endl;
				return;
			}
		}

		sort(tasks.begin(), tasks.end(),compareTaskByPeriod);

		output(cout);
	}

	void output(ostream& out){
		for(int i=0;i<NUM_OF_TASK;i++){
			out << "Task " << tasks[i].name << " is scheduled at time period " << tasks[i].period << "." << endl;
		}
	}
protected:
	void initialize(){
		TaskNode task1("A", 0, 4);
		tasks.push_back(task1);
		TaskNode task2("B", 0, 4);
		tasks.push_back(task2);
		TaskNode task3("C", 1, 2);
		tasks.push_back(task3);
		TaskNode task4("D", 2, 3);
		tasks.push_back(task4);
	}

	void sortTask(){
		sort(tasks.begin(), tasks.end(),compareTaskStartByTime);
		reverse(tasks.begin(), tasks.end());
	}

	vector<TaskNode> tasks;
};

int main(){
	Tasks tasks;
	tasks.scheduleTasks();
}

////Exercise 77, Example 6-6
//class WireNet: public EquivalentClassInChain{
//public:
//	WireNet(int pinNum) : EquivalentClassInChain(pinNum){}
//	void connect(int pinA, int pinB){
//		unite(find(pinA), find(pinB));
//	}
//};
//
//int main(){
//	clock_t start, finish;
//	int n = 1000000;
//	start = clock();
//	for(int i=0;i<n;i++){
//		WireNet wn(14);
//		//cout << wn << endl;
//		wn.connect(1, 11);
//		//cout << wn << endl;
//		wn.connect(7, 11);
//		//cout << wn << endl;
//		wn.connect(2, 12);
//		//cout << wn << endl;
//		wn.connect(12, 8);
//		//cout << wn << endl;
//		wn.connect(11, 12);
//		//cout << wn << endl;
//		wn.connect(3, 13);
//		//cout << wn << endl;
//		wn.connect(4, 13);
//		//cout << wn << endl;
//		wn.connect(13, 14);
//		//cout << wn << endl;
//		wn.connect(14, 9);
//		//cout << wn << endl;
//		wn.connect(5, 14);
//		//cout << wn << endl;
//		wn.connect(6, 10);
//		//cout << wn << endl;
//	}
//	finish = clock();
//	cout << n << " " << start<< " "<< finish  << " " << (double)(finish - start) / CLK_TCK << endl;
//
//}
////Exercise 76, Example 6-6
//class WireNet: public EquivalentClassInList{
//public:
//	WireNet(int pinNum) : EquivalentClassInList(pinNum){}
//	void connect(int pinA, int pinB){
//		unite(find(pinA), find(pinB));
//	}
//};
//
//int main(){
//	clock_t start, finish;
//	int n = 1000000;
//	start = clock();
//	for(int i=0;i<n;i++){
//		WireNet wn(14);
//		//cout << wn << endl;
//		wn.connect(1, 11);
//		//cout << wn << endl;
//		wn.connect(7, 11);
//		//cout << wn << endl;
//		wn.connect(2, 12);
//		//cout << wn << endl;
//		wn.connect(12, 8);
//		//cout << wn << endl;
//		wn.connect(11, 12);
//		//cout << wn << endl;
//		wn.connect(3, 13);
//		//cout << wn << endl;
//		wn.connect(4, 13);
//		//cout << wn << endl;
//		wn.connect(13, 14);
//		//cout << wn << endl;
//		wn.connect(14, 9);
//		//cout << wn << endl;
//		wn.connect(5, 14);
//		//cout << wn << endl;
//		wn.connect(6, 10);
//		//cout << wn << endl;
//	}
//	finish = clock();
//	cout << n << " " << start<< " "<< finish  << " " << (double)(finish - start) / CLK_TCK << endl;
//}

////Exercise 73, Example 6-6
//class WireNet: public EquivalentClassInSimChain{
//public:
//	WireNet(int pinNum) : EquivalentClassInSimChain(pinNum){}
//	void connect(int pinA, int pinB){
//		unite(find(pinA), find(pinB));
//	}
//};
//
//int main(){
//	clock_t start, finish;
//	int n = 1000000;
//	start = clock();
//	for(int i=0;i<n;i++){
//		WireNet wn(14);
//		//cout << wn << endl;
//		wn.connect(1, 11);
//		//cout << wn << endl;
//		wn.connect(7, 11);
//		//cout << wn << endl;
//		wn.connect(2, 12);
//		//cout << wn << endl;
//		wn.connect(12, 8);
//		//cout << wn << endl;
//		wn.connect(11, 12);
//		//cout << wn << endl;
//		wn.connect(3, 13);
//		//cout << wn << endl;
//		wn.connect(4, 13);
//		//cout << wn << endl;
//		wn.connect(13, 14);
//		//cout << wn << endl;
//		wn.connect(14, 9);
//		//cout << wn << endl;
//		wn.connect(5, 14);
//		//cout << wn << endl;
//		wn.connect(6, 10);
//		//cout << wn << endl;
//	}
//	finish = clock();
//	cout << n << " " << start<< " "<< finish  << " " << (double)(finish - start) / CLK_TCK << endl;
//
//}


////Exercise 71
//int main() {
//	string input1("2 3 1 1 2");
//	istringstream ss1(input1);
//	Polynomial p1(ss1);
//	cout << p1 << endl;
//	Polynomial p2;
//	cout << p2 << endl;
//	p2 = p1;
//	cout << p2 << endl;
//	Polynomial p3(p2);
//	cout << p3 << endl;
//
//	cout << p3.getDegree() << endl;
//	cout << p3.valueOf(2) << endl;
//	cout << p3.valueOf(0) << endl;
//
//	p2.add(p1);
//	cout << p2 << endl;
//	p2.subtract(p1);
//	cout << p2 << endl;
//
//	string input111("4 4 2 3 -1 2 -3 0 5");
//	istringstream ss111(input111);
//	Polynomial p111(ss111);
//	p2.add(p111);
//	cout << p2 << endl;
//	string input1111("4 4 2 3 1 2 -3 0 5");
//	istringstream ss1111(input1111);
//	Polynomial p1111(ss1111);
//	p3.subtract(p1111);
//	cout << p3 << endl;
//
//	istringstream ss4(string("3 5 5 3 -3 1 -1"));
//	Polynomial p4(ss4);
//	istringstream ss5(string("3 5 -5 3 3 1 3"));
//	Polynomial p5(ss5);
//
//	p5.add(p4);
//	cout << p5 << endl;
//
//	istringstream ss6(string("3 5 5 3 -3 1 -1"));
//	Polynomial p6(ss6);
//	istringstream ss7(string("2 3 3 1 3"));
//	Polynomial p7(ss7);
//	p6.subtract(p7);
//	cout << p6 << endl;
//
//	p3.subtract(p2);
//	cout << p3 << endl;
//	cout << "multiply" << endl;
//	istringstream ss8(string("2 1 1 0 1"));
//	Polynomial p8(ss8);
//	istringstream ss9(string("2 1 1 0 1"));
//	Polynomial p9(ss9);
//	p8.multiply(p9);
//	cout << p8 << endl;
//
//	Polynomial p10 = p2;
//	p10.multiply(p2);
//	cout << p10 << endl;
//
//	cout << p6 << endl;
//	cout << p7 << endl;
//	p7.multiply(p6);
//	cout << p7 << endl;
//	cout << "devide" << endl;
//	istringstream ss11(string("3 5 5 3 -3 1 -1"));
//	Polynomial p11(ss11);
//	istringstream ss12(string("2 3 3 1 3"));
//	Polynomial p12(ss12);
//
//	p11.divide(p12);
//	cout << p11 << endl;
//	p8.divide(p9);
//	cout << p8 << endl;
//	p8.divide(p9);
//	cout << p8 << endl;
//}
//
//int main() {
//	string input("3 1 2 3 4");
//	istringstream ss(input);
//	Polynomial p1(ss);
//	cout << p1 << endl;
//	Polynomial p2;
//	cout << p2 << endl;
//	p2 = p1;
//	cout << p2 << endl;
//	Polynomial p3(p2);
//	cout << p3 << endl;
//
//	cout << p3.getDegree() << endl;
//	cout << p3.valueOf(3) << endl;
//	cout << p3.valueOf(0) << endl;
//
//	p2.add(p1);
//	cout << p2 << endl;
//	p2.subtract(p1);
//	cout << p2 << endl;
//
//	istringstream ss4(string("5 0 -1 0 -3 0 5"));
//	Polynomial p4(ss4);
//	istringstream ss5(string("5 0 3 0 3 0 -5"));
//	Polynomial p5(ss5);
//
//	p5.add(p4);
//	cout << p5 << endl;
//
//	istringstream ss6(string("5 0 -1 0 -3 0 5"));
//	Polynomial p6(ss6);
//	istringstream ss7(string("3 0 3 0 3"));
//	Polynomial p7(ss7);
//	p6.subtract(p7);
//	cout << p6 << endl;
//
//	p3.subtract(p2);
//	cout << p3 << endl;
//
//	istringstream ss8(string("1 1 1"));
//	Polynomial p8(ss8);
//	istringstream ss9(string("1 1 1"));
//	Polynomial p9(ss9);
//	p8.multiply(p9);
//	cout << p8 << endl;
//
//	Polynomial p10 = p2;
//	p10.multiply(p2);
//	cout << p10 << endl;
//
//	cout << p6 << endl;
//	cout << p7 << endl;
//	p7.multiply(p6);
//	cout << p7 << endl;
//
//	istringstream ss11(string("5 0 -1 0 -3 0 5"));
//	Polynomial p11(ss11);
//	istringstream ss12(string("3 0 3 0 3"));
//	Polynomial p12(ss12);
//
//	p11.divide(p12);
//	cout << p11 << endl;
//	p8.divide(p9);
//	cout << p8 << endl;
//	p8.divide(p9);
//	cout << p8 << endl;
//}

////Exercise 69
//int main() {
//	BigIntegerInDouble n1(string("123"));
//	BigIntegerInDouble n2(n1);
//	BigIntegerInDouble n3(string("124"));
//	BigIntegerInDouble n4(string("1231"));
//	BigIntegerInDouble n5(string("-123"));
//	BigIntegerInDouble n6(string("-124"));
//	BigIntegerInDouble n7(string("-1231"));
//	BigIntegerInDouble n8 = n5;
//	cout << n1 << endl;
//	cout << n2 << endl;
//	cout << n5 << endl;
//	cout << (n1 == n2) << endl;
//	cout << (n1 != n2) << endl;
//	cout << (n1 < n4) << endl;
//	cout << (n1 <= n2) << endl;
//	cout << (n5 <= n7) << endl;
//	cout << (n1 > n5) << endl;
//	cout << "compare -123 and -124" << endl;
//	cout << (n5 >= n6) << endl;
//	cout << (n5 > n6) << endl;
//	cout << (n5 <= n6) << endl;
//	cout << (n5 < n6) << endl;
//	cout << (n5 == n6) << endl;
//	cout << (n5 != n6) << endl;
//	cout << "compare -123 and -123" << endl;
//	cout << (n5 >= n8) << endl;
//	cout << (n5 > n8) << endl;
//	cout << (n5 < n8) << endl;
//	cout << (n5 <= n8) << endl;
//	cout << (n5 == n8) << endl;
//	cout << (n5 != n8) << endl;
//	cout << "add" << endl;
//	n1 += n2;
//	cout << n1 << endl;
//	n1 += n4;
//	cout << n1 << endl;
//	n4 += n3;
//	cout << n4 << endl;
//	n1 += n4;
//	cout << n1 << endl;
//	n1 += n1;
//	cout << n1 << endl;
//	n1 += n1;
//	cout << n1 << endl;
//	n1 += n7;
//	cout << n1 << endl;
//	n1 += n7;
//	cout << n1 << endl;
//	n1 -= n7;
//	cout << n1 << endl;
//	n7 -= n1;
//	cout << n7 << endl;
//	cout << "+-*/" << endl;
//	cout << n1 - n7 << endl;
//	n1 -= n7;
//	cout << n1 << endl;
//	cout << n7 << endl;
//	cout << n7 + n4 << endl;
//	n7 += n4;
//	cout << n7 << endl;
//
//	BigIntegerInDouble n9("67467613204971504");
//	BigIntegerInDouble n10("89894378523475893054353443");
//	/*BigIntegerInDouble n9("-111");
//	BigIntegerInDouble n10("-11");*/
//	cout << n9 * n10 << endl;
//	n9 *= n10;
//	cout << n9 << endl;
//
//	BigIntegerInDouble n11("5345364787877");
//	BigIntegerInDouble n12("34545");
//	cout << n11 / n12 << endl;
//	cout << n11 % n12 << endl;
//	n11 /= n12;
//	cout << n11 << endl;
//	BigIntegerInDouble n13("5345364787877");
//	n13 %= n12;
//	cout << n13 << endl;
//
//}
////Exercise 69
//int main() {
//	BigInteger n1(string("123"));
//	BigInteger n2(n1);
//	BigInteger n3(string("124"));
//	BigInteger n4(string("1231"));
//	BigInteger n5(string("-123"));
//	BigInteger n6(string("-124"));
//	BigInteger n7(string("-1231"));
//	BigInteger n8 = n5;
//	cout << n1 << endl;
//	cout << n2 << endl;
//	cout << n5 << endl;
//	cout << (n1 == n2) << endl;
//	cout << (n1 != n2) << endl;
//	cout << (n1 < n4) << endl;
//	cout << (n1 <= n2) << endl;
//	cout << (n5 <= n7) << endl;
//	cout << (n1 > n5) << endl;
//	cout << "compare -123 and -124" << endl;
//	cout << (n5 >= n6) << endl;
//	cout << (n5 > n6) << endl;
//	cout << (n5 <= n6) << endl;
//	cout << (n5 < n6) << endl;
//	cout << (n5 == n6) << endl;
//	cout << (n5 != n6) << endl;
//	cout << "compare -123 and -123" << endl;
//	cout << (n5 >= n8) << endl;
//	cout << (n5 > n8) << endl;
//	cout << (n5 < n8) << endl;
//	cout << (n5 <= n8) << endl;
//	cout << (n5 == n8) << endl;
//	cout << (n5 != n8) << endl;
//	cout << "add" << endl;
//	n1 += n2;
//	cout << n1 << endl;
//	n1 += n4;
//	cout << n1 << endl;
//	n4 += n3;
//	cout << n4 << endl;
//	n1 += n4;
//	cout << n1 << endl;
//	n1 += n1;
//	cout << n1 << endl;
//	n1 += n1;
//	cout << n1 << endl;
//	n1 += n7;
//	cout << n1 << endl;
//	n1 += n7;
//	cout << n1 << endl;
//	n1 -= n7;
//	cout << n1 << endl;
//	n7 -= n1;
//	cout << n7 << endl;
//	n1 -= n7;
//	cout << n1 << endl;
//	cout << n7 << endl;
//	n7 += n4;
//	cout << n7 << endl;
//
//	BigInteger n9("67467613204971504");
//	BigInteger n10("89894378523475893054353443");
//	n9 *= n10;
//	cout << n9 << endl;
//
//	BigInteger n11("5345364787877");
//	BigInteger n12("34545");
//	n11 /= n12;
//	cout << n11 << endl;
//	BigInteger n13("5345364787877");
//	n13 %= n12;
//	cout << n13 << endl;
//
//}


////Exercise 68 in MoveLeftAndRightOnChain
//int main() {
//	Point p1(3, 2);
//	Point p2(2, 2);
//	Point p3(3, 1);
//	//MoveLeftAndRightOnChain<Point> pts;
//	//pts.insert(0, Point(1, 1));
//	//pts.insert(1, Point(2, 2));
//	//pts.insert(2, Point(3, 3));
//	//pts.insert(3, Point(4, 4));
//	//pts.insert(4, Point(5, 5));
//	//pts.insert(5, Point(6, 6));
//
//	MoveLeftAndRightOnChain<Point> pts;
//	pts.insert(0, Point(3, 2));
//	pts.insert(1, Point(2, 2));
//	pts.insert(2, Point(3, 1));
//	pts.insert(3, Point(5, 6));
//	pts.insert(4, Point(2, 7));
//	pts.insert(5, Point(3, 8));
//	pts.insert(6, Point(6, 2));
//	pts.insert(7, Point(7, 7));
//	pts.insert(0, Point(3824, -1234));
//	pts.insert(0, Point(-5678, -3213));
//	MoveLeftAndRightOnChain<Point> endpoints;
//	Point pole(0, 0);
//
//	cout << pointsInSameLine(pts, endpoints, pole) << endl;
//	cout << pole << endl;
//
//	//Point p4(3, 3);
//	////double tangent = calTangent(pole, p4);
//	////cout << tangent << endl;
//	////cout << calPoler(pole, p4, tangent) << endl;
//
//	//SortPoints(pts);
//	//pts.reset();
//	//while (!pts.atEnd()) {
//	//	cout << pts.current() << endl;
//	//	pts.moveToNext();
//	//}
//	//cout << pts.current() << endl;
//
//	//cout << lengthOfTwoPoints(p1, p3) << endl;
//	//cout << angleOfThreePoints(p2, p1, p3) << endl;;
//	//cout << angleOfThreePoints(p4, p2, p1) << endl;;
//	//cout << angleOfThreePointsCounterClockwise(p1, p2, p3) << endl;
//
//	MoveLeftAndRightOnChain<Point> convexHull;
//	getConvexHull(pts, convexHull);
//	convexHull.reset();
//	while (!convexHull.atEnd()) {
//		cout << convexHull.current() << endl;
//		convexHull.moveToNext();
//	}
//	cout << convexHull.current() << endl;
//}
////Exercise 67 in Chain
//int main() {
//	Point p1(3, 2);
//	Point p2(2, 2);
//	Point p3(3, 1);
//	//ExtendedChain<Point> pts;
//	//pts.insert(0, Point(1, 1));
//	//pts.insert(1, Point(2, 2));
//	//pts.insert(2, Point(3, 3));
//	//pts.insert(3, Point(4, 4));
//	//pts.insert(4, Point(5, 5));
//	//pts.insert(5, Point(6, 6));
//
//	ExtendedChain<Point> pts;
//	pts.insert(0, Point(3, 2));
//	pts.insert(1, Point(2, 2));
//	pts.insert(2, Point(3, 1));
//	pts.insert(3, Point(5, 6));
//	pts.insert(4, Point(2, 7));
//	pts.insert(5, Point(3, 8));
//	pts.insert(6, Point(6, 2));
//	pts.insert(7, Point(7, 7));
//	pts.insert(0, Point(3824, -1234));
//	pts.insert(0, Point(-5678, -3213));
//	ExtendedChain<Point> endpoints;
//	Point pole(0, 0);
//
//	//cout << pointsInSameLine(pts, endpoints, pole) << endl;
//	//cout << pole << endl;
//
//	//Point p4(3, 3);
//	////double tangent = calTangent(pole, p4);
//	////cout << tangent << endl;
//	////cout << calPoler(pole, p4, tangent) << endl;
//
//	//SortPoints(pts);
//	//for (Point pt : pts) {
//	//	cout << pt << endl;
//	//}
//
//	//cout << lengthOfTwoPoints(p1, p3) << endl;
//	//cout << angleOfThreePoints(p2, p1, p3) << endl;;
//	//cout << angleOfThreePoints(p4, p2, p1) << endl;;
//	//cout << angleOfThreePointsCounterClockwise(p1, p2, p3) << endl;
//
//	ExtendedChain<Point> convexHull;
//	getConvexHull(pts, convexHull);
//
//	for (Point pt : convexHull) {
//		cout << pt << endl;
//	}
//}
////Exercise 67 in DoubleCircular
//int main() {
//	Point p1(3, 2);
//	Point p2(2, 2);
//	Point p3(3, 1);
//	//ExtendedDoubleCircular<Point> pts({ Point(-5678, -3213), Point(3824, -1234), p1, p2, p3, Point(5,6), Point(2,7) , Point(3,8), Point(6,2), Point(7,7) });
//	//ExtendedDoubleCircular<Point> pts({ Point(1,1), Point(2,2), Point(3,3) , Point(4,4), Point(5,5), Point(6,6) });
//	//ExtendedDoubleCircular<Point> pts({ Point(1,1) });//VC bug??
//	/*ExtendedDoubleCircular<Point> pts;
//	pts.insert(0, Point(1, 1));
//	pts.insert(1, Point(2, 2));
//	pts.insert(2, Point(3, 3));
//	pts.insert(3, Point(4, 4));
//	pts.insert(4, Point(5, 5));
//	pts.insert(5, Point(6, 6));*/
//
//	ExtendedDoubleCircular<Point> pts;
//	pts.insert(0, Point(3, 2));
//	pts.insert(1, Point(2, 2));
//	pts.insert(2, Point(3, 1));
//	pts.insert(3, Point(5, 6));
//	pts.insert(4, Point(2, 7));
//	pts.insert(5, Point(3, 8));
//	pts.insert(6, Point(6, 2));
//	pts.insert(7, Point(7, 7));
//	pts.insert(0, Point(3824, -1234));
//	pts.insert(0, Point(-5678, -3213));
//	ExtendedDoubleCircular<Point> endpoints;
//	Point pole(0, 0);
//
//	//cout << pointsInSameLine(pts, endpoints, pole) << endl;
//	//cout << pole << endl;
//
//	//Point p4(3, 3);
//	////double tangent = calTangent(pole, p4);
//	////cout << tangent << endl;
//	////cout << calPoler(pole, p4, tangent) << endl;
//
//	//SortPoints(pts);
//	//for (Point pt : pts) {
//	//	cout << pt << endl;
//	//}
//
//	//cout << lengthOfTwoPoints(p1, p3) << endl;
//	//cout << angleOfThreePoints(p2, p1, p3) << endl;;
//	//cout << angleOfThreePoints(p4, p2, p1) << endl;;
//	//cout << angleOfThreePointsCounterClockwise(p1, p2, p3) << endl;
//
//	ExtendedDoubleCircular<Point> convexHull;
//	getConvexHull(pts, convexHull);
//
//	for (Point pt : convexHull) {
//		cout << pt << endl;
//	}
//}

////Exercise 67 in Double
//int main() {
//	Point p1(3, 2);
//	Point p2(2, 2);
//	Point p3(3, 1);
//	//ExtendedDouble<Point> pts({ Point(-5678, -3213), Point(3824, -1234), p1, p2, p3, Point(5,6), Point(2,7) , Point(3,8), Point(6,2), Point(7,7) });
//	//ExtendedDouble<Point> pts({ Point(1,1), Point(2,2), Point(3,3) , Point(4,4), Point(5,5), Point(6,6) });
//	//ExtendedDouble<Point> pts({ Point(1,1) });//VC bug??
//	//ExtendedDouble<Point> pts;
//	//pts.insert(0, Point(1, 1));
//	//pts.insert(1, Point(2, 2));
//	//pts.insert(2, Point(3, 3));
//	//pts.insert(3, Point(4, 4));
//	//pts.insert(4, Point(5, 5));
//	//pts.insert(5, Point(6, 6));
//
//	ExtendedDouble<Point> pts;
//	pts.insert(0, Point(3, 2));
//	pts.insert(1, Point(2, 2));
//	pts.insert(2, Point(3, 1));
//	pts.insert(3, Point(5, 6));
//	pts.insert(4, Point(2, 7));
//	pts.insert(5, Point(3, 8));
//	pts.insert(6, Point(6, 2));
//	pts.insert(7, Point(7, 7));
//	pts.insert(0, Point(3824, -1234));
//	pts.insert(0, Point(-5678, -3213));
//	//ExtendedDouble<Point> endpoints;
//	//Point pole(0, 0);
//
//	//cout << pointsInSameLine(pts, endpoints, pole) << endl;
//	//cout << pole << endl;
//
//	//Point p4(3, 3);
//	////double tangent = calTangent(pole, p4);
//	////cout << tangent << endl;
//	////cout << calPoler(pole, p4, tangent) << endl;
//
//	//SortPoints(pts);
//	//for (Point pt : pts) {
//	//	cout << pt << endl;
//	//}
//
//	//cout << lengthOfTwoPoints(p1, p3) << endl;
//	//cout << angleOfThreePoints(p2, p1, p3) << endl;;
//	//cout << angleOfThreePoints(p4, p2, p1) << endl;;
//	//cout << angleOfThreePointsCounterClockwise(p1, p2, p3) << endl;
//
//	ExtendedDouble<Point> convexHull;
//	getConvexHull(pts, convexHull);
//
//	for (Point pt : convexHull) {
//		cout << pt << endl;
//	}
//}

////Exercise 67 in vector
//int main() {
//	Point p1(3,2);
//	Point p2(2, 2);
//	Point p3(3,1);
//	vector<Point> pts = {Point(-5678, -3213), Point(3824, -1234), p1, p2, p3, Point(5,6), Point(2,7) , Point(3,8), Point(6,2), Point(7,7) };
//	//vector<Point> pts = { Point(1,1), Point(2,2), Point(3,3) , Point(4,4), Point(5,5), Point(6,6) };
//	vector<Point> endpoints;
//	Point pole(0,0);
//
//	//cout << pointsInSameLine(pts, endpoints, pole) << endl;
//	//cout << pole << endl;
//
//	//Point p4(3, 3);
//	////double tangent = calTangent(pole, p4);
//	////cout << tangent << endl;
//	////cout << calPoler(pole, p4, tangent) << endl;
//
//	//SortPoints(pts);
//	//for (Point pt : pts) {
//	//	cout << pt << endl;
//	//}
//
//	//cout << lengthOfTwoPoints(p1, p3) << endl;
//	//cout << angleOfThreePoints(p2, p1, p3) << endl;;
//	//cout << angleOfThreePoints(p4, p2, p1) << endl;;
//	//cout << angleOfThreePointsCounterClockwise(p1, p2, p3) << endl;
//
//	vector<Point> convexHull;
//	getConvexHull(pts, convexHull);
//
//	for (Point pt : convexHull) {
//		cout << pt << endl;
//	}
//}

////Exercise 63-66
//int main(){
//	cout << "Exercise 63" << endl;
//	Chain<StudentRecord>& chain= constructStudentRecordChain("D:\\study\\C++\\DS\\DS6\\studentrecord.txt");
//	cout << chain;
//	//chain.binSort(10);
//	chain.binSort(10, getStudentScore);
//	cout << chain;
//	cout << "Exercise 64" << endl;
//	Chain<StudentRecord>& chain2 = constructStudentRecordChain("D:\\study\\C++\\DS\\DS6\\studentrecord2.txt");
//	cout << chain2;
//	chain2.radixSort(10, 3);
//	//chain2.radixSort2(10, 3);
//	cout << chain2;
//
//	cout << "Exercise 66" << endl;
//	ExtendedChain<Card> chain3 = constructCards();
//	cout << chain3;
//
//	chain3.binSort(13, getFace);
//	chain3.binSort(4, getSuit);
//	chain3.binSort(10, getDeck);
//
//	cout << chain3;
//}


// #include <functional>
//using namespace std::placeholders;
//using namespace std;
// struct integer {
//     int i;
//      integer(int i) :i(i) {}
//      void incr_by(int j) { i += j; }
//
//	  void mem_samble() {
//		  auto f0 = bind(&integer::incr_by, _1, _2);
//		  f0(this, 2);     //x.incr_by(2)
//		  cout << this->i << endl;
//	  }
//};
// void main() {
//	 integer x(0);    //x.i=0;
//	 x.mem_samble();
// }

////Exercise 55-61
//int main() {
//	cout << "Exercise 55" << endl;
//
//	ExtendedDoubleCircular<int> c;
//	c.insert(0, 2);
//	cout << c;
//	c.insert(0, 3);
//	cout << c;
//	c.insert(1, 1);
//	cout << c;
//	c.insert(2, 4);
//	cout << c;
//
//	c.insert(1, 5);
//	c.insert(4, 9);
//	cout << c;
//
//	c.erase(2);
//	cout << c;
//	c.erase(4);
//	cout << c;
//	c.erase(2);
//	cout << c;
//	c.erase(1);
//	cout << c;
//	c.erase(1);
//	cout << c;
//	c.erase(0);
//	cout << c;
//
//	c.insert(0, 5);
//	cout << c;
//	c.insert(0, 6);
//	cout << c;
//	c.insert(2, 4);
//	cout << c;
//	c.insert(2, 7);
//	cout << c;
//	c.insert(0, 2);
//	cout << c;
//	c.insert(4, 7);
//	cout << c;
//	cout << c.size() << endl;
//	int x;
//	x = c.get(2);
//	cout << x << endl;
//
//	cout << c.indexOf(x) << endl;
//
//	//c.push_back(3);
//	//cout << c;
//	//c.clear();
//	//cout << c;
//	cout << "Exercise 56,57,58" << endl;
//
//	c.reverse();
//	cout << c;
//
//	ExtendedDoubleCircular<int> c2;
//	reverse(c, c2);
//	cout << c2;
//
//	//c.concat(c2);
//	//cout << c2;
//	//cout << c;
//
//	c2.push_back(8);
//	cout << c2;
//
//	ExtendedDoubleCircular<int> c3;
//	meld(c, c2, c3);
//	cout << c3;
//
//	ExtendedDoubleCircular<int> c33;
//	c33.meld(c, c2);
//	cout << c;
//	cout << c2;
//	cout << c33;
//
//	cout << "Exercise 59,60,61" << endl;
//	ExtendedDoubleCircular<int> c4, c5, c6;
//	c4.push_back(1);
//	c4.push_back(3);
//	c4.push_back(3);
//	c4.push_back(5);
//	c4.push_back(8);
//	c4.push_back(9);
//	cout << c4;
//
//	c5.push_back(3);
//	c5.push_back(4);
//	c5.push_back(4);
//	c5.push_back(5);
//	c5.push_back(6);
//	c5.push_back(7);
//	cout << c5;
//
//	merge(c4, c5, c6);
//	cout << c6;
//
//	ExtendedDoubleCircular<int> c7;
//	c7.merge(c4, c5);
//	cout << c4;
//	cout << c5;
//	cout << c7;
//
//	ExtendedDoubleCircular<int> c8, c9;
//	split(c3, c8, c9);
//	cout << c3;
//	cout << c8;
//	cout << c9;
//
//	ExtendedDoubleCircular<int> c10, c11;
//	c3.split(c10, c11);
//	cout << c3;
//	cout << c10;
//	cout << c11;
//
//	cout << "iterator testing." << endl;
//
//	ExtendedDoubleCircular<int>::iterator iter = c11.begin();
//	while(iter != c11.end())
//	{
//		cout << *iter++ << " ";
//	}
//	cout << endl;
//	iter = c11.end();
//	while(iter != c11.begin())
//	{
//		cout << *--iter << " ";
//	}
//	cout << endl;
//}
////Exercise 49-54
//int main() {
//	cout << "Exercise 49" << endl;
//
//	DoubleCircular<int> c;
//	c.insert(0, 2);
//	cout << c;
//	c.insert(0, 3);
//	cout << c;
//	c.insert(1, 1);
//	cout << c;
//	c.insert(2, 4);
//	cout << c;
//
//	c.insert(1, 5);
//	c.insert(4, 9);
//	cout << c;
//
//	c.erase(2);
//	cout << c;
//	c.erase(4);
//	cout << c;
//	c.erase(2);
//	cout << c;
//	c.erase(1);
//	cout << c;
//	c.erase(1);
//	cout << c;
//	c.erase(0);
//	cout << c;
//
//	c.insert(0, 5);
//	cout << c;
//	c.insert(0, 6);
//	cout << c;
//	c.insert(2, 4);
//	cout << c;
//	c.insert(2, 7);
//	cout << c;
//	c.insert(0, 2);
//	cout << c;
//	c.insert(4, 7);
//	cout << c;
//	cout << c.size() << endl;
//	int x;
//	x = c.get(2);
//	cout << x << endl;
//
//	cout << c.indexOf(x) << endl;
//
//	//c.push_back(3);
//	//cout << c;
//	//c.clear();
//	//cout << c;
//	cout << "Exercise 50,51,52" << endl;
//
//	c.reverse();
//	cout << c;
//
//	DoubleCircular<int> c2;
//	reverse(c, c2);
//	cout << c2;
//
//	//c.concat(c2);
//	//cout << c2;
//	//cout << c;
//
//	c2.push_back(8);
//	cout << c2;
//
//	DoubleCircular<int> c3;
//	meld(c, c2, c3);
//	cout << c3;
//
//	DoubleCircular<int> c33;
//	c33.meld(c, c2);
//	cout << c;
//	cout << c2;
//	cout << c33;
//
//	cout << "Exercise 53,54" << endl;
//	DoubleCircular<int> c4, c5, c6;
//	c4.push_back(1);
//	c4.push_back(3);
//	c4.push_back(3);
//	c4.push_back(5);
//	c4.push_back(8);
//	c4.push_back(9);
//	cout << c4;
//
//	c5.push_back(3);
//	c5.push_back(4);
//	c5.push_back(4);
//	c5.push_back(5);
//	c5.push_back(6);
//	c5.push_back(7);
//	cout << c5;
//
//	merge(c4, c5, c6);
//	cout << c6;
//
//	DoubleCircular<int> c7;
//	c7.merge(c4, c5);
//	cout << c4;
//	cout << c5;
//	cout << c7;
//
//	DoubleCircular<int> c8, c9;
//	split(c3, c8, c9);
//	cout << c3;
//	cout << c8;
//	cout << c9;
//
//	DoubleCircular<int> c10, c11;
//	c3.split(c10, c11);
//	cout << c3;
//	cout << c10;
//	cout << c11;
//
//}

////Exercise 43-48
//int main() {
//	cout << "Exercise 43" << endl;
//
//	Double<int> c;
//	c.insert(0, 2);
//	cout << c;
//	c.insert(0, 3);
//	cout << c;
//	c.insert(1, 1);
//	cout << c;
//	c.insert(2, 4);
//	cout << c;
//
//	c.insert(1, 5);
//	c.insert(4, 9);
//	cout << c;
//
//	c.erase(2);
//	cout << c;
//	c.erase(4);
//	cout << c;
//	c.erase(2);
//	cout << c;
//	c.erase(1);
//	cout << c;
//	c.erase(1);
//	cout << c;
//	c.erase(0);
//	cout << c;
//
//	c.insert(0, 5);
//	cout << c;
//	c.insert(0, 6);
//	cout << c;
//	c.insert(2, 4);
//	cout << c;
//	c.insert(2, 7);
//	cout << c;
//	c.insert(0, 2);
//	cout << c;
//	c.insert(4, 7);
//	cout << c;
//	cout << c.size() << endl;
//	int x;
//	x = c.get(2);
//	cout << x << endl;
//
//	cout << c.indexOf(x) << endl;
//
//	//c.push_back(3);
//	//cout << c;
//	//c.clear();
//	//cout << c;
//	cout << "Exercise 44,45,46" << endl;
//
//	c.reverse();
//	cout << c;
//
//	Double<int> c2;
//	reverse(c, c2);
//	cout << c2;
//
//	//c.concat(c2);
//	//cout << c2;
//	//cout << c;
//
//	c2.push_back(8);
//	cout << c2;
//
//	Double<int> c3;
//	meld(c, c2, c3);
//	cout << c3;
//
//	Double<int> c33;
//	c33.meld(c, c2);
//	cout << c33;
//
//	cout << "Exercise 47,48" << endl;
//	Double<int> c4, c5, c6;
//	c4.push_back(1);
//	c4.push_back(3);
//	c4.push_back(3);
//	c4.push_back(5);
//	c4.push_back(8);
//	c4.push_back(9);
//	cout << c4;
//
//	c5.push_back(3);
//	c5.push_back(4);
//	c5.push_back(4);
//	c5.push_back(5);
//	c5.push_back(6);
//	c5.push_back(7);
//	cout << c5;
//
//	merge(c4, c5, c6);
//	cout << c6;
//
//	Double<int> c7;
//	c7.merge(c4, c5);
//	cout << c4;
//	cout << c5;
//	cout << c7;
//
//	Double<int> c8, c9;
//	split(c3, c8, c9);
//	cout << c3;
//	cout << c8;
//	cout << c9;
//
//	Double<int> c10, c11;
//	c3.split(c10, c11);
//	cout << c3;
//	cout << c10;
//	cout << c11;
//
//}

////Exercise 29-37
//int main() {
//	cout << "Exercise 29,30,31" << endl;
//
//	Circular<int> c;
//	c.insert(0, 2);
//	cout << c;
//	c.insert(0, 3);
//	cout << c;
//	c.insert(1, 1);
//	cout << c;
//	c.insert(2, 4);
//	cout << c;
//
//	c.insert(1, 5);
//	c.insert(4, 9);
//	cout << c;
//
//	c.erase(2);
//	cout << c;
//	c.erase(4);
//	cout << c;
//	c.erase(2);
//	cout << c;
//	c.erase(1);
//	cout << c;
//	c.erase(1);
//	cout << c;
//	c.erase(0);
//	cout << c;
//
//	c.insert(0, 5);
//	cout << c;
//	c.insert(0, 6);
//	cout << c;
//	c.insert(2, 4);
//	cout << c;
//	c.insert(2, 7);
//	cout << c;
//	c.insert(0, 2);
//	cout << c;
//	c.insert(4, 7);
//	cout << c;
//	cout << c.size() << endl;
//	int x;
//	x = c.get(2);
//	cout << x << endl;
//
//	cout << c.indexOf(x) << endl;
//
//	//c.push_back(3);
//	//cout << c;
//	//c.clear();
//	//cout << c;
//
//	c.reverse();
//	cout << c;
//
//	Circular<int> c2;
//	reverse(c, c2);
//	cout << c2;
//
//	cout << "Exercise 32,33,34" << endl;
//	cout << c;
//	c2.push_back(8);
//	cout << c2;
//
//	Circular<int> c3;
//	meld(c, c2, c3);
//	cout << c3;
//
//	Circular<int> c4, c5, c6;
//	c4.push_back(1);
//	c4.push_back(3);
//	c4.push_back(3);
//	c4.push_back(5);
//	c4.push_back(8);
//	c4.push_back(9);
//	cout << c4;
//
//	c5.push_back(3);
//	c5.push_back(4);
//	c5.push_back(4);
//	c5.push_back(5);
//	c5.push_back(6);
//	c5.push_back(7);
//	cout << c5;
//
//	merge(c4, c5, c6);
//	cout << c6;
//
//	Circular<int> c7;
//	c7.merge(c4, c5);
//	cout << c4;
//	cout << c5;
//	cout << c7;
//	cout << "Exercise 35,36,37" << endl;
//
//	Circular<int> c8, c9;
//	split(c3, c8, c9);
//	cout << c3;
//	cout << c8;
//	cout << c9;
//
//	Circular<int> c10, c11;
//	c3.split(c10, c11);
//	cout << c3;
//	cout << c10;
//	cout << c11;
//
//	ChainNode<int>* y = c11.getNode(5);
//	c11.removeNode(y);
//	cout << c11;
//	y = c11.getNode(0);
//	c11.removeNode(y);
//	cout << c11;
//	y = c11.getNode(2);
//	c11.removeNode(y);
//	cout << c11;
//}
////Exercise 24,25
//int main(){
//	cout << "Exercise 24, 25" << endl;
//
//	MoveLeftAndRightOnChain<int> mc;
//	mc.insert(0, 2);
//	cout << mc;
//	mc.insert(0, 3);
//	cout << mc;
//	mc.insert(1, 1);
//	cout << mc;
//	mc.insert(2, 4);
//	cout << mc;
//
//	mc.insert(1, 5);
//	mc.insert(4, 9);
//	cout << mc;
//	mc.moveToNext();
//	mc.moveToNext();
//	mc.moveToNext();
//	cout << mc.current() << endl;
//	mc.erase(2);
//	cout << mc;
//	mc.moveToPrevious();
//	//cout << mc.current() << endl;
//	//mc.reset();
//	cout << mc.current() << endl;
//	mc.erase(4);
//	cout << mc;
//	mc.erase(2);
//	cout << mc;
//	mc.erase(1);
//	cout << mc;
//	mc.erase(1);
//	cout << mc;
//	mc.erase(0);
//	cout << mc;
//
//	mc.insert(0, 5);
//	cout << mc;
//	mc.insert(0, 6);
//	cout << mc;
//	mc.insert(2, 4);
//	cout << mc;
//	mc.insert(2, 7);
//	cout << mc;
//	mc.insert(0, 2);
//	cout << mc;
//	mc.insert(4, 7);
//	cout << mc;
//	cout << mc.atFront() << endl;
//	cout << mc.atEnd() << endl;
//	mc.moveToPrevious();
//	mc.moveToNext();
//	cout << mc;
//	cout << mc.atFront() << endl;
//	cout << mc.atEnd() << endl;
//	cout << mc.size() << endl;
//	int x;
//	x=mc.get(2);
//	cout << x << endl;
//
//	cout << mc.indexOf(x) << endl;
//}
////Exercise 2-23, 26
//int main(){
//	Chain<int> c;
//
//	c.insert(0, 2);
//	cout << c;
//	c.insert(0, 3);
//	cout << c;
//	c.insert(1, 1);
//	cout << c;
//	c.insert(2, 4);
//	cout << c;
//
//	c.insert(1, 4);
//	c.insert(4, 9);
//	cout << c;
//
//	c.erase(2);
//	cout << c;
//	c.erase(4);
//	cout << c;
//	c.erase(2);
//	cout << c;
//	c.erase(1);
//	cout << c;
//	c.erase(1);
//	cout << c;
//
//	c.insert(0, 5);
//	cout << c;
//	c.insert(0, 6);
//	cout << c;
//	c.insert(2, 4);
//	cout << c;
//	c.insert(2, 7);
//	cout << c;
//	c.insert(0, 2);
//	cout << c;
//	c.insert(4, 7);
//	cout << c;
//
//	auto b = c.begin();
//	while(b!=c.end()){
//		cout << *b++ << " ";
//	}
//	cout << endl;
//
//	cout << c.size() << endl;
//	int x;
//	x=c.get(2);
//	cout << x << endl;
//
//	cout << c.indexOf(x) << endl;
//	
//	cout << "Exercise 2,3,4" << endl;
//	Chain<int> c2(c);
//	cout << c2;
//	c2.setSize(6);
//	cout << c2;
//	c2.set(4, 8);
//	cout << c2;
//	c2.set(0, 3);
//	cout << c2;
//	Chain<int> c3(c);
//	c3.removeRange(0, 1);
//	cout << c3;
//	c3.removeRange(2, 3);
//	cout << c3;
//	cout << "Exercise 5,6,7" << endl;
//
//	cout << c.lastIndexOf(4) << endl;
//	cout << c.lastIndexOf(0) << endl;
//	cout << c.lastIndexOf(3) << endl;
//	cout << c.lastIndexOf(7) << endl;
//
//	Chain<int> c4(c);
//	c4[4] = 9;
//	ChainNode<int>& t = c4[3];
//	cout << t.element << endl;
//	cout << c4;
//
//	Chain<int> c5(c);
//	cout << (c == c4) << endl;
//	cout << (c == c5) << endl;
//
//	cout << "Exercise 8,9,10" << endl;
//	cout << (c != c4) << endl;
//	cout << (c != c5) << endl;
//
//	cout << (c < c4) << endl;
//	cout << (c < c5) << endl;
//	cout << (c4 < c) << endl;
//	cout << (c5 < c) << endl;
//	cout << (c < c2) << endl;
//	cout << (c2 < c) << endl;
//	cout << c;
//	cout << c2;
//	c.swap(c2);
//	cout << c;
//	cout << c2;
//
//	cout << "Exercise 11,12,13" << endl;
//	ArrayList<int> l;
//	l.insert(0,1);
//	l.insert(1,4);
//	l.insert(2,2);
//	l.insert(3,8);
//	l.insert(4,5);
//	l.insert(5,7);
//	cout << l;
//	Chain<int> c6;
//	listToChain<int>(l,c6);
//	cout << c6;
//	l.clear();
//	cout << l;
//	chainToList(c6,l);
//	cout << l;
//	l.clear();
//	cout << l;
//	chainToList2(c6,l);
//	cout << l;
//	Chain<int> c7;
//	c7.fromList(l);
//	cout << c7;
//	l.clear();
//	cout << l;
//	c7.toList(l);
//	cout << l;
//
//	cout << "Exercise 14,15,16" << endl;
//	c7.leftShift(0);
//	cout << c7;
//	c7.leftShift(2);
//	cout << c7;
//	c7.leftShift(4);
//	cout << c7;
//
//	c.reverse();
//	cout << c;
//	Chain<int> c8;
//	reverse(c6,c8);
//	cout << c8;
//	//clock_t start, finish;
//	//start = clock();
//	//int n = 10000000;
//	//for(int i=0;i<n;i++){
//	//	c.erase(2);
//	//	c.insert(1, 2);
//	//}
//	//finish = clock();
//	//cout << n << " " << start<< " "<< finish  << " " << (double)(finish - start) / CLK_TCK << endl;
//
//	cout << "Exercise 17, 18, 19" << endl;
//	ExtendedChain<int> ec;
//	cout << ec;
//	ec.push_back(1);
//	cout << ec;
//	ec.push_back(4);
//	cout << ec;
//	ec.push_back(2);
//	cout << ec;
//	ec.push_back(8);
//	cout << ec;
//	ec.push_back(5);
//	cout << ec;
//	ec.push_back(7);
//	cout << ec;
//
//	ExtendedChain<int> ec2(ec);
//	cout << ec2;
//	ec2.clear();
//	cout << ec2;
//	ExtendedChain<int> ec3(c8);
//	cout << ec3;
//	ExtendedChain<int> ec4;
//	meld(ec, ec3, ec4);
//	cout << ec4;
//	ExtendedChain<int> ec5(c2);
//	cout << ec5;
//	ExtendedChain<int> ec6;
//	meld(ec, ec5, ec6);
//	cout << ec6;
//
//	Chain<int> c9(c), c10(c2), c11;
//	cout << c9;
//	cout << c10;
//	c11.meld(c9,c10);
//	cout << c9;
//	cout << c10;
//	cout << c11;
//
//	ec.insertionSort();
//	cout << ec;
//	ec5.bubbleSort();
//	cout << ec5;
//	ExtendedChain<int> ec7;
//	merge(ec,ec5,ec7);
//	cout << ec7;
//	cout << "Exercise 20, 21, 22" << endl;
//	c.selectionSort();
//	cout << c;
//	c2.rankSort();
//	cout << c2;
//	Chain<int> c12;
//	c12.merge(c,c2);
//	cout << c;
//	cout << c2;
//	cout << c12;
//
//	ExtendedChain<int> ec8, ec9;
//	split(ec7, ec8, ec9);
//	cout << ec8;
//	cout << ec9;
//
//	Chain<int> c13, c14;
//	c12.split(c13, c14);
//	cout << c12;
//	cout << c13;
//	cout << c14;
//	cout << "Exercise 23" << endl;
//
//	ec9.circularShift(2);
//	cout << ec9;
//	ec9.circularShift(0);
//	cout << ec9;
//	ec9.circularShift(100);
//	cout << ec9;
//
//}
