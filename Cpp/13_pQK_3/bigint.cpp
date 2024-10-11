#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

const int bit_size = 64;
const uint64_t mask_64 = 0xFFFF'FFFF'FFFF'FFFF;

random_device seed_gen;
mt19937 engine(seed_gen());

uint64_t rand64(){
    uint64_t a = engine();
    uint64_t b = engine();
    return (a << 32) + b;
}

template<typename T>
void invec(vector<T> &v){
    for(auto &i : v) cin >> i;
    return;
}

template<typename T>
void outvec(vector<T> &v){
    bool b = false;
    for(auto i : v){
        if(b) cout << " ";
        else b = true;
        cout << i;
    }
    return;
}

struct biguint{
    size_t sz;
    vector<uint64_t> val;

    biguint(){
        sz = 0;
        val = {};
    }

    biguint(uint64_t x){
        sz = 1;
        val = {x};
    }

    biguint(__uint128_t x){
        sz = 2;
        val = {uint64_t(x & mask_64), uint64_t(x >> 64)};
    }

    biguint(size_t a, uint64_t x){
        sz = a;
        val.resize(sz);
        val[0] = x;
    }

    biguint(vector<uint64_t> x){
        sz = x.size();
        val = x;
    }

    biguint operator<<(size_t x){
        if(x == 0) return *this;
        size_t y = x / bit_size;
        size_t z = x % bit_size;

        biguint rtn(sz + y + 1, 0);
        for(size_t i = 0; i <= sz; i++){
            if(i < sz) rtn.val[i + y] = val[i] << z;
            if(i >= 0) rtn.val[i + y] |= val[i - 1] >> (bit_size - z);
        }

        return rtn;
    }

    biguint operator>>(size_t x){
        if(x == 0) return *this;
        size_t y = x / bit_size;
        size_t z = x % bit_size;

        if(y >= sz) return biguint(0UL);

        biguint rtn(sz - y, 0);
        for(size_t i = 0; i < sz - y; i++){
            if(i < sz - y) rtn.val[i] = val[i+y] >> z;
            if(i >= 0 && i + 1 < sz) rtn.val[i] |= val[i + 1] << (bit_size - z);
        }

        return rtn;
    }

    biguint operator+(biguint other){
        biguint rtn(max(sz, other.sz), 0);
        uint64_t c = 0;

        for(size_t i = 0; i < rtn.sz; i++){
            uint64_t xi = 0;
            if(i < sz) xi = val[i];
            uint64_t yi = 0;
            if(i < other.sz) yi = other.val[i];

            uint64_t rtn_i = xi + c;
            c = rtn_i < c;
            rtn_i += yi;
            c += rtn_i < yi;

            rtn.val[i] = rtn_i;
        }

        if(c){
            rtn.val.push_back(0);
            rtn.val[sz]++;
            rtn.sz++;
        }

        return rtn;
    }

    biguint operator-(biguint other){
        biguint rtn(max(sz, other.sz), 0);
        uint64_t c = 0;

        for(size_t i = 0; i < rtn.sz; i++){
            uint64_t xi = 0;
            if(i < sz) xi = val[i];
            uint64_t yi = 0;
            if(i < other.sz) yi = other.val[i];

            uint64_t pi = xi - c;
            c = pi > xi;
            uint64_t rtn_i = pi - yi;
            c += rtn_i > pi;

            rtn.val[i] = rtn_i;
        }

        if(c){
            cout << "ERROR : returned negative value." << endl;
            for(auto i : val) cout << bitset<64>(i) << " ";
            cout << endl;
            for(auto i : other.val) cout << bitset<64>(i) << " ";
            cout << endl;
            assert(false);
        }

        while(*(rtn.val.rbegin()) == 0) rtn.val.pop_back();
        rtn.sz = rtn.val.size();
        /*cout << "minus : ";
        print();
        cout << " - ";
        other.print();
        cout << endl;*/
        return rtn;
    }

    bool operator==(biguint other){
        size_t max_sz = max(sz, other.sz);
        for(size_t i = max_sz - 1; ; i--){
            uint64_t xi = (i < sz) ? val[i] : 0;
            uint64_t yi = (i < sz) ? other.val[i] : 0;
            if(xi == yi) continue;
            return false;
            if(i == 0) break;
        }
        return true;
    }

    bool operator<(biguint other){
        size_t max_sz = max(sz, other.sz);
        for(int i = (int)max_sz - 1; i >= 0; i--){
            uint64_t xi = (i < (int)sz) ? val[i] : 0;
            uint64_t yi = (i < (int)other.sz) ? other.val[i] : 0;
            if(xi == yi) continue;
            return (xi < yi);
        }
        return false;
    }

    bool operator>(biguint other){
        size_t max_sz = max(sz, other.sz);
        for(int i = (int)max_sz - 1; i >= 0; i--){
            uint64_t xi = (i < (int)sz) ? val[i] : 0;
            uint64_t yi = (i < (int)other.sz) ? other.val[i] : 0;
            if(xi == yi) continue;
            return (xi > yi);
        }
        return false;
    }

    bool operator!=(biguint other){
        return !(operator==(other));
    }

    bool operator>=(biguint other){
        return !(operator<(other));
    }

    bool operator<=(biguint other){
        return !(operator>(other));
    }

    void print(){
        for(auto i : val) cout << bitset<64>(i) << " ";
        cout << endl;
    }
};

biguint operator*(biguint x, biguint y){
    /*{
        cout << "start" << endl;
        x.print();
        y.print();
        cout << "start" << endl;
    }*/
    size_t max_sz = max(x.sz, y.sz);
    x.sz = max_sz;
    x.val.resize(max_sz, 0);
    y.sz = max_sz;
    y.val.resize(max_sz, 0);

    if(max_sz == 1){
        __uint128_t z = __uint128_t(x.val[0]) * __uint128_t(y.val[0]);
        biguint rtn = biguint(z);
        /*{
            cout << "end" << endl;
            x.print();
            y.print();
            rtn.print();
            cout << "end" << endl;
        }*/
        return rtn;
    }

    biguint xl, xr, yl, yr;
    size_t l_sz = max_sz / 2;
    xl.sz = l_sz;
    xr.sz = x.sz - l_sz;
    yl.sz = l_sz;
    yr.sz = y.sz - l_sz;
    for(size_t i = 0; i < xl.sz; i++) xl.val.push_back(x.val[i]);
    for(size_t i = 0; i < xr.sz; i++) xr.val.push_back(x.val[i + xl.sz]);
    for(size_t i = 0; i < yl.sz; i++) yl.val.push_back(y.val[i]);
    for(size_t i = 0; i < yr.sz; i++) yr.val.push_back(y.val[i + yl.sz]);

    //cout << "A" << endl;
    biguint a = xl * yl;
    //cout << "B" << endl;
    biguint b = xr * yr;
    //cout << "C" << endl;
    biguint c = (xl + xr) * (yl + yr);
    //cout << "D" << endl;
    biguint d = c - a - b;
    //cout << "E" << endl;
    biguint rtn = (b << (l_sz * bit_size * 2)) + (d << (l_sz * bit_size)) + a;

    /*{
        cout << "end" << endl;
        x.print();
        y.print();
        a.print();
        b.print();
        c.print();
        d.print();
        rtn.print();
        cout << "end" << endl;
    }*/
    return rtn;
}

biguint operator/(biguint x, biguint y){
    if(y == 0UL){
        cout << "ERROR : divide 0" << endl;
        assert(false);
    }

    biguint l(0UL);
    biguint r = x + 1UL;
    while(r - l > biguint(1UL)){
        biguint m = (r + l) >> 1;
        if(m * y <= x) l = m;
        else r = m;
    }

    return l;
}

biguint operator%(biguint x, biguint y){
    biguint a = x / y;
    assert(a.val.size() == a.sz);
    biguint b = a * y;
    assert(b.val.size() == b.sz);
    biguint c = x - b;
    assert(c.val.size() == c.sz);

    return x - x / y * y;
}

biguint rand_bigint(){
    size_t x_sz = engine()%10+1;
    vector<uint64_t> x_val(x_sz);
    for(size_t i = 0; i < x_sz; i++) x_val[i] = rand64();
    return biguint(x_val);
}

mpz_class two_64 = 0x1'0000'0000;

mpz_class biguint_to_mpz_class(biguint x){
    //cout << "A" << endl;
    mpz_class rtn = 0;
    for(int i = int(x.sz) - 1; i >= 0; i--){
        rtn = rtn * two_64 + x.val[i];
        //cout << x.val[i] << endl;
    }
    //cout << "B" << endl;
    return rtn;
}

template <typename T>
T f(T x, T y){
    return x % y;
}

int main(){
    two_64 *= two_64;

    int N; cin >> N;
    /*for(int i = 0; i < N; i++){
        biguint x = rand_bigint();
        uint a = engine()%10;
        biguint y = x << a;
        for(auto i : x.val) cout << bitset<64>(i) << " ";
        cout << endl;
        cout << a << endl;
        for(auto i : y.val) cout << bitset<64>(i) << " ";
        cout << endl;
        cout << endl;
    }return 0;*/

    for(int i = 0; i < N; i++){
        biguint xb = rand_bigint();
        biguint yb = rand_bigint();

        if(xb < yb) swap(xb, yb);

        mpz_class xm = biguint_to_mpz_class(xb);
        mpz_class ym = biguint_to_mpz_class(yb);
        
        biguint zb = f(xb, yb);
        mpz_class zm = f(xm, ym);

        assert(zb.val.size() == zb.sz);

        if(zm != biguint_to_mpz_class(zb)){
            for(auto i : xb.val) cout << bitset<64>(i) << " "; 
            cout << endl;
            for(auto i : yb.val) cout << bitset<64>(i) << " "; 
            cout << endl;
            for(auto i : zb.val) cout << bitset<64>(i) << " "; 
            cout << endl;
            cout << xm << " " << ym << " " << zm << endl;
            cout << biguint_to_mpz_class(zb) << endl;
        }
    }
}