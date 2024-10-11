#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

random_device seed_gen;
mt19937 engine(seed_gen());

template<typename T>
T rnd();
template<typename T>
T rnd(int n);

template<>
uint rnd<uint>(){
    return engine();
}

template<>
uint64_t rnd<uint64_t>(){
    uint64_t a = engine();
    uint64_t b = engine();
    return (a << 32) + b;
}

template<>
int rnd<int>(){
    return rnd<uint>();
}

template<>
int64_t rnd<int64_t>(){
    return rnd<uint64_t>();
}

template<>
char rnd<char>(){
    //32~126
    return engine()%95+32; 
}

template<>
string rnd<string>(int n){
    string rtn;
    for(int i = 0; i < n; i++) rtn.push_back(rnd<char>());
    return rtn;
}

//get time [nanosecond]
int64_t get_time(){
    struct::timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * int64_t(1'000'000'000) + t.tv_nsec;
}

template <typename T>
bool chmax(T &a, const T& b) {
    if (a < b) {
        a = b;  // aをbで更新
        //a.print();
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

template <typename T>
T pow(T x, T y){
    assert(y >= 0);
    assert(!(x == 0 && y == 0));

    if(x == 0) return 0;
    if(y == 0) return 1;
    if(x == 1) return 1;
    if(y == 1) return x;

    vector<pair<T, T>> a = {{y, y}};
    while(1){
        auto [l, r] = *a.rbegin();
        if(l == 0) break;
        a.push_back({l / 2, (r + 1) / 2});
    }

    int n = a.size();
    vector<pair<T, T>> pow_list(n);
    for(int i = n - 1; i >= 0; i--){
        auto [l, r] = a[i];
        auto &[pl, pr] = pow_list[i];

        if(l == 0) pl = 1;
        else if(l == 1) pl = x;
        else if(l % 2 == 0) pl = pow_list[i + 1].first * pow_list[i + 1].first;
        else pl = pow_list[i + 1].first * pow_list[i + 1].second;

        if(r == l) pr = pl;
        else if(r == 0) pr = 1;
        else if(r == 1) pr = x;
        else if(r % 2 == 0) pr = pow_list[i + 1].second * pow_list[i + 1].second;
        else pr = pow_list[i + 1].first * pow_list[i + 1].second;
    }

    return pow_list[0].first;
}

template <typename T>
T pow_mod(T x, T y, T p){
    assert(y >= 0);
    x %= p;

    if(x == 0) return 0;
    if(y == 0) return 1;
    if(x == 1) return 1;
    if(y == 1) return x;

    vector<pair<T, T>> a = {{y, y}};
    while(1){
        auto [l, r] = *a.rbegin();
        if(l == 0) break;
        a.push_back({l / 2, (r + 1) / 2});
    }

    int n = a.size();
    vector<pair<T, T>> pow_list(n);
    for(int i = n - 1; i >= 0; i--){
        auto [l, r] = a[i];
        auto &[pl, pr] = pow_list[i];

        if(l == 0) pl = 1;
        else if(l == 1) pl = x;
        else if(l % 2 == 0) pl = pow_list[i + 1].first * pow_list[i + 1].first % p;
        else pl = pow_list[i + 1].first * pow_list[i + 1].second % p;

        if(r == l) pr = pl;
        else if(r == 0) pr = 1;
        else if(r == 1) pr = x;
        else if(r % 2 == 0) pr = pow_list[i + 1].second * pow_list[i + 1].second % p;
        else pr = pow_list[i + 1].first * pow_list[i + 1].second % p;
    }

    return pow_list[0].first;
}

template <typename T>
int digit(T n){
    if(n == 0) return 0;
    if(n < 10) return 1;
    else return digit(n/10)+1;
}

bool miller_rabin(bigint x){
    if(x <= 1) return false;
    if(x == 2) return true;
    if(x % 2 == 0) return false;

    int s = 0;
    bigint d = x - 1;
    while(d % 2 == 0){
        d /= 2;
        s++;
    }

    bigint k = 100;//テスト回数
    if(x - 1 < k) k = x - 1;

    set<bigint> A;
    
    {
        bigint a_max = x - 1;
        while(A.size() < k){
            A.insert(rnd<uint>() % a_max + 1);
        }
    }
    //cout << "A" << endl;
    for(bigint a : A){
        bigint t = pow_mod(a, d, x);
        if(t == 1) continue;
        bool b = false;
        for(int i = 0; i < s; i++){
            if(t == x - 1){
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

template<typename T>
T next_pseudorand(T x, T p, T c){
    return (x * x + c) % p;
}

template<typename T>
T pollard_rho_sub(T x){
    for(T c = 1; c < x; c++){
        if(c == x - 2) continue;
        T r1 = 2;
        T r2 = 2;
        T d = 1;
        while(d == 1){
            r1 = next_pseudorand(r1, x, c);
            r2 = next_pseudorand(next_pseudorand(r2, x, c), x, c);
            d = gcd(abs(r1 - r2), x);
        }
        if(d == x) continue;
        return d;
    }
    return 1;
}

template<typename T>
vector<T> pollard_rho(T x){
    assert(x > 0);

    vector<T> rtn;
    queue<T> q;

    while(x % 2 == 0){
        rtn.push_back(2);
        x /= 2;
    }

    if(x == 1) return rtn;

    q.push(x);

    while(q.size()){
        T y = q.front();
        q.pop();

        if(miller_rabin(y)){
            rtn.push_back(y);
            continue;
        }

        T d = pollard_rho_sub(y);

        assert(1 < d && d < y && y % d == 0);
        q.push(d);
        q.push(y / d);
    }

    return rtn;
}

//カードの種類
//'a'~'n' は 'X' に 0 ~ 13 を代入した状態を指す.
const string alphabet = "0123456789TJQKXabcdefghijklmn";

int char_to_int(char c){
    if('0' <= c && c <= '9') return c - '0';
    else if(c == 'T') return 10;
    else if(c == 'J') return 11;
    else if(c == 'Q') return 12;
    else if(c == 'K') return 13;
    else if(c == 'X') return 14;
    else return c - 'a';
}

bigint str_to_int(string s){
    if(s.size() == 0) return 0;
    string t = s;
    char c = s[s.size()-1];
    t.pop_back();
    int i = min(char_to_int(c), 13);
    bigint rtn;

    int d = i < 10 ? 10 : 100;
    rtn = str_to_int(t) * d + i;
    return rtn;
}

vector<vector<vector<int>>> exp_list;

int log(int x, int y){
    assert(x <= 0);
    assert(y <= 0);

    int rtn = 0;
    while(y >= x){
        rtn++;
        y /= x;
    }
    return rtn;
}

//大きさが 2^n 以下の指数部を全列挙
void init_exp_list(int n){
    exp_list.resize((1<<n)+1);

    vector<vector<int>> pw(1 << n + 1);
    for(int i = 2; i <= (1<<n); i++){
        for(int p = 1; ; p *= i){
            pw[i].push_back(p);
            if(p > (1<<n) / i) break;
        }
    }

    vector<vector<pair<int, vector<int>>>> v(1);
    for(int i = 2; i <= (1<<n); i++) v[0].push_back({i, {i}});
    
    {
        int i = 0;
        while(v[i].size()){
            v.push_back(vector<pair<int, vector<int>>>());
            for(auto &[j, e] : v[i]){
                for(int k = 2; j < pw[k].size(); k++){
                    //k^j
                    int nj = pw[k][j];
                    vector<int> ne = e;
                    ne.push_back(k);
                    v[i+1].push_back({nj, ne});
                }
            }
            i++;
        }
    }

    for(auto &vi : v){
        for(auto &[j, e] : vi){
            reverse(e.begin(), e.end());
            exp_list[j].push_back(e);
        }
    }
}

//合成数場d桁
void c_search(string s, int d){
    for(bigint c = pow<bigint>(10, d - 1); c < pow<bigint>(10, d); c++){
        vector<bigint> v = pollard_rho(c);
    }
}

int main(){
    init_exp_list(8);
    string s; cin >> s;

}
