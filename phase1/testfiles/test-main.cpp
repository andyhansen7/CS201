#include <iostream>
#include "./CDA.cpp"

using namespace std;

int main() 
{
    // Default constructor test
    CDA<int> A;

    A.AddEnd(3);    // 3
    A.AddFront(0);  // 0 3
    A.AddEnd(1);    // 0 3 1
    A.Print();

    A.DelFront();   // 3 1
    A.AddFront(2);  // 2 3 1
    A.AddFront(1);  // 1 2 3 1
    A.Print();

    A.DelEnd();     // 1 2 3 
    A.Print();
    A.AddEnd(4);    // 1 2 3 4
    A.Print();

    /*
    // Operator testing
    A.AddFront(1);
    A.AddFront(2);
    A.AddFront(3);
    A.AddFront(4);

    A.Print();  // 4 3 2 1

    A.Reverse();

    A.Print(); // 1 2 3 4

    A.AddFront(5);
    A.AddEnd(0);

    A.Print(); // 5 4 3 2 1 0

    A.Reverse();
    A.DelFront();
    A.Print();  // 1 2 3 4 5

    A.DelEnd();
    A.Print();  // 1 2 3 4

    A.DelEnd();
    A.DelEnd();
    A.Print();  // 1 2
    
    A.Reverse();
    A.DelEnd();
    A.Print();  // 2

    A.AddEnd(1);
    A.AddFront(3);
    A.AddFront(4);
    A.Reverse();
    A.Print();      // 1 2 3 4

    // Alternate constructor tests
    CDA<int> B(123);

    CDA<int>C = A;
    C.Print();      // 1 2 3 4

    CDA<int> D(C);
    D.Reverse();
    D.Print();      // 4 3 2 1

    // Clear test
    D.Clear();
    D.Print();
    D.AddEnd(5);
    D.AddFront(4);
    D.AddFront(3);
    D.AddFront(2);
    D.Reverse();
    D.Print();      // 5 4 3 2

    // Search test
    cout << D.Search(5) << endl;    // 0
    cout << D.Search(-1) << endl;   // -3
    cout << D.Search(7) << endl;    // -5

    // Sorting test
    CDA<int> E;
    E.AddEnd(17);
    E.AddEnd(99);
    E.AddEnd(123);
    E.AddEnd(345);
    E.AddEnd(8);
    E.Sort();
    E.Print();      // 8 17 99 123 345

    // Binary search test
    cout << E.BinSearch(17) << endl;    // 1
    cout << E.BinSearch(123) << endl;    // 3

    // Select test
    cout << E.Select(1) << endl;    // 8
    cout << E.Select(2) << endl;    // 17
    cout << E.Select(5) << endl;    // 345
    */


    return 0;
}
