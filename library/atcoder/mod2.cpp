#include <bits/stdc++.h>
using namespace std;

int64_t get_time(){
    struct::timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * int64_t(1'000'000'000) + t.tv_nsec;
}

template<typename T>
T pow_mod(T a, T b, T n){
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
T ex_euclid(T a, T b, T &x, T &y){
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
struct modint{
    int64_t val;

    modint(){
        val = 0;
    }

    modint(int64_t a){
        if(a <= -mod) a %= mod;
        else if(a >= mod) a %= mod;
        if(a < 0) a += mod;
        val = a;
    }

    modint inv(){
        int64_t x, k;
        int64_t d = ex_euclid(val, mod, x, k);
        assert(d == 1);
        return modint(x);
    }

    bool operator==(modint other){
        return val == other.val;
    }
    bool operator!=(modint other){
        return val != other.val;
    }

    modint operator+(modint other){
        return modint(val + other.val);
    }
    modint operator-(modint other){
        return modint(val - other.val);
    }
    modint operator*(modint other){
        return modint(val * other.val);
    }
    modint operator/(modint other){
        return modint(val * other.inv().val);
    }

    void operator+=(modint other){
        val += other.val;
        if(val >= mod) val -= mod;
    }
    void operator-=(modint other){
        val -= other.val;
        if(val < 0) val += mod;
    }
    void operator*=(modint other){
        val *= other.val;
        val %= mod;
    }
    void operator/=(modint other){
        val *= other.inv().val;
        val %= mod;
    }

    void operator++(){
        val++;
        if(val >= mod) val -= mod;
    }
    void operator--(){
        val--;
        if(val < 0) val += mod;
    }
};

template <int64_t mod>
modint<mod> pow(modint<mod> a, int64_t b){
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
pair<vector<modint<mod>>, vector<modint<mod>>> init_mod_factorial(int N){
    using mint = modint<mod>;

    vector<mint> v(N+1);
    vector<mint> v_inv(N+1);
    for(int i = 0; i <= N; i++){
        if(i == 0) v[i] = 1;
        else v[i] = v[i - 1] * i;
    }
    for(int i = N; i >= 0; i--){
        if(i == N) v_inv[i] = v[i].inv();
        else v_inv[i] = v_inv[i+1] * (i + 1);
    }

    return make_pair(v, v_inv);
}

template <int64_t mod>
modint<mod> factorial_mod(int64_t x, pair<vector<modint<mod>>, vector<modint<mod>>> &factorial_list){
    return factorial_list.first[x];
}

template <int64_t mod>
modint<mod> factorial_inv_mod(int64_t x, pair<vector<modint<mod>>, vector<modint<mod>>> &factorial_list){
    return factorial_list.second[x];
}

template <int64_t mod>
modint<mod> comb_mod(int64_t x, int64_t y, pair<vector<modint<mod>>, vector<modint<mod>>> &factorial_list){
    if(y < 0 || x < y) return modint<mod>(0);
    return factorial_list.first[x] * factorial_list.second[y] * factorial_list.second[x - y];
}

int main(){
    
}
//static mod
