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

template <typename T>
struct group_plus{
    T val;

    group_plus(){
        val = 0;
    }

    group_plus(T x){
        val = x;
    }

    group_plus e(){
        return group_plus();
    }

    group_plus operator*(group_plus other){
        return group_plus(val + other.val);
    }

    group_plus inv(){
        return group_plus(-val);
    }

    string monoid_to_string(){
        string rtn = to_string(val);
        return rtn;
    }

    bool operator==(group_plus other){
        return val == other.val;
    }
    bool operator!=(group_plus other){
        return val != other.val;
    }
};

template <typename monoid>
struct segtree{
    int sz;
    vector<monoid> dat;

    segtree(){
        ;
    }
    
    segtree(int n){
        sz = 1;
        while(sz < n) sz *= 2;

        dat.resize(2*sz-1, monoid().e());
    }

    void update(int k, monoid a){
        k += sz-1;
        dat[k] = a;
        while(k > 0){
            k = (k-1)/2;
            dat[k] = dat[2*k+1]*dat[2*k+2];
        }
    }

    void plus(int k, monoid a){
        update(k, get(k, k+1)*a);
    }

    //[a,b)
    monoid get(int a, int b){
        return sub_get(a, b, 0, 0, sz);
    }

    monoid sub_get(int a, int b, int k, int l, int r){
        if(r <= a || b <= l) return monoid().e();
        if(a <= l && r <= b) return dat[k];
        monoid vl = sub_get(a, b, 2*k+1, l, (l+r)/2);
        monoid vr = sub_get(a, b, 2*k+2, (l+r)/2, r);
        return vl*vr;
    }

    void print(int a = 8){
        int len = sz;
        int i = 0;
        while(len){
            for(int j = 0; j < sz; j += len){
                //dat[i] : [j, j+len)
                string s(a * len - 1, ' ');
                string t = dat[i].monoid_to_string();
                int l = (a * len - t.size()) / 2;
                for(int k = 0; k < t.size(); k++){
                    s[l+k] = t[k];
                }
                cout << '|' << s;
                i++;
            }
            cout << "|\n";
            len /= 2;
        }
    }
};

int main(){
    using monoid = group_plus<double>;

    int n_max = 10;
    vector dp(n_max + 1, segtree<monoid>(n_max * (n_max + 1) / 2 + 1));
    dp[1].update(0, monoid(1));
    for(int i = 2; i <= n_max; i++){
        for(int j = 0; j <= i * (i - 1) / 2; j++){
            dp[i].update(j, dp[i - 1].get(max(0, j - i + 1), j + 1));
        }
    }

    /*for(int i = 1; i <= n_max; i++){
        for(int j = 0; j <= i * (i - 1) / 2; j++){
            cout << dp[i].get(j, j+1).val << " ";
        }
        cout << endl;
    }*/

    cout << fixed << setprecision(3);
    for(int n = 3; n <= 20; n++){
        for(int i = 4; i <= 20; i++){
            double p = 1.0 / i;
            double s = 0;
            for(int j = 0; j <= i * (i - 1) / 2; j++){
                s += pow(p, j) * pow(1 - p, n * (n - 1) / 2 - j) * dp[n].get(j, j + 1).val;
            }
            cout << log10(s) << " ";
        }
        cout << endl;
    }
    
}
//上手の勝率を固定したとき、ライト級の成績表がきれいになる確率
