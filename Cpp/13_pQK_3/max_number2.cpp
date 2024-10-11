#include <bits/stdc++.h>
using namespace std;

random_device seed_gen;
mt19937 engine(seed_gen());

uint64_t rand64(){
    uint64_t a = engine();
    uint64_t b = engine();
    return (a << 32) + b;
}

int64_t get_time(){
    struct::timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * int64_t(1'000'000'000) + t.tv_nsec;
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

//--------------------------------bigint--------------------------------

const int bit_size = 64;
const uint64_t mask_64 = 0xFFFF'FFFF'FFFF'FFFF;

struct biguint{
    size_t sz;
    vector<uint64_t> val;

    biguint(){
        sz = 1;
        val = {0};
    }

    

    biguint(uint64_t x){
        sz = 1;
        val = {x};
    }
    
    biguint(int x){
        biguint(uint64_t(x));
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

    bool operator!=(biguint other){
        return !(operator==(other));
    }

    void print(){
        for(auto i : val) cout << bitset<64>(i) << " ";
        cout << endl;
    }
};

bool operator<(biguint x, biguint y){
    size_t max_sz = max(x.sz, y.sz);
    for(int i = (int)max_sz - 1; i >= 0; i--){
        uint64_t xi = (i < (int)x.sz) ? x.val[i] : 0;
        uint64_t yi = (i < (int)y.sz) ? y.val[i] : 0;
        if(xi == yi) continue;
        return (xi < yi);
    }
    return false;
}

bool operator>=(biguint x, biguint y){
    return !(x < y);
}

bool operator>(biguint x, biguint y){
    //cout << x.sz << " " << y.sz << endl;
    assert(x.sz == x.val.size());
    assert(y.sz == y.val.size());
    size_t max_sz = max(x.sz, y.sz);
    for(int i = (int)max_sz - 1; i >= 0; i--){
        uint64_t xi = (i < (int)x.sz) ? x.val[i] : 0;
        uint64_t yi = (i < (int)y.sz) ? y.val[i] : 0;
        if(xi == yi) continue;
        return (xi > yi);
    }
    return false;
}

bool operator<=(biguint x, biguint y){
    return !(x > y);
}

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

    l.sz = l.val.size();

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

using mpz_class = biguint;
//--------------------------------bigint--------------------------------

//基本

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
T floor(T x, T y){
    if(y < 0){
        x *= -1;
        y *= -1;
    }
    T r = x%y;
    r = (r+y)%y;
    return (x-r)/y;
}

template <typename T>
T ceil(T x, T y){
    if(y < 0){
        x *= -1;
        y *= -1;
    }
    T r = x%y;
    r = (r+y)%y;
    if(r) x += y-r;
    return x/y;
}

int digit(mpz_class n){
    if(n == 0UL) return 0;
    if(n < 10UL) return 1;
    else return digit(n/10UL)+1;
}

int char_to_int(char c){
    if('0' <= c && c <= '9') return c - '0';
    else if(c == 'T') return 10;
    else if(c == 'J') return 11;
    else if(c == 'Q') return 12;
    else if(c == 'K') return 13;
    else if(c == 'X') return 14;
    else return c - 'a';
}

vector<char> int_to_char = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K','X','a','b','c','d','e','f','g','h','i','j','k','l','m','n'};
vector<int> card_92_KQJ1T = {9,8,7,6,5,4,3,2,14,13,12,11,1,10};

int msd(char c){
    if('0' <= c && c <= '9') return c-'0';
    return 1;
}

mpz_class str_to_int(string s){
    if(s.size() == 0) return 0UL;
    string t = s;
    char c = s[s.size()-1];
    t.pop_back();
    int i = min(char_to_int(c), 13);
    mpz_class rtn;
    if(i < 10) rtn = str_to_int(t)*10UL+uint64_t(i);
    else rtn = str_to_int(t)*100UL+uint64_t(i);
    return rtn;
}

template <typename T>
T pow_n(T x, T y){
    cout << "BA" << endl;
    if(x == T(0UL)) return T(0UL);
    if(x == T(1UL)) return T(1UL);
    if(y == T(0UL)) return T(1UL);
    if(y == T(1UL)) return x;
    cout << "BC" << endl;
    x.print();
    cout << endl;
    y.print();
    cout << endl;
    T rtn = pow_n(x, (y >> 1));
    cout << "BE" << endl;
    rtn = rtn * rtn;
    cout << "BD" << endl;
    if(y%2 == 1) rtn = rtn * x;
    cout << "BB" << endl;
    return rtn;
}

//x^y%p, 0^0 == 0
mpz_class pow_mod(mpz_class x, mpz_class y, mpz_class p){
    if(x >= p) x = x % p;
    if(x == 0UL) return 0UL;
    if(x == 1UL) return 1UL;
    if(y == 0UL) return 1UL;
    if(y == 1UL) return x;
    mpz_class rtn = pow_mod(x, y/2UL, p);
    rtn = rtn*rtn%p;
    if(y%2UL == 1UL) {
        rtn = rtn * x;
        rtn = rtn % p;
    }
    return rtn;
}

bool miller_rabin(mpz_class x){
    if(x <= 1) return false;
    if(x == 2) return true;
    if(x % 2 == 0) return false;

    int s = 0;
    mpz_class d = x - 1UL;
    while(d % 2 == 0){
        d = d / 2;
        s++;
    }

    mpz_class k = 100UL;
    if(x - 1 < k) k = x - 1UL;

    set<mpz_class> A;

    {
        mpz_class a_max = x - 1UL;
        while(biguint(int(A.size())) < k){
            A.insert(engine() % a_max + 1UL);
        }
    }

    for(mpz_class a : A){
        mpz_class t = pow_mod(a, d, x);
        if(t == 1) continue;
        bool b = false;
        for(int i = 0; i < s; i++){
            if(t == x - 1UL){
                b = true;
                break;
            }
            t = t * t % x;
        }
        if(b) continue;
        return false;
    }
    return true;
}

bool prime_quadruplet_test(mpz_class x){
    if(x % 2 == 0) return false;
    vector<int> odd = {1, 3, 7, 9};
    for(int i : odd){
        if(!miller_rabin(x/10*10+i)) return false;
    }
    return true;
}

bool number_test(mpz_class x){
    //return miller_rabin(x);
    return prime_quadruplet_test(x);
}

bool max_nutural_sub(string s, string t){
    return str_to_int(s + t) > str_to_int(t + s);
}

mpz_class hand_upper_bound(vector<string> v){
    for(auto &vi : v) if(vi == "X") vi = "K";

    sort(v.begin(), v.end(), max_nutural_sub);
    string s;
    for(auto vi : v) s += vi;
    return str_to_int(s);
}

bool skip_calc(string s, mpz_class x, vector<string> rest){
    string t = s;
    for(auto i : rest) t += i;
    for(char c : t) if(c == 'X') return false;

    cout << "L" << endl;
    mpz_class y = str_to_int(t);
    cout << "M" << endl;
    if(y % 3UL == 0UL) return true;
    cout << "R" << endl;

    if(rest.size() == 0) return false;

    for(auto i : rest){
        mpz_class z = str_to_int(i);
        if(z%2 != 0 && z%5 != 0){
            return false;
        }
    }
    return true;
}

string max_number(vector<string> v){
    if(v.size() == 0) return "-1";
    if(v.size() == 1){
        string s = v[0];
        if(s == "X") return s;
        if(number_test(str_to_int(s))) return s;
        return "-1";
    }

    priority_queue<tuple<mpz_class, string, mpz_class, vector<string>>> q;
    q.push({hand_upper_bound(v), "", 0, v});
    
    string rtn = "-1";
    mpz_class max_val(0UL);
    
    while(q.size()){
        cout << "A" << endl;
        auto[max_x, s, x, rest] = q.top();
        cout << "B" << endl;
        q.pop();
        cout << "C" << endl;
        if(max_val > max_x) break;
        cout << "D" << endl;
        if(skip_calc(s, x, rest)) continue;
        cout << "E" << endl;

        max_x.print();
        cout << " " << s << " ";
        x.print();
        cout << ",";
        for(auto ii : rest) cout << " " << ii;
        cout << endl;

        if(rest.size() == 0){
            if(x > max_val && number_test(x)){
                rtn = s;
                max_val = x;
            }
            continue;
        }
        cout << "F" << endl;
    
        int rest_sz = rest.size();
        set<string> checked;
        int exist_x = -1;
        for(int i = 0; i < rest_sz; i++){
            cout << "AA" << endl;
            string t = rest[i];
            if(checked.count(t)) continue;
            checked.insert(t);

            if(t == "X"){
                exist_x = i;
                continue;
            }
            else{
                cout << "AC" << endl;
                string next_s = s + t;
                mpz_class next_x = str_to_int(next_s);
                auto next_rest = rest;
                swap(next_rest[i], next_rest[rest_sz - 1]);
                next_rest.pop_back();
                cout << "AD" << endl;

                mpz_class ub_rest = hand_upper_bound(next_rest);
                int d_ub_rest = digit(ub_rest);
                cout << "AE" << endl;
                mpz_class next_max_x = next_x * pow_n(mpz_class(10), biguint(d_ub_rest)) + ub_rest;
                q.push({next_max_x, next_s, next_x, next_rest});
            }
            cout << "AB" << endl;
        }
        cout << "G" << endl;
        if(exist_x >= 0){
            int i = exist_x;
            auto next_rest = rest;
            swap(next_rest[i], next_rest[rest_sz - 1]);
            next_rest.pop_back();
            for(int j = 15; j <= 28; j++){
                if(s.size() == 0 && j == 15) continue;
                char c = int_to_char[j];
                if(checked.count(string(1, int_to_char[j-15]))) continue;
                string next_s = s + c;
                mpz_class next_x = str_to_int(next_s);

                mpz_class ub_rest = hand_upper_bound(next_rest);
                int d_ub_rest = digit(ub_rest);
                mpz_class next_max_x = next_x * pow_n(mpz_class(10), biguint(d_ub_rest)) + ub_rest;
                q.push({next_max_x, next_s, next_x, next_rest});
            }
        }
        cout << "H" << endl;
    }
    return rtn;
}

void output_assigned_x(string s){
    string assigned_list;
    for(char &c : s){
        if('a' <= c && c <= 'n'){
            assigned_list.push_back(int_to_char[char_to_int(c)]);
            c = 'X';
        }
    }
    cout << s;
    for(char c : assigned_list) cout << " | X = " << c;
    cout << endl; 
}

int main(){
    int N; cin >> N;
    vector<string> v(N);
    for(auto &s : v) cin >> s;
    auto time_start = get_time();
    string t = max_number(v);
    auto time_end = get_time();
    output_assigned_x(t);
    cout << fixed << setprecision(3);
    cout << (time_end - time_start) / 1e9 << "[s]" << endl;
}
