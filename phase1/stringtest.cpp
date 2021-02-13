#include <iostream>
#include <string>

using namespace std;

template<typename T>
class Arr {
    public:

    Arr() {
        arr = new T[5];
    }

    T& operator[](int i) { return arr[i]; }

    T* arr;
};

int main() {
    //string* a = new string[5];
    Arr<string> a;

    for(int i = 0; i < 5; i++) a[i] = std::to_string(i);

    for(int i = 0; i < 5; i++) std::cout << a[i] << endl;

    return 0;
}