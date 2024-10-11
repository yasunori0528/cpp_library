#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

//!時間取得
double calcTime(){
    struct::timespec getTime;
    clock_gettime(CLOCK_MONOTONIC, &getTime);
    return (getTime.tv_sec + getTime.tv_nsec*1e-9) *1000;
}

template <typename T>
vector<T> operator+(vector<T> v, vector<T> w){
    vector<T> rtn = v;
    for(T i : w){
        rtn.push_back(i);
    }
    return rtn;
}

template <typename T>
void print_v(vector<T> v){
    for(T i : v){
        cout << i << " ";
    }
    cout << endl;
}

template <typename T>
void print_vv(vector<vector<T>> v){
    for(vector<T> i : v){
        print_v(i);
    }
}

//整数

int operator%(mpz_class n, int m){
    if(m <= 1) return 0;
    mpz_class rtn = n % (mpz_class)m;
    int l = 0;
    int r = m;
    while(r - l > 1){
        int mid = (r + l) / 2;
        if(mid <= rtn){
            l = mid;
        }
        else{
            r = mid;
        }
    }
    return l;
}

int log (mpz_class x, mpz_class y){
    int cnt = 0;
    while(y > 1){
        y /= x;
        cnt++;
    }
    return cnt;
}

mpz_class pow_unlimit(mpz_class x, mpz_class y){
    if(x == 1 || y == 0) return 1;
    if(x == 0) return 0;
    if(y == 1) return x;
    mpz_class y1, y2;
    y1 = y/2;
    y2 = y%2;
    mpz_class p1, p2;
    p1 = pow_unlimit(x, y1);
    p2 = pow_unlimit(x, y2);
    mpz_class rtn = p1*p1*p2;
    return rtn;
}

int MAX_DECK = 1;
int INT_INF = MAX_DECK*240;//指数部分の最大値 (2^INT_INF > 10^(72*MAX_DECK))
mpz_class INF = pow_unlimit(2, INT_INF);

mpz_class pow(mpz_class x, mpz_class y){
    if(x == 1 || y == 0) return 1;
    if(x == 0) return 0;
    if(y == 1) return x;
    if(log(2, x) * y >= INT_INF) return INF;
    mpz_class y1, y2;
    y1 = y/2;
    y2 = y%2;
    mpz_class p1, p2;
    p1 = pow(x, y1);
    p2 = pow(x, y2);
    mpz_class rtn = p1 * p1 * p2;
    return rtn;
}

mpz_class pow_mod(mpz_class x, mpz_class y, mpz_class z){
    if(z < 2) return 0;
    x %= z;
    if(y == 0) return 1;
    if(x == 0) return 0;
    if(y == 1) return x;
    if(x == 1) return 1;

    mpz_class y1, y2;
    y1 = y/2;
    y2 = y%2;
    mpz_class p1, p2;
    p1 = pow_mod(x, y1, z);
    p2 = pow_mod(x, y2, z);
    return p1*p1*p2%z;
}

bool MRpt(mpz_class n){
    if(n < 2) return false;
    if(n == 2) return true;
    if(n % 2 == 0) return false;

    int k = 100;
    int s = 0;
    mpz_class m = n-1;
    while(m%2 == 0){
        s++;
        m /= 2;
    }
    int w = pow(10,9)*2;
    if(w > n-2) w = ((mpz_class)(n-2) % w);
    //cout << n << endl;
    for(int i = 0; i < k; i++){
        int a = rand()%w+2;
        mpz_class p = pow_mod(a, m, n);
        if(p == 1 || p == n - 1) continue;
        bool b2 = false;
        for(int j = 1; j < s; j++){
            p = p*p%n;
            //cout << a << "^" << "(2^" << j << "*" << m << ")=" << p << endl;
            if(p == n - 1) {
                b2 = true;
                break;
            }
        }
        if(!b2) return false;
    }
    return true;
}

//カード

int to_strength(char c){
    if('0' <= c && c <= '9'){
        return c - '0';
    }
    else if(c == 'T'){
        return 10;
    }
    else if(c == 'J'){
        return 11;
    }
    else if(c == 'Q'){
        return 12;
    }
    else if(c == 'K'){
        return 13;
    }
    else if(c == 'X'){
        return -1;
    }
    return -2;
}

char to_card(int n){
    if(0 <= n && n < 10){
        return '0' + n;
    }
    else if(n == 10){
        return 'T';
    }
    else if(n == 11){
        return 'J';
    }
    else if(n == 12){
        return 'Q';
    }
    else if(n == 13){
        return 'K';
    }
    else if(n == -1){
        return 'X';
    }
    return 'E';
}

//{'T',10}
struct pqk_cd {
    char card;
    mpz_class strength;
    pqk_cd(){
        card = 'E';
        strength = -1;
    }
    pqk_cd(int n){
        strength = n;
        card = to_card(n);
    }
    pqk_cd(char c){
        card = c;
        to_strength(c);
    }
};


//カード列

mpz_class to_strength(string s){
    int n = s.size();
    if(n == 0){
        return 0;
    }
    if(n == 1){
        return to_strength(s[0]);
    }

    string t = s;
    char c = s[n-1];
    t.pop_back();

    mpz_class m =  to_strength(t);
    int l = to_strength(c);

    if(m == -2 || l == -2) return -2;
    if(m == -1 || l == -1) return -1;


    mpz_class rtn;
    if(l < 10) {
        rtn = m * 10 + l;
    }
    else {
        rtn = m * 100 + l;
    }
    return rtn;
}

string to_row(mpz_class n){
    if(n < -1) return "E";
    if(n == -1) return "X";
    if(n < 10){
        int m = n%10;
        char c = '0'+m;
        string c_str;
        c_str.push_back(c);
        return c_str;
    }

    mpz_class m = n/10;
    int r = n%10;
    string s = to_row(m);
    char c = to_card(r);
    return s+c;
}

bool check_consistency(string &s){
    if(s[0] == '0') {
        s = "E";
        return false;
    }
    if(to_strength(s) == -2){
        s = "E";
        return false;
    }
    return true;
}

//{"QK", 1213, 2, 4}
struct pqk_n {
    string row;
    mpz_class strength;
    int size;
    int digit;
    pqk_n() {
        row = "E";
        strength = -2;
        size = -2;
        digit = -2;
    }
    pqk_n(string s){
        row = s;
        strength = to_strength(s);
        size = s.size();
        digit = to_row(strength).size();
    }
    pqk_n(mpz_class n){
        strength = n;
        row = to_row(strength);
        size = row.size();
        digit = to_row(strength).size();
    }

    void normalize(){
        mpz_class i = to_strength(row);
        if(i == -2){
            row = "E";
            strength = -2;
            size = -2;
            digit = -2;
        }
        else if(i == -1){
            strength = -1;
            digit = -1;
        }
    }

    pqk_n operator+ (const pqk_n &other){
        pqk_n rtn;
        rtn.row = row + other.row;
        rtn.size = size + other.size;
        rtn.digit = digit + other.digit;
        rtn.strength = strength * pow(10, other.digit) + other.strength;
        rtn.normalize();
        return rtn;
    }

    void print(){
        cout << row << " " << strength << " " << size << " " << digit << endl;
    }
};

bool operator< (pqk_n n, pqk_n m){
    return n.strength < m.strength;
}
bool operator<= (pqk_n n, pqk_n m){
    return n.strength <= m.strength;
}
bool operator> (pqk_n n, pqk_n m){
    return n.strength > m.strength;
}
bool operator>= (pqk_n n, pqk_n m){
    return n.strength >= m.strength;
}


//手札
//{{'1',2},...,{'T',4}}
using hand = map<char,int>;

hand to_hand(string s){
    hand h;
    for(char c : s){
        h[c]++;
    }
    return h;
}

hand to_hand(vector<string> g){
    hand h;
    for(string s : g){
        for(char c : s){
            h[c]++;
        }
    }
    return h;
}


//合成数
using fact_int = vector<vector<mpz_class>>;
using fact_cd = vector<vector<string>>;

mpz_class fact_to_strength(vector<mpz_class> vi){
    int a = vi.size();
    if(a == 0) return 1;
    for(int j = a - 1; j > 0; j--){
        vi[j - 1] = pow(vi[j - 1], vi[j]);
    }
    return vi[0];
}

mpz_class fact_to_strength(fact_int f){
    mpz_class rtn = 1;
    for(vector<mpz_class> vi : f){
        rtn *= fact_to_strength(vi);
    }
    return rtn;
}
fact_int fact_to_fact_int(fact_cd f){
    fact_int rtn;
    int sz = 0;
    for(vector<string> vs : f){
        rtn.push_back({});
        sz++;
        for(string s : vs){
            rtn[sz-1].push_back(to_strength(s));
        }
    }
    return rtn;
}
fact_cd fact_to_fact_cd(string s){
    fact_cd rtn(1,vector<string>(1,""));
    int i = 0;
    int j = 0;
    for(char c : s){
        if(c == '*'){
            rtn.push_back({""});
            i++;
            j = 0;
        }
        else if(c == '^'){
            rtn[i].push_back("");
            j++;
        }
        else{
            rtn[i][j].push_back(c);
        }
    }
    return rtn;
}

mpz_class fact_to_strength(fact_cd f){
    return fact_to_strength(fact_to_fact_int(f));
}
mpz_class fact_to_strength(string s){
    return fact_to_strength(fact_to_fact_cd(s));
}
fact_int fact_to_fact_int(string s){
    return fact_to_fact_int(fact_to_fact_cd(s));
}

fact_cd fact_to_fact_cd(fact_int f){
    fact_cd rtn;
    int sz = 0;
    for(vector<mpz_class> vi : f){
        rtn.push_back({});
        sz++;
        for(mpz_class i : vi){
            rtn[sz-1].push_back(to_row(i));
        }
    }
    return rtn;
}

//{"KQ", 1312, 2, 4, {{2,5},{41}}}
struct pqk_c {
    string row;
    mpz_class strength;
    int size;
    int digit;
    fact_cd factor;

    pqk_c(){
        row = "E";
        strength = -2;
        size = 0;
        digit = 0;
        factor = {{"0"}};
    }
    pqk_c(string s){
        factor = fact_to_fact_cd(s);
        strength = fact_to_strength(factor);
        row = to_row(strength);
        size = row.size();
        digit = row.size();
    }
    pqk_c(string s, mpz_class n){
        factor = fact_to_fact_cd(s);
        strength = n;
        row = to_row(strength);
        size = row.size();
        digit = row.size();
    }
    pqk_c(fact_int f){
        factor = fact_to_fact_cd(f);
        strength = fact_to_strength(f);
        row = to_row(strength);
        size = row.size();
        digit = row.size();
    }
    pqk_c(fact_int f, mpz_class n){
        factor = fact_to_fact_cd(f);
        strength = n;
        row = to_row(strength);
        size = row.size();
        digit = row.size();
    }

    pqk_c operator*(const pqk_c &other){
        pqk_c rtn;
        rtn.strength = strength * other.strength;
        rtn.factor = factor + other.factor;

        rtn.row = to_row(rtn.strength);
        rtn.size = rtn.row.size();
        rtn.digit = rtn.row.size();

        return rtn;
    }

    void check(){
        if(!check_consistency(row)){
            pqk_c();
            return;
        }
        for(vector<string> vs : factor){
            for(string s : vs){
                if(!check_consistency(s)){
                    pqk_c();
                    return;
                }
                if(to_strength(s) < 2){
                    pqk_c();
                    return;
                }
            }
        }
        mpz_class r_str = to_strength(row);
        mpz_class f_str = fact_to_strength(factor);
        if(strength != r_str || strength != f_str){
            pqk_c();
        }
    }

    void print(){
        cout << row << endl;
        //cout << strength << endl;
        print_vv(factor);
        //cout << size << " " << digit << endl;
    }
};


//pqkable

int pqkable (hand h){
    int rtn = 0;
    for(auto pr : h){
        char c;
        int i;
        int st;
        tie(c,i) = pr;
        st = to_strength(c);
        if(st < -1) return -2;
        if(st == -1 || st == 0) rtn += i;
        else rtn += max(0,i-4); 
    }
    return rtn;
}

int pqkable (string s){
    hand h = to_hand(s);
    return pqkable(h);
}

int pqkable (vector<string> g){
    hand h = to_hand(g);
    return pqkable(h);
}

int pqkable_cut (hand h){
    int rtn = 0;
    for(int i = 3; i > 1; i--){
        char c = to_card(10 + i);
        int x = h[c];
        int y = h['1'];
        int z = h['0' + i];
        int w = 0;
        if(x > 4 && y < 4 && z < 4){
            w = min(x - 4, min(4 - y, 4 - z));
        }

        h[c] -= w;
        h['1'] += w;
        h['0' + i] += w;
    }
    {
        int x = h['J'];
        int y = h['1'];
        int w = 0;
        if(x > 4 && y < 4){
            w = min(x - 4, (4 - y) / 2);
        }

        h['J'] -= w;
        h['1'] += 2*w;
    }
    rtn = pqkable(h);
    return rtn;
}

int pqkable_cut (string s){
    hand h = to_hand(s);
    return pqkable_cut(h);
}

int pqkable_cut (vector<string> g){
    hand h = to_hand(g);
    return pqkable_cut(h);
}

vector<mpz_class> analyze_pqkable (mpz_class n){
    string s = to_row(n);
    int d = s.size();
    vector<int> v(d);
    vector<int> w(d);
    vector<int> x(d);
    vector<bool> b(d,true);
    int vi = 0;
    for(int i = 0; i < d; i++){
        v[i] = vi; 
        if(s[i] == '1') vi++;
        else vi = 0;
    }
    int xi;
    for(int i = d - 1; i >= 0; i--){
        char c = s[i];
        if(i == d - 1 || c != '1'){
            w[i] = c - '0';
            xi = i;
            x[i] = i;
        }
        else if(w[i+1] > 3){
            w[i] = 1;
            xi = i;
            x[i] = i;
        }
        else{
            w[i] = w[i+1];
            x[i] = xi;
        }
    }
    for(int i = 0; i < d; i++){
        if(s[i] != '1') continue;
        if(x[i] == i) continue;
        if(v[i]%2 == 0){
            b[i] = false;
        }
        if(w[i] != 1 && x[i] - i < 2){
            b[i] = false;
        }
    }

    vector<string> vs(1);
    for(int i = 0; i < d; i++){
        if(i && b[i-1]) vs.push_back("");
        vs[vs.size()-1].push_back(s[i]);
    }

    vector<mpz_class> vn;
    for(string t : vs){
        vn.push_back(to_strength(t));
    }

    return vn;
}

vector<mpz_class> analyze_pqkable (vector<mpz_class> v){
    vector<mpz_class> rtn;
    for(mpz_class i : v){
        rtn = rtn + analyze_pqkable(i);
    }
    return rtn;
}

int pqkable_analyzed (vector<mpz_class> v){
    hand h;
    vector<int> loop_max(4,0);
    for(mpz_class i : v){
        if(i < 100){
            h[to_card(i%14)]++;
        }
        else{
            loop_max[i%10]++;
        }
    }
    
    vector<int> loop_now(4,0);
    bool b = true;
    int rtn = INT_INF;
    while(b){
        hand ha = h;
        for(int i = 0; i < 4; i++){
            int x = loop_now[i];
            int y = loop_max[i] - x;
            ha['1'] += x;
            ha[to_card(10 + i)] += x;
            ha['J'] += y;
            ha['0' + i] += y;
        }

        rtn = min(rtn, pqkable_cut(ha));

        b = false;
        for(int i = 0; i < 4; i++){
            if(loop_now[i] < loop_max[i]) {
                loop_now[i]++;
                for(int j = i-1; j >= 0; j--){
                    loop_now[j] = 0;
                }
                b = true;
                break;
            }
        }
    }

    return rtn;
}

int pqkable (mpz_class n){
    vector<mpz_class> v = analyze_pqkable(n);
    return pqkable_analyzed(v);
}

int pqkable (vector<mpz_class> v){
    vector<mpz_class> w = analyze_pqkable(v);
    return pqkable_analyzed(w);
}

int pqkable (pqk_c c){
    vector<mpz_class> v;
    v.push_back(c.strength);
    for(vector<string> vs : c.factor){
        for(string s : vs){
            v.push_back(to_strength(s));
        }
    }
    return pqkable(v);
}


//指数部
vector<vector<vector<mpz_class>>> exp_list(INT_INF);
void calc_exp(){
    //p^x
    for(int i = 2; i < INT_INF; i++){
        exp_list[i].push_back({i});
    }
    //p^x^x
    for(int i = 2; i < INT_INF; i++){
        int e = i;
        for(int j = 2; j < INT_INF; j++){
            e *= i;
            if(e < INT_INF){
                exp_list[e].push_back({i,j});
            }
            else break;
        }
    }
    //p^x^x^x
    for(int i = 2; i < INT_INF; i++){
        int maxjk = log(i, INT_INF) + 1;
        for(int j = 2; j < INT_INF; j++){
            int jk = j;
            for(int k = 2; k < INT_INF; k++){
                jk *= j;
                if(jk > maxjk) break;
                int ijk = pow(i,jk);
                if(ijk < INT_INF){
                    exp_list[ijk].push_back({i, j, k});
                }
                else break;
            }
        }
    }
    //p^x^x^x^x >= p^65536

    //print
    /*for(int i = 2; i < INT_INF; i++){
        if(exp_list[i].size() < 2) continue;
        cout << i << endl;
        print_vv(exp_list[i]);
        cout << endl;
    }*/
}

int main(){
    srand(time(NULL));
    calc_exp();

    mpz_class i_start;
    cin >> i_start;

    double time_start = calcTime();
    double time_1 = time_start;
    double time_interval = 1*1000;

    mpz_class MAX_N = pow((mpz_class)10,36);
    vector<pqk_c> v(INT_INF);
    int MAX_E = INT_INF-1;
    mpz_class BIG_N = pow((mpz_class)2, 122);
    for(mpz_class i = i_start; i < MAX_N; i++){
        if(!MRpt(i)) continue;
        {
            double time_now = calcTime();
            if(time_now - time_1 >= time_interval){
                cout << "t = " << (int)((time_now - time_start)/time_interval);
                cout << ", n = " << i;
                cout << ", MAX_E = " << MAX_E << endl;
                time_1 = time_now;
            }
        }
        string s = to_row(i);
        mpz_class n = i;
        vector<mpz_class> i_v = {i};
        for(int j = 2; j <= MAX_E; j++){
            n *= i;
            if(to_row(n).size()+1+s.size() > 72) {
                for(int k = MAX_E; k >= j; k--){
                    if(v[k].strength < 0) continue;
                    v[k].print();
                }
                MAX_E = j - 1;
                break;
            }
            for(vector<mpz_class> f : exp_list[j]){
                fact_int pf = {i_v + f};
                pqk_c c(pf, n);
                if(pqkable(c) <= 2){
                    v[j] = c; 
                    if(n >= BIG_N){
                        cout << ">>>";
                        c.print();
                    }
                }
            }
        }
    }
}