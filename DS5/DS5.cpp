#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "exceptions.h"
//#include "arraylist.h"
//#include "circularArrayList.h"
//#include "vectorlist.h"
//#include "arraylist2.h"
#include "arraylistNoSTL.h"
//数据结构算法与应用-C++语言描述 第二版  第五章
using namespace std;
//Exercise 44
int main(){
	ArrayListNoSTL<int> l;

	l.insert(0, 2);
	cout << l;
	l.insert(0, 3);
	cout << l;
	l.insert(1, 1);
	cout << l;
	l.insert(2, 4);
	cout << l;

	l.insert(1, 4);
	l.insert(4, 9);
	cout << l;

	l.erase(2);
	cout << l;
	l.erase(3);
	cout << l;
	l.erase(2);
	cout << l;
	l.erase(0);
	cout << l;
	l.erase(0);
	cout << l;

	l.insert(0, 5);
	cout << l;
	l.insert(0, 6);
	cout << l;
	l.insert(2, 4);
	cout << l;
	l.insert(2, 7);
	cout << l;
	l.insert(0, 2);
	cout << l;
	l.insert(4, 8);
	cout << l;

	cout << l.size() << endl;
	cout << l.get(2) << endl;
	cout << l.indexOf(5) << endl;
}
//Exercise 41-43
//int main()
//{
//	ArrayList<int> l(20, 3);
//
//	l.insert(1, 0, 1);
//	l.insert(2, 0, 2);
//	l.insert(3, 0, 3);
//	cout << l;
//	l.insert(1, 1, 4);
//	l.insert(2, 0, 5);
//	l.insert(3, 1, 6);
//	cout << l;
//	l.insert(1, 0, 7);
//	l.insert(2, 1, 8);
//	l.insert(3, 2, 9);
//	cout << l;
//
//	l.erase(1, 1);
//	l.erase(2, 2);
//	l.erase(3, 3);
//	l.erase(1, 1);
//	cout << l;
//	l.erase(1, 1);
//	cout << l;
//
//	l.insert(1, 0, 1);
//	l.insert(2, 0, 2);
//	l.insert(3, 0, 3);
//	cout << l;
//	l.insert(1, 1, 1);
//	l.insert(2, 0, 2);
//	l.insert(3, 1, 3);
//	cout << l;
//	l.insert(1, 0, 1);
//	l.insert(2, 1, 2);
//	l.insert(3, 2, 3);
//	cout << l;
//	l.insert(3, 0, 3);
//	l.insert(3, 0, 3); 
//	l.insert(3, 0, 3);
//	l.insert(3, 0, 3);
//	l.insert(3, 0, 3);
//	cout << l;
//	l.insert(2, 1, 2);
//	l.insert(2, 1, 2);
//	l.insert(2, 1, 2);
//	l.insert(2, 1, 2);
//	l.insert(2, 1, 2);
//	l.insert(2, 1, 2);
//	l.insert(2, 1, 2);
//	l.insert(2, 1, 2);
//	cout << l;
//}
//Exercise 37-40
//int main(){
//	VectorList<int> l;
//
//	l.insert(0, 2);
//	cout << l;
//	l.insert(0, 3);
//	cout << l;
//	l.insert(1, 1);
//	cout << l;
//	l.insert(1, 4);
//	cout << l;
//	l.insert(2, 5);
//	cout << l;
//	l.insert(1, 9);
//	cout << l;
//
//	l.erase(1);
//	cout << l;
//	l.erase(3);
//	cout << l;
//	l.erase(2);
//	cout << l;
//	l.erase(0);
//	cout << l;
//	l.erase(1);
//	cout << l;
////	l.erase(0);
////	cout << l;
//
//	l.insert(0, 5);
//	cout << l;
//	l.insert(0, 6);
//	cout << l;
//	l.insert(2, 4);
//	cout << l;
//	l.insert(2, 7);
//	cout << l;
//	l.insert(0, 2);
//	cout << l;
//	l.insert(4, 8);
//	cout << l;
//
//	cout << l.size() << endl;
//	cout << l.get(2) << endl;
//	cout << l.indexOf(5) << endl;
//
//	VectorList<int> l2(l);
//
//	cout << l2;
//
//	cout << "Excecise 37,38,39,40" << endl;
//	cout << l2;
//	//cout << l2.half();
//	l2.insert(6,3);
//	VectorList<int> m;
//	cout << l;
//	cout << l2;
//	m.meld(l,l2);
//	cout << m;
//
//	VectorList<int> a;
//	a.insert(0, 2);
//	a.insert(1, 2);
//	a.insert(0, 1);
//	a.insert(3, 4);
//	cout << a;
//
//	VectorList<int> b;
//	b.insert(0, 5);
//	b.insert(1, 6);
//	b.insert(0, 4);
//	b.insert(3, 7);
//	b.insert(0, 2);
//	b.insert(5, 8);
//	b.insert(6, 9);
//	cout << b;
//
//
//	VectorList<int> c;
//	c.merge(a,b);
//	cout << c;
//
//	VectorList<int> c1, c2;
//	l.split(c1,c2);
//	cout << c1;
//	cout << c2;
//}

//Exercise 31-36
//int main(){
//	CircularArrayList<int> l;
//
//	l.insert(0, 2);
//	cout << l;
//	l.insert(0, 3);
//	cout << l;
//	l.insert(1, 1);
//	cout << l;
//	l.insert(1, 4);
//	cout << l;
//	l.insert(2, 5);
//	cout << l;
//	l.insert(1, 9);
//	cout << l;
//
//	l.erase(1);
//	cout << l;
//	l.erase(3);
//	cout << l;
//	l.erase(2);
//	cout << l;
//	l.erase(0);
//	cout << l;
//	l.erase(1);
//	cout << l;
////	l.erase(0);
////	cout << l;
//
//	l.insert(0, 5);
//	cout << l;
//	l.insert(0, 6);
//	cout << l;
//	l.insert(2, 4);
//	cout << l;
//	l.insert(2, 7);
//	cout << l;
//	l.insert(0, 2);
//	cout << l;
//	l.insert(4, 8);
//	cout << l;
//
//	cout << l.size() << endl;
//	cout << l.get(2) << endl;
//	cout << l.indexOf(5) << endl;
//
//	cout << "iterator testing." << endl;
//
//	CircularArrayList<int>::iterator iter = l.begin();
//	while(iter != l.end())
//	{
//		cout << *iter++ << " ";
//	}
//	cout << endl;
//	iter = l.end();
//	while(iter != l.begin())
//	{
//		cout << *--iter << " ";
//	}
//	cout << endl;
//	CircularArrayList<int> l2(l);
//
//	cout << l2;
//
//
//	//sort<CircularArrayList<int>::iterator>(l2.begin(), l2.end());
//	//cout << l2;
//
//	cout << "Excecise 33,34,35,36" << endl;
//	cout << l2;
//	cout << l2.reverse();
//	l2.insert(6,3);
//	CircularArrayList<int> m;
//	cout << l;
//	cout << l2;
//	m.meld(l,l2);
//	cout << m;
//
//	CircularArrayList<int> a;
//	a.insert(0, 2);
//	a.insert(1, 2);
//	a.insert(0, 1);
//	a.insert(3, 4);
//	cout << a;
//
//	CircularArrayList<int> b;
//	b.insert(0, 5);
//	b.insert(1, 6);
//	b.insert(0, 4);
//	b.insert(3, 7);
//	b.insert(0, 2);
//	b.insert(5, 8);
//	b.insert(6, 9);
//	cout << b;
//
//
//	CircularArrayList<int> c;
//	c.merge(a,b);
//	cout << c;
//
//	CircularArrayList<int> c1, c2;
//	l.split(c1,c2);
//	cout << c1;
//	cout << c2;
//}
//Exercise 5-30
//int main(){
//	//IllegalIndex i("test");
//	//i.outputMessage();
//
//	ArrayList<int> l;
//
//
//	l.insert(0, 2);
//	cout << l;
//	l.insert(0, 3);
//	cout << l;
//	l.insert(1, 1);
//	cout << l;
//	l.insert(2, 4);
//	cout << l;
//
//	l.insert(1, 4);
//	//l.insert(4, 9);
//	cout << l;
//
//	l.erase(2);
//	cout << l;
//	l.erase(3);
//	cout << l;
//	l.erase(2);
//	cout << l;
//	l.erase(0);
//	cout << l;
//	l.erase(0);
//	cout << l;
//	l.trimToSize();
//	cout << l;
//
//	l.insert(0, 5);
//	cout << l;
//	l.insert(0, 6);
//	cout << l;
//	l.insert(2, 4);
//	cout << l;
//	l.insert(2, 7);
//	cout << l;
//	l.insert(0, 2);
//	cout << l;
//	l.insert(4, 8);
//	cout << l;
//	//l.setSize(3);
//	//cout << l;
//
//	cout << l.size() << endl;
//	cout << l.get(2) << endl;
//	cout << l.indexOf(5) << endl;
//
//	cout << "iterator testing." << endl;
//
//	ArrayList<int>::iterator iter = l.begin();
//	while(iter != l.end())
//	{
//		cout << *iter++ << " ";
//	}
//	cout << endl;
//
//	cout << "operator testing." << endl;
//	for(int i=0;i<l.size();i++){
//		cout << l[i] << " ";
//	}
//	cout << endl;
//
//	ArrayList<int> l2(l);
//	//l2.erase(5);
//	l2.insert(6,5);
//	cout << l2;
//	cout << (l == l2) << endl;
//	cout << (l != l2) << endl;
//	cout << (l < l2) << endl;
//
//	cout << "Excecise 11,12" << endl;
//
//	l.push_back(7);
//	cout << l;
//	int x;
//	l.pop_back(x);
//	cout << x << endl;
//	cout << l;
//
//	cout << "Excecise 13,14,15" << endl;
//	l.swapList(l2);
//	cout << l;
//	cout << l2;
//
//	l.reserve(20);
//	cout << l;
//
//	x = l.set(3,3);
//	cout << x << endl;
//	cout << l;
//
//	cout << "Excecise 16,17,18" << endl;
//	//l.clear();
//	l.removeRange(3, 2);
//	cout << l;
//
//	cout << l.lastIndexOf(5) << endl;
//
//	cout << "Excecise 22,23,24" << endl;
//	cout << l2;
//	cout << l2.reverse();
//	reverse(l2);
//	cout << l2;
//
//	l2.leftShift(0);
//	cout << l2;
//
//	l2.circularShift(2);
//	cout << l2;
//
//	cout << "Excecise 25,26,27" << endl;
//	l2.half();
//	cout << l2;
//	half(l2);
//	cout << l2;
//
//	//auto a = l2.begin();
//
//	//sort<ArrayList<int>::iterator>(l2.begin(), l2.end());
//	//cout << l2;
//
//	//vector<int> v;
//	//v.push_back(1);v.push_back(4);v.push_back(2);v.push_back(8);v.push_back(5);v.push_back(7);
//	//vector<int>::iterator b = v.begin(), e = v.end();
//
//	//sort(b, e);
//	//for(int i: v)
//	//	cout << i << " ";
//	//cout << endl;
//
//	cout << "Excecise 28,29,30" << endl;
//	ArrayList<int> m;
//	cout << l;
//	cout << l2;
//	m.meld(l,l2);
//	cout << m;
//
//	ArrayList<int> a;
//	a.insert(0, 2);
//	a.insert(1, 2);
//	a.insert(0, 1);
//	a.insert(3, 4);
//	cout << a;
//
//	ArrayList<int> b;
//	b.insert(0, 5);
//	b.insert(1, 6);
//	b.insert(0, 4);
//	b.insert(3, 7);
//	b.insert(0, 2);
//	b.insert(5, 8);
//	b.insert(6, 9);
//	cout << b;
//
//
//	ArrayList<int> c;
//	c.merge(a,b);
//	cout << c;
//
//	ArrayList<int> c1, c2;
//	c.split(c1,c2);
//	cout << c1;
//	cout << c2;
//}

//int main(){
//	int** a = new int*[2];
//	for(int i=0;i<2;i++){
//		a[i] = new int[3];
//	}
//
//	for(int i=0;i<2;i++)
//		for(int j=0;j<3;j++)
//			a[i][j] = i+j;
//
//	for(int i=0;i<2;i++){
//		for(int j=0;j<3;j++)
//			cout << a[i][j] << " ";
//		cout <<endl;
//	}
//
//	changeLength2D(a,2,3,3,4);
//	for(int i=0;i<3;i++){
//		for(int j=0;j<4;j++)
//			cout << a[i][j] << " ";
//		cout <<endl;
//	}
//}


