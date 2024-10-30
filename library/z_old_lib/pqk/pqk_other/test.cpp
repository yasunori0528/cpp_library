#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

#include "../pqk_lib/pqk_all.cpp"

int main(){
    while(1){
        int N; cin >> N;
        vector<string> V(N);
        for(int i = 0; i < N; i++) cin >> V[i];
        cout << max_number(V) << endl;
    }
}