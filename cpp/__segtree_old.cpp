#include <bits/stdc++.h>
using namespace std;

template <typename T>
bool chmax(T &a, const T& b) {
    if (a < b) {
        a = b;  // aをbで更新
        return true;
    }
    return false;
}

template <typename T>
bool chmin(T &a, const T& b) {
    if (a > b) {
        a = b;  // aをbで更新
        return true;
    }
    return false;
}

template <typename T>
T exEuclid(T a, T b, T &x, T &y){
    T d = a;
    if(b != 0){
        d = exEuclid(b, a%b, y, x);
        y -= (a/b)*x;
    }
    else{
        x = 1;
        y = 0;
    }
    //cout << a << " * " << x << " + " << b << " * " << y << " = " << d << endl;
    return d;
}

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
        int64_t x, y, d;
        d = exEuclid(other.n, p, x, y);
        int64_t rtn = x*n;
        if(d > 1) rtn /= d;
        return modint(rtn);
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
        int64_t x, y, d;
        d = exEuclid(other.n, p, x, y);
        n *= x;
        if(d > 1) n /= d;
        if(n <= p || p <= n) n %= p;
        if(n < 0) n += p;
        return;
    }
    void operator++(){
        n++;
        if(n == p) n = 0;
        return;
    }
    void operator--(){
        n--;
        if(n == -1) n = p-1;
        return;
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

void init_fact(int64_t n){
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
    for(int64_t i = min(n, mod-1); i >= 0; i--){
        if(i == min(n, mod-1)){
            inv_fact_mod_v[i] = modint(fact_mod_v[i]).pow(-1);
        }
        else{
            inv_fact_mod_v[i] = modint(inv_fact_mod_v[i+1].n*(i+1));
        }
        //cout << i << endl;
    }
}

template <typename T>
struct segtree_min{
    int sz;
    vector<T> dat;
    T NUL;

    segtree_min(){
        ;
    }

    segtree_min(int n){
        NUL = 1;
        while(chmax(NUL,2*NUL));

        sz = 1;
        while(sz <= n) sz *= 2;

        dat.resize(2*sz-1,NUL);
    }

    void update(int k, T a){
        k += sz-1;
        dat[k] = a;
        while(k > 0){
            k = (k-1)/2;
            dat[k] = min(dat[2*k+1],dat[2*k+2]);
        }
    }

    //[a,b)
    T get(int a, int b){
        return sub_get(a, b, 0, 0, sz);
    }

    T sub_get(int a, int b, int k, int l, int r){
        if(r <= a || b <= l) return NUL;
        if(a <= l && r <= b) return dat[k];
        T vl = sub_get(a, b, 2*k+1, l, (l+r)/2);
        T vr = sub_get(a, b, 2*k+2, (l+r)/2, r);
        return min(vl, vr);
    }
};

template <typename T>
struct segtree_max{
    int sz;
    vector<T> dat;
    T NUL;

    segtree_max(){
        ;
    }
    
    segtree_max(int n){
        NUL = -1;
        while(chmin(NUL,2*NUL));

        sz = 1;
        while(sz <= n) sz *= 2;

        dat.resize(2*sz-1,NUL);
    }

    void update(int k, T a){
        k += sz-1;
        dat[k] = a;
        while(k > 0){
            k = (k-1)/2;
            dat[k] = max(dat[2*k+1],dat[2*k+2]);
        }
    }

    //[a,b)
    T get(int a, int b){
        return sub_get(a, b, 0, 0, sz);
    }

    T sub_get(int a, int b, int k, int l, int r){
        if(r <= a || b <= l) return NUL;
        if(a <= l && r <= b) return dat[k];
        T vl = sub_get(a, b, 2*k+1, l, (l+r)/2);
        T vr = sub_get(a, b, 2*k+2, (l+r)/2, r);
        return max(vl, vr);
    }
};

template <typename T>
struct segtree_plus{
    int sz;
    vector<T> dat;
    T NUL;

    segtree_plus(){
        ;
    }
    
    segtree_plus(int n){
        NUL = 0;

        sz = 1;
        while(sz <= n) sz *= 2;

        dat.resize(2*sz-1,NUL);
    }

    void update(int k, T a){
        k += sz-1;
        dat[k] = a;
        while(k > 0){
            k = (k-1)/2;
            dat[k] = dat[2*k+1] + dat[2*k+2];
        }
    }

    //[a,b)
    T get(int a, int b){
        return sub_get(a, b, 0, 0, sz);
    }

    T sub_get(int a, int b, int k, int l, int r){
        if(r <= a || b <= l) return NUL;
        if(a <= l && r <= b) return dat[k];
        T vl = sub_get(a, b, 2*k+1, l, (l+r)/2);
        T vr = sub_get(a, b, 2*k+2, (l+r)/2, r);
        return vl + vr;
    }
};

struct segtree_rolling_hash{
    int64_t b;
    int64_t p;
    int sz;
    vector<modint> dat;
    modint NUL;

    segtree_rolling_hash(){
        ;
    }

    segtree_rolling_hash(int n, int64_t c, int64_t q){
        b = c;
        p = q;
        NUL = modint(0, p);
        sz = 1;
        while(sz <= n) sz *= 2;
        dat.resize(2*sz-1,NUL);
    }

    void update(int k, modint a){
        k += sz-1;
        dat[k] = a * modint(b, p).pow(k);
        while(k > 0){
            k = (k-1)/2;
            dat[k] = dat[2*k+1] + dat[2*k+2];
        }
    }

    //[a,b)
    T get(int a, int b){
        return sub_get(a, b, 0, 0, sz);
    }

    T sub_get(int a, int b, int k, int l, int r){
        if(r <= a || b <= l) return NUL;
        if(a <= l && r <= b) return dat[k];
        T vl = sub_get(a, b, 2*k+1, l, (l+r)/2);
        T vr = sub_get(a, b, 2*k+2, (l+r)/2, r);
        return vl + vr;
    }
};
