// DS3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <ctime>
#include "exceptions.h"
//#include "list.h"
//#include "Chain.h"
//#include "IndirectList.h"
//#include "SimChain2.h"
#include "XorChain.h"

using namespace std;

//SimSpace<int> SimNode<int>::S;
//SimSpace<int> SimChain<int>::S;
SimSpace<int> XorChain<int>::S;

//ChainNode<int>* ChainNode<int>::FreeNodes =nullptr;

int main(){
	//SimChain<int> c;
	XorChain<int> c;

	c.Insert(0, 2);
	cout << c;
	c.Insert(0, 3);
	cout << c;
	c.Insert(1, 1);
	cout << c;
	c.Insert(2, 4);
	cout << c;
	c.ROutput(cout);

	c.Insert(1, 4);
	//c.Insert(4, 9);
	cout << c;

	int x;
	c.Delete(2, x);
	cout << c;
	cout << x << endl;
	c.Delete(4, x);
	cout << c;
	c.Delete(2, x);
	cout << c;
	c.Delete(1, x);
	cout << c;
	c.Delete(1, x);
	cout << c;

	//SimChain<int> d;
	c.Insert(0, 5);
	cout << c;
	c.Insert(0, 6);
	cout << c;
	c.Insert(2, 4);
	cout << c;
	c.Insert(2, 7);
	cout << c;
	c.Insert(0, 2);
	cout << c;
	c.Insert(4, 7);
	cout << c;

	clock_t start, finish;
	start = clock();
	int n = 10000000;
	for(int i=0;i<n;i++){
		c.Delete(2, x);
		c.Insert(1, 2);
	}
	finish = clock();
	cout << n << " " << start<< " "<< finish  << " " << (double)(finish - start) / CLK_TCK << endl;

	//SimIterator<int> iter(c);
	//int * n = iter.Next();
	//while(n){
	//	cout << * n << " ";
	//	n = iter.Next();
	//}
	//cout << endl;

	//cout << c.Length() << endl;
	//int x;
	//c.Find(2, x);
	//cout << x << endl;

	//cout << c.Search(x) << endl;
	


	////c.InsertionSort();
	////c.SelectionSort();
	//c.BubbleSort();
	////c.RankSort();
	//cout << c;
	//cout << endl;

	//IndirectListIterator<int> iter(d);
	//int *np;
	//while((np = iter.Next())!=nullptr){
	//	cout << *np << " ";
	//}
	//int x = 6;
	//cout << d.BinarySearch(x) << endl;


}


//int main()
//{
//	//LinearList<int> l;
//
//	//l.Insert(0, 3);
//	//l.Insert(1, 1);
//	//l.Insert(2, 1);
//	////cout << l;
//	//l.Insert(3, 6);
//	//l.Insert(4, 5);
//	//l.Insert(5, 5);
//	////cout << l;
//
//
//	//Chain<int> d(l);
//	//cout << d;
//
//	//cout << d.FromList(l);
//
//	//cout << d.ToList();
//
//	//cout << d.ToList2();
//
//	//cout << d.Reverse();
//
//	//Chain<int> e;
//	//Reverse(d, e);
//	//cout << d;
//	//cout << e;
//
//	DoubleCircular<int> c;
//	//c.Append(5);
//	//c.Append(7);
//	c.Insert(0, 3);
//	cout << c;
//	c.Insert(0, 2);
//	cout << c;
//	c.Insert(2, 4);
//	cout << c;
//	//c.Append(6);
//	c.Insert(1, 2);
//	c.Insert(4, 9);
//	cout << c;
//
//	DoubleCircular<int> d;
//	d.Insert(0, 6);
//	//cout << d;
//	d.Insert(0, 5);
//	//cout << d;
//	d.Insert(2, 8);
//	//cout << d;
//	d.Insert(2, 7);
//	//cout << d;
//	d.Insert(0, 2);
//	//cout << d;
//	d.Insert(4, 7);
//	cout << d;
//
//	//int x;
//	//cout << d.ResetLeft() << endl;
//	//cout << d.Current(x) << endl;
//	//cout << x << endl;
//	//cout << d.Front() << endl;
//	//cout << d.End() << endl;
//	//cout << d.Previous() << endl;
//	//cout << d.ResetLeft() << endl;
//	//cout << d.Next() << endl;
//	//cout << d.Current(x) << endl;
//	//cout << x << endl;
//	//cout << d.ResetRight() << endl;
//	//cout << d.Front() << endl;
//	//cout << d.End() << endl;
//	//cout << d.Next() << endl;
//	//cout << d.ResetRight() << endl;
//	//cout << d.Previous() << endl;
//	//cout << d.Current(x) << endl;
//	//cout << x << endl;
//	//cout << d.Previous() << endl;
//	//cout << d.Previous() << endl;
//	//cout << d.Current(x) << endl;
//	//cout << x << endl;
//
//	//DoubleCircular<int> e;
//	////e.Alternate(c, d);
//	//e.Merge(c, d);
//	//cout << e;
//
//	//DoubleCircular<int> e, f;
//	//d.Split(e, f);
//	//cout << e;
//	//cout << f;
//
//	//d.Reverse();
//	//cout << d;
//
//	//cout << c.Length() << endl;
//	//c.Erase();
//	//cout << c.Length() << endl;
//
//	//int x;
//	//c.Find(2, x);
//	//cout << x << endl;
//
//	//cout << c.Search(x) << endl;
//
//	//int x;
//	//c.Delete(2, x);
//	//cout << c;
//	//cout << x << endl;
//	//c.Delete(3, x);
//	//cout << c;
//	//c.Delete(1, x);
//	//cout << c;
//	//c.Delete(1, x);
//	//cout << c;
//
//	//Chain<int> a, b;
//
//	////c.Split(a, b, c);
//	//c.Split(a, b);
//	//cout << a;
//	//cout << b;
//
//	//c.SelectionSort();
//	//c.InsertionSort();
//	//c.BubbleSort();
//	//c.RankSort();
//	//cout << c;
//	//d.BubbleSort();
//	//cout << d;
//
//	////Chain<int>& e = c.Merge(d);
//	//Chain<int> e;
//	//e.Merge(c, d);
//	//cout << e;
//
//	//Chain<int> &e = c.Alternate(d);
//	//cout << e;
//
//	//Chain<int> f;
//	//f.Alternate(c, d);
//	//cout << f;
//
//	//Chain<int> d(c);
//	//cout << d;
//
//	//cout << c;
//	//cout << "Length: " << c.Length() << endl;
//
//	//int x;
//	//c.Find(3, x);
//	//cout << "Find: " << x << endl;
//
//	//
//	//cout << "Search: " << c.Search(x) << endl;
//
//	//
//
//
//
//
//}
//
//


//For LinearList
//int main()
//{
//	LinearList<int> l(20, 3);
//
//	l.Insert(1, 0, 1);
//	l.Insert(2, 0, 2);
//	l.Insert(3, 0, 3);
//	cout << l;
//	l.Insert(1, 1, 4);
//	l.Insert(2, 0, 5);
//	l.Insert(3, 1, 6);
//	cout << l;
//	l.Insert(1, 0, 7);
//	l.Insert(2, 1, 8);
//	l.Insert(3, 2, 9);
//	cout << l;
//
//	int x;
//	l.Delete(1, 1, x);
//	l.Delete(2, 2, x);
//	l.Delete(3, 3, x);
//	l.Delete(1, 1, x);
//	cout << l;
//	l.Delete(1, 1, x);
//	cout << l;

//l.Insert(1, 0, 1);
//l.Insert(2, 0, 2);
//l.Insert(3, 0, 3);
//cout << l;
//l.Insert(1, 1, 1);
//l.Insert(2, 0, 2);
//l.Insert(3, 1, 3);
//cout << l;
//l.Insert(1, 0, 1);
//l.Insert(2, 1, 2);
//l.Insert(3, 2, 3);
//cout << l;
//l.Insert(3, 0, 3);
//l.Insert(3, 0, 3); 
//l.Insert(3, 0, 3);
//l.Insert(3, 0, 3);
//l.Insert(3, 0, 3);
//cout << l;
//l.Insert(2, 1, 2);
//l.Insert(2, 1, 2);
//l.Insert(2, 1, 2);
//l.Insert(2, 1, 2);
//l.Insert(2, 1, 2);
//l.Insert(2, 1, 2);
//l.Insert(2, 1, 2);
//l.Insert(2, 1, 2);
//cout << l;



//l.Insert(0, 1);
//cout << l;
//l.Insert(1, 2);
//cout << l;
//l.Insert(1, 3);
//cout << l;
//l.Insert(2, 4);
//cout << l;
//l.Insert(0, 8);
//cout << l;
//l.Insert(1, 2);
//cout << l;
//l.Insert(1, 5);
//cout << l;
//l.Insert(1, 7);
//cout << l;

//m.Insert(0, 8);
//cout << m;
//m.Insert(1, 4);
//cout << m;
//m.Insert(2, 2);
//cout << m;

//int x;
//l.Delete(0, x);
//cout << l;
//l.Delete(5, x);
//cout << l;
//l.Delete(2, x);
//cout << l;
//l.Delete(5, x);
//cout << l;

//LinearList<int> q, o;

//l.Split(q, o);
//cout << q;
//cout << o;

//LinearList<int> &n = l.Alternate(l, m);
//cout << n;
//delete &n;

//l.BubbleSort();
//cout << l;
//m.BubbleSort();
//cout << m;
//LinearList<int> &r = l.Merge(l, m);
//cout << r;
//delete& r;

//l.Half();
//cout << l;
//LinearList<int> p(l);
//cout << p;



//l.Next();
//cout << l.Current() << endl;
//l.Next();
//cout << l.Current() << endl;
//l.Previous();
//cout << l.Current() << endl;
//l.Reset();
//cout << l.Current() << endl;
//cout << l.End() << endl;
//cout << l.Front() << endl;
//l.Previous();




//int n = 10000000;
//for (int i = 0; i < n; i++)
//{
//	l.Insert(i, i);
//}

//clock_t start, finish;
//start = clock();
//Reverse(l);
//finish = clock();
////cout << l;

//cout << n << " " << start<< " "<< finish  << (finish - start) / CLK_TCK << endl;
//int x = -1;

//cout << l.Find(3, x)<< endl;
//cout << "\t" << x << endl;

//cout << l.Search(2) << endl;

//l.Delete(0, x);
//cout << l;
//l.Delete(3, x);
//cout << l;
//l.Delete(1, x);
//cout << l;
//l.Delete(1, x);
//cout << l;

//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
