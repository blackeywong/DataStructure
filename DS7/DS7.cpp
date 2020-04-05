// DS7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
using namespace std;
//数据结构算法与应用-C++语言描述 第七章
#include "matrix.h"
#include "matrixAs2DArray.h"
#include "diagonalMatrix.h"
#include "tridiagonalMatrix.h"
#include "tridiagonalByColumns.h"
#include "tridiagonalByRows.h"
#include "tridiagonalAsIrregularArray.h"
#include "lowerTriangleAsIrregularArray.h"
#include "upperTriangleAsIrregularArray.h"
#include "lowerTriangularMatrix.h"
#include "upperTriangularMatrix.h"
#include "TwoLowerTriangleAsIrregularArray.h"
#include "lowerSymmetricMatrix.h"
#include "cMatrix.h"
#include "antidiagonalMatrix.h"
#include "toeplitzMatrix.h"
#include "squareBandMatrix.h"
#include "squareBandAsIrregularArray.h"
#include "sparseMatrix.h"
#include "sparseMatrixColumnMajor.h"
#include "newSparseMatrix.h"
#include "linkedMatrix.h"
#include "linkedMatrixArray.h"
#include "verticalLinkedMatrix.h"

//Exercise 53
int main() {
	string s1 = "4 8 9 1 4 2 1 7 1 2 2 6 2 5 7 2 8 3 3 4 9 3 6 8 4 2 4 4 3 5";
	istringstream ss1(s1);
	verticalLinkedMatrix<int> m1;
 	ss1 >> m1;
	cout << m1;
	verticalLinkedMatrix<int> m2;
	m1.transpose(m2);
	cout << m2;
	string s3 = "4 8 6 1 1 3 1 4 5 1 6 7 2 2 -6 2 3 5 2 5 3";
	istringstream ss3(s3);
	verticalLinkedMatrix<int> m3;
	ss3 >> m3;
	cout << m3;
	verticalLinkedMatrix<int> m4;
	m1.add(m3, m4);
	cout << m4;
	verticalLinkedMatrix<int> m7;
	m4.substract(m1, m7);
	cout << m7;
	cout << m1.get(1, 1) << endl;//0
	cout << m1.get(1, 4) << endl;//2
	cout << m1.get(1, 8) << endl;//0
	cout << m1.get(2, 1) << endl;//0
	cout << m1.get(2, 4) << endl;//0
	cout << m1.get(2, 8) << endl;//3
	cout << m1.get(3, 1) << endl;//0
	cout << m1.get(3, 2) << endl;//0
	cout << m1.get(4, 2) << endl;//4
	cout << m1.get(4, 8) << endl;//0

	m1.set(1, 1, 1);
	m1.set(1, 4, 0);
	m1.set(1, 8, 3);
	m1.set(2, 1, 4);
	m1.set(2, 4, 5);
	m1.set(2, 8, 6);
	m1.set(3, 1, 7);
	m1.set(3, 2, 8);
	m1.set(4, 2, 9);
	m1.set(4, 8, 10);
	cout << m1;

	verticalLinkedMatrix<int> m5(m3);
	cout << m5;

	verticalLinkedMatrix<int> m6;
	m3.multiply(m2, m6);
	cout << m6;
}

////Exercise 52
//int main() {
//	string s1 = "4 8 9 1 4 2 1 7 1 2 2 6 2 5 7 2 8 3 3 4 9 3 6 8 4 2 4 4 3 5";
//	istringstream ss1(s1);
//	linkedMatrixArray<int> m1;
//	ss1 >> m1;
//	cout << m1;
//	linkedMatrixArray<int> m2;
//	m1.transpose(m2);
//	cout << m2;
//	string s3 = "4 8 6 1 1 3 1 4 5 1 6 7 2 2 -6 2 3 5 2 5 3";
//	istringstream ss3(s3);
//	linkedMatrixArray<int> m3;
//	ss3 >> m3;
//	cout << m3;
//	linkedMatrixArray<int> m4;
//	m1.add(m3, m4);
//	cout << m4;
//	linkedMatrixArray<int> m7;
//	m4.substract(m1, m7);
//	cout << m7;
//	cout << m1.get(1, 1) << endl;//0
//	cout << m1.get(1, 4) << endl;//2
//	cout << m1.get(1, 8) << endl;//0
//	cout << m1.get(2, 1) << endl;//0
//	cout << m1.get(2, 4) << endl;//0
//	cout << m1.get(2, 8) << endl;//3
//	cout << m1.get(3, 1) << endl;//0
//	cout << m1.get(3, 2) << endl;//0
//	cout << m1.get(4, 2) << endl;//4
//	cout << m1.get(4, 8) << endl;//0
//
//	m1.set(1, 1, 1);
//	m1.set(1, 4, 0);
//	m1.set(1, 8, 3);
//	m1.set(2, 1, 4);
//	m1.set(2, 4, 5);
//	m1.set(2, 8, 6);
//	m1.set(3, 1, 7);
//	m1.set(3, 2, 8);
//	m1.set(4, 2, 9);
//	m1.set(4, 8, 10);
//	cout << m1;
//
//	linkedMatrixArray<int> m5(m3);
//	cout << m5;
//
//	linkedMatrixArray<int> m6;
//	m3.multiply(m2, m6);
//	cout << m6;
//}

////Exercise 51
//int main() {
//	string s1 = "4 8 9 1 4 2 1 7 1 2 2 6 2 5 7 2 8 3 3 4 9 3 6 8 4 2 4 4 3 5";
//	istringstream ss1(s1);
//	linkedMatrix<int> m1;
//	ss1 >> m1;
//	cout << m1;
//	linkedMatrix<int> m2;
//	m1.transpose(m2);
//	cout << m2;
//	string s3 = "4 8 6 1 1 3 1 4 5 1 6 7 2 2 -6 2 3 5 2 5 3";
//	istringstream ss3(s3);
//	linkedMatrix<int> m3;
//	ss3 >> m3;
//	cout << m3;
//	linkedMatrix<int> m4;
//	m1.add(m3, m4);
//	cout << m4;
//	linkedMatrix<int> m7;
//	m4.substract(m1, m7);
//	cout << m7;
//	cout << m1.get(1, 1) << endl;//0
//	cout << m1.get(1, 4) << endl;//2
//	cout << m1.get(1, 8) << endl;//0
//	cout << m1.get(2, 1) << endl;//0
//	cout << m1.get(2, 4) << endl;//0
//	cout << m1.get(2, 8) << endl;//3
//	cout << m1.get(3, 1) << endl;//0
//	cout << m1.get(3, 2) << endl;//0
//	cout << m1.get(4, 2) << endl;//4
//	cout << m1.get(4, 8) << endl;//0
//	
//	m1.set(1, 1, 1);
//	m1.set(1, 4, 0);
//	m1.set(1, 8, 3);
//	m1.set(2, 1, 4);
//	m1.set(2, 4, 5);
//	m1.set(2, 8, 6);
//	m1.set(3, 1, 7);
//	m1.set(3, 2, 8);
//	m1.set(4, 2, 9);
//	m1.set(4, 8, 10);
//	cout << m1;
//	
//	linkedMatrix<int> m5(m3);
//	cout << m5;
//
//	linkedMatrix<int> m6;
//	m3.multiply(m2, m6);
//	cout << m6;
//}

////Exercise 47
//int main() {
//	string s1 = "4 8 9 1 4 2 1 7 1 2 2 6 2 5 7 2 8 3 3 4 9 3 6 8 4 2 4 4 3 5";
//	istringstream ss1(s1);
//	newSparseMatrix<int> m1;
//	ss1 >> m1;
//	cout << m1;
//	newSparseMatrix<int> m2;
//	m1.transpose(m2);
//	cout << m2;
//	string s3 = "4 8 6 1 1 3 1 4 5 1 6 7 2 2 -6 2 3 5 2 5 3";
//	istringstream ss3(s3);
//	newSparseMatrix<int> m3;
//	ss3 >> m3;
//	cout << m3;
//	newSparseMatrix<int> m4;
//	m1.add(m3, m4);
//	cout << m4;
//	cout << m1.get(1, 1) << endl;//0
//	cout << m1.get(1, 4) << endl;//2
//	cout << m1.get(1, 8) << endl;//0
//	cout << m1.get(2, 1) << endl;//0
//	cout << m1.get(2, 4) << endl;//0
//	cout << m1.get(2, 8) << endl;//3
//	cout << m1.get(3, 1) << endl;//0
//	cout << m1.get(3, 2) << endl;//0
//	cout << m1.get(4, 2) << endl;//4
//	cout << m1.get(4, 8) << endl;//0
//	
//	m1.set(1, 1, 1);
//	m1.set(1, 4, 0);
//	m1.set(1, 8, 3);
//	m1.set(2, 1, 4);
//	m1.set(2, 4, 5);
//	m1.set(2, 8, 6);
//	m1.set(3, 1, 7);
//	m1.set(3, 2, 8);
//	m1.set(4, 2, 9);
//	m1.set(4, 8, 10);
//	cout << m1;
//	cout << "Exercise 47" << endl;
//
//	newSparseMatrix<int> m5(m3);
//	cout << m5;
//
//	cout << "Exercise 48" << endl;
//	newSparseMatrix<int> m6;
//	m3.multiply(m2, m6);
//	cout << m6;
//}


////Exercise 44
//int main() {
//	string s1 = "8 4 9 2 2 6 2 4 4 3 4 5 4 1 2 4 3 9 5 2 7 6 3 8 7 1 1 8 2 3";
//	istringstream ss1(s1);
//	sparseMatrixColumnMajor<int> m1;
//	ss1 >> m1;
//	cout << m1;
//	sparseMatrixColumnMajor<int> m2;
//	m1.transpose(m2);
//	cout << m2;
//	string s3 = "8 4 6 1 1 3 2 2 -6 3 2 5 4 1 5 5 2 3 6 1 7";
//	istringstream ss3(s3);
//	sparseMatrixColumnMajor<int> m3;
//	ss3 >> m3;
//	cout << m3;
//	sparseMatrixColumnMajor<int> m4;
//	m1.add(m3, m4);
//	cout << m4;
//	cout << "Exercise 44" << endl;
//	cout << m1.get(1, 1) << endl;//0
//	cout << m1.get(1, 4) << endl;//2
//	cout << m1.get(1, 8) << endl;//0
//	cout << m1.get(2, 1) << endl;//0
//	cout << m1.get(2, 4) << endl;//0
//	cout << m1.get(2, 8) << endl;//3
//	cout << m1.get(3, 1) << endl;//0
//	cout << m1.get(3, 2) << endl;//0
//	cout << m1.get(4, 2) << endl;//4
//	cout << m1.get(4, 8) << endl;//0
//
//	m1.set(1, 1, 1);
//	m1.set(1, 4, 2);
//	m1.set(1, 8, 3);
//	m1.set(2, 1, 4);
//	m1.set(2, 4, 5);
//	m1.set(2, 8, 6);
//	m1.set(3, 1, 7);
//	m1.set(3, 2, 8);
//	m1.set(4, 2, 9);
//	m1.set(4, 8, 10);
//	cout << m1;
//
//	sparseMatrixColumnMajor<int> m5(m3);
//	cout << m5;
//
//	cout << "Exercise 46" << endl;
//	sparseMatrixColumnMajor<int> m6;
//	m3.multiply(m2, m6);
//	cout << m6;
//}

////Exercise 41
//int main() {
//	string s1 = "4 8 9 1 4 2 1 7 1 2 2 6 2 5 7 2 8 3 3 4 9 3 6 8 4 2 4 4 3 5";
//	istringstream ss1(s1);
//	sparseMatrix<int> m1;
//	ss1 >> m1;
//	cout << m1;
//	sparseMatrix<int> m2;
//	m1.transpose(m2);
//	cout << m2;
//	string s3 = "4 8 6 1 1 3 1 4 5 1 6 7 2 2 -6 2 3 5 2 5 3";
//	istringstream ss3(s3);
//	sparseMatrix<int> m3;
//	ss3 >> m3;
//	cout << m3;
//	sparseMatrix<int> m4;
//	m1.add(m3, m4);
//	cout << m4;
//	cout << m1.get(1, 1) << endl;//0
//	cout << m1.get(1, 4) << endl;//2
//	cout << m1.get(1, 8) << endl;//0
//	cout << m1.get(2, 1) << endl;//0
//	cout << m1.get(2, 4) << endl;//0
//	cout << m1.get(2, 8) << endl;//3
//	cout << m1.get(3, 1) << endl;//0
//	cout << m1.get(3, 2) << endl;//0
//	cout << m1.get(4, 2) << endl;//4
//	cout << m1.get(4, 8) << endl;//0
//	
//	m1.set(1, 1, 1);
//	m1.set(1, 4, 2);
//	m1.set(1, 8, 3);
//	m1.set(2, 1, 4);
//	m1.set(2, 4, 5);
//	m1.set(2, 8, 6);
//	m1.set(3, 1, 7);
//	m1.set(3, 2, 8);
//	m1.set(4, 2, 9);
//	m1.set(4, 8, 10);
//	cout << m1;
//	cout << "Exercise 41" << endl;
//
//	sparseMatrix<int> m5(m3);
//	cout << m5;
//
//	cout << "Exercise 45" << endl;
//	sparseMatrix<int> m6;
//	m3.multiply(m2, m6);
//	cout << m6;
//}

////Exercise 37-5
//int main() {
//	cout << "Exercise 37-5" << endl;
//	string s1("3 4 5 2 3 4 5 1 2 3 4 5 1 2 3 4 1 2 3");
//	istringstream iss1(s1);
//	squareBandAsIrregularArray<int> m1(5, 3);
//	iss1 >> m1;
//	cout << m1 << endl;
//	string s2("1 1 1 1 2 2 2 1 2 3 3 3 2 3 4 4 3 4 5");
//	istringstream iss2(s2);
//	squareBandAsIrregularArray<int> m2(5, 3);
//	iss2 >> m2;
//	cout << m2 << endl;
//	squareBandAsIrregularArray<int> m3;
//	m3 = m1 + m2;
//	cout << m3 << endl;
//	squareBandAsIrregularArray<int> m4 = m3 - m2;
//	cout << m4 << endl;
//	squareBandAsIrregularArray<int> m5 = m1.transpose();
//	cout << m5 << endl;
//	matrix<int> m6 = m2 * m4;
//	cout << m6 << endl;
//	squareBandAsIrregularArray<int> m7(m2);
//	cout << m7 << endl;
//	squareBandAsIrregularArray<int> m8 = m7;
//	cout << m8 << endl;
//}
////Exercise 37-4
//int main() {
//	cout << "Exercise 37-4" << endl;
//	string s1("1 1 1 2 2 2 2 3 3 3 3 3 4 4 4 4 5 5 5");
//	istringstream iss1(s1);
//	squareBandMatrix<int> m1(5,3);
//	iss1 >> m1;
//	cout << m1 << endl;
//	string s2("1 2 3 1 2 3 4 1 2 3 4 5 1 2 3 4 1 2 3");
//	istringstream iss2(s2);
//	squareBandMatrix<int> m2(5, 3);
//	iss2 >> m2;
//	cout << m2 << endl;
//	squareBandMatrix<int> m3;
//	m3 = m1 + m2;
//	cout << m3 << endl;
//	squareBandMatrix<int> m4 = m3 - m2;
//	cout << m4 << endl;
//	squareBandMatrix<int> m5 = m1.transpose();
//	cout << m5 << endl;
//	matrix<int> m6 = m2 * m4;
//	cout << m6 << endl;
//	squareBandMatrix<int> m7(m2);
//	cout << m7 << endl;
//	squareBandMatrix<int> m8 = m7;
//	cout << m8 << endl;
//}

////Exercise 36
//int main() {
//	cout << "Exercise 36" << endl;
//	string s1("1 2 3 4 5 0 1 2 3");
//	istringstream iss1(s1);
//	toeplitzMatrix<int> m1(5);
//	iss1 >> m1;
//	cout << m1 << endl;
//	string s2("5 4 3 2 1 6 7 8 9");
//	istringstream iss2(s2);
//	toeplitzMatrix<int> m2(5);
//	iss2 >> m2;
//	cout << m2 << endl;
//	toeplitzMatrix<int> m3;
//	m3 = m1 + m2;
//	cout << m3 << endl;
//	toeplitzMatrix<int> m4 = m3 - m2;
//	cout << m4 << endl;
//	toeplitzMatrix<int> m5 = m1.transpose();
//	cout << m5 << endl;
//	matrix<int> m6 = m2 * m4;
//	cout << m6 << endl;
//	toeplitzMatrix<int> m7(m2);
//	cout << m7 << endl;
//	toeplitzMatrix<int> m8 = m7;
//	cout << m8 << endl;
//}

////Exercise 35
//int main() {
//	cout << "Exercise 35" << endl;
//	string s1("1 2 3 4 5");
//	istringstream iss1(s1);
//	antidiagonalMatrix<int> m1(5);
//	iss1 >> m1;
//	cout << m1 << endl;
//	string s2("3 2 1 0 -1");
//	istringstream iss2(s2);
//	antidiagonalMatrix<int> m2(5);
//	iss2 >> m2;
//	cout << m2 << endl;
//	antidiagonalMatrix<int> m3;
//	m3 = m1 + m2;
//	cout << m3 << endl;
//	antidiagonalMatrix<int> m4 = m3 - m2;
//	cout << m4 << endl;
//	antidiagonalMatrix<int> m5 = m1.transpose();
//	cout << m5 << endl;
//	diagonalMatrix<int> m6 = m2 * m4;
//	cout << m6 << endl;
//	antidiagonalMatrix<int> m7(m2);
//	cout << m7 << endl;
//	antidiagonalMatrix<int> m8 = m7;
//	cout << m8 << endl;
//}

////Exercise 34
//int main() {
//	cout << "Exercise 34" << endl;
//	string s1("1 1 1 1 1 5 5 5 5 5 2 3 4");
//	istringstream iss1(s1);
//	cMatrix<int> m1(5);
//	iss1 >> m1;
//	cout << m1 << endl;
//	string s2("1 2 3 4 5 1 2 3 4 5 1 1 1");
//	istringstream iss2(s2);
//	cMatrix<int> m2(5);
//	iss2 >> m2;
//	cout << m2 << endl;
//	cMatrix<int> m3;
//	m3 = m1 + m2;
//	cout << m3 << endl;
//	cMatrix<int> m4 = m3 - m2;
//	cout << m4 << endl;
//	matrix<int> m5 = m1.transpose();
//	cout << m5 << endl;
//	matrix<int> m6 = m2 * m4;
//	cout << m6 << endl;
//	cMatrix<int> m7(m2);
//	cout << m7 << endl;
//	cMatrix<int> m8 = m7;
//	cout << m8 << endl;
//}

////Exercise 33
//int main() {
//	cout << "Exercise 33" << endl;
//	string s1("1 2 2 3 3 3 4 4 4 4 5 5 5 5 5");
//	istringstream iss1(s1);
//	lowerSymmetricMatrix<int> m1(5);
//	iss1 >> m1;
//	cout << m1 << endl;
//	string s2("1 1 2 1 2 3 1 2 3 4 1 2 3 4 5");
//	istringstream iss2(s2);
//	lowerSymmetricMatrix<int> m2(5);
//	iss2 >> m2;
//	cout << m2 << endl;
//	lowerSymmetricMatrix<int> m3;
//	m3 = m1 + m2;
//	cout << m3 << endl;
//	lowerSymmetricMatrix<int> m4 = m3 - m2;
//	cout << m4 << endl;
//	lowerSymmetricMatrix<int> m5 = m1.transpose();
//	cout << m5 << endl;
//	matrix<int> m6 = m2 * m4;
//	cout << m6 << endl;
//	lowerSymmetricMatrix<int> m7(m2);
//	cout << m7 << endl;
//	lowerSymmetricMatrix<int> m8 = m7;
//	cout << m8 << endl;
//}

//Exercise 30, 32
//int main() {
	//cout << "Exercise 30" << endl;
	//string s1("1 1 2 1 2 3 1 2 3 4 1 2 3 4 5 1 2 2 3 3 3 4 4 4 4 5 5 5 5 5");
	//istringstream iss1(s1);
	//TwoLowerTriangleAsIrregularArray<int> m1(5);
	//iss1 >> m1;
	//cout << m1 << endl;

	//cout << m1.getA(4, 3) << endl;
	//cout << m1.getB(4, 3) << endl;
	//m1.setA(4, 3, 6);
	//m1.setB(4, 3, 6);
	//cout << m1 << endl;

	//string s2("1 2 2 3 3 3 4 4 4 4 5 5 5 5 5");
	//istringstream iss2(s2);
	//lowerTriangularMatrix<int> m2(5);
	//iss2 >> m2;
	//cout << m2 << endl;
	//string s3("1 1 1 1 1 2 2 2 2 3 3 3 4 4 5");
	//istringstream iss3(s3);
	//upperTriangularMatrix<int> m3(5);
	//iss3 >> m3;
	//cout << m3 << endl;

	//matrix<int> m4 = m2 * m3;
	//cout << m4 << endl;
//}

//Exercise 27
//int main() {
//	cout << "Exercise 27" << endl;
//	string s1("1 1 1 1 1 2 2 2 2 3 3 3 4 4 5");
//	istringstream iss1(s1);
//	upperTriangularMatrix<int> m1(5);
//	iss1 >> m1;
//	cout << m1 << endl;
//	string s2("1 2 3 4 5 1 2 3 4 1 2 3 1 2 1");
//	istringstream iss2(s2);
//	upperTriangularMatrix<int> m2(5);
//	iss2 >> m2;
//	cout << m2 << endl;
//	upperTriangularMatrix<int> m3;
//	m3 = m1 + m2;
//	cout << m3 << endl;
//	upperTriangularMatrix<int> m4 = m3 - m2;
//	cout << m4 << endl;
//	lowerTriangularMatrix<int> m5 = m1.transpose();
//	cout << m5 << endl;
//	upperTriangularMatrix<int> m6 = m2 * m4;
//	cout << m6 << endl;
//	upperTriangularMatrix<int> m7(m2);
//	cout << m7 << endl;
//	upperTriangularMatrix<int> m8 = m7;
//	cout << m8 << endl;
//}
//Exercise 28, 29, 31
//int main() {
//	cout << "Exercise 28" << endl;
//	string s1("1 2 2 3 3 3 4 4 4 4 5 5 5 5 5");
//	istringstream iss1(s1);
//	lowerTriangularMatrix<int> m1(5);
//	iss1 >> m1;
//	cout << m1 << endl;
//	string s2("1 1 2 1 2 3 1 2 3 4 1 2 3 4 5");
//	istringstream iss2(s2);
//	lowerTriangularMatrix<int> m2(5);
//	iss2 >> m2;
//	cout << m2 << endl;
//	lowerTriangularMatrix<int> m3;
//	m3 = m1 + m2;
//	cout << m3 << endl;
//	lowerTriangularMatrix<int> m4 = m3 - m2;
//	cout << m4 << endl;
//	upperTriangularMatrix<int> m5 = m1.transpose();
//	cout << m5 << endl;
//	lowerTriangularMatrix<int> m6 = m2 * m4;
//	cout << m6 << endl;
//	lowerTriangularMatrix<int> m7(m2);
//	cout << m7 << endl;
//	lowerTriangularMatrix<int> m8 = m7;
//	cout << m8 << endl;
//}

////Exercise 26
////int main() {
////	cout << "Exercise 26" << endl;
////	string s1("1 1 1 1 1 2 2 2 2 3 3 3 4 4 5");
////	istringstream iss1(s1);
////	upperTriangleAsIrregularArray<int> m1(5);
////	iss1 >> m1;
////	cout << m1 << endl;
////	string s2("1 2 3 4 5 1 2 3 4 1 2 3 1 2 1");
////	istringstream iss2(s2);
////	upperTriangleAsIrregularArray<int> m2(5);
////	iss2 >> m2;
////	cout << m2 << endl;
////	upperTriangleAsIrregularArray<int> m3;
////	m3 = m1 + m2;
////	cout << m3 << endl;
////	upperTriangleAsIrregularArray<int> m4 = m3 - m2;
////	cout << m4 << endl;
////	lowerTriangleAsIrregularArray<int> m5 = m1.transpose();
////	cout << m5 << endl;
////	upperTriangleAsIrregularArray<int> m6 = m2 * m4;
////	cout << m6 << endl;
////	upperTriangleAsIrregularArray<int> m7(m2);
////	cout << m7 << endl;
////	upperTriangleAsIrregularArray<int> m8 = m7;
////	cout << m8 << endl;
////}
//
//int main() {
//	cout << "Exercise 26" << endl;
//	string s1("1 2 2 3 3 3 4 4 4 4 5 5 5 5 5");
//	istringstream iss1(s1);
//	lowerTriangleAsIrregularArray<int> m1(5);
//	iss1 >> m1;
//	cout << m1 << endl;
//	string s2("1 1 2 1 2 3 1 2 3 4 1 2 3 4 5");
//	istringstream iss2(s2);
//	lowerTriangleAsIrregularArray<int> m2(5);
//	iss2 >> m2;
//	cout << m2 << endl;
//	lowerTriangleAsIrregularArray<int> m3;
//	m3 = m1 + m2;
//	cout << m3 << endl;
//	lowerTriangleAsIrregularArray<int> m4 = m3 - m2;
//	cout << m4 << endl;
//	upperTriangleAsIrregularArray<int> m5 = m1.transpose();
//	cout << m5 << endl;
//	lowerTriangleAsIrregularArray<int> m6 = m2 * m4;
//	cout << m6 << endl;
//	lowerTriangleAsIrregularArray<int> m7(m2);
//	cout << m7 << endl;
//	lowerTriangleAsIrregularArray<int> m8 = m7;
//	cout << m8 << endl;
//}


////Exercise 25
//int main() {
//	cout << "Exercise 25" << endl;
//	string s1("2 3 1 2 3 1 2 3 1 2 3 1 2");
//	istringstream iss1(s1);
//	tridiagonalAsIrregularArray<int> m1(5);
//	iss1 >> m1;
//	cout << m1 << endl;
//	string s2("1 2 -1 1 2 -1 1 2 -1 1 2 -1 1");
//	istringstream iss2(s2);
//	tridiagonalAsIrregularArray<int> m2(5);
//	iss2 >> m2;
//	cout << m2 << endl;
//	tridiagonalAsIrregularArray<int> m3;
//	m3 = m1 + m2;
//	cout << m3 << endl;
//	tridiagonalAsIrregularArray<int> m4 = m3 - m2;
//	cout << m4 << endl;
//	tridiagonalAsIrregularArray<int> m5 = m1.transpose();
//	cout << m5 << endl;
//	matrix<int> m6 = m5 * m4;
//	cout << m6 << endl;
//	tridiagonalAsIrregularArray<int> m7(m5);
//	cout << m7 << endl;
//	tridiagonalAsIrregularArray<int> m8 = m7;
//	cout << m8 << endl;
//}


////Exercise 23
//int main() {
//	cout << "Exercise 23" << endl;
//	string s1("2 3 1 2 3 1 2 3 1 2 3 1 2");
//	istringstream iss1(s1);
//	tridiagonalByRows<int> m1(5);
//	iss1 >> m1;
//	cout << m1 << endl;
//	string s2("1 2 -1 1 2 -1 1 2 -1 1 2 -1 1");
//	istringstream iss2(s2);
//	tridiagonalByRows<int> m2(5);
//	iss2 >> m2;
//	cout << m2 << endl;
//	tridiagonalByRows<int> m3;
//	m3 = m1 + m2;
//	cout << m3 << endl;
//	tridiagonalByRows<int> m4 = m3 - m2;
//	cout << m4 << endl;
//	tridiagonalByRows<int> m5 = m1.transpose();
//	cout << m5 << endl;
//	matrix<int> m6 = m5 * m4;
//	cout << m6 << endl;
//	tridiagonalByRows<int> m7(m5);
//	cout << m7 << endl;
//	tridiagonalByRows<int> m8 = m7;
//	cout << m8 << endl;
//}

////Exercise 22
//int main() {
//	cout << "Exercise 22" << endl;
//	string s1("2 1 3 2 1 3 2 1 3 2 1 3 2");
//	istringstream iss1(s1);
//	tridiagonalByColumns<int> m1(5);
//	iss1 >> m1;
//	cout << m1 << endl;
//	string s2("1 -1 2 1 -1 2 1 -1 2 1 -1 2 1");
//	istringstream iss2(s2);
//	tridiagonalByColumns<int> m2(5);
//	iss2 >> m2;
//	cout << m2 << endl;
//	tridiagonalByColumns<int> m3;
//	m3 = m1 + m2;
//	cout << m3 << endl;
//	tridiagonalByColumns<int> m4 = m3 - m2;
//	cout << m4 << endl;
//	tridiagonalByColumns<int> m5 = m1.transpose();
//	cout << m5 << endl;
//	matrix<int> m6 = m5 * m4;
//	cout << m6 << endl;
//	tridiagonalByColumns<int> m7(m5);
//	cout << m7 << endl;
//	tridiagonalByColumns<int> m8 = m7;
//	cout << m8 << endl;
//}


////Exercise 21
//int main() {
//	cout << "Exercise 21" << endl;
//	string s1("1 1 1 1 2 2 2 2 2 3 3 3 3");
//	istringstream iss1(s1);
//	tridiagonalMatrix<int> m1(5);
//	iss1 >> m1;
//	cout << m1 << endl;
//	string s2("-1 -1 -1 -1 1 1 1 1 1 2 2 2 2");
//	istringstream iss2(s2);
//	tridiagonalMatrix<int> m2(5);
//	iss2 >> m2;
//	cout << m2 << endl;
//	tridiagonalMatrix<int> m3;
//	m3 = m1 + m2;
//	cout << m3 << endl;
//	tridiagonalMatrix<int> m4 = m3 - m2;
//	cout << m4 << endl;
//	tridiagonalMatrix<int> m5 = m1.transpose();
//	cout << m5 << endl;
//	matrix<int> m6 = m5 * m4;
//	cout << m6 << endl;
//	tridiagonalMatrix<int> m7(m5);
//	cout << m7 << endl;
//	tridiagonalMatrix<int> m8 = m7;
//	cout << m8 << endl;
//}

////Exercise 20
//int main() {
//	cout << "Exercise 20" << endl;
//	string s1("2 3 0 1 2 3 4 5");
//	istringstream iss1(s1);
//	diagonalMatrix<int> m1;
//	iss1 >> m1;
//	cout << m1 << endl;
//	string s2("2 3 6 5 4 3 2 1");
//	istringstream iss2(s2);
//	diagonalMatrix<int> m2;
//	iss2 >> m2;
//	cout << m2 << endl;
//	diagonalMatrix<int> m3;
//	m3 = m1 + m2;
//	cout << m3 << endl;
//	diagonalMatrix<int> m4 = m3 - m2;
//	cout << m4 << endl;
//	diagonalMatrix<int> m5 = m1.transpose();
//	cout << m5 << endl;
//	diagonalMatrix<int> m6 = m5 * m4;
//	cout << m6 << endl;
//	diagonalMatrix<int> m7(m5);
//	cout << m7 << endl;
//	diagonalMatrix<int> m8 = m7;
//	cout << m8 << endl;
//}

//Exercise 15-17
//int main()
//{
//	string s1("2 3 0 1 2 3 4 5");
//	istringstream iss1(s1);
//	matrix<int> m1;
//	iss1 >> m1;
//	cout << m1 << endl;
//	m1 += 1;
//	cout << m1 << endl;
//	m1 -= 2;
//	cout << m1 << endl;
//	m1 *= 3;
//	cout << m1 << endl;
//	m1 /= 2;
//	cout << m1 << endl;
//	string s2("2 3 6 5 4 3 2 1");
//	istringstream iss2(s2);
//	matrix<int> m2;
//	iss2 >> m2;
//	cout << m2 << endl;
//	matrix<int> m3 = m1 + m2;
//	cout << m3 << endl;
//	matrix<int> m4 = m3 - m2;
//	cout << m4 << endl;
//	matrix<int> m5 = m1.transpose();
//	cout << m5 << endl;
//	matrix<int> m6 = m5 * m4;
//	cout << m6 << endl;
//	matrix<int> m7(m5);
//	cout << m7 << endl;
//	matrix<int> m8 = m7;
//	cout << m8 << endl;
//	++m8;
//	cout << m8 << endl;
//	--m8;
//	cout << m8 << endl;
//	
//	//cout << "Exercise 17" << endl;
//	//string s1("2 3 0 1 2 3 4 5");
//	//istringstream iss1(s1);
//	//matrixAs2DArray<int> m1;
//	//iss1 >> m1;
//	//cout << m1 << endl;
//	//string s2("2 3 6 5 4 3 2 1");
//	//istringstream iss2(s2);
//	//matrixAs2DArray<int> m2;
//	//iss2 >> m2;
//	//cout << m2 << endl;
//	//matrixAs2DArray<int> m3;
//	//m3 = m1 + m2;
//	//cout << m3 << endl;
//	//matrixAs2DArray<int> m4 = m3 - m2;
//	//cout << m4 << endl;
//	//matrixAs2DArray<int> m5 = m1.transpose();
//	//cout << m5 << endl;
//	//matrixAs2DArray<int> m6 = m5 * m4;
//	//cout << m6 << endl;
//	//matrixAs2DArray<int> m7(m5);
//	//cout << m7 << endl;
//	//matrixAs2DArray<int> m8 = m7;
//	//cout << m8 << endl;
//
//	//matrixAs2DArray<int> m9;
//	//matrixAs2DArray<int> m10;
//	matrix<int> m9;
//	matrix<int> m10;
//
//	clock_t start, finish;
//	start = clock();
//	int n = 1000000;
//	for(int i=0;i<n;i++){
//		m9 = m5 * m4;
//		//m10 = m1 + m2;
//	}
//	finish = clock();
//	cout << n << " " << start<< " "<< finish  << " " << (double)(finish - start) / CLK_TCK << endl;
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
