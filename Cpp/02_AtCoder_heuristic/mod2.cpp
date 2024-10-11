#include <bits/stdc++.h>
using namespace std;

int64_t mod;
struct modint{
    int64_t n;
    int64_t p;

    modint(){
        n = 0;
        p = mod;
    }
    modint(int64_t a){
        if(a <= -mod) a %= mod;
        else if(a >= mod) a %= mod;
        if(a < 0) a += mod;
        n = a;
        p = mod;
    }
    modint(int64_t a, int64_t q){
        if(a <= -q) a %= q;
        else if(a >= q) a %= q;
        if(a < 0) a += q;
        n = a;
        p = q;
    }

    modint pow(int64_t a){
        if(a <= 1-p) a %= p-1;
        else if(a >= p-1) a %= p-1;
        if(a < 0) a += p-1;

        modint rtn;
        if(n == 0) {
            rtn.n = 0;
            return rtn;
        }
        if(n == 1) {
            rtn.n = 1;
            return rtn;
        }
        if(a == 0) {
            rtn.n = 1;
            return rtn;
        }
        if(a == 1) {
            rtn.n = n;
            return rtn;
        }

        int64_t b = a/2;
        int64_t c = a%2;
        rtn = pow(b);
        rtn *= rtn;
        if(c){
            rtn *= modint(n);
        }
        return rtn;
    }

    modint operator+(modint other){
        modint rtn(n+other.n, p);
        return rtn;
    }
    modint operator-(modint other){
        modint rtn(n-other.n, p);
        return rtn;
    }
    modint operator*(modint other){
        modint rtn(n*other.n, p);
        return rtn;
    }
    modint operator/(modint other){
        modint rtn(n*(other.pow(-1)).n, p);
        return rtn;
    }

    void operator+=(modint other){
        n += other.n;
        if(n >= p) n %= p;
    }
    void operator-=(modint other){
        n -= other.n;
        if(n < 0) n += p;
    }
    void operator*=(modint other){
        n *= other.n;
        if(n >= p) n %= p;
    }
    void operator/=(modint other){
        n *= (other.pow(-1)).n;
        if(n >= p) n %= p;
    }
};

vector<modint> fact_mod_v;
vector<modint> inv_fact_mod_v;

modint comb_mod(int64_t n, int64_t m){
    if(n < 0 || m < 0 || m > n) return 0;
    modint rtn = fact_mod_v[n]*inv_fact_mod_v[m]*inv_fact_mod_v[n-m];
    return rtn;
}

modint comb_mod_small(int64_t n, int64_t m){
    if(m < mod){
        return comb_mod(n%mod, m);
    }
    return comb_mod_small(n/mod, m/mod)*comb_mod(n%mod, m%mod);
}

void init_fact(int n){
    fact_mod_v.resize(n+1,0);
    inv_fact_mod_v.resize(n+1,0);
    for(int64_t i = 0; i <= n; i++){
        if(i == 0){
            fact_mod_v[i] = modint(1);
        }
        else{
            fact_mod_v[i] = modint(i*fact_mod_v[i-1].n);
        }
        //cout << i << endl;
    }
    for(int64_t i = n; i >= 0; i--){
        if(i == n){
            inv_fact_mod_v[i] = modint(fact_mod_v[i]).pow(-1);
        }
        else{
            inv_fact_mod_v[i] = modint(inv_fact_mod_v[i+1].n*(i+1));
        }
        //cout << i << endl;
    }
}

int main(){
    mod = 998244353;
    init_fact(50000);

    int64_t n, m; cin >> n >> m;
    modint x(n);
    modint y(m);

    cout << (x+y).n << endl;
    cout << (x-y).n << endl;
    cout << (x*y).n << endl;
    cout << (x/y).n << endl;
    cout << x.pow(m).n << endl;
    cout << comb_mod(n,m).n << endl;
}