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
        a.print();
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

bigint pow(bigint x, bigint y){
    assert(y >= 0);
    assert(!(x == 0 && y == 0));

    if(x == 0) return 0;
    if(y == 0) return 1;
    if(x == 1) return 1;
    if(y == 1) return x;

    vector<pair<bigint, bigint>> a = {{y, y}};
    while(1){
        auto [l, r] = *a.rbegin();
        if(l == 0) break;
        a.push_back({l / 2, (r + 1) / 2});
    }

    int n = a.size();
    vector<pair<bigint, bigint>> pow_list(n);
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

bigint pow_mod(bigint x, bigint y, bigint p){
    assert(y >= 0);
    x %= p;

    if(x == 0) return 0;
    if(y == 0) return 1;
    if(x == 1) return 1;
    if(y == 1) return x;

    vector<pair<bigint, bigint>> a = {{y, y}};
    while(1){
        auto [l, r] = *a.rbegin();
        if(l == 0) break;
        a.push_back({l / 2, (r + 1) / 2});
    }

    int n = a.size();
    vector<pair<bigint, bigint>> pow_list(n);
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

int digit(bigint n){
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

bool number_test(bigint x){
    //return miller_rabin(x);
    //x /= 10;
    x *= 10;
    return miller_rabin(x + 1) && miller_rabin(x + 3) && miller_rabin(x + 7) && miller_rabin(x + 9);
}

bool max_nutural_sub(string s, string t){
    return str_to_int(s + t) > str_to_int(t + s);
}

bigint hand_upper_bound(vector<string> v){
    for(auto &vi : v) if(vi == "X") vi = "K";

    sort(v.begin(), v.end(), max_nutural_sub);
    string s;
    for(auto vi : v) s += vi;
    return str_to_int(s);
}

map<bigint, set<vector<string>>> pushed_state;

bool skip_calc(string s, bigint x, vector<string> rest){
    if(s.size() >= 2){
        string sr = s.substr(s.size() - 2);
        bigint sr_int = str_to_int(sr);
        if(10 <= sr_int && sr_int <= 13){
            string s1;
            if(sr_int == 10) s1 = "T";
            else if(sr_int == 11) s1 = "J";
            else if(sr_int == 12) s1 = "Q";
            else s1 = "K";

            for(auto resti : rest){
                if(resti == s1) return true;
            }
        }
    }
    
    string t = s;
    for(auto i : rest) t += i;
    for(char c : t) if(c == 'X') return false;

    bigint y = str_to_int(t);
    if(y % 3 == 1) return false;

    if(rest.size() == 0) return false;

    /*for(auto i : rest){
        bigint z = str_to_int(i);
        if(z%2 != 0 && z%5 != 0){
            return false;
        }
    }*/
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

    set<tuple<bigint, string, bigint, vector<string>>> q;
    q.insert({hand_upper_bound(v), "", 0, v});
    
    string rtn = "-1";
    bigint max_val = 0;
    int64_t loop_cnt = 0;
    while(q.size()){
        auto itr = q.rbegin();
        auto[max_x, s, x, rest] = *itr;
        q.erase(*itr);
        if(max_val > max_x) break;
        if(skip_calc(s, x, rest)) continue;

        if(loop_cnt%100000 == 0){
            cout << q.size() << " " << pushed_state.size() << endl;
            cout << max_x << " " << s << " " << x << ",";
            for(auto ii : rest) cout << " " << ii;
            cout << endl;
        }
        loop_cnt++;

        
        while(pushed_state.size()){
            bigint max_key = (*pushed_state.rbegin()).first;
            if(max_key > max_x) pushed_state.erase(max_key);
            else break;
        }

        if(rest.size() == 0){
            if(x > max_val && number_test(x)){
                rtn = s;
                max_val = x;
            }
            continue;
        }

        int rest_sz = rest.size();
        set<string> checked;
        int exist_x = -1;
        for(int i = 0; i < rest_sz; i++){
            string t = rest[i];
            if(checked.count(t)) continue;
            checked.insert(t);

            if(t == "X"){
                exist_x = i;
                continue;
            }
            else{
                string next_s = s + t;
                bigint next_x = str_to_int(next_s);
                auto next_rest = rest;
                swap(next_rest[i], next_rest[rest_sz - 1]);
                next_rest.pop_back();
                sort(next_rest.begin(), next_rest.end());
                if(pushed_state[next_x].count(next_rest)) continue;

                bigint ub_rest = hand_upper_bound(next_rest);
                bigint d_ub_rest = digit(ub_rest);
                bigint next_max_x = next_x * pow(bigint(10), d_ub_rest) + ub_rest;
                q.insert({next_max_x, next_s, next_x, next_rest});
                pushed_state[next_x].insert(next_rest);
            }
        }

        if(exist_x >= 0){
            int i = exist_x;
            auto next_rest = rest;
            swap(next_rest[i], next_rest[rest_sz - 1]);
            next_rest.pop_back();
            sort(next_rest.begin(), next_rest.end());

            //for(int j = 15 + 0; j <= 15 + 13; j++){
            for(int j = 15 + 10; j <= 15 + 13; j++){//ジョーカーを絵札としてのみ使用
                if(s.size() == 0 && j == 15) continue;
                char c = alphabet[j];
                if(checked.count(string(1, alphabet[j-15]))) continue;
                string next_s = s + c;
                bigint next_x = str_to_int(next_s);
                if(pushed_state[next_x].count(next_rest)) continue;

                bigint ub_rest = hand_upper_bound(next_rest);
                bigint d_ub_rest = digit(ub_rest);
                bigint next_max_x = next_x * pow(bigint(10), d_ub_rest) + ub_rest;
                q.insert({next_max_x, next_s, next_x, next_rest});
                pushed_state[next_x].insert(next_rest);
            }
        }
    }
    return rtn;
}

void output_assigned_x(string s){
    string assigned_list;
    for(char &c : s){
        if('a' <= c && c <= 'n'){
            assigned_list.push_back(alphabet[char_to_int(c)]);
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
