#pragma once
#ifndef _EXPRESSION_H
#define _EXPRESSION_H
#include <string>
#include <sstream>

#include "LinkedBinaryTree.h"
//Exercise 52
class Expression : public LinkedBinaryTree<std::string> {
public:
    Expression() :LinkedBinaryTree<std::string>() {}
    explicit Expression(const std::string& expr, TRAVERSE_ORDER order = TRAVERSE_ORDER::INFIX);//Exercise 52.3 52.4 52.5
    double calValue();//Exercise 52.6

    std::string toParenInOrder() { return toParenInOrderRecursive(this->root); }//Exercise 52.1
    std::string toPreOrderExpr() {//Exercise 52.2
        Expression::forOutput = "";
        preOrder(outputContent);
        return forOutput;
    }
    std::string toPostOrderExpr() {//Exercise 52.2
        Expression::forOutput = "";
        postOrder(outputContent);
        return forOutput;
    }
private:
    double calExprTree(BinaryTreeNode<std::string>* node);
    bool createTreeWithPostExpr(const std::string& postStr);//Exercise 52.4
    bool createTreeWithPreExpr(const std::string& preStr);//Exercise 52.3
    std::string toParenInOrderRecursive(BinaryTreeNode<std::string>* node);//Exercise 52.1
    bool createTreeWithInExprParen(const std::string& inStr);//Exercise 52.5

    static std::string forOutput;
    //static std::ostringstream ossForOutput(forOutput);
    static void outputContent(BinaryTreeNode<std::string>* node) { forOutput += node->element + " "; }
};

#endif

