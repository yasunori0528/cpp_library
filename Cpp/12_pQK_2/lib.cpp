#include <bits/stdc++.h>
#include <gmpxx.h>
using namespace std;

//a^b
mpz_class pow(mpz_class a, int b){
    if(a == 0) return 0;
    if(b == 0) return 1;
    if(a == 1) return 1;
    if(b == 1) return a;

    mpz_class rtn = pow(a,b/2);
    rtn *= rtn;
    if(b%2) rtn *= a;
    return rtn;
}

// floor(log2(a))
int log(mpz_class a){
    if(a == 1) return 0;
    return log(a/2)+1;
}

// b*floor(log2(a))
int log(mpz_class a, int b){
    if(a == 1) return 0;
    return log(a)*b;
}

mpz_class INF = pow((mpz_class)10,72);

mpz_class pow_vec(vector<int64_t> &v){
    int sz = v.size();
    if(sz == 0) return 1;
    if(sz == 1) return v[0];
    if(v[0] == 0) return 0;
    if(v[0] == 1) return 1;
}

struct composite {
    mpz_class n;
    vector<vector<int64_t>> prime_factor;
    vector<mpz_class> sub;
    composite(){
        n = 1;
    }

    void push_back(vector<int64_t> v){
        ;
    }

};

int main(){
    ;
}