#include <iostream>

using namespace std;

class Bracket {
    public:

        Bracket() {

        }

        int operator[](int index) 
        {
            return vals[index];
        }

        void test()
        {
            cout << (*this)[0] << endl;
        }

        int vals[5] = {1,2,3,4,5};
};

int main()
{
    Bracket b;

    b.test();
}