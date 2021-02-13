#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;
#include "CDA.cpp"

template<typename elmtype>
void printCDA(CDA<elmtype> x) {
	cout << "[";
	for (int i=0; i<x.Length()-1; i++) cout << x[i] << " ";
	if (x.Length() > 0) cout << x[x.Length()-1];
	cout << "]";
}

int main() {
	CDA<int> A;
	cout << "Default constructor, length, capacity: " << A.Length() << " = 0, " << A.Capacity() << " = 1" << endl << endl;

	A.AddEnd(3); A.AddFront(0); A.AddEnd(1); A.DelFront(); A.AddFront(2); A.AddFront(1); A.DelEnd(); A.AddEnd(4);
	cout << "Adding/deleting, doubling capacity: ";
	printCDA(A);
	cout << " = [1 2 3 4], " << A.Length() << " = 4, " << A.Capacity() << " = 4" << endl << endl;

	CDA<int> B = A;
	B.DelEnd();
	cout << "Copy constructor: ";
	printCDA(A);
	cout << " = [1 2 3 4], ";
	printCDA(B);
	cout << " = [1 2 3]" << endl << endl;
	
	A = B;
	for (int i = 4; i <= 15; i++) B.AddEnd(i);
	cout << "Copy assignment operator: ";
	printCDA(A);
	cout << " = [1 2 3], ";
	printCDA(B);
	cout << " = [1 2 3 4 5 6 7 8 9 10 11 12 13 14 15]" << endl << endl;
	
	for (int i = 15; i > 3; i--) 
	{
		B.DelFront();
		//printCDA(B);
		//cout << endl;
	}
	cout << "Halving capacity: " << B.Length() << " = 3, " << B.Capacity() << " = 8" << endl << endl;

	A.Clear();
	cout << "Clear: " << A.Length() << " = 0, " << A.Capacity() << " = 4" << endl << endl;

	//cout << "HERE" << endl << endl << endl;

	A.AddEnd(0);
	//printCDA(A);

	for (int i = 1; i <= 5; i++) {
		A.AddEnd(i);
		A.AddFront(-i);
		A.Reverse();
	}
	//printCDA(A);

	A.DelEnd(); A.DelFront(); A.AddEnd(10); A.Reverse(); A.DelEnd(); 
	cout << "Reversing: ";
	printCDA(A);
	cout << " = [10 4 -3 2 -1 0 1 -2 3]" << endl << endl;

	CDA<int> C(10);
	cout << "Fixed size contructor: " << C.Length() << " = 10, " << C.Capacity() << " = 10" << endl << endl;

	C[0] = 1;
	C[1] = 4;
	C[2] = 19;
	C[3] = 8;
	C[4] = 13;
	C[5] = 3;
	C[6] = 15;
	C[7] = 7;
	C[8] = 20;
	C[9] = 12;
	cout << "Bracket operator: ";
	printCDA(C);
	cout << " = [1 4 19 8 13 3 15 7 20 12]" << endl << endl;

	cout << "Bracket operator errors (should be two of them): " << endl;
	C[10] = 0;
	C[-1] = 1;
	cout << endl;

	cout << "Select: " << C.Select(8) << " = 15, " << C.Select(6) << " = 12, " << C[1] << " = 4" << endl << endl;

	//C.Print();

	cout << "Search: " << C.Search(3) << " = 5, " << C.Search(5) << " = -1" << endl << endl;
	
	C.Sort();
	cout << "Sort: ";
	printCDA(C);
	cout << " = [1 3 4 7 8 12 13 15 19 20]" << endl << endl;

	cout << "Binary Search: " << C.BinSearch(3) << " = 1, " << C.BinSearch(5) << " = " << ~(3) << ", " << C.BinSearch(30) << " = " << ~(10) << endl << endl;

	CDA<string> D;
	D.AddEnd("pizza"); D.AddEnd("dog"); D.AddEnd("cat"); D.Reverse(); D.DelEnd(); D.AddFront("mouse"); D.AddEnd("caterpillar"); D.Reverse(); D.AddFront("elephant"); D.AddEnd("lion");
	cout << "Adding/deleting/reversing with strings: ";
	printCDA(D);
	cout << " = [elephant caterpillar dog cat mouse lion]" << endl << endl;

	cout << "Select/Search with strings: " << D.Select(2) << " = caterpillar, " << D.Search("cat") << " = 3, " << D.Search("frog") << " = -1" << endl << endl;

	D.Sort();
	cout << "Sort with strings: ";
	printCDA(D);
	cout << " = [cat caterpillar dog elephant lion mouse]" << endl << endl;

	cout << "Binary Search with strings: " << D.BinSearch("cat") << " = 0, " << D.BinSearch("frog") << " = " << ~(4) << ", " << D.BinSearch("zebra") << " = " << ~(6) << endl;
	
	return 0;
}