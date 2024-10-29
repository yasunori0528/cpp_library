#include <bits/stdc++.h>
using namespace std;

const uint64_t rh_mod = 0x1FFFFFFFFFFFFFFF;
const uint64_t rh_mask30 = 0x3FFFFFFF;
const uint64_t rh_mask31 = 0x7FFFFFFF;
const uint64_t rh_mask61 = rh_mod;
uint64_t rh_base;
vector<uint64_t> rh_base_pow;
uint64_t rh_mul(uint64_t a, uint64_t b){
    uint64_t au = a >> 31;
    uint64_t ad = a & rh_mask31;
    uint64_t bu = b >> 31;
    uint64_t bd = b & rh_mask31;
    uint64_t mid = ad * bu + au * bd;
    uint64_t midu = mid >> 30;
    uint64_t midd = mid & rh_mask30;

    uint64_t x = au * bu * 2 + midu + (midd << 31) + ad * bd;
    uint64_t xu = x >> 61;
    uint64_t xd = x & rh_mask61;

    uint64_t rtn = xu + xd;
    if(rtn >= rh_mod) rtn -= rh_mod;
    return rtn;
}

struct monoid_rolling_hash{
    uint64_t val;
    int size;

    monoid_rolling_hash(){
        val = 0;
        size = 0;
    }
    monoid_rolling_hash(char c){
        val = (int)c;
        size = 1;
    }

    monoid_rolling_hash e(){
        return monoid_rolling_hash();
    }

    monoid_rolling_hash operator*(monoid_rolling_hash other){
        monoid_rolling_hash rtn;
        rtn.size = size + other.size;
        rtn.val = rh_mul(val, rh_base_pow[other.size]) + other.val;
        if(rtn.val >= rh_mod) rtn.val -= rh_mod;
        return rtn;
    }
};

void init_rh_base(int N){
    rh_base = (uint64_t(1) << 32) + rand();
    rh_base_pow.resize(N+1);
    rh_base_pow[0] = 1;
    for(int i = 1; i <= N; i++){
        rh_base_pow[i] = rh_mul(rh_base_pow[i-1], rh_base);
    }
}

int main(){
    srand(time(NULL));
    int N; cin >> N;
    for(int i = 0; i < N; i++){
        uint64_t a = rand();
        uint64_t b = rand();
        uint64_t c = rand();
        uint64_t d = rand();
        uint64_t x = (a << 32) + b;
        uint64_t y = (c << 32) + d;
        x %= rh_mod;
        y %= rh_mod;
        __uint128_t p = rh_mul(x, y);
        __uint128_t q = __uint128_t(x) * y % rh_mod;
        if(p != q){
            cout << x << " " << y << " " << (uint64_t)(q-p) << endl;
        }
    }
}