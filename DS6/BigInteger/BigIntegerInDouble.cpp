#include "BigIntegerInDouble.h"


BigIntegerInDouble::BigIntegerInDouble(const string& number) : BigIntegerInDouble() {
	for (int i = number.size() - 1; i > 0; i--) {
		insert(0, number[i] - 48);
	}
	if (number[0] == '-') sign = -1;
	else if (number[0] == '+') sign = 1;
	else {
		insert(0, number[0] - 48);
		sign = 1;
	}
}

void BigIntegerInDouble::copyData(const BigIntegerInDouble& other) {
	clear();
	DoubleNode<int>* cur = other.firstNode;
	while (cur) {
		push_back(cur->element);
		cur = cur->right;
	}
	sign = other.sign;
}

bool BigIntegerInDouble::equals(const BigIntegerInDouble& right) const {
	if (listSize != right.listSize) return false;
	if (sign != right.sign) return false;

	DoubleNode<int>* cur = firstNode;
	DoubleNode<int>* curRight = right.firstNode;

	while (cur && curRight) {
		if (cur->element != curRight->element) return false;
		cur = cur->right;
		curRight = curRight->right;
	}

	return true;
}

bool  BigIntegerInDouble::lessThanIgnoreSign(const BigIntegerInDouble& right) const {
	if (listSize < right.listSize) {
		return true;
	}
	else {
		if (listSize > right.listSize) {
			return false;
		}
		else {
			DoubleNode<int>* cur = firstNode;
			DoubleNode<int>* curRight = right.firstNode;

			while (cur && curRight) {
				if (cur->element < curRight->element) return  true;
				else if (cur->element > curRight->element) return false;
				cur = cur->right;
				curRight = curRight->right;
			}
		}
	}
	return false;
}


bool BigIntegerInDouble::lessThan(const BigIntegerInDouble& right) const {
	if (sign != right.sign) {//one is positive, the other is negative
		if (sign == 1) return false;
		else return true;
	}
	bool result = false;
	result = lessThanIgnoreSign(right);
	if (sign == -1) {
		result = !result && *this != right;
	}

	return result;
}

BigIntegerInDouble& BigIntegerInDouble::operator+=(const BigIntegerInDouble& right) {
	if (sign == right.sign) {
		add(right);
	}
	else {
		if (lessThanIgnoreSign(right)) {
			BigIntegerInDouble temp = right;
			temp.minus(*this);
			sign = right.sign;
			swap(lastNode, temp.lastNode);
			swap(firstNode, temp.firstNode);
			swap(listSize, temp.listSize);
		}
		else {
			minus(right);
		}
	}

	return *this;
}


BigIntegerInDouble& BigIntegerInDouble::operator-=(const BigIntegerInDouble& right) {
	if (sign != right.sign) {
		add(right);
	}
	else {
		if (lessThanIgnoreSign(right)) {
			BigIntegerInDouble temp = right;
			temp.minus(*this);
			sign = right.sign;
			swap(lastNode, temp.lastNode);
			swap(firstNode, temp.firstNode);
			swap(listSize, temp.listSize);
		}
		else {
			minus(right);
		}
	}

	return *this;
}

BigIntegerInDouble& BigIntegerInDouble::operator*=(const BigIntegerInDouble& right) {
	if (sign == right.sign) sign = 1;
	else sign = -1;

	BigIntegerInDouble bi = multiply(right);
	swap(lastNode, bi.lastNode);
	swap(firstNode, bi.firstNode);
	swap(listSize, bi.listSize);

	return *this;
}

BigIntegerInDouble& BigIntegerInDouble::operator/=(const BigIntegerInDouble& right) {
	if (sign == right.sign) sign = 1;
	else sign = -1;

	BigIntegerInDouble quotient, remainder;
	divide(right, quotient, remainder);
	swap(lastNode, quotient.lastNode);
	swap(firstNode, quotient.firstNode);
	swap(listSize, quotient.listSize);

	return *this;
}

BigIntegerInDouble& BigIntegerInDouble::operator%=(const BigIntegerInDouble& right) {
	if (sign == right.sign) sign = 1;
	else sign = -1;

	BigIntegerInDouble quotient, remainder;
	divide(right, quotient, remainder);
	swap(lastNode, remainder.lastNode);
	swap(firstNode, remainder.firstNode);
	swap(listSize, remainder.listSize);

	return *this;
}

void BigIntegerInDouble::add(const BigIntegerInDouble& right) {
	int i = 0;
	int carry = 0;
	DoubleNode<int>* cur = lastNode;
	DoubleNode<int>* curRight = right.lastNode;
	do {
		cur->element += curRight->element + carry;
		carry = cur->element / 10;
		cur->element %= 10;

		cur = cur->left;
		curRight = curRight->left;
	} while (cur && curRight);

	int oldsize = listSize;
	for (; cur || curRight; i++) {
		if (oldsize < right.listSize) {
			insert(0,curRight->element + carry);
			cur = firstNode;
			curRight = curRight->left;
		}
		else {
			cur->element += carry;
		}
		carry = cur->element / 10;
		cur->element %= 10;
		cur = cur->left;
	}
	if (carry != 0) insert(0,carry);
}

void BigIntegerInDouble::minus(const BigIntegerInDouble& right) {
	int i = 0;
	int borrow = 0;
	DoubleNode<int>* cur = lastNode;
	DoubleNode<int>* curRight = right.lastNode;
	do {
		cur->element -= curRight->element + borrow;
		if (cur->element < 0) {
			borrow = 1;
			cur->element = cur->element + 10;
		}
		else {
			borrow = 0;
		}
		cur = cur->left;
		curRight = curRight->left;
	} while (cur&& curRight);

	int oldsize = listSize;
	for (; cur || curRight; i++) {
		if (oldsize < right.listSize) {
			insert(0, 10 - curRight->element - borrow);
			cur = firstNode;
			borrow = 1;
			curRight = curRight->left;
		}
		else {
			cur->element -= borrow;
			if (cur->element < 0) {
				borrow = 1;
				cur->element = cur->element + 10;
			}
			else {
				borrow = 0;
			}
		}
		cur = cur->left;
	}
	if (borrow != 0) {
		insert(0, 10 - borrow);
	}
	
	removeLeadingZero();
}

BigIntegerInDouble BigIntegerInDouble::multiply(const BigIntegerInDouble& right) {
	BigIntegerInDouble result;

	DoubleNode<int>* curRes = nullptr;
	DoubleNode<int>* curLeft = lastNode;
	DoubleNode<int>* curRight = right.lastNode;
	int len1 = listSize;
	int len2 = right.listSize;
	
	for (int i = 0; i < len2; i++) {
		curLeft = lastNode;
		curRes = result.lastNode;
		//move pointer of lowest digit to align with current digit of 'right'
		for (int k = 0; k < i; k++) curRes = curRes->left;
		int carry = 0;

		for (int j = 0; j < len1; j++) {
			int temp = curLeft->element * curRight->element + carry;
			if (curRes == nullptr) {
				result.insert(0, temp);
				curRes = result.firstNode;
			}
			else {
				curRes->element += temp;
			}
			carry = curRes->element / 10;
			curRes->element %= 10;
			curLeft = curLeft->left;
			curRes = curRes->left;
		}

		while (carry != 0) {
			if (curRes == nullptr) {
				result.insert(0, carry);
				curRes = result.firstNode;
			}
			else {
				curRes->element += carry;
			}
			carry = curRes->element / 10;
			curRes->element %= 10;
			curRes = curRes->left;
		}
		curRight = curRight->left;
	}

	return result;
}

void BigIntegerInDouble::divide(const BigIntegerInDouble& right, BigIntegerInDouble& quotient, BigIntegerInDouble& remainder) {
	int len1 = listSize;
	int len2 = right.listSize;
	if (len1 < len2) {
		quotient = BigIntegerInDouble("0");
		remainder = *this;
		return;
	}
	DoubleNode<int>* cur = firstNode;
	DoubleNode<int>* curRight = right.firstNode;

	remainder = BigIntegerInDouble("0");

	BigIntegerInDouble divisor = right;
	if (divisor.sign = -1) divisor.sign = 1;
	BigIntegerInDouble dividend;
	dividend.sign = 1;
	for (int i = 0; i < divisor.listSize; i++) {
		dividend.push_back(cur->element);
		cur = cur->right;
	}

	int j = 0;

	do {
		int digit = 0;
		while (dividend >= divisor) {
			dividend -= divisor;
			digit++;
		}
		quotient.push_back(digit);
		if (j > len1 - len2 - 1) break;
		dividend.push_back(cur->element);
		dividend.removeLeadingZero();
		cur = cur->right;

		j++;
	} while (true);

	remainder = dividend;
	quotient.removeLeadingZero();
}

void BigIntegerInDouble::removeLeadingZero() {
	if (listSize > 1 && firstNode->element == 0) erase(0);
}

void BigIntegerInDouble::output(ostream& out) const {
	if (sign == -1) out << '-';
	DoubleNode<int>* cur = firstNode;
	while (cur) {
		out << cur->element;
		cur = cur->right;
	}
}

ostream& operator<<(ostream& out, BigIntegerInDouble& bi) {
	bi.output(out);
	return out;
}

BigIntegerInDouble operator+(BigIntegerInDouble& left, BigIntegerInDouble& right) {
	BigIntegerInDouble result("0");
	result += left;
	result += right;
	return result;
}

BigIntegerInDouble operator-(BigIntegerInDouble& left, BigIntegerInDouble& right) {
	BigIntegerInDouble result("0");
	result += left;
	result -= right;
	return result;
}

BigIntegerInDouble operator*(BigIntegerInDouble& left, BigIntegerInDouble& right) {
	BigIntegerInDouble result("0");
	result += left;
	result *= right;
	return result;
}

BigIntegerInDouble operator/(BigIntegerInDouble& left, BigIntegerInDouble& right) {
	BigIntegerInDouble result("0");
	result += left;
	result /= right;
	return result;
}

BigIntegerInDouble operator%(BigIntegerInDouble& left, BigIntegerInDouble& right) {
	BigIntegerInDouble result("0");
	result += left;
	result %= right;
	return result;
}