#include <bits/stdc++.h>
using namespace std;

int64_t get_time() {
    struct::timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * int64_t(1'000'000'000) + t.tv_nsec;
}

template<typename T>
T pow_mod(T a, T b, T n) {
    a %= n;
    if(a == 0) return 0;
    if(a == 1 || b == 0) return 1;
    if(b == 1) return a;
    T c = b/2;
    T d = b%2;
    T ac = pow_mod(a,c,n);
    T ad = pow_mod(a,d,n);
    return ac*ac%n*ad%n;
}

template <typename T>
T ex_euclid(T a, T b, T &x, T &y) {
    T d = a;
    if(b != 0){
        d = ex_euclid(b, a%b, y, x);
        y -= (a/b)*x;
    }
    else{
        x = 1;
        y = 0;
    }
    //cout << a << " * " << x << " + " << b << " * " << y << " = " << d << endl;
    return d;
}

template <int64_t mod>
struct modint {
private:
    int64_t val;

public:
    modint() {
        val = 0;
    }

    modint(int64_t a) {
        if(a <= -mod) a %= mod;
        else if(a >= mod) a %= mod;
        if(a < 0) a += mod;
        val = a;
    }

    modint inv() {
        int64_t x, k;
        int64_t d = ex_euclid(val, mod, x, k);
        assert(d == 1);
        return modint(x);
    }

    int64_t get() {
        return val;
    }

    int64_t p() {
        return mod;
    }

    bool operator==(modint other) {
        return val == other.val;
    }
    bool operator!=(modint other) {
        return val != other.val;
    }

    modint operator+(modint other) {
        return modint(val + other.val);
    }
    modint operator-(modint other) {
        return modint(val - other.val);
    }
    modint operator*(modint other) {
        return modint(val * other.val);
    }
    modint operator/(modint other) {
        return modint(val * other.inv().val);
    }

    void operator+=(modint other) {
        val += other.val;
        if(val >= mod) val -= mod;
    }
    void operator-=(modint other) {
        val -= other.val;
        if(val < 0) val += mod;
    }
    void operator*=(modint other) {
        val *= other.val;
        val %= mod;
    }
    void operator/=(modint other) {
        val *= other.inv().val;
        val %= mod;
    }

    void operator++() {
        val++;
        if(val >= mod) val -= mod;
    }
    void operator--() {
        val--;
        if(val < 0) val += mod;
    }
};

template <int64_t mod>
modint<mod> pow(modint<mod> a, int64_t b) {
    using mint = modint<mod>;

    if(b <= -(mod - 1)) b %= mod - 1;
    else if(b >= (mod - 1)) b %= mod - 1;
    if(b < 0) b += mod - 1;

    if(a == 0) return mint(0);
    if(b == 0) return mint(1);
    if(a == 1) return mint(1);
    if(b == 1) return a;

    mint x = pow(a, b / 2);
    mint y = pow(a, b % 2);
    return x * x * y;
}

template <int64_t mod>
struct fact_mod {
private:
    int64_t sz;
    vector<modint<mod>> factorial; // factorial[i] = i!
    vector<modint<mod>> factorial_inv; // factorial_inv[i] = 1 / i!

public:
    fact_mod() {}

    fact_mod(int64_t sz_) {
        sz = min(mod, sz_);
        factorial.resize(sz);
        factorial_inv.resize(sz);
    }

    void build() {
        for(int64_t i = 0; i < sz; i++) {
            if(i == 0) factorial[i] = 1;
            else factorial[i] = factorial[i-1] * i;
        }
        for(int64_t i = sz - 1; i >= 0; i--) {
            if(i == sz - 1) factorial_inv[i] = factorial[i].inv();
            else factorial_inv[i] = factorial_inv[i+1] * (i+1);
        }
    }

    modint<mod> fact(int64_t x) {
        if(x >= mod) return 0;
        assert(0 <= x && x < sz);
        return factorial[x];
    }

    modint<mod> fact_inv(int64_t x) {
        assert(0 <= x && x < sz);
        return factorial_inv[x];
    }

    modint<mod> comb(int64_t x, int64_t y) {
        if(x < 0) return 0;
        if(y < 0 || x < y) return 0;
        if(x >= mod) return comb(x / mod, y / mod) * comb(x % mod, y % mod);
        return fact(x) * fact_inv(y) * fact_inv(x - y);
    }
};

int main(){
    const int64_t mod = 998244353;
    int max_n = 10000000;
    int n = 1000;

    int64_t t_start = get_time();
    using mint = modint<mod>;
    fact_mod<mod> F(max_n);
    F.build();

    vector C(n+1, vector<mint>(n+1));
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= i; j++) {
            C[i][j] = F.comb(i, j);
            if(j == 0 || j == i) assert(C[i][j] == 1);
            else assert(C[i][j] == C[i-1][j-1] + C[i-1][j]);
        }
    }
    
    int64_t t_end = get_time();
    cout << (t_end - t_start) / 1e9 << "[s]" << endl;
}
//static prime mod
