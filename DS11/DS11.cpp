// DS11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include "ListBinaryTree.h"
#include "ChainBinaryTree.h"
#include "ExpressTree.h"
#include "LinkedBinaryTree.h"
#include "Expression.h"
#include "DistributionTree.h"
#include "FlatSetTree.h"
#include "SetTree.h"
#include "TestSetTree.h"
int tolerance = 8;
int main()
{
    //std::cout << "Exercise 20" << std::endl;
    //ListBinaryTree<std::string> lbt20(3);
    //std::string s20{"1 A 2 B 3 C 5 D 7 E"};
    //std::istringstream iss20(s20);
    //lbt20.input(iss20);
    //lbt20.output(std::cout, TRAVERSE_ORDER::PREFIX);
    //std::cout << std::endl;
    //std::cout << "Exercise 21" << std::endl;
    //lbt20.output(std::cout, TRAVERSE_ORDER::INFIX);
    //std::cout << std::endl;
    //std::cout << "Exercise 22" << std::endl;
    //lbt20.output(std::cout, TRAVERSE_ORDER::POSTFIX);
    //std::cout << std::endl;
    //std::cout << "Exercise 23" << std::endl;
    //lbt20.output(std::cout, TRAVERSE_ORDER::LEVEL);
    //std::cout << std::endl;

    // std::cout << "Exercise 24" << std::endl;
    //ListBinaryTree<std::string> lbt24(lbt20);
    //lbt24.output(std::cout, TRAVERSE_ORDER::LEVEL);
    //std::cout << std::endl;

    //std::cout << "Chain BinaryTree" << std::endl;
    //ChainBinaryTree<std::string> cbt;
    //std::string s_cbt = s20;
    //std::istringstream iss_cbt(s_cbt);
    //cbt.input(iss_cbt);
    //cbt.output(std::cout, TRAVERSE_ORDER::PREFIX);
    //std::cout << std::endl;
    //cbt.output(std::cout, TRAVERSE_ORDER::INFIX);
    //std::cout << std::endl;
    //cbt.output(std::cout, TRAVERSE_ORDER::POSTFIX);
    //std::cout << std::endl;
    //cbt.output(std::cout, TRAVERSE_ORDER::LEVEL);
    //std::cout << std::endl;

    //std::cout << "Exercise 25" << std::endl;
    //ChainBinaryTree<std::string> cbt25_1(cbt);
    //cbt25_1.output(std::cout, TRAVERSE_ORDER::LEVEL);
    //std::cout << std::endl;
    //ChainBinaryTree<std::string> cbt25_2(cbt, TRAVERSE_ORDER::POSTFIX);
    //cbt25_2.output(std::cout, TRAVERSE_ORDER::LEVEL);
    //std::cout << std::endl;

    //std::cout << "Exercise 26" << std::endl;
    //ExpressTree<std::string> et;
    //std::string s26 = "1 + 2 - 3 + 4 - 5 * 6 + 7 * 9 1 10 2 11 3 12 4 13 5 14 / 15 6 28 7 29 8";
    ////std::string s26 = "1 1";
    ////std::string s26 = "1 - 3 1";
    ////std::string s26 = "1 / 2 7 3 8";
    //std::istringstream iss26(s26);
    //et.input(iss26);
    //et.output(std::cout, TRAVERSE_ORDER::POSTFIX);
    //std::cout << std::endl;
    //std::cout << et.calValue() << std::endl;

    //std::cout << "Exercise 27" << std::endl;
    //std::cout << et.Height() << std::endl;

    //std::cout << "Exercise 28" << std::endl;
    //std::cout << et.countNode() << std::endl;

    //std::cout << "Exercise 29" << std::endl;
    //std::cout << et.levelWithMostnodes() << std::endl;
    //
    //auto func = [](const std::string& s) {std::cout << s << " "; };
    //std::cout << "Exercise 30" << std::endl;
    //cbt.output(std::cout, TRAVERSE_ORDER::INFIX);
    //std::cout << std::endl;
    //cbt.inOrderNoRecursive(func);
    //std::cout << std::endl;

    //std::cout << "Exercise 31" << std::endl;
    //cbt.output(std::cout, TRAVERSE_ORDER::PREFIX);
    //std::cout << std::endl;
    //cbt.preOrderNoRecursive(func);
    //std::cout << std::endl;

    //std::cout << "Exercise 32" << std::endl;
    //cbt.output(std::cout, TRAVERSE_ORDER::POSTFIX);
    //std::cout << std::endl;
    //cbt.postOrderNoRecursive(func);
    //std::cout << std::endl;

    //std::cout << "Exercise 33" << std::endl;
    ////std::string s33Pre = "abcdefgh";
    ////std::string s33In = "cdbagfeh";
    //std::string s33Pre = "abcdefghijkl";
    //std::string s33In = "aefdcgihjklb";
    //ChainBinaryTree<std::string> cbt33;
    //cbt33.createTreePreAndInOrder(s33Pre, s33In);
    //cbt33.output(std::cout, TRAVERSE_ORDER::PREFIX);
    //std::cout << std::endl;
    //cbt33.output(std::cout, TRAVERSE_ORDER::INFIX);
    //std::cout << std::endl;

    //std::cout << "Exercise 34" << std::endl;
    //std::string s34Pre = "abcdefgh";
    //std::string s34Post = "dcbgfhea";
    //ChainBinaryTree<std::string> cbt34;
    //cbt34.createTreePreAndPostOrder(s34Pre, s34Post);
    //cbt34.output(std::cout, TRAVERSE_ORDER::PREFIX);
    //std::cout << std::endl;
    //cbt34.output(std::cout, TRAVERSE_ORDER::POSTFIX);
    //std::cout << std::endl;

    //std::cout << "Exercise 35" << std::endl;
    ////std::string s35Post = "abcdefgh";
    ////std::string s35In = "aedbchgf";
    //std::string s35Post = "abcdefghijkl";
    //std::string s35In = "backdejifghl";
    //ChainBinaryTree<std::string> cbt35;
    //cbt35.createTreePostAndInOrder(s35Post, s35In);
    //cbt35.output(std::cout, TRAVERSE_ORDER::POSTFIX);
    //std::cout << std::endl;
    //cbt35.output(std::cout, TRAVERSE_ORDER::INFIX);
    //std::cout << std::endl;

    //std::cout << "Exercise 36" << std::endl;
    //std::string s36 = "a b + c d - / e + g h * a / +";
    ////std::string s36 = "x - y z * - a b + c d / e * + +";
    ////std::string s36 = "a b + c e - > a b < x y < y z > || && ||";
    //ExpressTree<std::string> et36(s36, POSTFIX);
    //et36.output(std::cout, TRAVERSE_ORDER::POSTFIX);
    //std::cout << std::endl;

    //std::cout << "Exercise 37" << std::endl;
    //std::string s37 = "+ + / + a b - c d e / * g h a";
    ////std::string s37 = "+ - - x * y z + + a b * / c d e";
    ////std::string s37 = "|| > + a b - c e && < a b || < x y > y z";
    //ExpressTree<std::string> et37(s37, PREFIX);
    //et37.output(std::cout, TRAVERSE_ORDER::PREFIX);
    //std::cout << std::endl;

    //std::cout << "Exercise 38" << std::endl;
    ////std::cout << et36.toParenInOrder() << std::endl;
    //std::cout << postExprToParenInOrder(s36) << std::endl;
    //std::cout << std::endl;

    //std::cout << "Exercise 39" << std::endl;
    ////std::cout << et37.toParenInOrder() << std::endl;
    //std::cout << preExprToParenInOrder(s37) << std::endl;
    //std::cout << std::endl;

    //std::cout << "Exercise 40" << std::endl;
    ////std::string s40 = "(a+b)/(c-d)+e+g*h/a";
    ////std::string s40 = "-x-y*z+(a+b+c/d*e)";
    //std::string s40 = "((a+b)>(c-e))||a<b&&(x<y||y>z)";
    //std::cout << parenInExprToPostOrder(s40) << std::endl;
    //std::cout << std::endl;

    //std::cout << "Exercise 41" << std::endl;
    //std::cout << parenInExprToPreOrder(s40) << std::endl;
    //std::cout << std::endl;

    //std::cout << "Exercise 42" << std::endl;
    //ExpressTree<std::string> et42(s40, INFIX);
    //et42.output(std::cout, TRAVERSE_ORDER::PREFIX);
    //std::cout << std::endl;

    //std::cout << "Exercise 43" << std::endl;
    //std::string s43 = "1 - 2 3 * - 4 5 + 7 8 / 6 * + +";
    //std::cout << calPostOrderExpr(s43) << std::endl;
    //std::cout << std::endl;

    //std::cout << "LinkedBinaryTree" << std::endl;
    LinkedBinaryTree<std::string> lbt;
    std::string slbt{ "1 A 2 B 3 C 4 F 5 D 6 G 7 E" };
    std::istringstream isslbt(slbt);
    lbt.input(isslbt);
    lbt.draw();
    std::cin.ignore();
 
    //lbt.output(std::cout, TRAVERSE_ORDER::PREFIX);
    //std::cout << std::endl;
    //lbt.output(std::cout, TRAVERSE_ORDER::INFIX);
    //std::cout << std::endl;
    //lbt.output(std::cout, TRAVERSE_ORDER::POSTFIX);
    //std::cout << std::endl;
    //lbt.output(std::cout, TRAVERSE_ORDER::LEVEL);
    //std::cout << std::endl;
    //std::cout << lbt.Height() << std::endl;
    //std::cout << std::endl;
    //std::cout << lbt.size() << std::endl;
    //std::cout << std::endl;

    //std::cout << "Exercise 44" << std::endl;
    //LinkedBinaryTree<std::string> lbt44(lbt);
    //lbt44.output(std::cout, TRAVERSE_ORDER::INFIX);
    //std::cout << std::endl;

    //std::cout << "Exercise 45" << std::endl;
    //LinkedBinaryTree<std::string> lbt45;
    //std::string s45{ "1 + 2 - 3 + 4 - 5 * 6 + 7 * 9 1 10 2 11 3 12 4 13 5 14 / 15 6 28 7 29 8" };
    //std::istringstream iss45(s45);
    //lbt45.input(iss45);
    //lbt45.output(std::cout, TRAVERSE_ORDER::INFIX);
    //std::cout << std::endl;
    //std::cout << lbt.compare(lbt44) << std::endl;
    //std::cout << lbt.compare(lbt45) << std::endl;

    //std::cout << "Exercise 46" << std::endl;
    //lbt.swapTrees(lbt45);
    //lbt.output(std::cout, TRAVERSE_ORDER::INFIX);
    //std::cout << std::endl;
    //lbt45.output(std::cout, TRAVERSE_ORDER::INFIX);
    //std::cout << std::endl;

    //std::cout << "Exercise 47" << std::endl;
    //std::cout << lbt.maxHeightDifferent() << std::endl;
    //LinkedBinaryTree<std::string> lbt47;
    //std::string s47{ "1 + 2 - 3 + 4 - 5 * 6 + 7 * 9 1 10 2 11 3 12 4 13 5 14 / 15 6 28 7 29 8 56 9 112 10" };
    //std::istringstream iss47(s47);
    //lbt47.input(iss47);
    //std::cout << lbt47.maxHeightDifferent() << std::endl;

    //std::cout << "Exercise 48" << std::endl;
    //for (auto bi48 = lbt.beginInOrder(); bi48 != lbt.endInOrder(); ++bi48) {
    //    std::cout << *bi48 << " ";
    //}
    //std::cout << std::endl;
    //auto bi48 = lbt.beginInOrder();
    //auto bi48_2 = bi48++;
    //std::cout << *bi48 << " " << std::endl;
    //std::cout << bi48_2->at(0) << " " << std::endl;

    //std::cout << "Exercise 49" << std::endl;
    //lbt.output(std::cout, TRAVERSE_ORDER::PREFIX);
    //std::cout << std::endl;
    //for (auto bi49 = lbt.beginPreOrder(); bi49 != lbt.endPreOrder(); ++bi49) {
    //    std::cout << *bi49 << " ";
    //}
    //std::cout << std::endl;
    //auto bi49 = lbt.beginPreOrder();
    //auto bi49_2 = bi49++;
    //std::cout << *bi49 << " " << std::endl;
    //std::cout << bi49_2->at(0) << " " << std::endl;

    //std::cout << "Exercise 50" << std::endl;
    //lbt.output(std::cout, TRAVERSE_ORDER::POSTFIX);
    //std::cout << std::endl;
    //for (auto bi50 = lbt.beginPostOrder(); bi50 != lbt.endPostOrder(); ++bi50) {
    //    std::cout << *bi50 << " ";
    //}
    //std::cout << std::endl;
    //auto bi50 = lbt.beginPostOrder();
    //auto bi50_2 = bi50++;
    //std::cout << *bi50 << " " << std::endl;
    //std::cout << bi50_2->at(0) << " " << std::endl;

    //std::cout << "Exercise 51" << std::endl;
    //lbt.output(std::cout, TRAVERSE_ORDER::LEVEL);
    //std::cout << std::endl;
    //for (auto bi51 = lbt.beginLevelOrder(); bi51 != lbt.endLevelOrder(); ++bi51) {
    //    std::cout << *bi51 << " ";
    //}
    //std::cout << std::endl;
    //auto bi51 = lbt.beginLevelOrder();
    //auto bi51_2 = bi51++;
    //std::cout << *bi51 << " " << std::endl;
    //std::cout << bi51_2->at(0) << " " << std::endl;

    //std::cout << "Exercise 52" << std::endl;
 
    //std::cout << "Exercise 52.3, 52.1, 52.2" << std::endl;
    //std::string s52_3 = "+ + / + a b - c d e / * g h a";
    ////std::string s52_3 = "+ - - x * y z + + a b * / c d e";
    ////std::string s52_3 = "|| > + a b - c e && < a b || < x y > y z";
    //Expression ex52_3(s52_3, PREFIX);
    //std::cout << ex52_3.toParenInOrder() << std::endl;
    //std::cout << ex52_3.toPreOrderExpr() << std::endl;
    //std::cout << ex52_3.toPostOrderExpr() << std::endl;
    //
    //std::cout << "Exercise 52.4" << std::endl;
    //std::string s52_4 = "a b + c d - / e + g h * a / +";
    ////std::string s52_4 = "x - y z * - a b + c d / e * + +"; 
    ////std::string s52_4 = "a b + c e - > a b < x y < y z > || && ||";
    //Expression ex52_4(s52_4, POSTFIX);
    //std::cout << ex52_4.toPostOrderExpr() << std::endl;

    //std::cout << "Exercise 52.5" << std::endl;
    ////std::string s52_5 = "(a+b)/(c-d)+e+g*h/a";
    ////std::string s52_5 = "-x-y*z+(a+b+c/d*e)";
    //std::string s52_5 = "((a+b)>(c-e))||a<b&&(x<y||y>z)";
    //Expression ex52_5(s52_5);
    //std::cout << ex52_5.toParenInOrder() << std::endl;

    //std::cout << "Exercise 52.6" << std::endl;
    //std::string s52_6 = "1 - 2 3 * - 4 5 + 7 8 / 6 * + +";
    //Expression ex52_6(s52_6, POSTFIX);
    //std::cout << ex52_6.toPostOrderExpr() << std::endl;
    //std::cout << ex52_6.calValue() << std::endl;

    //std::cout << "Distrution Tree" << std::endl;
    //tolerance = 8;
    //std::string sdt = "1 0 2 4 3 3 4 6 5 2 6 5 7 2 8 2 9 4 10 6 11 4 12 5 13 3 14 6 15 2";
    //LinkedBinaryTree<Booster> dt;
    //std::istringstream issdt(sdt);
    //dt.input(issdt);
    //dt.postOrder(placeBoosters);
    //dt.output(std::cout, LEVEL);
    //std::cout << std::endl;

    //tolerance = 11;
    //std::string sdt_2 = "1 0 2 2 3 4 4 5 5 6 6 3 7 4 8 2 9 6 10 3 11 1 12 3 13 2 14 6 15 3";
    //LinkedBinaryTree<Booster> dt_2;
    //std::istringstream issdt_2(sdt_2);
    //dt_2.input(issdt_2);
    //dt_2.postOrder(placeBoosters);
    //dt_2.output(std::cout, LEVEL);
    //std::cout << std::endl;

    //tolerance = 6;
    //std::cout << "Exercise 57" << std::endl;
    //DistributionTree dt57;
    //std::istringstream iss57(sdt_2);
    //dt57.input(iss57);
    //dt57.postOrder(placeBoosters2);
    //dt57.output(std::cout, POSTFIX);
    //std::cout << std::endl;

    //std::cout << "Ordinary Set Tree" << std::endl;
    //std::string s_ost = "16 1 10 2 10 3 12 4 12 5 14 6 14 7 14 9 15 10 16 11 16 12 16 13 16";
    //std::istringstream iss_ost(s_ost);
    //FlatSetTree fst;
    //fst.input(iss_ost);
    //std::cout << fst.find(1) << std::endl;
    //std::cout << fst.find(9) << std::endl;
    //fst.unite(8, 15);
    //fst.output(std::cout);
    //std::cout << std::endl;

    //std::cout << "Set Tree" << std::endl;
    //std::istringstream iss_st(s_ost);
    //SetTree st;
    //st.input(iss_st);
    //std::cout << st.find(1) << std::endl;
    //std::cout << st.find(9) << std::endl;
    //st.unite(8, 15);
    //st.output(std::cout);
    //std::cout << std::endl;

    //std::cout << "Exercise 63" << std::endl;
    //int count = 10000;
    //TestSetTree tst(count);
    ////SetTree st1(count);
    ////std::cout << "Set Tree No Find rule, No Unite rule" << std::endl;
    ////tst.test(st1, SetTree::NO_FIND_RULE, SetTree::NO_UNITE_RULE);
    //SetTree st2(count);
    //std::cout << "Set Tree Weight and Path Compaction" << std::endl;
    //tst.test(st2, SetTree::PATH_COMPACTION, SetTree::WEIGHT);

    //std::cout << "Exercise 66" << std::endl;
    //SetTree st3(count);
    //std::cout << "Set Tree Weight and Path Splitting" << std::endl;
    //tst.test(st3, SetTree::PATH_SPLITTING, SetTree::WEIGHT);
    //SetTree st4(count);
    //std::cout << "Set Tree Weight and Path Halving" << std::endl;
    //tst.test(st4, SetTree::PATH_HALVING, SetTree::WEIGHT);
    //SetTree st5(count);
    //std::cout << "Set Tree Height and Path Compaction" << std::endl;
    //tst.test(st5, SetTree::PATH_COMPACTION, SetTree::WEIGHT);
    //SetTree st6(count);
    //std::cout << "Set Tree Height and Path Splitting" << std::endl;
    //tst.test(st6, SetTree::PATH_SPLITTING, SetTree::WEIGHT);
    //SetTree st7(count);
    //std::cout << "Set Tree Height and Path Halving" << std::endl;
    //tst.test(st7, SetTree::PATH_HALVING, SetTree::WEIGHT);

}

