#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "CDA.cpp"

using namespace std;

CDA<int> arr;

void PrintArr() {
    for(int i = 0; i < 125; i++){
        for(int j = 0; j < 8; j++)  cout << arr[(8*i) + j] << "\t";
        cout << endl;
    }
}

int main() {
    srand(time(NULL));

    for(int i= 0; i < 1000; i++) {
        arr.AddFront((rand() % 5000) - 2500);
        //arr.AddFront(i);
    }

    cout << "INITIAL ARRAY:" << endl << endl << endl;

    PrintArr();

    cout << endl << endl << "SORTING TEST" << endl << endl << endl;

    arr.Sort();

    PrintArr();

    for(int i = 1; i < 998; i++) if(arr[i-1] > arr[i] || arr[i+1] < arr[i]) cout << "FUCKED" << endl;

    for(int i = 0; i < 1000; i++) {
        int target = arr[i];
        int actual = arr.Select(i + 1);

        if(actual != target) cout << "FUCKED SELECT" << endl;
    }
    
}