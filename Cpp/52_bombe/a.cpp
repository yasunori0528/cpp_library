#include <bits/stdc++.h>
using namespace std;

int main() {
    int n_max = 4;
    int m_max = 20;
    for(int n = 2; n <= n_max; n++) {
        for(int m = 2; m <= m_max; m++) {
            int a = m + (1 << n) - 2;
            int b = (1 << n) - 2;
            vector<int> loop(a, 0);
            for(int i = a - b; i < a; i++) loop[i] = 1;

            do{
                
            }while(next_permutation(loop.begin(), loop.end()));
        }
    }
}
