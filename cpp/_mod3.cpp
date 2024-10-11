#include <bits/stdc++.h>
using namespace std;

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

struct modint{
    int64_t val;
    int64_t mod;

    modint(){
        val = 0;
        mod = 1;
    }

    modint(int64_t a, int64_t p){
        if(a <= -p) a %= p;
        else if(a >= p) a %= p;
        if(a < 0) a += p;
        val = a;
        mod = p;
    }

    modint inv(){
        int64_t x, k;
        int64_t d = ex_euclid(val, mod, x, k);
        assert(d == 1);
        return modint(x, mod);
    }

    bool operator==(modint other){
        return val == other.val && mod == other.mod;
    }
    bool operator!=(modint other){
        return val != other.val || mod != other.mod;
    }

    modint operator+(modint other){
        assert(mod == other.mod);
        return modint(val + other.val, mod);
    }
    modint operator-(modint other){
        assert(mod == other.mod);
        return modint(val - other.val, mod);
    }
    modint operator*(modint other){
        assert(mod == other.mod);
        return modint(val * other.val, mod);
    }
    modint operator/(modint other){
        assert(mod == other.mod);
        return modint(val * other.inv().val, mod);
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

modint pow(modint a, int64_t b){
    if(b <= -(a.mod - 1)) b %= a.mod - 1;
    else if(b >= (a.mod - 1)) b %= a.mod - 1;
    if(b < 0) b += a.mod - 1;

    if(a.val == 0) return modint(0, a.mod);
    if(b == 0) return modint(1, a.mod);
    if(a.val == 1) return modint(1, a.mod);
    if(b == 1) return a;

    modint x = pow(a, b / 2);
    modint y = pow(a, b % 2);
    return x * x * y;
}

pair<vector<modint>, vector<modint>> init_mod_factorial(int64_t mod, int N){
    vector<modint> v(N+1);
    vector<modint> v_inv(N+1);
    for(int i = 0; i <= N; i++){
        if(i == 0) v[i] = modint(1, mod);
        else v[i] = v[i - 1] * modint(i, mod);
    }
    for(int i = N; i >= 0; i--){
        if(i == N) v_inv[i] = v[i].inv();
        else v_inv[i] = v_inv[i+1] * modint(i + 1, mod);
    }

    return make_pair(v, v_inv);
}

modint factorial_mod(int64_t x, pair<vector<modint>, vector<modint>> &factorial_list){
    return factorial_list.first[x];
}

modint factorial_inv_mod(int64_t x, pair<vector<modint>, vector<modint>> &factorial_list){
    return factorial_list.second[x];
}

modint comb_mod(int64_t x, int64_t y, pair<vector<modint>, vector<modint>> &factorial_list){
    if(y < 0 || x < y) return modint(0, factorial_list.first[0].mod);
    return factorial_list.first[x] * factorial_list.second[y] * factorial_list.second[x - y];
}

int main(){
    int T;
    int64_t mod;

    cin >> T >> mod;
    auto fact_list = init_mod_factorial(mod, min(mod-1, (int64_t)10'000'000));

    for(int i = 0; i < T; i++){
        int64_t n, k;
        cin >> n >> k;
        cout << comb_mod(n, k, fact_list).val << endl;
    }
}
//dynamic mod
