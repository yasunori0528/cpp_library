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
}