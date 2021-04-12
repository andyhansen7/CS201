#include <iostream>

class Knapsack
{
    public:
        Knapsack(int P[], int W[], int n, int M) 
        {
            int T[n+1][M+1];

            for(int i = 0; i <= n; i++)
            {
                for(int j = 0; j <= M; j++)
                {
                    T[i][j] = 0;
                }
            }
    
            // Loop through items
            for(int j = 0; j <= n; j++)
            {
                // Loop through all weights
                for(int k = 0; k <= M; k++)
                {
                    // No item = no value
                    if(j == 0 || k == 0) T[j][k] = 0;

                    // Item too heavy, use last combination
                    else if(k < W[j]) 
                        T[j][k] = T[j-1][k];

                    // Try to fit item
                    else
                        T[j][k] = maxValue(T[j-1][k], T[j-1][k-W[j]] + P[j]);
                }
            }
        
            // Print table
            std::cout << "   ";
            for(int j = 0; j <= M; j++) std::cout << j << '\t';
            std::cout << std::endl;

            for(int k = 0; k <= n; k++)
            {
                std::cout << k << "  ";

                for(int j = 0; j <= M; j++)
                {
                    std::cout << T[k][j] << '\t';
                }

                std::cout << std::endl;
            }

            std::cout << std::endl;

            // Find items used in table
            int currentM = M;
            int currentN = n;

            std::cout << "Solution: ";

            while(currentM > 0 && currentN > 0)
            {
                // Item is used
                if(T[currentN-1][currentM] < T[currentN][currentM])
                {
                    std::cout << currentN << ", ";
                    currentM -= W[currentN];
                    currentN -= 1;
                }

                // Item unused
                else 
                {
                    currentN -= 1;
                }
            }

        }

        int maxValue(int a, int b)
        {
            if(a > b) return a;
            else return b;
        }
};

int main()
{
    int n = 4;
    int P[n] = { 0, 12, 15, 16, 18};
    int W[n] = { 0, 2, 3, 4, 6};
    int M = 8;

    Knapsack k(P, W, n, M);

    return 0;
}