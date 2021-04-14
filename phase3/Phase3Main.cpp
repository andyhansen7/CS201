#include <iostream>
using namespace std;
#include "Heap.cpp"
#include "BHeap.cpp"


int main(){
	string A[10] = {"A","B","C","D","E","F","H","I","J","K"};
	int B[10] = {10,9,8,7,6,5,4,3,2,1};
	
	/*
	Heap<int> T1, T2(B,10);
	
	T2.printKey();
	//Should output  1 2 4 3 6 5 8 10 7 9
	
	for(int i=0; i<10; i++) {
		T1.insert(B[i]);
		//T1.printKey();
	}
	
	T1.printKey();
	// Should output 1 2 5 4 3 9 6 10 7 8
	
	cout << T2.peekKey() << endl;
	//Should output 1
	
	cout << T1.extractMin() << endl;
	//Should output 1
	
	T1.printKey();
	//Should output 2 3 5 4 8 9 6 10 7

	Heap<int> C(T1);
	Heap<int> D = C;

	C.printKey();
	D.printKey();
	*/
	/*BHeap<int> x;
	for(int i = 1; i < 9; i++) x.insert(i);
	x.printKey();

	//cout << x.extractMin() << endl;
	//x.printKey();

	cout << x.peekKey() << endl;*/
	

	
	BHeap<string> X(A,10);//, Y;

	X.printKey();
	//Should output 
	//B1
	//J K
	//
	//B3
	//A E H I F C D B

	/*
	cout << X.extractMin() << endl;
	//Should output A
	
	X.printKey();
	//Should output
	//B0
	//B
	//
	//B3
	//C E H I F J K D
	
	Y.insert("M"); 
	Y.insert("O");
	Y.insert("G");
	Y.insert("N");
	Y.insert("L");
	
	Y.printKey();
	//Should output
	//B0
	//L
	//
	//B2
	//G M O N
	
	Y.merge(X);
	cout << Y.peekKey() << endl;
	//Should output B
	
	Y.printKey();
	//Should output
	//B1
	//B L
	//
	//B2
	//G M O N
	//
	//B3
	//C E H I F J K D
    */
			
	return 0;
}