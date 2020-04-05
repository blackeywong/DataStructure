#include "PolynomialInVector.h"
#include "../../DS5/exceptions.h"

PolynomialInVector::PolynomialInVector(istream& in) {
	in >> degree;
	if (degree > 0) {
		coefficients = new vector<int>(degree + 1, 0);
	}
	int para;
	for (int i = 0; i <= degree && in >> para;i++) {
		(*coefficients)[i] = para;
	}
}

void PolynomialInVector::checkIndex(const int exponent) const {
	if (exponent < 0 || exponent > degree) {
		ostringstream s;
		s << "exponent = " << exponent << " degree = " << degree;
		throw IllegalIndex(s.str());
	}
}


void PolynomialInVector::output(ostream& out) const {
	if (coefficients->size() == 0) return;
	out << degree << " ";
	for (int i = 0; i <= degree ; i++) {
		out << (*coefficients)[i] << " ";
	}
}

void PolynomialInVector::copyData(const PolynomialInVector& other) {
	degree = other.degree;
	if (degree > 0) {
		coefficients = new vector<int>(degree + 1, 0);
	}
	copy(other.coefficients->begin(), other.coefficients->end(), coefficients->begin());
}

PolynomialInVector& PolynomialInVector::add(const PolynomialInVector& right){
	int maxdegree = degree > right.degree ? degree : right.degree;
	vector<int>* newCoeff = nullptr;
	newCoeff = new vector<int>(maxdegree + 1, 0);

	int i = 0;
	for (; i <= degree && i <= right.degree; i++) {
		(*newCoeff)[i] = (*coefficients)[i] + (*right.coefficients)[i];
	}
	for (; i <= degree; i++) {
		(*newCoeff)[i] = (*coefficients)[i];
	}
	for (; i <= right.degree; i++) {
		(*newCoeff)[i] = (*right.coefficients)[i];
	}

	//search for the largest index of non-zero, as the degree of result
	for (i = maxdegree; i > 0; i--) {
		if ((*newCoeff)[i] != 0) break;
	}
	degree = i;
	delete coefficients;
	coefficients = newCoeff;
	return *this;
}
PolynomialInVector& PolynomialInVector::subtract(const PolynomialInVector& right) {
	int maxdegree = degree > right.degree ? degree : right.degree;
	vector<int>* newCoeff = nullptr;
	newCoeff = new vector<int>(maxdegree + 1, 0);

	int i = 0;
	for (; i <= degree && i <= right.degree; i++) {
		(*newCoeff)[i] = (*coefficients)[i] - (*right.coefficients)[i];
	}
	for (; i <= degree; i++) {
		(*newCoeff)[i] = (*coefficients)[i];
	}
	for (; i <= right.degree; i++) {
		(*newCoeff)[i] = - (*right.coefficients)[i];
	}

	//search for the largest index of non-zero, as the degree of result
	for (i = maxdegree; i > 0; i--) {
		if ((*newCoeff)[i] != 0) break;
	}
	degree = i;
	delete coefficients;
	coefficients = newCoeff;
	return *this;
}
PolynomialInVector& PolynomialInVector::multiply(const PolynomialInVector& right) {
	if (degree == 0 && (coefficients->size() == 0 || (*coefficients)[0] ==0)) return *this;
	if (right.degree == 0 && (right.coefficients->size() == 0 || (*right.coefficients)[0] == 0)) {
		degree = 0;
		coefficients->clear();
		coefficients->push_back(0);
		return *this;
	}

	int resultdegree = degree + right.degree;
	vector<int>* newCoeff = new vector<int>(resultdegree + 1, 0);
	for (int i = 0; i <= degree; i++) {
		for (int j = 0; j <= right.degree; j++) {
			(*newCoeff)[i+j] += (*coefficients)[i] * (*right.coefficients)[j];
		}
	}

	degree = resultdegree;
	delete coefficients;
	coefficients = newCoeff;
	return *this;
}
PolynomialInVector& PolynomialInVector::divide(const PolynomialInVector& right) {
	if (right.degree == 0 && (right.coefficients->size() == 0 || (*right.coefficients)[0] == 0)) {
		throw OutOfBounds();
	}

	if(degree < right.degree || degree == right.degree && (*coefficients)[degree] < (*right.coefficients)[degree]){
		degree = 0;
		coefficients->clear();
		return *this;
	}
	
	for (int i = 0; i <= degree - right.degree; i++) {
		int quotient = (*coefficients)[degree - i] / (*right.coefficients)[right.degree];
		(*coefficients)[degree - i] = quotient;
		for (int j = degree - i -1, k = right.degree - 1; k>=0; j--, k--) {
			(*coefficients)[j] -= quotient * (*right.coefficients)[k];
		}
	}
	degree = degree - right.degree;
	vector<int>* newCoeff = new vector<int>(degree + 1, 0);
	for (int i = degree; i >= 0; i--) {
		(*newCoeff)[i] = (*coefficients)[i + right.degree];
	}

	delete coefficients;
	coefficients = newCoeff;
	return *this;
}


ostream& operator<<(ostream& out, PolynomialInVector& bi) {
	bi.output(out);
	return out;
}