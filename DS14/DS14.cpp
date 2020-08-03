// DS14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<iterator>

#include "BinarySearchTree.h"
#include "DS14_Application.h"
#include "DupBinarySearchTree.h"
#include "IndexedBinarySearchTree.h"
#include "DupIndexedBinarySearchTree.h"
#include "LinearListAsBinaryTree.h"

int main()
{
    std::cout << "Exercise 6" << std::endl;
    BinarySearchTree<int, int> bst1;
    std::string sbst1{ "10 4 4 12 12 8 8 16 16 6 6 18 18 24 24 2 2 14 14 3 3" };
    std::istringstream issbst1(sbst1);
    bst1.input(issbst1);
    bst1.ascend();
    bst1.erase(6);
    bst1.erase(14);
    bst1.erase(16);
    bst1.erase(4);
    bst1.ascend();

    std::cout << "Exercise 7" << std::endl;
    BinarySearchTree<int, int> bst2;
    std::string sbst2{ "12 10 10 5 5 20 20 14 14 30 30 8 8 6 6 35 35 25 25 3 3 12 12 17 17" };
    std::istringstream issbst2(sbst2);
    bst2.input(issbst2);
    bst2.ascend();
    bst2.erase(35);
    bst2.erase(30);
    bst2.erase(20);
    bst2.erase(10);
    bst2.ascend();

    std::cout << "Exercise 8" << std::endl;
    BinarySearchTree<int, int> bst3;
    std::istringstream issbst3(sbst2);
    bst3.input(issbst3);
    bst3.outputInRange(1, 100);
    bst3.outputInRange(9, 11);
    bst3.outputInRange(5, 25);
    bst3.outputInRange(3, 19);
    bst3.outputInRange(13, 24);

    std::cout << "Exercise 9" << std::endl;
    int n = 100;
    TestBinarySearchTree<int, int> tbst(n);
    tbst.testFind(FIND1);
    tbst.testFind(FIND2);

    std::cout << "Exercise 10" << std::endl;
    int sbst10[] = { 4, 12, 8, 16, 6, 18, 24, 2, 14, 3 };
    int count10 = sizeof(sbst10) / sizeof(int);
    BSTSort(sbst10, count10);
    std::copy(sbst10, sbst10 + count10, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    int sbst10_2[] = { 4, 12, 8, 16, 6, 18, 24, 2, 14, 3 };
    bubbleSort(sbst10_2, count10);
    std::copy(sbst10_2, sbst10_2 + count10, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    int sbst10_3[] = { 4, 12, 8, 16, 6, 18, 24, 2, 14, 3 };
    insertionSort(sbst10_3, count10);
    std::copy(sbst10_3, sbst10_3 + count10, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    int sbst10_4[] = { 4, 12, 8, 16, 6, 18, 24, 2, 14, 3 };
    selectionSort(sbst10_4, count10);
    std::copy(sbst10_4, sbst10_4 + count10, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    int sbst10_5[] = { 4, 12, 8, 16, 6, 18, 24, 2, 14, 3 };
    rankSort(sbst10_5, count10);
    std::copy(sbst10_5, sbst10_5 + count10, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "Exercise 10_2" << std::endl;
    n = 100;
    TestSorting<int> ts(n);
    std::cout << "insertion sort\t\t";
    ts.testSort(INSERTION_SORT);
    std::cout << "selection sort\t\t";
    ts.testSort(SELECTION_SORT);
    std::cout << "rank sort\t\t";
    ts.testSort(RANK_SORT);
    std::cout << "Bubble sort\t\t";
    ts.testSort(BUBBLE_SORT);
    std::cout << "heap sort\t\t";
    ts.testSort(HEAP_SORT);
    std::cout << "winner tree sort\t";
    ts.testSort(WT_SORT);
    std::cout << "binary search tree sort\t";
    ts.testSort(BST_SORT);

    std::cout << "Exercise 12" << std::endl;
    for (int i = 1; i <= 31; ++i)
    {
        std::cout << "Split by: " << i << std::endl;
        BinarySearchTree<int, int> bst12;
        std::string sbst12{ "15 16 16 8 8 24 24 4 4 12 12 20 20 28 28 2 2 6 6 10 10 14 14 18 18 22 22 26 26 30 30" };
        std::istringstream issbst12(sbst12);
        bst12.input(issbst12);
        BinarySearchTree<int, int> bst12_1, bst12_2;
        std::pair<int, int>* p12;
        p12 = bst12.split(i, &bst12_1, &bst12_2);
        bst12_1.ascend();
        bst12_2.ascend();
        if (p12)
            std::cout << p12->first << std::endl;
        else
            std::cout << "nullptr" << std::endl;
        delete p12;
    }

    std::cout << "Exercise 13" << std::endl;
    n = 100;
    averageHeight(n);

    std::cout << "Exercise 14" << std::endl;
    for (auto it14 = bst2.begin(); it14 != bst2.end(); ++it14) {
        std::cout << *it14 << " ";
    }
    std::cout << std::endl;

    std::cout << "Exercise 15_1" << std::endl;
    bst2.eraseMax();
    bst2.ascend();
    bst2.eraseMax();
    bst2.ascend();
    bst2.eraseMax();
    bst2.ascend();
    bst2.eraseMax();
    bst2.ascend();
    bst2.eraseMax();
    bst2.ascend();
    bst2.eraseMax();
    bst2.ascend();
    bst2.eraseMax();
    bst2.ascend();
    bst2.eraseMax();
    bst2.ascend();
    bst2.eraseMax();
    bst2.ascend();
    //bst2.draw();
    //std::cin.ignore();

    std::cout << "Exercise 15_2" << std::endl;
    n = 100;
    TestInsertEraseMax<int, int> tiem(n);
    //tiem.testInsertEraseMax(MAX_HEAP);
    //tiem.testInsertEraseMax(BINARY_SEARCH_TREE);

    std::cout << "Exercise 17" << std::endl;
    DupBinarySearchTree<int, int> dbst17;
    std::string sdbst17{ "12 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2" };
    //std::string sdbst17{ "7 2 2 2 2 2 2 2 2 2 2 2 2 2 2" };
    std::istringstream issdbst17(sdbst17);
    dbst17.input(issdbst17);
    dbst17.erase(2);
    dbst17.ascend();

    std::cout << "Exercise 18/19" << std::endl;
    IndexedBinarySearchTree<int, int> ibst18;
    std::string sibst18{ "10 4 4 12 12 8 8 16 16 6 6 18 18 24 24 2 2 14 14 3 3" };
    std::istringstream issibst18(sibst18);
    ibst18.input(issibst18);
    ibst18.ascend();
    ibst18.find(3);
    ibst18.find(6);
    ibst18.find(8);
    std::cout << ibst18.getIndex(2) << std::endl;
    std::cout << ibst18.getIndex(3) << std::endl;
    std::cout << ibst18.getIndex(4) << std::endl;
    std::cout << ibst18.getIndex(6) << std::endl;
    std::cout << ibst18.getIndex(8) << std::endl;
    std::cout << ibst18.getIndex(12) << std::endl;
    std::cout << ibst18.getIndex(14) << std::endl;
    std::cout << ibst18.getIndex(16) << std::endl;
    std::cout << ibst18.getIndex(18) << std::endl;
    std::cout << ibst18.getIndex(24) << std::endl;
    std::cout << ibst18.getIndex(0) << std::endl;
    ibst18.deleteAt(7);
    ibst18.deleteAt(5);
    ibst18.deleteAt(0);
    ibst18.erase(6);
    ibst18.erase(14);
    ibst18.erase(4);
    ibst18.ascend();
 
    std::cout << "Exercise 20" << std::endl;
    DupIndexedBinarySearchTree<int, int> dibst20;
    std::string sdibst20{ "12 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2" };
    //std::string sdibst20{ "7 2 2 2 2 2 2 2 2 2 2 2 2 2 2" };
    std::istringstream issdibst20(sdibst20);
    dibst20.input(issdibst20);
    dibst20.erase(2);
    dibst20.ascend();
    //dibst20.draw();
    //std::cin.ignore();

    std::cout << "Exercise 22_1" << std::endl;
    LinearListAsBinaryTree<int, int> bst22_1;
    std::string sbst22_1{ "10 4 4 12 12 8 8 16 16 6 6 18 18 24 24 2 2 14 14 3 3" };
    std::istringstream issbst22_1(sbst22_1);
    bst22_1.input(issbst22_1);
    bst22_1.ascend();
    bst22_1.erase(6);
    bst22_1.erase(14);
    bst22_1.erase(16);
    bst22_1.erase(4);
    bst22_1.ascend();

    std::cout << "Exercise 22_2" << std::endl;
    LinearListAsBinaryTree<int, int> bst22_2;
    std::string sbst22_2{ "12 10 10 5 5 20 20 14 14 30 30 8 8 6 6 35 35 25 25 3 3 12 12 17 17" };
    std::istringstream issbst22_2(sbst22_2);
    bst22_2.input(issbst22_2);
    bst22_2.ascend();
    bst22_2.erase(35);
    bst22_2.erase(30);
    bst22_2.erase(20);
    bst22_2.erase(10);
    bst22_2.ascend();

    std::cout << "Exercise 23" << std::endl;
    int arr23[] = {1, 3, 6, 8, 1, 4, 8, 4, 23443, 6, 3, 7, 8, -1};
    arrayHistogramming(arr23, 14);

    std::cout << "Exercise 24" << std::endl;
    int arr24[] = { 1, 3, 6, 8, 1, 4, 8, 4, 23443, 6, 3, 7, 8, -1 };
    hashHistogramming(arr24, 14);

    std::cout << "Binary Search Tree Histogramming" << std::endl;
    int arr[] = { 1, 3, 6, 8, 1, 4, 8, 4, 23443, 6, 3, 7, 8, -1 };
    bstHistogramming(arr, 14);

    std::cout << "Best Fit Pack with findGE" << std::endl;
    int objectSize[] = {0, 3, 8, 9, 10, 2, 6, 7, 6};
    bestFitPack(objectSize, 8, 15);

    std::cout << "Exercise 25" << std::endl;
    int objectSize25[] = { 0, 3, 8, 9, 10, 2, 6, 7, 6 };
    bestFitPack2(objectSize25, 8, 15);

    std::cout << "Exercise 26" << std::endl;
    int theC26[] = { 0, 6, 4, 5, 8, 3, 2, 10, 9, 1, 7 };
    //int k26[] = {0, 5, 3, 3, 4, 2, 1, 3, 2, 0, 0};
    crossingDistribution(theC26, 10);

    std::cout << "Exercise 27" << std::endl;
    int theC27[] = { 0, 10, 9, 8, 1, 2, 3, 7, 6, 5, 4 };
    //int k27[] = { 0, 9, 8, 7, 0, 0, 0, 3, 2, 1, 0 };
    crossingDistribution(theC27, 10);

    std::cout << "Exercise 28_1" << std::endl;
    crossingDistribution2(theC26, 10);

    std::cout << "Exercise 28_2" << std::endl;
    crossingDistribution2(theC27, 10);

    std::cout << "Exercise 29" << std::endl;
    //indexText("D:\\study\\C++\\DS\\DS14\\toindex.txt", "D:\\study\\C++\\DS\\DS14\\toindex.out");
    indexText("D:\\study\\C++\\DS\\DS14\\index.txt", "D:\\study\\C++\\DS\\DS14\\index.out");

}

