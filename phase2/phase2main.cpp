#include <iostream>
#include "RBTree.cpp"

using namespace std;

int main() 
{
    RBTree<int, int> t;

    for(int i = 0; i < 10; i++) {
        t.insert(i, i);
        t.inorder();
        cout << endl;
    }
    //cout << endl << t.size() << endl;
    //cout << *(t.predecessor(2)) << endl;
    //cout << *(t.successor(6)) << endl;

    //for(int i = 1; i <  11; i++) cout << t.select(i) << endl;

    /*cout << endl << endl;

    for(int i = 0; i < 10; i++ ) {
        t.remove(i);
        t.inorder();
        cout << endl << endl;
    }*/

    /*for(int i = 0; i < 10; i++) {
        std::cout << *(t.search(i)) << endl;
    }*/

    cout << endl << endl;

    RBTree<int, int> a(t);
    t.inorder();

    RBTree<int, int> b = t;
    b.inorder();

    return 0;
}