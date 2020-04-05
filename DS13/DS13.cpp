// DS13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "CompleteWinnerTree.h"
#include "DS13_Applications.h"
#include "FullWinnerTree.h"
#include "CompleteWinnerTree2.h"
#include "CompleteWinnerTree3.h"
#include "CompleteWinnerTree4.h"
#include "CompleteLoserTree.h"
#include "FullLoserTree.h"
#include "CompleteLoserTree2.h"
#include "../DS12/DS12_Application.h"

int main()
{
    std::cout << "Exercise 1" << std::endl;
    int players1[] = {0, 3, 5, 6, 7, 20, 8, 2, 9};
    int count1 = sizeof(players1) / sizeof(int) - 1;
    CompleteWinnerTree<int> cwt1(players1,count1, true);
    std::cout << "Smallest is: " << cwt1.winner() << std::endl;
    players1[5] = 1;
    cwt1.rePlay(5);
    std::cout << "After replace 20 with 1 smallest is: " << cwt1.winner() << std::endl;
    players1[5] = 20;
    CompleteWinnerTree<int> cwt1_2(players1, count1, false);
    std::cout << "Largest is: " << cwt1_2.winner() << std::endl;
    players1[5] = 1;
    cwt1_2.rePlay(5);
    std::cout << "After replace 20 with 1 largest is: " << cwt1_2.winner() << std::endl;

    std::cout << "Exercise 2" << std::endl;
    int players2[] = { 0, 20, 10, 12, 18, 30, 16, 35, 33, 45, 7, 15, 19, 33, 11, 17, 25 };
    int count2 = sizeof(players2) / sizeof(int) - 1;
    CompleteWinnerTree<int> cwt2(players2, count2, true);
    std::cout << "Smallest is: " << cwt2.winner() << std::endl;
    players2[15] = 42;
    cwt2.rePlay(15);
    std::cout << "After replace 17 with 42 smallest is: " << cwt2.winner() << std::endl;
    players2[15] = 17;
    CompleteWinnerTree<int> cwt2_2(players2, count2, false);
    std::cout << "Largest is: " << cwt2_2.winner() << std::endl;
    players2[15] = 42;
    cwt2_2.rePlay(15);
    std::cout << "After replace 17 with 42 largest is: " << cwt2_2.winner() << std::endl;

    std::cout << "Exercise 3" << std::endl;
    int players3[] = { 0, 3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17 };
    int count3 = sizeof(players3) / sizeof(int) - 1;
    CompleteWinnerTree<int> cwt3(players3, count3, true);
    std::cout << "Smallest is: " << cwt3.winner() << std::endl;
    players3[7] = 11;
    cwt3.rePlay(7);
    std::cout << "After replace 2 with 11 smallest is: " << cwt3.winner() << std::endl;
    players3[7] = 2;
    CompleteWinnerTree<int> cwt3_2(players3, count3, false);
    std::cout << "Largest is: " << cwt3_2.winner() << std::endl;
    players3[7] = 11;
    cwt3_2.rePlay(7);
    std::cout << "After replace 2 with 11 largest is: " << cwt3_2.winner() << std::endl;

    std::cout << "Exercise 4" << std::endl;
    int players4[] = { 0, 10, 2, 7, 6, 5, 9, 12, 35, 22, 15, 1, 3, 4 };
    int count4 = sizeof(players4) / sizeof(int) - 1;
    CompleteWinnerTree<int> cwt4(players4, count4, true);
    std::cout << "Smallest is: " << cwt4.winner() << std::endl;
    players4[6] = 0;
    cwt4.rePlay(6);
    std::cout << "After replace 9 with 0 smallest is: " << cwt4.winner() << std::endl;
    players4[6] = 9;
    CompleteWinnerTree<int> cwt4_2(players4, count4, false);
    std::cout << "Largest is: " << cwt4_2.winner() << std::endl;
    players4[6] = 0;
    cwt4_2.rePlay(6);
    std::cout << "After replace 9 with 0 largest is: " << cwt4_2.winner() << std::endl;

    std::cout << "Exercise 8" << std::endl;
    winnerTreeSort(players1, count1);
    winnerTreeSort(players2, count2);
    winnerTreeSort(players3, count3);
    winnerTreeSort(players4, count4);

    std::cout << "Exercise 10" << std::endl;
    int players10_1[] = { 0, 3, 5, 6, 7, 20, 8, 2, 9 };
    int count10_1 = sizeof(players10_1) / sizeof(int) - 1;
    FullWinnerTree<int> cwt10_1(players10_1, count10_1, true);
    std::cout << "Smallest is: " << cwt10_1.winner() << std::endl;
    players10_1[5] = 1;
    cwt10_1.rePlay(5);
    std::cout << "After replace 20 with 1 smallest is: " << cwt10_1.winner() << std::endl;
    players10_1[5] = 20;
    FullWinnerTree<int> cwt10_1_2(players10_1, count10_1, false);
    std::cout << "Largest is: " << cwt10_1_2.winner() << std::endl;
    players10_1[5] = 1;
    cwt10_1_2.rePlay(5);
    std::cout << "After replace 20 with 1 largest is: " << cwt10_1_2.winner() << std::endl;

    std::cout << "Exercise 10_2" << std::endl;
    int players10_2[] = { 0, 20, 10, 12, 18, 30, 16, 35, 33, 45, 7, 15, 19, 33, 11, 17, 25 };
    int count10_2 = sizeof(players10_2) / sizeof(int) - 1;
    FullWinnerTree<int> cwt10_2(players10_2, count10_2, true);
    std::cout << "Smallest is: " << cwt10_2.winner() << std::endl;
    players10_2[15] = 42;
    cwt10_2.rePlay(15);
    std::cout << "After replace 17 with 42 smallest is: " << cwt10_2.winner() << std::endl;
    players10_2[15] = 17;
    FullWinnerTree<int> cwt10_2_2(players10_2, count10_2, false);
    std::cout << "Largest is: " << cwt10_2_2.winner() << std::endl;
    players10_2[15] = 42;
    cwt10_2_2.rePlay(15);
    std::cout << "After replace 17 with 42 largest is: " << cwt10_2_2.winner() << std::endl;

    std::cout << "Exercise 11" << std::endl;
    int players11_1[] = { 0, 3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17 };
    int count11_1 = sizeof(players11_1) / sizeof(int) - 1;
    CompleteWinnerTree2<int> cwt11_1(players11_1, count11_1, true);
    std::cout << "Smallest is: " << cwt11_1.winner() << std::endl;
    players11_1[7] = 11;
    cwt11_1.rePlay(7);
    std::cout << "After replace 2 with 11 smallest is: " << cwt11_1.winner() << std::endl;
    players11_1[7] = 2;
    CompleteWinnerTree2<int> cwt11_1_2(players11_1, count11_1, false);
    std::cout << "Largest is: " << cwt11_1_2.winner() << std::endl;
    players11_1[7] = 11;
    cwt11_1_2.rePlay(7);
    std::cout << "After replace 2 with 11 largest is: " << cwt11_1_2.winner() << std::endl;

    std::cout << "Exercise 11_2" << std::endl;
    int players11_2[] = { 0, 10, 2, 7, 6, 5, 9, 12, 35, 22, 15, 1, 3, 4 };
    int count11_2 = sizeof(players11_2) / sizeof(int) - 1;
    CompleteWinnerTree2<int> cwt11_2(players11_2, count11_2, true);
    std::cout << "Smallest is: " << cwt11_2.winner() << std::endl;
    players11_2[6] = 0;
    cwt11_2.rePlay(6);
    std::cout << "After replace 9 with 0 smallest is: " << cwt11_2.winner() << std::endl;
    players11_2[6] = 9;
    CompleteWinnerTree2<int> cwt11_2_2(players11_2, count11_2, false);
    std::cout << "Largest is: " << cwt11_2_2.winner() << std::endl;
    players11_2[6] = 0;
    cwt11_2_2.rePlay(6);
    std::cout << "After replace 9 with 0 largest is: " << cwt11_2_2.winner() << std::endl;

    std::cout << "Exercise 12_1" << std::endl;
    int players12_1[] = { 0, 3, 5, 6, 7, 20, 8, 2, 9 };
    int count12_1 = sizeof(players12_1) / sizeof(int) - 1;
    CompleteWinnerTree3<int> cwt12_1(players12_1, count12_1, true);
    std::cout << "Smallest is: " << cwt12_1.winner() << std::endl;
    players12_1[5] = 1;
    cwt12_1.rePlay(5);
    std::cout << "After replace 20 with 1 smallest is: " << cwt12_1.winner() << std::endl;
    players12_1[5] = 20;
    CompleteWinnerTree3<int> cwt12_1_2(players12_1, count12_1, false);
    std::cout << "Largest is: " << cwt12_1_2.winner() << std::endl;
    players12_1[5] = 1;
    cwt12_1_2.rePlay(5);
    std::cout << "After replace 20 with 1 largest is: " << cwt12_1_2.winner() << std::endl;

    std::cout << "Exercise 12_2" << std::endl;
    int players12_2[] = { 0, 20, 10, 12, 18, 30, 16, 35, 33, 45, 7, 15, 19, 33, 11, 17, 25 };
    int count12_2 = sizeof(players12_2) / sizeof(int) - 1;
    CompleteWinnerTree3<int> cwt12_2(players12_2, count12_2, true);
    std::cout << "Smallest is: " << cwt12_2.winner() << std::endl;
    players12_2[15] = 42;
    cwt12_2.rePlay(15);
    std::cout << "After replace 17 with 42 smallest is: " << cwt12_2.winner() << std::endl;
    players12_2[15] = 17;
    CompleteWinnerTree3<int> cwt12_2_2(players12_2, count12_2, false);
    std::cout << "Largest is: " << cwt12_2_2.winner() << std::endl;
    players12_2[15] = 42;
    cwt12_2_2.rePlay(15);
    std::cout << "After replace 17 with 42 largest is: " << cwt12_2_2.winner() << std::endl;

    std::cout << "Exercise 12_3" << std::endl;
    int players12_3[] = { 0, 3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17 };
    int count12_3 = sizeof(players12_3) / sizeof(int) - 1;
    CompleteWinnerTree3<int> cwt12_3(players12_3, count12_3, true);
    std::cout << "Smallest is: " << cwt12_3.winner() << std::endl;
    players12_3[7] = 11;
    cwt12_3.rePlay(7);
    std::cout << "After replace 2 with 11 smallest is: " << cwt12_3.winner() << std::endl;
    players12_3[7] = 2;
    CompleteWinnerTree3<int> cwt12_3_2(players12_3, count12_3, false);
    std::cout << "Largest is: " << cwt12_3_2.winner() << std::endl;
    players12_3[7] = 11;
    cwt12_3_2.rePlay(7);
    std::cout << "After replace 2 with 11 largest is: " << cwt12_3_2.winner() << std::endl;

    std::cout << "Exercise 12_4" << std::endl;
    int players12_4[] = { 0, 10, 2, 7, 6, 5, 9, 12, 35, 22, 15, 1, 3, 4 };
    int count12_4 = sizeof(players12_4) / sizeof(int) - 1;
    CompleteWinnerTree3<int> cwt12_4(players12_4, count12_4, true);
    std::cout << "Smallest is: " << cwt12_4.winner() << std::endl;
    players12_4[6] = 0;
    cwt12_4.rePlay(6);
    std::cout << "After replace 9 with 0 smallest is: " << cwt12_4.winner() << std::endl;
    players12_4[6] = 9;
    CompleteWinnerTree3<int> cwt12_4_2(players12_4, count12_4, false);
    std::cout << "Largest is: " << cwt12_4_2.winner() << std::endl;
    players12_4[6] = 0;
    cwt12_4_2.rePlay(6);
    std::cout << "After replace 9 with 0 largest is: " << cwt12_4_2.winner() << std::endl;

    std::cout << "Exercise 13_1" << std::endl;
    int players13_1[] = { 0, 3, 5, 6, 7, 20, 8, 2, 9 };
    int count13_1 = sizeof(players13_1) / sizeof(int) - 1;
    CompleteWinnerTree4<int> cwt13_1(players13_1, count13_1, true);
    std::cout << "Smallest is: " << cwt13_1.winner() << std::endl;
    players13_1[5] = 1;
    cwt13_1.rePlay(5);
    std::cout << "After replace 20 with 1 smallest is: " << cwt13_1.winner() << std::endl;
    players13_1[5] = 20;
    CompleteWinnerTree4<int> cwt13_1_2(players13_1, count13_1, false);
    std::cout << "Largest is: " << cwt13_1_2.winner() << std::endl;
    players13_1[5] = 1;
    cwt13_1_2.rePlay(5);
    std::cout << "After replace 20 with 1 largest is: " << cwt13_1_2.winner() << std::endl;

    std::cout << "Exercise 13_2" << std::endl;
    int players13_2[] = { 0, 20, 10, 12, 18, 30, 16, 35, 33, 45, 7, 15, 19, 33, 11, 17, 25 };
    int count13_2 = sizeof(players13_2) / sizeof(int) - 1;
    CompleteWinnerTree4<int> cwt13_2(players13_2, count13_2, true);
    std::cout << "Smallest is: " << cwt13_2.winner() << std::endl;
    players13_2[15] = 42;
    cwt13_2.rePlay(15);
    std::cout << "After replace 17 with 42 smallest is: " << cwt13_2.winner() << std::endl;
    players13_2[15] = 17;
    CompleteWinnerTree4<int> cwt13_2_2(players13_2, count13_2, false);
    std::cout << "Largest is: " << cwt13_2_2.winner() << std::endl;
    players13_2[15] = 42;
    cwt13_2_2.rePlay(15);
    std::cout << "After replace 17 with 42 largest is: " << cwt13_2_2.winner() << std::endl;

    std::cout << "Exercise 13_3" << std::endl;
    int players13_3[] = { 0, 3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17 };
    int count13_3 = sizeof(players13_3) / sizeof(int) - 1;
    CompleteWinnerTree4<int> cwt13_3(players13_3, count13_3, true);
    std::cout << "Smallest is: " << cwt13_3.winner() << std::endl;
    players13_3[7] = 11;
    cwt13_3.rePlay(7);
    std::cout << "After replace 2 with 11 smallest is: " << cwt13_3.winner() << std::endl;
    players13_3[7] = 2;
    CompleteWinnerTree4<int> cwt13_3_2(players13_3, count13_3, false);
    std::cout << "Largest is: " << cwt13_3_2.winner() << std::endl;
    players13_3[7] = 11;
    cwt13_3_2.rePlay(7);
    std::cout << "After replace 2 with 11 largest is: " << cwt13_3_2.winner() << std::endl;

    std::cout << "Exercise 13_4" << std::endl;
    int players13_4[] = { 0, 10, 2, 7, 6, 5, 9, 12, 35, 22, 15, 1, 3, 4 };
    int count13_4 = sizeof(players13_4) / sizeof(int) - 1;
    CompleteWinnerTree4<int> cwt13_4(players13_4, count13_4, true);
    std::cout << "Smallest is: " << cwt13_4.winner() << std::endl;
    players13_4[6] = 0;
    cwt13_4.rePlay(6);
    std::cout << "After replace 9 with 0 smallest is: " << cwt13_4.winner() << std::endl;
    players13_4[6] = 9;
    CompleteWinnerTree4<int> cwt13_4_2(players13_4, count13_4, false);
    std::cout << "Largest is: " << cwt13_4_2.winner() << std::endl;
    players13_4[6] = 0;
    cwt13_4_2.rePlay(6);
    std::cout << "After replace 9 with 0 largest is: " << cwt13_4_2.winner() << std::endl;

    std::cout << "Exercise 14" << std::endl;
    int players14[] = { 0, 3, 5, 6, 7, 20, 8, 2, 9 };
    int count14 = sizeof(players14) / sizeof(int) - 1;
    CompleteLoserTree<int> clt14(players14, count14, true);
    std::cout << "Smallest is: " << clt14.winner() << std::endl;
    players14[7] = 4;
    clt14.rePlay();
    std::cout << "After replace 2 with 4 smallest is: " << clt14.winner() << std::endl;
    players14[7] = 2;
    CompleteLoserTree<int> clt14_2(players14, count14, false);
    std::cout << "Largest is: " << clt14_2.winner() << std::endl;
    players14[5] = 10;
    clt14_2.rePlay();
    std::cout << "After replace 20 with 10 largest is: " << clt14_2.winner() << std::endl;

    std::cout << "Exercise 15" << std::endl;
    int players15[] = { 0, 20, 10, 12, 18, 30, 16, 35, 33, 45, 7, 15, 19, 33, 11, 17, 25 };
    int count15 = sizeof(players15) / sizeof(int) - 1;
    CompleteLoserTree<int> clt15(players15, count15, true);
    std::cout << "Smallest is: " << clt15.winner() << std::endl;
    players15[10] = 12;
    clt15.rePlay();
    std::cout << "After replace 7 with 12 smallest is: " << clt15.winner() << std::endl;
    players15[10] = 7;
    CompleteLoserTree<int> clt15_2(players15, count15, false);
    std::cout << "Largest is: " << clt15_2.winner() << std::endl;
    players15[9] = 34;
    clt15_2.rePlay();
    std::cout << "After replace 45 with 34 largest is: " << clt15_2.winner() << std::endl;

    std::cout << "Exercise 16" << std::endl;
    int players16[] = { 0, 20, 10, 12, 14, 9, 11, 30, 33, 25, 7, 15 };
    int count16 = sizeof(players16) / sizeof(int) - 1;
    CompleteLoserTree<int> clt16(players16, count16, true);
    std::cout << "Smallest is: " << clt16.winner() << std::endl;
    players16[10] = 16;
    clt16.rePlay();
    std::cout << "After replace 7 with 16 smallest is: " << clt16.winner() << std::endl;
    players16[10] = 7;
    CompleteLoserTree<int> clt16_2(players16, count16, false);
    std::cout << "Largest is: " << clt16_2.winner() << std::endl;
    players16[8] = 5;
    clt16_2.rePlay();
    std::cout << "After replace 33 with 5 largest is: " << clt16_2.winner() << std::endl;

    std::cout << "Exercise 17" << std::endl;
    int players17[] = { 0, 3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17 };
    int count17 = sizeof(players17) / sizeof(int) - 1;
    CompleteLoserTree<int> clt17(players17, count17, true);
    std::cout << "Smallest is: " << clt17.winner() << std::endl;
    players17[7] = 14;
    clt17.rePlay();
    std::cout << "After replace 2 with 14 smallest is: " << clt17.winner() << std::endl;
    players17[7] = 2;
    CompleteLoserTree<int> clt17_2(players17, count17, false);
    std::cout << "Largest is: " << clt17_2.winner() << std::endl;
    players17[11] = 19;
    clt17_2.rePlay();
    std::cout << "After replace 30 with 19 largest is: " << clt17_2.winner() << std::endl;

    std::cout << "Exercise 18" << std::endl;
    int players18[] = { 0, 10, 2, 7, 6, 5, 9, 12, 35, 22, 15, 1, 3, 4 };
    int count18 = sizeof(players18) / sizeof(int) - 1;
    CompleteLoserTree<int> clt18(players18, count18, true);
    std::cout << "Smallest is: " << clt18.winner() << std::endl;
    players18[11] = 11;
    clt18.rePlay();
    std::cout << "After replace 1 with 11 smallest is: " << clt18.winner() << std::endl;
    players18[11] = 1;
    CompleteLoserTree<int> clt18_2(players18, count18, false);
    std::cout << "Largest is: " << clt18_2.winner() << std::endl;
    players18[8] = 8;
    clt18_2.rePlay();
    std::cout << "After replace 35 with 8 largest is: " << clt18_2.winner() << std::endl;

    std::cout << "Exercise 20" << std::endl;
    int players20_1[] = { 0, 3, 5, 6, 7, 20, 8, 2, 9 };
    int count20_1 = sizeof(players20_1) / sizeof(int) - 1;
    FullLoserTree<int> flt20_1(players20_1, count20_1, true);
    std::cout << "Smallest is: " << flt20_1.winner() << std::endl;
    players20_1[7] = 4;
    flt20_1.rePlay();
    std::cout << "After replace 2 with 4 smallest is: " << flt20_1.winner() << std::endl;
    players20_1[7] = 2;
    FullLoserTree<int> flt20_1_2(players20_1, count20_1, false);
    std::cout << "Largest is: " << flt20_1_2.winner() << std::endl;
    players20_1[5] = 10;
    flt20_1_2.rePlay();
    std::cout << "After replace 20 with 10 largest is: " << flt20_1_2.winner() << std::endl;

    std::cout << "Exercise 20_2" << std::endl;
    int players20_2[] = { 0, 20, 10, 12, 18, 30, 16, 35, 33, 45, 7, 15, 19, 33, 11, 17, 25 };
    int count20_2 = sizeof(players20_2) / sizeof(int) - 1;
    FullLoserTree<int> flt20_2(players20_2, count20_2, true);
    std::cout << "Smallest is: " << flt20_2.winner() << std::endl;
    players20_2[10] = 12;
    flt20_2.rePlay();
    std::cout << "After replace 7 with 12 smallest is: " << flt20_2.winner() << std::endl;
    players20_2[15] = 7;
    FullLoserTree<int> flt20_2_2(players20_2, count20_2, false);
    std::cout << "Largest is: " << flt20_2_2.winner() << std::endl;
    players20_2[9] = 34;
    flt20_2_2.rePlay();
    std::cout << "After replace 45 with 34 largest is: " << flt20_2_2.winner() << std::endl;

    std::cout << "Exercise 21_1" << std::endl;
    int players21_1[] = { 0, 3, 5, 6, 7, 20, 8, 2, 9 };
    int count21_1 = sizeof(players21_1) / sizeof(int) - 1;
    CompleteLoserTree2<int> clt21_1(players21_1, count21_1, true);
    std::cout << "Smallest is: " << clt21_1.winner() << std::endl;
    players21_1[7] = 4;
    clt21_1.rePlay();
    std::cout << "After replace 2 with 4 smallest is: " << clt21_1.winner() << std::endl;
    players21_1[7] = 2;
    CompleteLoserTree2<int> clt21_1_2(players21_1, count21_1, false);
    std::cout << "Largest is: " << clt21_1_2.winner() << std::endl;
    players21_1[5] = 10;
    clt21_1_2.rePlay();
    std::cout << "After replace 20 with 10 largest is: " << clt21_1_2.winner() << std::endl;

    std::cout << "Exercise 21_2" << std::endl;
    int players21_2[] = { 0, 20, 10, 12, 18, 30, 16, 35, 33, 45, 7, 15, 19, 33, 11, 17, 25 };
    int count21_2 = sizeof(players21_2) / sizeof(int) - 1;
    CompleteLoserTree2<int> clt21_2(players21_2, count21_2, true);
    std::cout << "Smallest is: " << clt21_2.winner() << std::endl;
    players21_2[10] = 12;
    clt21_2.rePlay();
    std::cout << "After replace 7 with 12 smallest is: " << clt21_2.winner() << std::endl;
    players21_2[10] = 7;
    CompleteLoserTree2<int> clt21_2_2(players21_2, count21_2, false);
    std::cout << "Largest is: " << clt21_2_2.winner() << std::endl;
    players21_2[9] = 34;
    clt21_2_2.rePlay();
    std::cout << "After replace 45 with 34 largest is: " << clt21_2_2.winner() << std::endl;

    std::cout << "Exercise 21_3" << std::endl;
    int players21_3[] = { 0, 20, 10, 12, 14, 9, 11, 30, 33, 25, 7, 15 };
    int count21_3 = sizeof(players21_3) / sizeof(int) - 1;
    CompleteLoserTree2<int> clt21_3(players21_3, count21_3, true);
    std::cout << "Smallest is: " << clt21_3.winner() << std::endl;
    players21_3[10] = 16;
    clt21_3.rePlay();
    std::cout << "After replace 7 with 16 smallest is: " << clt21_3.winner() << std::endl;
    players21_3[10] = 7;
    CompleteLoserTree2<int> clt21_3_2(players21_3, count21_3, false);
    std::cout << "Largest is: " << clt21_3_2.winner() << std::endl;
    players21_3[8] = 5;
    clt21_3_2.rePlay();
    std::cout << "After replace 33 with 5 largest is: " << clt21_3_2.winner() << std::endl;

    std::cout << "Exercise 21_4" << std::endl;
    int players21_4[] = { 0, 3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17 };
    int count21_4 = sizeof(players21_4) / sizeof(int) - 1;
    CompleteLoserTree2<int> clt21_4(players21_4, count21_4, true);
    std::cout << "Smallest is: " << clt21_4.winner() << std::endl;
    players21_4[7] = 14;
    clt21_4.rePlay();
    std::cout << "After replace 2 with 14 smallest is: " << clt21_4.winner() << std::endl;
    players21_4[7] = 2;
    CompleteLoserTree2<int> clt21_4_2(players21_4, count21_4, false);
    std::cout << "Largest is: " << clt21_4_2.winner() << std::endl;
    players21_4[11] = 19;
    clt21_4_2.rePlay();
    std::cout << "After replace 30 with 19 largest is: " << clt21_4_2.winner() << std::endl;

    std::cout << "Exercise 21_5" << std::endl;
    int players21_5[] = { 0, 10, 2, 7, 6, 5, 9, 12, 35, 22, 15, 1, 3, 4 };
    int count21_5 = sizeof(players21_5) / sizeof(int) - 1;
    CompleteLoserTree2<int> clt21_5(players21_5, count21_5, true);
    std::cout << "Smallest is: " << clt21_5.winner() << std::endl;
    players21_5[11] = 11;
    clt21_5.rePlay();
    std::cout << "After replace 1 with 11 smallest is: " << clt21_5.winner() << std::endl;
    players21_5[11] = 1;
    CompleteLoserTree2<int> clt21_5_2(players21_5, count21_5, false);
    std::cout << "Largest is: " << clt21_5_2.winner() << std::endl;
    players21_5[8] = 8;
    clt21_5_2.rePlay();
    std::cout << "After replace 35 with 8 largest is: " << clt21_5_2.winner() << std::endl;

    std::cout << "Exercise 22" << std::endl;
    winnerTreeSort(players21_1, count21_1);
    winnerTreeSort(players21_2, count21_2);
    winnerTreeSort(players21_3, count21_3);
    winnerTreeSort(players21_4, count21_4);
    winnerTreeSort(players21_5, count21_5);

    std::cout << "First Fit Pack" << std::endl;
    int bin1[] = {0, 3, 5, 2, 4 };
    int countffp = sizeof(bin1) / sizeof(int) - 1;
    firstFitPack(bin1, countffp, 7);
 
    std::cout << "Exercise 23" << std::endl;
    int bin23[] = {0, 6, 1, 4, 4, 5 };
    int count23 = sizeof(bin23) / sizeof(int) - 1;
    firstFitPack(bin23, count23, 10);

    std::cout << "Exercise 25_1" << std::endl;
    int bin25_1[] = { 0, 3, 5, 2, 4 };
    int count25_1 = sizeof(bin25_1) / sizeof(int) - 1;
    firstFitPack2(bin25_1, count25_1, 7);

    std::cout << "Exercise 25_2" << std::endl;
    int bin25_2[] = { 0, 6, 1, 4, 4, 5 };
    int count25_2 = sizeof(bin25_2) / sizeof(int) - 1;
    firstFitPack2(bin25_2, count25_2, 10);

    //std::cout << "Exercise 25_3" << std::endl;
    //int n25 = 100;
    //TestPacking tp25(n25);
    //std::cout << "First Fit: ";
    //tp25.test(FIRST_FIT);
    //std::cout << "First Fit2: ";
    //tp25.test(FIRST_FIT2);

    std::cout << "Exercise 26_1" << std::endl;
    int bin26_1[] = { 0, 3, 5, 2, 4 };
    int count26_1 = sizeof(bin26_1) / sizeof(int) - 1;
    firstFitPack3(bin26_1, count26_1, 7);

    std::cout << "Exercise 26_2" << std::endl;
    int bin26_2[] = { 0, 6, 1, 4, 4, 5 };
    int count26_2 = sizeof(bin26_2) / sizeof(int) - 1;
    firstFitPack3(bin26_2, count26_2, 10);

    std::cout << "Exercise 28_1_1 firstFitDecreasingPack" << std::endl;
    int bin28_1_1[] = { 0, 3, 5, 2, 4 };
    int count28_1_1 = sizeof(bin28_1_1) / sizeof(int) - 1;
    firstFitDecreasingPack(bin28_1_1, count28_1_1, 7);

    std::cout << "Exercise 28_1_2 firstFitDecreasingPack" << std::endl;
    int bin28_1_2[] = { 0, 6, 1, 4, 4, 5 };
    int count28_1_2 = sizeof(bin28_1_2) / sizeof(int) - 1;
    firstFitDecreasingPack(bin28_1_2, count28_1_2, 10);

    std::cout << "Exercise 28_2_1 worstFitDecreasingPack" << std::endl;
    ItemNode bin28_2_1[] = { {1,3}, {2,5}, {3,2}, {4,4} };
    int count28_2_1 = sizeof(bin28_2_1) / sizeof(ItemNode);
    packItems(bin28_2_1, count28_2_1, 3, 7);

    std::cout << "Exercise 28_2_2 worstFitDecreasingPack" << std::endl;
    ItemNode bin28_2_2[] = { {1,6}, {2,1}, {3,4}, {4,4}, {5,5} };
    int count28_2_2 = sizeof(bin28_2_2) / sizeof(ItemNode);
    packItems(bin28_2_2, count28_2_2, 3, 10);

    std::cout << "Exercise 29_1 nextFitPack" << std::endl;
    int bin28_3_1[] = { 0, 3, 5, 2, 4 };
    int count28_3_1 = sizeof(bin28_3_1) / sizeof(int) - 1;
    nextFitPack(bin28_3_1, count28_3_1, 7);

    std::cout << "Exercise 29_2 nextFitPack" << std::endl;
    int bin28_3_2[] = { 0, 6, 1, 4, 4, 5 };
    int count28_3_2 = sizeof(bin28_3_2) / sizeof(int) - 1;
    nextFitPack(bin28_3_2, count28_3_2, 10);

    std::cout << "Exercise 28" << std::endl;
    int n28 = 100;
    TestPacking tp28(n28);
    std::cout << "Worst Fit: ";
    tp28.test(WORST_FIT);
    std::cout << "First Fit: ";
    tp28.test(FIRST_FIT);
    std::cout << "First Fit Decreasing: ";
    tp28.test(FIRST_FIT_DECREASING);
    std::cout << "Next Fit: ";
    tp28.test(NEXT_FIT);
    std::cout << "Next Fit: ";
    tp28.test(RIGHT_FIT);

    std::cout << "Exercise 30_1" << std::endl;
    int bin30_1[] = { 0, 3, 5, 2, 4 };
    int count30_1 = sizeof(bin30_1) / sizeof(int) - 1;
    rightFitPack(bin30_1, count30_1, 7);

    std::cout << "Exercise 30_2" << std::endl;
    int bin30_2[] = { 0, 6, 1, 4, 4, 5 };
    int count30_2 = sizeof(bin30_2) / sizeof(int) - 1;
    rightFitPack(bin30_2, count30_2, 10);
}

