#include <iostream>
#include "RBTree.cpp"

using namespace std;

int main() 
{
    RBTree t;

    for(int i = 0; i < 10; i++) t.insert(i, i);
    t.inorder();
    //cout << endl << t.size() << endl;

    return 0;
}