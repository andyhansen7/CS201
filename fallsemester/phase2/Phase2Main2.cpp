#include <iostream>
using namespace std;
#include "Two4Tree.cpp"

int main(){

	/* TESTED WORKING 
	char K[10] = {'A','B','C','D','E','F','G','H','I','K'};
	int V[10] = {10,9,8,7,6,5,4,3,2,1};
	
	Two4Tree<char,int> T1, T2(K,V,10);
	
	for(int i=0; i<10; i++) T1.insert(K[i],V[i]);
	// T1 and T2 should be identical trees

    //T1.inorder();
    T1.inorder();
    T2.inorder();
	
	cout << *(T1.search('C')) << endl;
    cout << *(T2.search('C')) << endl;
	// Should output 8
	
	cout << T1.rank('C') << endl;
    cout << T2.rank('C') << endl;
	//Should output 3
	
	cout << T1.select(3) << endl;
    cout << T2.select(3) << endl;
	//Should output C 
	
    T1.preorder();
	T2.preorder();
	//Should output D B A C F H E G I K
	
    T1.inorder();
	T2.inorder();
	//Should output	A B C D E F G H I K
	
    cout << T1.remove('C') << endl;
	cout << T2.remove('C') << endl;
	//Should output 1
	
    T1.preorder();
	T2.preorder();
	//Should output F B A D E H G I K
	
    T1.inorder();
	T2.inorder();
	//Should output	A B D E F G H I K
	
    cout << T1.remove('J') << endl;
	cout << T2.remove('J') << endl;
	//Should output 0
	
    cout <<T1.rank('G') << endl;
	cout <<T2.rank('G') << endl;
	//Should output 6
	
    cout <<T1.successor('D')<<endl;
	cout <<T2.successor('D')<<endl;
	//Should output E
	
	cout <<T1.predecessor('D')<<endl;
    cout <<T2.predecessor('D')<<endl;
	//Should output B		
    
	
    Two4Tree<int,int> X;
	//for (int i=1;i<20;i++) {  }
    
    
	for (int i=1;i<100;i++) {
		X.insert(i,i); 
		X.inorder();
        //cout << X.rank(i) << ", " << i << endl;
		//if(X.rank(i) != i) cout << "Rank error" << endl;
        //cout << X.select(i) << ", " << i << endl;
		//if(X.select(i) != i) cout << "Select error" << endl;
        //cout << *(X.search(i)) << ", " << i << endl;
		//if(*(X.search(i)) != i) cout << "Search error" << endl;
	}*/

	/*Two4Tree<int,int> X;
	for (int i=1;i<10000;i++) X.insert(i,i);

	for (int i=1;i<10000;i++) {
		if(X.rank(i) != i) cout << "Rank error" << endl;
		if(X.select(i) != i) cout << "Select error" << endl;
		if(*(X.search(i)) != i) cout << "Search error" << endl;

		//cout << i << endl;
	} 

	X.inorder();*/


	Two4Tree<int, int> K;

	for(int i = 0; i < 20; i++) K.insert(i, i);

	K.inorder();

	Two4Tree<int, int> A(K);

	A.inorder();

	Two4Tree<int, int> B;
	B = K;

	B.inorder();
    
	//Should be no output and should take seconds, not minutes
	return 0;
}