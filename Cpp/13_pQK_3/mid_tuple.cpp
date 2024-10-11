#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
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
    if(n == 0) return 0;
    if(n < 10) return 1;
    else return digit(n/10)+1;
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
    if(s.size() == 0) return 0;
    string t = s;
    char c = s[s.size()-1];
    t.pop_back();
    int i = min(char_to_int(c), 13);
    mpz_class rtn;
    if(i < 10) rtn = str_to_int(t)*10+i;
    else rtn = str_to_int(t)*100+i;
    return rtn;
}

template <typename T>
T pow_n(T x, T y){
    if(x == 0) return 0;
    if(x == 1) return 1;
    if(y == 0) return 1;
    if(y == 1) return x;

    T rtn = pow_n(x,(T)(y/2));
    rtn *= rtn;
    if(y%2 == 1) rtn *= x;
    return rtn;
}

//x^y%p, 0^0 == 0
mpz_class pow_mod(mpz_class x, mpz_class y, mpz_class p){
    if(x >= p) x %= p;
    if(x == 0) return 0;
    if(x == 1) return 1;
    if(y == 0) return 1;
    if(y == 1) return x;
    mpz_class rtn = pow_mod(x, y/2, p);
    rtn = rtn*rtn%p;
    if(y%2 == 1) {
        rtn *= x;
        rtn %= p;
    }
    return rtn;
}

bool miller_rabin(mpz_class x){
    if(x <= 1) return false;
    if(x == 2) return true;
    if(x % 2 == 0) return false;

    int s = 0;
    mpz_class d = x - 1;
    while(d % 2 == 0){
        d /= 2;
        s++;
    }

    mpz_class k = 100;
    if(x - 1 < k) k = x - 1;

    set<mpz_class> A;

    {
        mpz_class a_max = x - 1;
        while(A.size() < k){
            A.insert(engine() % a_max + 1);
        }
    }

    for(mpz_class a : A){
        mpz_class t = pow_mod(a, d, x);
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
    //return prime_quadruplet_test(x);
    int cnt = 0;
    if(miller_rabin(x * 10 + 1)) cnt++;
    if(miller_rabin(x * 100 + 11)) cnt++;
    //if(miller_rabin(x * 1000 + 111)) cnt++;
    //if(miller_rabin(x * 10000 + 1111)) cnt++;
    return cnt >= 2;
}

int main(){
    string s; cin >> s;
    int n = s.size();
    vector<string> v;
    v.push_back("");
    for(int i = 1; i <= 13; i++){
        string vijk;
        vijk.push_back(int_to_char[i]);
        v.push_back(vijk);
    }
    for(int i = 1; i <= 13; i++){
        for(int j = 1; j <= 13; j++){
            string vijk;
            vijk.push_back(int_to_char[i]);
            vijk.push_back(int_to_char[j]);
            v.push_back(vijk);
        }
    }
    for(int i = 1; i <= 13; i++){
        for(int j = 1; j <= 13; j++){
            for(int k = 1; k <= 13; k++){
                string vijk;
                vijk.push_back(int_to_char[i]);
                vijk.push_back(int_to_char[j]);
                vijk.push_back(int_to_char[k]);
                v.push_back(vijk);
            }
        }
    }

    for(auto t : v){
        string u = s + t;
            if(number_test(str_to_int(u))) cout << "\"" << t << "\"" << endl;
    }
    for(int i = 0; i < n; i++){
        cout << s[i] << string(16, '-') << endl;
        string s2;
        if(i - 1 >= 0) s2 += s.substr(0, i);
        if(i + 1 < n) s2 += s.substr(i + 1);
        for(auto t : v){
            string u = s2 + t;
            if(number_test(str_to_int(u))) cout << "\"" << t << "\"" << endl;
        }
    }
}
