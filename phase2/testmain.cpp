#include <iostream>
#include "RBTree.cpp"

using namespace std;

int main() 
{
    RBTree t;

    for(int i = 0; i < 10; i++) {
        t.insert(i, i);
        t.inorder();
        cout << endl;
    }
    cout << endl << t.size() << endl;
    cout << *(t.predecessor(2)) << endl;
    cout << *(t.successor(6)) << endl;

    return 0;
}