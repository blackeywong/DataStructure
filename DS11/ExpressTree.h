#pragma once
#ifndef _EXPRESSTREE_H
#define _EXPRESSTREE_H

#include <string>
#include <sstream>
#include "ChainBinaryTree.h"

bool isSym(const std::string& s);
std::string postExprToParenInOrder(const std::string& postStr);//Exercise 38
std::string preExprToParenInOrder(const std::string& preStr);//Exercise 39
std::string parenInExprToPostOrder(const std::string& inStr);//Exercise 40
std::string parenInExprToPreOrder(const std::string& inStr);//Exercise 41
bool priorityOver(const std::string& sym1, const std::string& sym2);
std::string nextToken(const std::string& s, size_t& start);
double calPostOrderExpr(const std::string& expr);//Exercise 43

 
//Exercise 26
template<class T>
class ExpressTree : public ChainBinaryTree<T> {
public:
    double calValue();
    ExpressTree() :ChainBinaryTree<T>() {}
    ExpressTree(const std::string& expr, TRAVERSE_ORDER order);//Exercise 36,37, 42

    std::string toParenInOrder() { return toParenInOrderRecursive(this->root); }//Exercise 38, 39
private:
    double calExprTree(BinaryTreeNode<T>* node);
    bool createTreeWithPostExpr(const std::string& postStr);//Exercise 36
    bool createTreeWithPreExpr(const std::string& preStr);//Exercise 37
    std::string toParenInOrderRecursive(BinaryTreeNode<T>* node);//Exercise 38
    bool createTreeWithInExprParen(const std::string& preStr);//Exercise 42
};

template<class T>
double ExpressTree<T>::calValue() {
    return calExprTree(this->root);
}

template<class T>
double ExpressTree<T>::calExprTree(BinaryTreeNode<T>* node) {
    if (node->leftChild == nullptr && node->rightChild == nullptr) {
        return std::atof(node->element.c_str());
    }

    if (node->leftChild == nullptr) {
        if (node->element == "-")
            return -calExprTree(node->rightChild);
        else
            return calExprTree(node->rightChild);
    }

    if (node->element == "+")
        return calExprTree(node->leftChild) + calExprTree(node->rightChild);
    else if (node->element == "-")
        return calExprTree(node->leftChild) - calExprTree(node->rightChild);
    else if (node->element == "*")
        return calExprTree(node->leftChild) * calExprTree(node->rightChild);
    else if (node->element == "/")
        return calExprTree(node->leftChild) / calExprTree(node->rightChild);
    //else if (node->element == "%")
    //  return calExprTree(node->leftChild) % calExprTree(node->rightChild);

    return 0.0;
}

template<class T>
ExpressTree<T>::ExpressTree(const std::string& expr, TRAVERSE_ORDER order) {
    switch (order) {
    case TRAVERSE_ORDER::POSTFIX: createTreeWithPostExpr(expr); break;
    case TRAVERSE_ORDER::PREFIX: createTreeWithPreExpr(expr); break;
    case TRAVERSE_ORDER::INFIX: createTreeWithInExprParen(expr); break;
    }
}

template<class T>
bool ExpressTree<T>::createTreeWithPostExpr(const std::string& postStr) {
    this->clear(this->root);
    std::stack<BinaryTreeNode<T>*> st;
    std::string s;
    std::istringstream iss(postStr);
    while (iss >> s) {
        BinaryTreeNode<T>* node = new BinaryTreeNode<T>(s);
        if (isSym(s)) {
            if (st.empty()) {
                return false;
            }
            else {
                node->rightChild = st.top();
                st.pop();
                if (!st.empty()) {
                    node->leftChild = st.top();
                    st.pop();
                }
            }
        }
        st.push(node);
    }
    if (st.size() != 1)
        return false;
    this->root = st.top();
    return true;
}
 
template<class T>
bool ExpressTree<T>::createTreeWithPreExpr(const std::string& preStr) {
    std::stack<std::string> stAll;
    std::string s;
    std::istringstream iss(preStr);
    while (iss >> s) {
        stAll.push(s);
    }

    this->clear(this->root);
    std::stack<BinaryTreeNode<T>*> st;
    while (!stAll.empty()) {
        s = stAll.top();
        stAll.pop();
        BinaryTreeNode<T>* node = new BinaryTreeNode<T>(s);
        if (isSym(s)) {
            if (st.empty()) {
                return false;
            }
            else {
                if (st.size() > 1) {
                    node->leftChild = st.top();
                    st.pop();
                }
                node->rightChild = st.top();
                st.pop();
             }
        }
        st.push(node);
    }
    if (st.size() != 1)
        return false;
    this->root = st.top();
    return true;
}

template<class T>
bool ExpressTree<T>::createTreeWithInExprParen(const std::string& inStr) {
    this->clear(this->root);
    std::stack<std::string> stSym;
    std::stack<BinaryTreeNode<std::string>*> stOpr;
    std::string s;
    for (size_t i = 0; i < inStr.size();) {
        s = nextToken(inStr, i);
        if (!isSym(s)) {
            stOpr.push(new BinaryTreeNode<std::string>(s));
            continue;
        }

        if (stSym.empty()) {
            stSym.push(s);
            continue;
        }

        if (!priorityOver(stSym.top(), s)) {
            stSym.push(s);
            continue;
        }

        while (!stSym.empty() && s != "" && priorityOver(stSym.top(), s)) {
            BinaryTreeNode<std::string>* node = new BinaryTreeNode<std::string>(stSym.top());
            node->rightChild = stOpr.top();
            stOpr.pop();
            if (stSym.top() != "!" && !stOpr.empty()) {
                node->leftChild = stOpr.top();
                stOpr.pop();
            }
            stSym.pop();
            stOpr.push(node);

            if (s == ")") {
                if (stSym.empty()) {
                    this->root = stOpr.top();
                    return false;
                }
                while (stSym.top() != "(") {
                    node = new BinaryTreeNode<std::string>(stSym.top());
                    node->rightChild = stOpr.top();
                    stOpr.pop();
                    if (stSym.top() != "!" && !stOpr.empty()) {
                        node->leftChild = stOpr.top();
                        stOpr.pop();
                    }
                    stSym.pop();
                    stOpr.push(node);
                }
                stSym.pop();
                s = "";
            }
        }
        if (s != "") {
            stSym.push(s);
        }
    }
    while (!stSym.empty()) {
        BinaryTreeNode<std::string>* node = new BinaryTreeNode<std::string>(stSym.top());
        node->rightChild = stOpr.top();
        stOpr.pop();
        if (stSym.top() != "!" && !stOpr.empty()) {
            node->leftChild = stOpr.top();
            stOpr.pop();
        }
        stSym.pop();
        stOpr.push(node);
    }
    this->root = stOpr.top();
    return true;
}

template<class T>
std::string ExpressTree<T>::toParenInOrderRecursive(BinaryTreeNode<T>* node) {
    std::string s;
    if (node != nullptr) {
        s += "(";
        s += toParenInOrderRecursive(node->leftChild);
        s += node->element;
        s += toParenInOrderRecursive(node->rightChild);
        s += ")";
    }
    return s;
}

#endif