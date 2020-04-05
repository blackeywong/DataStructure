#include "ExpressTree.h"

bool isSym(const std::string& s) {
    if (s == "+"
        || s == "-"
        || s == "*"
        || s == "/"
        || s == "%"
        || s == ">"
        || s == "<"
        || s == ">="
        || s == "<="
        || s == "=="
        || s == "!="
        || s == "||"
        || s == "&&"
        || s == "!"
        || s == "("
        || s == ")")
        return true;
    return false;
}

std::string postExprToParenInOrder(const std::string& postStr) {//Exercise 38
    std::stack<std::string> st;
    std::string opr1, opr2, sym;
    std::string result;
    std::istringstream iss(postStr);
    std::string s;
    while (iss >> s) {
        if (!isSym(s)) {
            result = "(" + s + ")";
            st.push(result);
        }
        else {
            if (!st.empty()) {
                opr2 = st.top();
                st.pop();
                if (!st.empty()) {
                    opr1 = st.top();
                    st.pop();
                }
                result = "(" + opr1 + s + opr2 +")";
                st.push(result);
            }
            else {
                return result;
            }
        }
        opr1 = opr2 = "";
    }
    return result;
}


std::string preExprToParenInOrder(const std::string& preStr) {//Exercise 39
    std::vector<std::string> v;
    std::string result;
    std::istringstream iss(preStr);
    std::string s;
    while (iss >> s) {
        v.push_back(s);
    }

 
    for(size_t i = 0;i<v.size();++i){
        if (v.size() == 1) {
            if (!isSym(v[0]))
                result = "(" + v[0] + ")";
            return result;
        }
        
        if (isSym(v[i]))
            continue;

        if (i >0 && isSym(v[i - 1])) {
            if ((i + 1 == v.size() || i + 1 < v.size() && isSym(v[i + 1])) && result == "") {
                result = v[i - 1] + "(" + v[i] + ")";
                v[i - 1] = result;
                v.erase(v.begin() + i);
                i -= 2;
            }
            continue;
         }

        if (i == 1) {
            result = v[i - 1] + "(" + v[i] + ")";
            v[i - 1] = result;
            v.erase(v.begin() + i);
            i -= 2;
        }
        else if(i >=2){
            result = "(" + v[i-1] + ")" + v[i - 2] + "(" + v[i] + ")";
            v[i - 2] = result;
            v.erase(v.begin() + i);
            v.erase(v.begin() + i-1);
            i -= 3;
         }
    }
    return result;
}

std::string parenInExprToPostOrder(const std::string& inStr) {
    std::stack<std::string> st;
    std::string result;
    std::string s;
    for (size_t i = 0; i < inStr.size();) {
        s = nextToken(inStr, i);
        if (!isSym(s)) {
            result += s;
            continue;
        }

        if (st.empty()) {
            st.push(s);
            continue;
        }

        if (!priorityOver(st.top(), s)) {
            st.push(s);
            continue;
        }

        while (!st.empty() && s != "" && priorityOver(st.top(), s)) {
            result += st.top();
            st.pop();
            if (s == ")") {
                if (st.empty()) {
                    return result;
                }
                while (st.top() != "(") {
                    result += st.top();
                    st.pop();
                }
                st.pop();
                s = "";
            }
        }
        if (s != "") {
            st.push(s);
        }
    }
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
    return result;
}

std::string parenInExprToPreOrder(const std::string& inStr) {
    std::stack<std::string> stSym;
    std::stack<std::string> stOpr;
    std::string s;
    for (size_t i = 0; i < inStr.size();) {
        s = nextToken(inStr, i);
        if (!isSym(s)) {
            stOpr.push(s);
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
            std::string midres = stOpr.top();
            stOpr.pop();
            if (stSym.top() != "!" && !stOpr.empty()) {
                midres = stOpr.top() + midres;
                stOpr.pop();
            }
            midres = stSym.top() + midres;
            stSym.pop();
            stOpr.push(midres);

            if (s == ")") {
                if (stSym.empty()) {
                    return stOpr.top();
                }
                while (stSym.top() != "(") {
                    midres = stOpr.top();
                    stOpr.pop();
                    if (stSym.top() != "!" && !stOpr.empty()) {
                        midres = stOpr.top() + midres;
                        stOpr.pop();
                    }
                    midres = stSym.top() + midres;
                    stSym.pop();
                    stOpr.push(midres);
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
        std::string midres = stOpr.top();
        stOpr.pop();
        if (stSym.top() != "!" && !stOpr.empty()) {
            midres = stOpr.top() + midres;
            stOpr.pop();
        }
        midres = stSym.top() + midres;
        stSym.pop();
        stOpr.push(midres);
    }
    while (stOpr.size() > 1) {
        std::string midres = stOpr.top();
        stOpr.pop();
        midres = stOpr.top() + midres;
        stOpr.pop();
        stOpr.push(midres);
    }
    return stOpr.top();
}

bool priorityOver(const std::string& symInStack, const std::string& symInStr) {
    if (symInStr == ")" || symInStr == "") return true;//anytime out-of-stack is ")", pop from stack, that is, ")" takes lowest priority and never enter stack.
                                       //In-stack symbol is always higher that out-of-stack ")"
                                        //When a ")" encountered, there must be a "(" in stack and has to be popped up
    if (symInStr == "(") return false;//out-of-stack "(" is highest priority
    if (symInStack == "!") return true;
    if (symInStack == "*" || symInStack == "/") {
        if (symInStr == "!")
            return false;
        return true;
    } 
    if (symInStack == "%") {
        if (symInStr == "!" || symInStr == "*" || symInStr == "/") {
            return false;
        }
        return true;
    }
    if (symInStack == "+" || symInStack == "-") {
        if (symInStr == "!" || symInStr == "*" || symInStr == "/" || symInStr == "%") {
            return false;
        }
        return true;
    }
    if (symInStack == ">" || symInStack == ">=" || symInStack == "<" || symInStack == "<=") {
        if (symInStr == "!" || symInStr == "*" || symInStr == "/" || symInStr == "%" || symInStr == "+" || symInStr == "-") {
            return false;
        }
        return true;
    }
    if (symInStack == "==" || symInStack == "!=") {
        if (symInStr == "!" || symInStr == "*" || symInStr == "/" || symInStr == "%" || symInStr == "+" || symInStr == "-" || symInStr == ">" || symInStr == ">=" || symInStr == "<" || symInStr == "<=") {
            return false;
        }
        return true;
    }
    if (symInStack == "&&") {
        if (symInStr == "!" || symInStr == "*" || symInStr == "/" || symInStr == "%" || symInStr == "+" || symInStr == "-" || symInStr == ">" || symInStr == ">=" || symInStr == "<" || symInStr == "<=" || symInStr == "==" || symInStr == "!=") {
            return false;
        }
        return true;
    }
    if (symInStack == "||") {
        if (symInStr == "!" || symInStr == "*" || symInStr == "/" || symInStr == "%" || symInStr == "+" || symInStr == "-" || symInStr == ">" || symInStr == ">=" || symInStr == "<" || symInStr == "<=" || symInStr == "==" || symInStr == "!=" || symInStr == "&&") {            return false;
        }
        return true;
    }
    if (symInStack == "(" && symInStr == "(") return true;//symbol in stack takes priority of that in string
    return false;
}

std::string nextToken(const std::string& s, size_t& start) {
    std::string result;
    while(isblank(s[start])){
        ++start;
    }
    if (isalpha(s[start])) {
        while (start < s.size() && (isalnum(s[start]) || s[start] == '_')) {
            result += s[start++];
        }       
    }
    else if (isdigit(s[start])) {
        while (start < s.size() && isdigit(s[start])) {
            result += s[start++];
        }
        if (s[start] == '.') {
            result += s[start++];
            while (start < s.size() && isdigit(s[start])) {
                result += s[start++];
            }
        }
    }
    else {
        result += s[start++];
        if (start < s.size() && !isalnum(s[start])) {
            if ((s[start-1] == '>' || s[start-1] == '<') && s[start] == '='
                || s[start-1] == '=' && s[start] == '='
                || s[start-1] == '|' && s[start] == '|'
                || s[start-1] == '&' && s[start] == '&') {
                result += s[start++];
             }
        }
    }
    return result;
}

double calPostOrderExpr(const std::string& expr) {
    std::vector<std::string> v;
    size_t start = 0;
    while (start < expr.size()) {
        std::string token = nextToken(expr, start);
        v.push_back(token);
    }

    std::stack<double> st;
    for (size_t i = 0; i < v.size(); ++i) {
        if (!isSym(v[i])) {
            st.push(atof(v[i].c_str()));
            continue;
        }

        if (st.empty()) {
            return - DBL_MAX;
        }

        if ((v[i] == "+" || v[i] == "-") && st.size() == 1) {
            double opr = st.top();
            if (v[i] == "-")
                opr = -opr;
            st.pop();
            st.push(opr);
        }
        else if(st.size() > 1){
            double opr2 = st.top();
            st.pop();
            double opr1 = st.top();
            st.pop();
            double res = 0.0;
            if (v[i] == "+") {
                res = opr1 + opr2;
            }
            else if (v[i] == "-") {
                res = opr1 - opr2;
            }
            else if (v[i] == "*") {
                res = opr1 * opr2;
            }
            else if (v[i] == "/") {
                if (opr2 != 0) {
                    res = opr1 / opr2;
                }
                else {
                    return -DBL_MAX;
                }
            }
            else if (v[i] == "%") {
                res = (int)opr1 % (int)opr2;
            }
            st.push(res);
        }
    }
    return st.top();
}