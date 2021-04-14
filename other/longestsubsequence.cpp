#include <iostream>

using namespace std;

class LongestSequence
{
    public:
        LongestSequence(char* M, int lM, char* N, int lN)
        {
            int L[lM + 1][lN + 1];

            for(int j = 0; j <= lM; j++)
            {
                for(int k = 0; k <= lN; k++)
                {
                    if(j == 0 || k == 0) L[j][k] = 0;

                    else if(M[j] == N[k]) L[j][k] = L[j-1][k-1] + 1;

                    else
                    {
                        if(L[j-1][k] > L[j][k-1]) L[j][k] = L[j-1][k];
                        else L[j][k] = L[j][k-1];
                    }
                }
            } 

            std::cout << "LCS: " << L[lM][lN] << std::endl << std::endl;

            // Print top row
            std::cout << "   ";
            for(int i = 0; i <= lN; i++) std::cout << i << '\t';
            std::cout << std::endl;

            // Print array
            for(int j = 0; j <= lM; j++)
            {
                std::cout << j << "  ";

                for(int k = 0; k <= lN; k++)
                {
                    std::cout << L[j][k] << '\t';
                }

                if(j>0) std::cout << M[j-1];

                std::cout << std::endl;
            }

            std::cout << "   \t";
            for(int i = 0; i < lN; i++) std::cout << N[i] << '\t';
            std::cout << std::endl << std::endl;
        }
};

int main()
{
    char* m = "abbcba";
    int lm = 6;
    char* n = "cbabca";
    int ln = 6;

    LongestSequence seq(m, lm, n, ln);

    return 0;
}