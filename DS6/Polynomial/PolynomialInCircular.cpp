#include "PolynomialInCircular.h"
#include "../../DS5/exceptions.h"

Polynomial::Polynomial(istream& in) {
	firstNode = new PolynomialNode(); this->listSize = 0; firstNode->next = firstNode;
	in >> listSize;
	if (listSize <= 0) return;
	int para1;
	double para2;
	PolynomialNode* cur = firstNode;
	for (int i = 0; i < listSize && in >> para1 && in >> para2; i++) {
		cur->next = new PolynomialNode(para2, para1);
		cur = cur->next;
	}
	cur->next = firstNode;
}

void Polynomial::checkIndex(const int exponent) const {
	if (exponent < 0 || exponent > getDegree()) {
		ostringstream s;
		s << "exponent = " << exponent << " degree = " << getDegree();
		throw IllegalIndex(s.str());
	}
}

int Polynomial::getDegree() const {
	if (listSize > 0) return firstNode->next->exp;
	return 0;
}

double Polynomial::valueOf(const int exponent) const {
	checkIndex(exponent);
	PolynomialNode* cur = firstNode->next;
	for (int i = 0; i < listSize; i++) {
		if (exponent == cur->exp) return cur->coeff;
		if (exponent > cur->exp) return 0;
		cur = cur->next;
	}
	return 0;
}

void Polynomial::clear() {
	PolynomialNode* cur = firstNode->next;
	for (int i = 0; i < listSize; i++) {
		firstNode = cur->next;
		delete cur;
		cur = firstNode;
	}
	firstNode->next = firstNode;
}

void Polynomial::output(ostream& out) const {
	out << listSize << " ";
	if (listSize == 0) return;
	PolynomialNode* cur = firstNode->next;
	for (int i = 0; i < listSize; i++) {
		out << cur->exp << " " << cur->coeff << " ";
		cur = cur->next;
	}
}

void Polynomial::copyData(const Polynomial& other) {
	listSize = other.listSize;
	PolynomialNode* cur = firstNode;
	PolynomialNode* curOther = other.firstNode->next;
	for (int i = 0; i < listSize; i++) {
		cur->next = new PolynomialNode(curOther->coeff, curOther->exp);
		cur = cur->next;
		curOther = curOther->next;
	}
	cur->next = firstNode;
}

Polynomial& Polynomial::add(const Polynomial& right) {
	if (right.listSize == 0) return *this;

	PolynomialNode* cur = firstNode;
	PolynomialNode* curRight = right.firstNode->next;

	while (curRight->exp != -1) {
		if (curRight->exp > cur->next->exp) {
			PolynomialNode* tmp = cur->next;
			cur->next = new PolynomialNode(curRight->coeff, curRight->exp);
			cur = cur->next;
			cur->next = tmp;
			listSize++;
			curRight = curRight->next;
		}
		else if (curRight->exp == cur->next->exp) {
			cur->next->coeff += curRight->coeff;
			if (cur->next->coeff == 0) {
				PolynomialNode* tmp = cur->next;
				cur->next = cur->next->next;
				delete tmp;
				listSize--;
			}else{
				cur = cur->next;
			}
			curRight = curRight->next;
		}else{
			cur = cur->next;
		}

	}
	return *this;
}
Polynomial& Polynomial::subtract(const Polynomial& right) {
	if (right.listSize == 0) return *this;

	PolynomialNode* cur = firstNode;
	PolynomialNode* curRight = right.firstNode->next;

	while (curRight->exp != -1) {
		if (curRight->exp > cur->next->exp) {
			PolynomialNode* tmp = cur->next;
			cur->next = new PolynomialNode(- curRight->coeff, curRight->exp);
			cur = cur->next;
			cur->next = tmp;
			listSize++;
			curRight = curRight->next;
		}
		else if (curRight->exp == cur->next->exp) {
			cur->next->coeff -= curRight->coeff;
			if (cur->next->coeff == 0) {
				PolynomialNode* tmp = cur->next;
				cur->next = cur->next->next;
				delete tmp;
				listSize--;
			}else{
				cur = cur->next;
			}
			curRight = curRight->next;
		}else{
			cur = cur->next;
		}
	}
	return *this;
}

void Polynomial::BubbleSort() {
	for (int i = 0; i < listSize; i++) {
		bool sorted = false;
		PolynomialNode* prev = firstNode->next;
		PolynomialNode* cur = prev->next;
		while (prev->exp != -1 && cur->exp != -1) {
			if (prev->exp < cur->exp) {
				swap(prev->exp, cur->exp);
				swap(prev->coeff, cur->coeff);
				sorted = true;
			}
			prev = cur;
			cur = cur->next;

		}
		if (!sorted) 
			break;
	}
}

Polynomial& Polynomial::multiply(const Polynomial& right) {
	if (listSize == 0 || getDegree() == 0 && firstNode->next->coeff == 0) return *this;
	if (right.listSize == 0 || right.getDegree() == 0 && right.firstNode->next->coeff == 0) {
		clear();
		firstNode->next = new PolynomialNode(0, 0);
		firstNode->next->next = firstNode;
		listSize = 1;
		return *this;
	}

	Polynomial result;

	PolynomialNode* cur = result.firstNode;
	PolynomialNode* curLeft = firstNode->next;
	PolynomialNode* curRight;
	while (curLeft->exp != -1) {
		curRight = right.firstNode->next;
		while (curRight->exp != -1) {
			cur->next = new PolynomialNode(curLeft->coeff * curRight->coeff, curLeft->exp + curRight->exp);
			result.listSize++;
			cur = cur->next;
			curRight = curRight->next;
		}
		curLeft = curLeft->next;
	}
	cur->next = result.firstNode;
	//sort result
	result.BubbleSort();
	//merge the nodes that has same exp
	PolynomialNode* prev = result.firstNode->next;
	while (prev->exp != -1 && prev->next->exp != -1) {
		cur = prev->next;
		if (prev->exp == cur->exp) {
			prev->coeff += cur->coeff;
			prev->next = cur->next;
			delete cur;
			result.listSize--;
		}
		else {
			prev = cur;
		}

	}

	swap(listSize, result.listSize);
	swap(firstNode, result.firstNode);

	return *this;
}

Polynomial& Polynomial::divide(const Polynomial& right) {
	if (right.listSize == 0 || right.getDegree() == 0 && right.firstNode->next->coeff == 0) {
		throw OutOfBounds();
	}

	if (getDegree() < right.getDegree() || getDegree() == right.getDegree() && firstNode->next->coeff < right.firstNode->next->coeff) {
		clear();
		firstNode->next = new PolynomialNode(0, 0);
		firstNode->next->next = firstNode;
		listSize = 1;
		return *this;
	}

	Polynomial result, remainder, backup(*this);

	PolynomialNode* cur = result.firstNode;
	PolynomialNode* curLeft = firstNode->next;
	PolynomialNode* curRight = right.firstNode->next;

	while (curLeft->exp >= curRight->exp) {
		double quotient = curLeft->coeff / curRight->coeff;
		int resultExp = curLeft->exp - curRight->exp;
		cur->next = new PolynomialNode(quotient, resultExp);
		cur = cur->next;
		cur->next = result.firstNode;
		result.listSize++;

		remainder = backup;
		Polynomial poly1 = right;
		poly1.multiply(result);
		remainder.subtract(poly1);

		curLeft = remainder.firstNode->next;
		curRight = right.firstNode->next;
	}

	swap(listSize, result.listSize);
	swap(firstNode, result.firstNode);

	return *this;
}


ostream& operator<<(ostream& out, Polynomial& bi) {
	bi.output(out);
	return out;
}