#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

random_device seed_gen;
mt19937 engine(seed_gen());

//get time [nanosecond]
int64_t get_time(){
    struct::timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * int64_t(1'000'000'000) + t.tv_nsec;
}

template<typename T>
uint bigint_to_int(T x);

template<>
uint bigint_to_int(mpz_class x) {
    return x.get_ui();
}

/*template<>
uint bigint_to_int(boost::multiprecision::cpp_int x) {
    return static_cast<uint>(x);
}*/

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
            A.insert(engine() % a_max + 1);
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
const string ALPHABET = "0123456789TJQKXabcdefghijklmn";
const string DECK = "111122223333444455556666777788889999TTTTJJJJQQQQKKKKXX";
const int NUM_CARD_TYPES = 15;

char int_to_char(int x) {
    assert(0 <= x && x < NUM_CARD_TYPES);
    return ALPHABET[x];
}

int char_to_int(char c) {
    if('0' <= c && c <= '9') return c - '0';
    if(c == 'T') return 10;
    if(c == 'J') return 11;
    if(c == 'Q') return 12;
    if(c == 'K') return 13;
    if(c == 'X') return 14;
    assert(false);
    return 0;
}

char assign(char &c) {
    if('a' <= c && c <= 'n') return ALPHABET[c - 'a'];
    return c;
}

char unassign(char &c) {
    if('a' <= c && c <= 'n') return 'X';
    return c;
}

bool is_symbol(char &c) {
    return c == '=' || c == '*' || c == '^';
}

bool is_joker(char &c) {
    return c == 'X' || ('a' <= c && c <= 'n');
}

string int_to_str(bigint x) {
    string s;
    while(x) {
        bigint r = x % 10;
        s.push_back('0' + bigint_to_int(r));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

bigint str_to_int(string &s) {
    bigint rtn = 0;
    for(char &c : s) {
        int x = char_to_int(assign(c));
        if(x < 10) rtn = rtn * 10 + x;
        else rtn = rtn * 100 + x;
    }
    return rtn;
}

void print_str(string &s) {
    string s_unassign = s;
    string s_assign = s;
    for(char &c : s_unassign) c = unassign(c);
    for(char &c : s_assign) c = assign(c);

    cout << s_unassign;
    if(s_assign != s_unassign) {
        cout << "(" << s_assign << ")";
    }
}

const int HAND_SEGMENT_WIDTH = 4;
class hand {
public:
    hand() {
        a = 0;
        len = 0;
    }

    hand(string &s) {
        a = 0;
        len = 0;
        for(char &c : s) {
            if(is_symbol(c)) continue;
            a += uint64_t(1) << (char_to_int(c) * HAND_SEGMENT_WIDTH);
            len++;
        }
    }

    int get_a() {
        return a;
    }

    int size() {
        return len;
    }

    int count(int x) {
        return a >> (x * HAND_SEGMENT_WIDTH) & uint64_t(0b1111);
    }

    int count(char c) {
        return a >> (char_to_int(c) * HAND_SEGMENT_WIDTH) & uint64_t(0b1111);
    }

    bool contain(string &s) {
        hand s_hand(s);
        for(int i = 0; i < NUM_CARD_TYPES; i++) {
            if(s_hand.count(i) > count(i)) return false;
        }
        return true;
    }

    void draw(int x) {
        a += uint64_t(1) << (x * HAND_SEGMENT_WIDTH);
        len++;
    }

    void draw(char c) {
        a += uint64_t(1) << (char_to_int(c) * HAND_SEGMENT_WIDTH);
        len++;
    }

    void discard(int x) {
        a -= uint64_t(1) << (x * HAND_SEGMENT_WIDTH);
        len--;
    }

    void discard(char c) {
        a -= uint64_t(1) << (char_to_int(c) * HAND_SEGMENT_WIDTH);
        len--;
    }

    void play(string &s) {
        for(char &c : s) {
            if(is_symbol(c)) continue;
            a -= uint64_t(1) << (char_to_int(c) * HAND_SEGMENT_WIDTH);
            len++;
        }
    }

    bool div25() {
        if(count(1)) return false;
        if(count(3)) return false;
        if(count(7)) return false;
        if(count(9)) return false;
        if(count(11)) return false;
        if(count(13)) return false;
        if(count(14)) return false;
        return true;
    }

    int mod3() {
        if(count(14)) return -1;
        int r = 0;
        for(int i = 0; i <= 13; i++) {
            r += count(i) * i;
        }
        r %= 3;
        return r;
    }

    int mod11() {
        if(count(14)) return -1;
        for(int i = 0; i < 10; i++) if(count(i)) return -1;
        
        int r = 0;
        for(int i = 10; i <= 13; i++) {
            r += count(i) * i;
        }
        r %= 11;
        return r;
    }

    bigint max_natural() {
        bigint rtn = 0;
        for(int i = 9; i >= 0; i--) {
            for(int j = 0; j < count(i); j++) {
                rtn = rtn * 10 + i;
            }
        }
        for(int j = 0; j < count(14); j++) {
            rtn = rtn * 100 + 13;
        }
        for(int i = 13; i >= 10; i--) {
            for(int j = 0; j < count(i); j++) {
                rtn = rtn * 100 + i;
            }
        }

        return rtn;
    }

    void print() {
        for(int i = 0; i <= 14; i++) {
            for(int j = 0; j < count(i); j++) {
                cout << int_to_char(i);
            }
        }
    }

private:
    uint64_t a;
    int len;
};

bool operator<(hand h, hand g) {
    return h.get_a() < g.get_a();
}

bool number_test(bigint x) {
    return miller_rabin(x);
}

bigint max_potential(bigint x, hand g) {
    if(g.size() == 0) return x;
    if(g.div25()) return 0;

    bigint y = g.max_natural();
    int d = digit(y);
    bigint rtn = x * pow((bigint)10, (bigint)d) + y;
    
    int r3 = g.mod3();
    if(r3 >= 0 && (x + r3) % 3 == 0) return 0;

    int r11 = g.mod11();
    if(r11 >= 0 && d % 2) r11 = 11 - r11;
    if(r11 >= 0 && (x + r11) % 11 == 0) return 0;

    return rtn;
}

bigint max_prime(hand h) {
    set<tuple<bigint, bigint, hand>> Q;
    Q.insert(make_tuple(h.max_natural(), bigint(0), h));

    while(Q.size()) {
        auto itr = Q.rbegin();
        auto [max_x, x, g] = *itr;
        Q.erase(*itr);

        //cout << x << " ";
        //g.print();
        //cout << endl;

        if(g.size() == 0) {
            if(engine() % 10000 == 0) cout << x << endl;
            if(number_test(x)) return x;
            else continue;
        }

        for(int i = 0; i <= 13; i++) {
            if(i == 0 && x == 0) continue;

            bigint next_x;
            if(i < 10) next_x = x * 10 + i;
            else next_x = x * 100 + i;

            hand next_g = g;
            if(g.count(i)) {
                next_g.discard(i);
                bigint next_max_x = max_potential(next_x, next_g);
                if(next_max_x > 0) Q.insert(make_tuple(next_max_x, next_x, next_g));
            }
            else if(g.count(14)) {
                next_g.discard(14);
                bigint next_max_x = max_potential(next_x, next_g);
                if(next_max_x > 0) Q.insert(make_tuple(next_max_x, next_x, next_g));
            }
        }
    }

    return 0;
}

int main() {
    string s; cin >> s;
    int64_t t_start = get_time();

    cout << max_prime(hand(s)) << endl;

    int64_t t_end = get_time();
    cout << fixed << setprecision(6);
    cout << (t_end - t_start) / 1'000'000'000.0 << "[s]" << endl;
}
