#include "BigIntegerInVector.h"


BigInteger::BigInteger(const string& number): BigInteger() {
	for (int i = number.size()-1; i >0 ; i--) {
		digits->push_back((number[i] - 48));
	}
	if (number[0] == '-') sign = -1;
	else if (number[0] == '+') sign = 1;
	else {
		digits->push_back((number[0] - 48));
		sign = 1;
	}
}

void BigInteger::copyData(const BigInteger& other) {
	digits->clear();
	copy(other.digits->cbegin(), other.digits->cend(), back_inserter(*digits));
	sign = other.sign;
}

bool BigInteger::equals(const BigInteger& right) const {
	if (digits->size() != right.digits->size()) return false;
	if (sign != right.sign) return false;
	for (int i = digits->size()-1; i >=0; i--) {
		if ((*digits)[i] != (*right.digits)[i]) return false;
	}
	return true;
}

bool  BigInteger::lessThanIgnoreSign(const BigInteger& right) const {
	if (digits->size() < right.digits->size()) {
		return true;
	}
	else {
		if (digits->size() > right.digits->size()) {
			return false;
		}
		else {
			for (int i = digits->size() - 1; i >= 0; i--) {
				if ((*digits)[i] < (*right.digits)[i]) return  true;
				else if ((*digits)[i] > (*right.digits)[i]) return false;
			}
		}
	}
	return false;
}


bool BigInteger::lessThan(const BigInteger& right) const {
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

BigInteger& BigInteger::operator+=(const BigInteger& right) {
	if (sign == right.sign) {
		add(right);
	}
	else {
		if (lessThanIgnoreSign(right)) {
			sign = right.sign;
		}
		minus(right);
	}

	return *this;
}


BigInteger& BigInteger::operator-=(const BigInteger& right) {
	if (sign != right.sign) {
		add(right);
	}
	else {
		if (lessThanIgnoreSign(right)) {
			sign = right.sign;
		}
		minus(right);
	}

	return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& right) {
	if (sign == right.sign) sign = 1;
	else sign = -1;

	BigInteger bi = multiply(right);
	swap(digits, bi.digits);

	return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& right) {
	if (sign == right.sign) sign = 1;
	else sign = -1;

	BigInteger quotient, remainder;
	divide(right, quotient, remainder);
	swap(digits, quotient.digits);

	return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& right) {
	if (sign == right.sign) sign = 1;
	else sign = -1;

	BigInteger quotient, remainder;
	divide(right, quotient, remainder);
	swap(digits, remainder.digits);

	return *this;
}

void BigInteger::add(const BigInteger& right) {
	int i = 0;
	int carry = 0;
	do {
		(*digits)[i] += (*right.digits)[i] + carry;
		carry = (*digits)[i] / 10;
		(*digits)[i] %= 10;

		i++;
	}while (i < digits->size() && i < right.digits->size());

	for (; i < digits->size() || i < right.digits->size(); i++) {
		if (digits->size() < right.digits->size()) {
			digits->push_back(0);
			(*digits)[i] = (*right.digits)[i] + carry;
		}
		else {
			(*digits)[i] += carry;
		}
		carry = (*digits)[i] / 10;
		(*digits)[i] %= 10;
	}
	if(carry !=0) digits->push_back(carry);
}

void BigInteger::minus(const BigInteger& right) {
	int i = 0;
	int borrow = 0;
	do {
		(*digits)[i] -= (*right.digits)[i] + borrow;
		if ((*digits)[i] < 0) {
			borrow = 1;
			(*digits)[i] = (*digits)[i] + 10;
		}
		else {
			borrow = 0;
		}
		i++;
	} while (i < digits->size() && i < right.digits->size());

	for (; i < digits->size() || i < right.digits->size(); i++) {
		if (digits->size() < right.digits->size()) {
			digits->push_back(0);
			(*digits)[i] = 10 - (*right.digits)[i] - borrow;
			borrow = 1;
		}
		else {
			(*digits)[i] -= borrow;
			if ((*digits)[i] < 0) {
				borrow = 1;
				(*digits)[i] = (*digits)[i] + 10;
			}
			else {
				borrow = 0;
			}
		}
	}
	if (borrow != 0) {
		digits->push_back(10 - borrow);
	}
	//remove top '0's
	while (digits->back() == 0 && digits->size() > 1) {
		digits->erase(digits->end() - 1);
	}
}

BigInteger BigInteger::multiply(const BigInteger& right) {
	BigInteger result;

	int carry = 0;
	int len1 = digits->size();
	int len2 = right.digits->size();
	int i = 0;
	for (; i < len1 + len2 - 1; i++) {
		result.digits->push_back(carry);
		int j = i < len1-1 ? i : len1-1;
		int k = i-j;
		while (j>=0 && k <= i && k < len2) {
			(*result.digits)[i] += (*digits)[j] * (*right.digits)[k];
			j--;
			k++;
		}
		carry = (*result.digits)[i] / 10;
		(*result.digits)[i] %= 10;
	}
	while (carry != 0) {
		result.digits->push_back(carry);
		carry = (*result.digits)[i] / 10;
		(*result.digits)[i] %= 10;
		i++;
	}

	return result;
}

void BigInteger::divide(const BigInteger& right, BigInteger& quotient, BigInteger& remainder) {
	int len1 = digits->size();
	int len2 = right.digits->size();
	if (len1 < len2) {
		quotient = BigInteger("0");
		remainder = *this;
		return;
	}

	remainder = BigInteger("0");

	BigInteger divisor = right;
	if (divisor.sign = -1) divisor.sign = 1;
	BigInteger dividend;
	dividend.sign = 1;
	for (int i = 0; i < divisor.digits->size(); i++) {
		dividend.digits->insert(dividend.digits->begin(), (*digits)[len1 - i - 1]);
	}

	int j = 0;
	
	do {
		int digit = 0;
		while (dividend >= divisor) {
			dividend -= divisor;
			digit++;
		}
		quotient.digits->insert(quotient.digits->begin(), digit);
		if (j > len1 - len2 - 1) break;
		dividend.digits->insert(dividend.digits->begin(), (*digits)[len1 - len2 - j - 1]);

		j++;
	}while (true);

	remainder = dividend;
	if (quotient.digits->back() == 0&&quotient.digits->size()>1) quotient.digits->erase(quotient.digits->end() - 1);
}


void BigInteger::output(ostream& out) const {
	if (sign == -1) out << '-';
	for (int i = digits->size() - 1; i >= 0; i--) out << (*digits)[i];
}

ostream& operator<<(ostream& out, BigInteger& bi) {
	bi.output(out);
	return out;
}