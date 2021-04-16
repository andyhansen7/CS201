#include "CDA.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    /* Sorting tests
    CDA<int> a(100);
    for(int i = 0; i < 100; i++) a[i] = (rand() % 1000) - 500;
    a.Print();
    cout << endl <<endl;

    a.MergeSort();
    a.Print();
    cout << endl <<endl;

    for(int i = 0; i < 100; i++) a[i] = (rand() % 1000) - 500;
    a.InsertionSort();
    a.Print();
    cout << endl <<endl;

    for(int i = 0; i < 100; i++) a[i] = (rand() % 1000);
    a.CountingSort(1000);
    a.Print();
    cout << endl <<endl;
    */

    /* Adding, deleting and selecting tests 
    CDA<int> b;
    b.AddEnd(1);
    b.AddFront(2);
    b.AddEnd(3);
    b.AddFront(4);
    b.AddEnd(5);
    b.AddFront(6);

    b.Print();
    cout << b.SetOrdered() << endl;
    cout << b.Select(3) << endl;
    b.Print();
    b.MergeSort();
    cout << b.SetOrdered() << endl;
    b.Print();

    cout << b.Select(1) << endl;
    cout << b.Select(3) << endl;
    b.Print();

    cout << b.Search(1) << endl;
    cout << b.Search(3) << endl;
    */

    CDA<int> c(10);
    for(int i = 0; i < 10; i++) c[i] = i;
    c.Print();

    CDA<int> d(c);
    d.Print();

    CDA<int> e = d;
    e.Print();

    return 0;
}