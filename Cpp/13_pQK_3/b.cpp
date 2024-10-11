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
    mpz_class x;
    cin >> x;
    vector<mpz_class> V = {x};
    auto y = x;
    while(y%2 == 0){
        y /= 2;
        V.push_back(y);
    }
    int N = V.size();
    vector<mpz_class> W(N);
    for(int i = 0; i < N; i++){
        W[i] = f(V[i]);
    }

    int cnt = 0;
    mpz_class a1 = V[0];
    int ans = 0;
    mpz_class a2 = V[0];
    for(int i = 0; i < N-1; i++){
        if(W[i] < W[i+1]) cnt++;
        else {
            cnt = 0;
            a1 = V[i+1];
        }
        if(chmax(ans, cnt)) a2 = V[i+1];
    }
    cout << ans << endl;
    cout << a2 << endl;
}