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
    int maxcnt = 0;
    mpz_class x;
    cin >> x;
    vector<pair<mpz_class,mpz_class>> v = {{x, f(x)}};
    mpz_class y = x;
    while(1){
        y *= 2;
        mpz_class s = f(y);
        if(v[v.size()-1].second > s) v.push_back({y, s});
        else break;
    }
    cout << v.size() << endl;
}