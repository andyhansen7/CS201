#include <iostream>
#include "Two4Tree.cpp"
//#include "234tree-example.h"

using namespace std;

int main() {
    int K[10] = {1,2,3,4,5,6,7,8,9,10};
    Two4Tree<int, int> a(K, K, 10);

    //a.debug();

    /*a.insert(1,1);
    //a.inorder();

    a.insert(2,2);
    //a.inorder();

    a.insert(3,3);
    //a.inorder();

    a.insert(4,4);
    //a.inorder();

    a.insert(5,5);
    //a.inorder();

    a.insert(0,0);
    //a.inorder();

    a.insert(8,8);
    //a.inorder();

    a.insert(12,12);
    //a.inorder();

    a.insert(15,15);
    a.inorder();*/

    

    /*cout << a.size() << endl;

    cout << a.rank(5) << endl;

    cout << a.sucessor(5) << endl;
    cout << a.predecessor(5) << endl;

    cout << a.select(1) << endl;
    cout << a.select(2) << endl;
    cout << a.select(3) << endl;*/

    //a.remove(3);
    //a.remove(0);
    //a.remove(15);
    
    a.inorder();
    
    return 0;
}