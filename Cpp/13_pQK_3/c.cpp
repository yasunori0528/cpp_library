#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

template <typename T>
bool chmax(T &a, const T& b) {
    if (a < b) {
        a = b;  // aをbで更新
        return true;
    }
    return false;
}

mpz_class f(mpz_class x){
    mpz_class rtn = 0;
    while(x){
        rtn += x % 10;
        x /= 10;
    }
    return rtn;
}

int main(){
    int N = 90;
    vector<mpz_class> V(N, 1);
    for(int i = 1; i < N; i++){
        V[i] = V[i-1]*2;
    }

    for(int i = 0; i < N; i++){
        mpz_class msd = V[i];
        while(msd >= 10) msd /= 10;
        if(msd >= 8) continue;
        cout << V[i];
        cout << string(N, '0');
    }
    cout << endl;
}