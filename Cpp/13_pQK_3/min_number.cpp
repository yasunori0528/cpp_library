#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
template <typename T> using min_priority_queue = priority_queue<T,vector<T>,greater<T>>;

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
    return miller_rabin(x);
}

bool max_nutural_sub(string s, string t){
    return str_to_int(s + t) < str_to_int(t + s);
}

mpz_class hand_upper_bound(vector<string> v){
    for(auto &vi : v) if(vi == "X") vi = "0";

    sort(v.begin(), v.end(), max_nutural_sub);
    string s;
    for(auto vi : v) s += vi;
    return str_to_int(s);
}

string max_number(vector<string> v){
    if(v.size() == 0) return "-1";
    if(v.size() == 1){
        string s = v[0];
        if(s == "X") return s;
        if(number_test(str_to_int(s))) return s;
        return "-1";
    }

    min_priority_queue<tuple<mpz_class, string, mpz_class, vector<string>>> q;
    q.push({hand_upper_bound(v), "", 0, v});
    
    string rtn = "-1";
    mpz_class min_val = pow_n((mpz_class)10, (mpz_class)1000);
    while(q.size()){
        auto[max_x, s, x, rest] = q.top();

        cout << max_x << " " << s << " " << x << ",";
        for(auto ii : rest) cout << " " << ii;
        cout << endl;
        
        q.pop();
        if(min_val < max_x) break;

        if(rest.size() == 0){
            if(x < min_val && number_test(x)){
                rtn = s;
                min_val = x;
            }
            continue;
        }

        int rest_sz = rest.size();
        set<string> checked;
        for(int i = 0; i < rest_sz; i++){
            string t = rest[i];
            if(checked.count(t)) continue;
            checked.insert(t);

            if(t == "X"){
                auto next_rest = rest;
                swap(next_rest[i], next_rest[rest_sz - 1]);
                next_rest.pop_back();
                for(int j = 15; j <= 28; j++){
                    if(s.size() == 0 && j == 15) continue;
                    char c = int_to_char[j];
                    string next_s = s + c;
                    mpz_class next_x = str_to_int(next_s);

                    mpz_class ub_rest = hand_upper_bound(next_rest);
                    mpz_class d_ub_rest = digit(ub_rest);
                    mpz_class next_max_x;
                    if(next_rest.size()) next_max_x = next_x * pow_n(mpz_class(10), d_ub_rest) + ub_rest;
                    else next_max_x = next_x;
                    q.push({next_max_x, next_s, next_x, next_rest});
                }
            }
            else{
                string next_s = s + t;
                mpz_class next_x = str_to_int(next_s);
                auto next_rest = rest;
                swap(next_rest[i], next_rest[rest_sz - 1]);
                next_rest.pop_back();

                mpz_class ub_rest = hand_upper_bound(next_rest);
                mpz_class d_ub_rest = digit(ub_rest);
                mpz_class next_max_x = next_x * pow_n(mpz_class(10), d_ub_rest) + ub_rest;
                q.push({next_max_x, next_s, next_x, next_rest});
            }
        }
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
    string t = max_number(v);
    output_assigned_x(t);
}
