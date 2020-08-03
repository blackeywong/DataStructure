#include "Expression.h"
#include "ExpressTree.h"

Expression::Expression(const std::string& expr, TRAVERSE_ORDER order)
{
    switch (order) {
    case TRAVERSE_ORDER::POSTFIX: createTreeWithPostExpr(expr); break;
    case TRAVERSE_ORDER::PREFIX: createTreeWithPreExpr(expr); break;
    case TRAVERSE_ORDER::INFIX: createTreeWithInExprParen(expr); break;
    }
}

double Expression::calValue()
{
    return calExprTree(this->root);
}

double Expression::calExprTree(BinaryTreeNode<std::string>* node)
{
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

    return 0.0;
}

bool Expression::createTreeWithPostExpr(const std::string& postStr)
{
    this->erase();
    std::stack<BinaryTreeNode<std::string>*> st;
    std::string s;
    std::istringstream iss(postStr);
    while (iss >> s) {
        BinaryTreeNode<std::string>* node = new BinaryTreeNode<std::string>(s);
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


bool Expression::createTreeWithPreExpr(const std::string& preStr)
{
    std::stack<std::string> stAll;
    std::string s;
    std::istringstream iss(preStr);
    while (iss >> s) {
        stAll.push(s);
    }

    this->erase();
    std::stack<BinaryTreeNode<std::string>*> st;
    while (!stAll.empty()) {
        s = stAll.top();
        stAll.pop();
        BinaryTreeNode<std::string>* node = new BinaryTreeNode<std::string>(s);
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


std::string Expression::toParenInOrderRecursive(BinaryTreeNode<std::string>* node)
{
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
 

bool Expression::createTreeWithInExprParen(const std::string& inStr)
{
    this->erase();
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

std::string Expression::forOutput = "";