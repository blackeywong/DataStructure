// DS1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

////Example 1-3
template<class T>
inline void Swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}
//int j = 0;
//template<class T>
//void Perm(T list[], int k, int m) {
//	j++;
//	int i;
//	if (k == m) {
//		for (i = 0; i <= m; i++)
//			;// cout << list[i];
//		cout << endl;
//	}
//	else {
//		for (i = k; i <= m; i++) {
//			Swap(list[k], list[i]);
//			Perm(list, k + 1, m);
//			Swap(list[k], list[i]);
//		}
//	}
//}
//
//int main()
//{
//	char s[] = "abc";
//	Perm<char>(s,0,2);
//}

////Exercise 1
//template<class T>
//bool Input(T& n) {
//	cout << "Please input a non-negative number: ";
//	for (int i = 0; i < 3; i++) {
//		cin >> n;
//		if (n >= 0) return true;
//		cout << "negative number! Please input again." << endl;
//	}
//
//	return false;
//}
//
//
//int main()
//{
//	int n = 0;
//	if (Input<int>(n)) {
//		cout << n << endl;
//	}
//}

////Exercise 2
//template<class T>
//bool testSort(T list[], int k, int m) {
//	if (k + 1 <= m) {
//		return (list[k] <= list[k+1]) && testSort(list, k+1, m);
//	}
//	else return true;
//}
//
//
//int main()
//{
//	int list[] = {1,2,3,4,4,6};
//	if (testSort(list,0,5)) {
//		cout << "yes!" << endl;
//	}
//}

////Exercise 3
//int factorial(int n) {
//	int result = 1;
//	for (int i = 1; i <= n; i++) {
//		result *= i;
//	}
//	return result;
//}
//
//
//int main()
//{
//	cout << factorial(10) << endl;
//}

////Exercise 4
//int fibonacci(int n) {
//	if (n == 0 || n == 1) {
//		//cout << n <<", ";
//		return n;
//	} 
//	int m = fibonacci(n - 2) + fibonacci(n - 1);
//	//cout << m << ", ";
//	return m;
//}
//
//int fibonacci2(int n) {
//	if (n == 0 || n == 1) {
//		//cout << n <<", ";
//		return n;
//	}
//	int result = 0, r1 = 0, r2 = 1;
//	for (int i = 2; i <= n; i++) {
//		result = r1 + r2;
//		r1 = r2;
//		r2 = result;
//	}
//	return result;
//}
//
//
//int main()
//{
//	cout << fibonacci2(5) << endl;
//}

////Exercise 5
//void subset(char list[], int tag[], int n) {
//	if (n == 3) {
//		cout << "{";
//		for (int i = 0; i < n; i++) {
//			if (tag[i] == 1)
//				cout << list[i] << " ";
//		}
//		cout << "}" << endl;
//		return;
//	}
//
//	tag[n] = 0;
//	subset(list, tag, n + 1);
//	tag[n] = 1;
//	subset(list, tag, n + 1);
//
//}
//
//
//
//int main()
//{
//	char list[] = "abc";
//	int tag[5];
//	subset(list, tag, 0);
//
//}

////Exercise 6
//bool exist(int list[], int k, int size, int x) {
//	if (list[k] == x) {
//		return true;
//	}
//	if (k >= size) {
//		return false;
//	}
//
//	return exist(list, k + 1, size, x);
//
//}
//
//
//
//int main()
//{
//	int list[4] = {1, 2, 3, 4};
//	cout << exist(list, 0, 4, 0) << endl;
//	
//}

////Exercise 7
//template<class T>
//T* ChangeSize1D(T* a, int n, int toSize) {
//	//auto b = make_shared<T*>();
//	T* b = new T[toSize];
//	T* tmp1 = a;
//	T* tmp2 = b;
//	for (int i = 0; i < n; i++) {
//		*b++ = *a++;
//	}
//
//	delete[] tmp1;
//
//	return tmp2;
//}
//
//int main() {
//	int* a = new int[5]{ 1,2,3 };
//	int * b = ChangeSize1D<int>(a, 3, 7);
//	delete[]b;
//	//cout << size(b) << endl;
//}

////Exercise 8
//template<class T>
//T** ChangeSize2D(T** a, int nRow, int nCol, int toSizeRow, int toSizeCol) {
//	//auto b = make_shared<T*>();
//	T** b = new T*[toSizeRow];
//	for (int i = 0; i < toSizeRow; i++) {
//		b[i] = new T[toSizeCol];
//	}
//
//	for (int i = 0; i < nRow; i++) {
//		for(int j=0;j < nCol; j++){
//			b[i][j] = a[i][j];
//		}
//	}
//
//	for (int i = 0; i < nRow; i++) {
//		delete[] a[i];
//	}
//	delete [] a;
//
//	return b;
//}
//
//int main() {
//	int** a = new int*[5];
//	for (int i = 0; i < 5; i++) {
//		a[i] = new int[5]{1,2,3};
//	}
//
//	int** b = ChangeSize2D<int>(a, 3, 3, 7, 7);
//	for (int i = 0; i < 7; i++) {
//		delete[] b[i];
//	}	delete[]b;
//	//cout << size(b) << endl;
//}

//Excercise 7
//int main() {
//	char a = -1;
//	cout << (int)(unsigned char)a << endl;
//	short b = -1;
//	cout << (unsigned short)b << endl;
//	int c = -1;
//	cout << (unsigned int)c << endl;
//	long d = -1;
//	cout << (unsigned long)d << endl;
//	long long e = -1;
//	cout << (unsigned long long)e << endl;
//}

//Excercise 12
//enum sign {plus, minus};
//class Currency {
//	friend istream& operator>>(istream& in, Currency& x);
//	friend ostream& operator<<(ostream& out, const Currency& x);
//public:
//	// ¹¹Ôìº¯Êý
//	Currency(sign s = sign::plus, unsigned long d = 0, unsigned int c = 0);
//	// Îö¹¹º¯Êý
//	~Currency() {}
//	bool operator=(int a);
//	bool operator=(double a);
//	sign Sign() const
//	{
//		if (amount < 0) return sign::minus;
//		else return sign::plus;
//	}
//	unsigned long Dollars() const
//	{
//		if (amount < 0) return (-amount) / 100;
//		else return amount / 100;
//	}
//	unsigned int Cents() const
//	{
//		if (amount < 0)
//			return -amount - Dollars() * 100;
//		else return amount - Dollars() * 100;
//	}
//	Currency operator+(const Currency & x) const;
//	Currency operator-(const Currency& x) const;
//	Currency operator*(const double x) const;
//	Currency operator/(const double x) const;
//	Currency operator%(const double x) const;
//	Currency& operator+=(const Currency & x)
//	{
//		amount += x.amount; return *this;
//	}
//
//	Currency& operator-=(const Currency& x) {
//		amount -= x.amount;
//		return *this;
//	}
//
//	Currency& operator*=(const double x) {
//		amount = (long)amount * x;
//		return *this;
//	}
//
//	Currency& operator/=(const double x) {
//		if (x == 0.0) {
//			cout << "divide 0!" << endl;
//			exit(1);
//		}
//		amount = (long)amount / x;
//		return *this;
//	}
//
//	Currency& operator%=(const float x) {
//		if (x == 0.0) {
//			cout << "divide 0!" << endl;
//			exit(1);
//		}
//		amount = (long) amount / 100.0 * x;
//		return *this;
//	}
//
//private:
//	long amount;
//};
//class BadInitializers {
//public:
//	BadInitializers() {}
//};
//Currency::Currency(sign s, unsigned long d, unsigned int c)
//{// ´´½¨Ò»¸öC u r r e n c y¶ÔÏó
//	if (c > 99) throw BadInitializers();
//	amount = d * 100 + c;
//	if (s == sign::minus) amount = -amount;
//}
//bool Currency::operator=(int a)
//{// È¡Öµ
//	amount = a;
//	return true;
//}
//bool Currency::operator=(double a)
//{// È¡Öµ
//sign sgn;
//	if (a < 0) { sgn = sign::minus; a = -a; }
//	else sgn = sign::plus;
//	amount = (a + 0.001) * 100;
//	if (sgn == sign::minus) amount = -amount;
//	return true;
//}
//
//	Currency Currency::operator+(const Currency & x) const
//{// °Ñx ÀÛ¼ÓÖÁ* t h i s .
//	Currency y;
//	y.amount = amount + x.amount;
//	return y;
//}
//
//	Currency Currency::operator-(const Currency& x) const
//	{
//		Currency y;
//		y.amount = amount - x.amount;
//		return y;
//	}
//
//	Currency Currency::operator*(const double x) const
//	{
//		Currency y;
//		double f = amount/100.0 * x;
//		y = f;
//		return y;
//	}
//
//	Currency Currency::operator/(const double x) const
//	{
//		if (x == 0.0) {
//			cout << "Devide 0!" << endl;
//			exit(1);
//		}
//		Currency y;
//		double f = amount / 100.0 / x;
//		y = f;
//		return y;
//	}
//
//	Currency Currency::operator%(const double x) const
//	{
//		if (x == 0.0) {
//			cout << "divide 0!" << endl;
//			exit(1);
//		}
//		Currency y;
//		double f = amount /10000.0 * x;
//		y=f;
//		return y;
//	}
//
//// ÖØÔØ< <
//ostream& operator<<(ostream& out, const Currency& x)
//{
//	// ½«currency µÄÖµ²åÈëµ½Êä³öÁ÷
//	long a = x.amount;
//	if (a < 0) { out << '-'; a = -a; }
//	long d = a / 100; // ÃÀÔª
//	out << '$' << d << '.';
//	int c = a - d * 100; // ÃÀ·Ö
//	if (c < 10) out << "0";
//	out << c;
//	return out;
//}
//
//istream& operator>>(istream& in, Currency& x) {
//	float a = 0.0;
//	in >> a;
//
//	x=a;
//
//	return in;
//}
//
//void main(void)
//{
//	Currency g, h(sign::plus, 3, 50), i, j,k,l,m, n, o, p, q;
//	g=225;
//	i = -6.45;
//	j = h + g;
//	cout << j << endl;
//	i += h;
//	cout << i << endl;
//	j = i + g + h;
//	cout << j << endl;
//	j = (i += g) + h;
//	cout << j << endl;
//	cout << i << endl;
//	k = i * 2.25;
//	m = i / 2.25;
//	n = i % 22.5;
//	cin >> o;
//	n *= 2.25;
//	m /= 2.25;
//	k %= 2.25;
//
//
//}
//////////////////////////////////////////////////////////////////////////////
//µÚ¶þ°æ
//Exercise 21
//int func(int n) {
//	if (n % 2 == 0)
//		return n / 2;
//	else
//		return func(n * 3 + 1);
//}

//int func(int n) {
//	if (n % 2 == 0)
//		return n / 2;
//	else
//		return (n * 3 + 1)/2;
//}
//
//
//int main()
//{
//	cout << func(1) << endl;
//	cout << func(2) << endl;
//	cout << func(3) << endl;
//	cout << func(4) << endl;
//	cout << func(5) << endl;
//	cout << func(6) << endl;
//	cout << func(7) << endl;
//	cout << func(8) << endl;
//}

//Exercise 22
//long long count1 = 0; 
//long long ackermann(long long i, long long j) {
//	if (i < 1 || j < 1) {
//		cout << "bad i,j" << endl;
//		return -1;
//	}
//	count1++;
//	if (i == 1)
//		return 1LL << j;
//	else if (j == 1)
//		return ackermann(i - 1, 2);
//	else
//		return ackermann(i-1, ackermann(i,j-1));
//
//}
//
//int main() {
//	//cout << ackermann(1,1) << endl;
//	//cout << ackermann(1, 2) << endl;
//	//cout << ackermann(2, 1) << endl;
//	//cout << ackermann(2, 2) << endl;
//	//cout << ackermann(3, 1) << endl;
//	//cout << ackermann(1, 3) << endl;
//	//cout << ackermann(3, 2) << endl;
//	//cout << ackermann(2, 3) << endl;
//	cout << ackermann(3, 3) << endl;
//	cout << ::count1 << endl;
//}

//Exercise 23
//int gcd(int x, int y) {
//	if (x < 0 || y < 0)
//	{
//		cout << "bad x, y" << endl;
//		return -1;
//	}
//	if (y == 0)
//		return x;
//	else
//		return gcd(y, x % y);
//}
//
//int main()
//{
//	cout << gcd(20, 30) << endl;
//	cout << gcd(112, 42) << endl;
//}

//Exercise 26
//string GrayCode(int n) {
//	if (n == 1) return "1";
//	return GrayCode(n - 1) + "," + to_string(n) + "," + GrayCode(n - 1);
//}
//
//int main() {
//	cout << GrayCode(3) << endl;
//	cout << GrayCode(4) << endl;
//}

//Exercise 27
//template<class T, class S>
//T accumulate(S start, S end, T initialValue)
//{
//	while (start != end) {
//		initialValue += *start++;
//	}
//	return initialValue;
//}
//
//
//int Add(int a, int b) {
//	return a + b;
//}
//
//int Multi(int a, int b) {
//	return a * b;
//}
//
////Exercise 28
//template<class T, class S>
//T accumulate(S start, S end, T initialValue, T (*Oper)(T,T))
//{
//	while (start != end) {
//		initialValue = Oper(initialValue, *start++);
//	}
//	return initialValue;
//}
//
////Exercise 29
//template<class T, class S>
//T* copy(S start, S end, T* to)
//{
//	T* ret = to;
//	while (start != end) {
//		*to++ = *start++;
//	}
//	return ret;
//}
//
//int main()
//{
//	int list[] = { 1,3,5,7 };
//	//int res = accumulate<int, int*>(list, list+4, 0);
//	//int res = accumulate<int, int*>(list, list + 4, 0, Add);
//	//int res = accumulate<int, int*>(list, list + 4, 1, Multi);
//	//cout << res << endl;
//
//	int list2[4];
//	copy<int, int*>(list,list+4,list2);
//	for(int a: list2)
//		cout << a << " ";
//	cout << endl;
//}

//template<class T>
//bool my_next_permutation(T first, T last)
//{
//	if(first == last) return false;//empty
//	T i = last;
//	i--;
//	if(first == i) return false; //only 1 item
//
//	for(;;){
//		T ii = i;
//		i--;
//		if(*i < * ii)
//		{
//			T j = last;
//			while(*i>*--j)
//				;
//
//			iter_swap(i,j);
//			reverse(ii,last);
//			return true;
//		}
//		if(i == first)
//		{
//			reverse(first,last);
//			return false;
//		}
//	}
//
//}
//
//template<class T>
//void permutations(T list[], int k, int m)
//{
//	do{
//		copy(list+k, list+m+1,ostream_iterator<T>(cout,""));
//		cout << endl;
//	//}while(next_permutation(list+k,list+m+1));
//	//}while(my_next_permutation(list+k,list+m+1));
//	}while(my_next_permutation<char*>(list+k,list+m+1));
//}
////Exercise 30
//template<class T>
//void all_permutations(T list[], int k, int m)
//{
//	sort(list+k, list+m+1);
//	permutations<char>(list, k,m);
//
//}
////Exercise 31
//template<class T>
//void all_permutations2(T list[], int k, int m)
//{
//	T*list2=new T[m-k+1];
//	copy(list+k,list+m+1,list2);
//	do{
//		copy(list+k, list+m+1,ostream_iterator<T>(cout,""));
//		cout << endl;
//	}while(next_permutation(list+k,list+m+1));
//
//	prev_permutation(list2,list2+m-k+1);//abandon the origin one
//	do{
//		copy(list2, list2+m-k+1,ostream_iterator<T>(cout,""));
//		cout << endl;
//	}while(prev_permutation(list2,list2+m-k+1));
//}
//
////Exercise 32
//template<class T>
//void all_permutations3(T list[], int k, int m)
//{
//	do{
//		//copy(list+k, list+m+1,ostream_iterator<T>(cout,""));
//		//cout << endl;
//	}while(next_permutation(list+k,list+m+1));
//
//	do{
//		copy(list+k, list+m+1,ostream_iterator<T>(cout,""));
//		cout << endl;
//	}while(next_permutation(list+k,list+m+1));
//}
//
//int main()
//{
//	char list[] = {'b', 'd', 'a', 'c', 'e'};
//	//permutations<char>(list, 1,3);
//	//all_permutations<char>(list, 1,3);
//	//all_permutations2<char>(list, 1,3);
//	all_permutations3<char>(list, 1,3);
//
//}

////Exerciese 33, 39
//template<class T, class S>
//int my_count(T first, T last, const S& value)
//{
//	int res = 0;
//	while(first != last)
//	{
//		if(*first++ == value)
//			++res;
//	}
//	return res;
//}
//
//int main()
//{
//	int list[] = {1,3,5,3,9};
//	//cout << count(list,list+4,3) << endl;
//	cout << my_count(list,list+4,0) << endl;
//}

////Exerciese 34, 40
//template<class T, class S>
//void my_fill(T first, T last, const S& value)
//{
//	int res = 0;
//	while(first != last)
//		*first++ = value;
//}
//
//int main()
//{
//	int list[5];
//	//fill(list+1,list+4,3);
//	my_fill(list+1,list+4,2);
//
//	for(int n: list)
//		cout << n << " ";
//	cout << endl;
//}

////Exerciese 35, 41
//template<class T, class S>
//int my_inner_product(T first1, T last1, T first2, const S& initValue)
//{
//	S res = 0;
//	while(first1 != last1)
//	{
//		res += *first1++ * *first2++;
//	}
//	return res;
//}
//
//int main()
//{
//	int list1[] = {1,3,5,3,9};
//	int list2[] = {2,4,6,8,10};
//	//cout << inner_product(list1+1,list1+4,list2+1, 0) << endl;
//	cout << my_inner_product(list1+1,list1+4,list2+1,0) << endl;
//}

////Exerciese 36, 42
//template<class T, class S>
//void my_iota(T first, T last, const S& value)
//{
//	int index = 0;
//	while(first != last)
//		*first++ = index++ + value;
//}
//
//int main()
//{
//	int list[5]= {1,3,5,3,9};
//	//iota(list+1,list+4,3);
//	my_iota(list+1,list+4,3);
//
//	for(int n: list)
//		cout << n << " ";
//	cout << endl;
//}
//
////Exerciese 37, 43
//template<class T>
//bool my_is_sorted(T first, T last)
//{
//	T next = first+1;
//	while(next != last)
//	{
//		if(*first++ > * next++)
//			return false;
//	}
//	return true;
//}
//
//int main()
//{
//	int list[] = {1,3,3,7,9};
//	//cout << is_sorted(list+1,list+4) << endl;
//	cout << my_is_sorted(list+1,list+4) << endl;
//}

//Exerciese 38, 44
template<class T>
pair<T,T> my_mismatch(T first1, T last1, T first2)
{
	while(first1 != last1)
	{
		if(*first1 ! *first2)
			break;
		++first1;
		++first2;
	}
	return make_pair(first1,first2);
}

int main()
{
	int list1[] = {1,3,3,7,9};
	int list2[] = {1,3,3,6,9};
	pair<int*,int*> p = mismatch(list1+1,list1+4, list2+1);
	cout << *(p.first) << " " << *(p.second) << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

