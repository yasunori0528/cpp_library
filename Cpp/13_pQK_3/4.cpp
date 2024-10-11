#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

//時間計測

double time_start;
double time_now;
double time_end;
double time_1;
double time_interval;

double calcTime(){
    struct::timespec getTime;
    clock_gettime(CLOCK_MONOTONIC, &getTime);
    return (getTime.tv_sec + getTime.tv_nsec*1e-9) *1000;
}

void printTime(){
    time_now = calcTime();
    time_1 = time_now;
    cout << time_now - time_start << "[ms]" << endl;
}

bool printTime(double t){
    time_now = calcTime();
    if(time_now - time_1 >= t){
        printTime();
        return 1;
    }
    return 0;
}
//基本

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

int digit(mpz_class n){
    if(n < 10) return 1;
    else return digit(n/10)+1;
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

//基本
//素数大富豪基本

int MAX_DIGIT = 34;
mpz_class MAX_N;
mpz_class MIN_CMP = pow_n((mpz_class)2,(mpz_class)1);

void separate_string(string s, map<int,int> &v){
    int l = 0;
    int r = s.size();
    int m = 0;
    while(l < r){
        if(m < r-1 && s[m] == '1' && s[m+1] <= '3'){
            m++;
        }
        else{
            while(m-l > 2){
                v[stoi(s.substr(l,2))]++;
                l += 2;
            }
            v[stoi(s.substr(l,m-l+1))]++;
            l = m+1;
            m = l;
        }
    }
}

//素数大富豪基本
//素因数

vector<int64_t> prime_list;

void calc_prime_list(int64_t x){
    vector<int64_t> natural(x+1,0);
    for(int64_t i = 2; i*i <= x; i++){
        if(natural[i]) continue;
        int64_t j = i*i;
        while(j <= x){
            natural[j] = i;
            j += i;
        }
    }
    for(int64_t i = 2; i <= x; i++){
        if(!natural[i]) prime_list.push_back(i);
    }
}

vector<int> MR_list = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

//a^(x-1)%x == 1, x-1 == 2^r*d;
bool MR_sub(int a, mpz_class x, int r, mpz_class d){
    mpz_class ad = pow_mod(a, d, x);
    if(ad == 1) return true;
    for(int i = 0; i < r; i++){
        if(ad == x-1) return true;
        ad = ad*ad%x;
    }
    return false;
}

bool MR_test(mpz_class x){
    if(x <= 1) return false;
    if(x == 2) return true;
    if(x%2 == 0) return false;

    int r = 0;
    mpz_class d = x-1;
    while(d%2 == 0){
        d /= 2;
        r++;
    }

    for(int a : MR_list){
        if(a >= x) break;
        if(MR_sub(a,x,r,d)) continue;
        return false;
    }
    return true;
}

//素因数
//指数

//指数 { 81 , {3,2,2} , 3 }
struct exponent{
    int abs;
    vector<int> ex;
    int digit;

    void print(){
        //cout << digit << ":" << abs << "=";
        bool b = 0;
        for(int i : ex){
            if(b) cout << "^";
            else b = 1;
            cout << i;
        }
    }
};


//exp_list[digit][j]
vector<vector<exponent>> exp_list;

void calc_exp_list(int x){
    exp_list.resize(x+1);

    exp_list[1].push_back({1,{},0});
    for(int i = 2; i <= x; i++){
        exp_list[i].push_back({i,{i},digit(i)});
    }
    for(int i = 2; i <= x; i++){
        bool b = 0;
        for(int j = 2; j <= x; j++){
            int a = pow_n(i,j);
            //cout << a << " " << i << " " << j << endl;
            if(a > x) {
                if(j == 2) b = 1;
                break;
            }
            exp_list[a].push_back({a,{i,j},digit(i)+digit(j)});
        }
        if(b) break;
    }
    for(int i = 2; i <= x; i++){
        bool b1 = 0;
        for(int j = 2; j <= x; j++){
            bool b2 = 0;
            for(int k = 2; k <= x; k++){
                int a = pow_n(i,pow_n(j,k));
                //cout << a << " " << i << " " << j << " " << k << endl;
                if(a > x){
                    if(k == 2) {
                        b2 = 1;
                        if(j == 2) b1 = 1;
                    }
                    break;
                }
                exp_list[a].push_back({a,{i,j,k},digit(i)+digit(j)+digit(k)});
            }
            if(b2) break;
        }
        if(b1) break;
    }
}

//指数
//冪

//{6561,3,8,2}
struct power{
    mpz_class abs;
    mpz_class base;
    exponent exp;
    int digit;

    power(){
        ;
    }

    power(mpz_class n){
        abs = n;
    }

    power(mpz_class a, mpz_class b, exponent e, int d){
        abs = a;
        base = b;
        exp = e;
        digit = d;
    }

    void print(){
        cout << base;
        if(exp.ex.size()){
            cout << "^";
            exp.print();
        }
        //cout << "=" << abs << endl;
    }
};

bool operator<(const power & x, const power & y){
    return x.abs < y.abs;
}

vector<vector<power>> pow_list;

//冪の桁数, 冪の大きさ, 合成数としての桁数
void calc_pow_list(int d_pow, mpz_class ab, int d_cmp){
    pow_list.resize(d_pow+1+3);
    for(int64_t p : prime_list){
        mpz_class pow_p_i = p;
        int digit_p = digit(p);
        for(int i = 1; i <= exp_list.size(); i++){
            for(exponent j : exp_list[i]){
                int dij_pow = digit_p + j.digit;
                int dij_cmp = dij_pow + digit(pow_p_i);
                power pw(pow_p_i, (mpz_class)p, j, dij_pow);
                /*if(dij_pow <= d_pow)*/ pow_list[dij_pow].push_back(pw);
            }
            pow_p_i *= p;
            if(pow_p_i >= ab) break;
        }
    }

    for(int i = 1; i <= d_pow+3; i++){
        sort(pow_list[i].begin(), pow_list[i].end());
    }

    /*for(int i = 1; i <= d_pow+3; i++){
        cout << "d = " << i << " --------------------------------" << endl;
        for(power j : pow_list[i]){
            j.print();
            cout << endl;
        }
    }*/
}

//冪
//素因数場
//{abs,p_fact,digit}
struct composite{
    mpz_class abs;
    vector<power> p_fact;
    int digit;

    composite(mpz_class a, vector<power> p, int d){
        abs = a;
        p_fact = p;
        digit = d;
    }

    void print(){
        cout << abs << "=";
        bool b = 0;
        for(power p : p_fact){
            if(b) cout << "*";
            else b = 1;
            p.print();
        }
        cout << endl;
    }

    void print_p_fact(){
        bool b = 0;
        for(power p : p_fact){
            if(b) cout << "*";
            else b = 1;
            p.print();
        }
        cout << endl;
    }

    int pqkable(){
        if(p_fact.size() == 1 && p_fact[0].exp.abs == 1) return 100;
        map<int,int> v;
        string cmp_abs = abs.get_str();
        separate_string(cmp_abs, v);
        for(power p : p_fact){
            string p_base = p.base.get_str();
            separate_string(p_base, v);
            for(int i : p.exp.ex){
                separate_string(to_string(i), v);
            }
        }

        vector<int> pqk_loop_now(4,0);
        vector<int> pqk_loop_max(4);
        for(int i = 0; i <= 3; i++){
            pqk_loop_max[i] = v[110+i];
        }

        int rtn = 100;
        while(1){
            auto vi = v;
            for(int j = 0; j <= 3; j++){
                int a1 = pqk_loop_now[j];
                int a2 = pqk_loop_max[j] - a1;
                vi[11] += a1;
                vi[j] += a1;
                vi[1] += a2;
                vi[10+j] += a2;
                vi[110+j] = 0;
            }

            for(int j = 13; j >= 12; j--){
                while(vi[j] > 2 && vi[1] < 2 && vi[j%10] < 2){
                    vi[j]--;
                    vi[1]++;
                    vi[j%10]++;
                }
            }
            if(vi[11] > 2 && vi[1] <= 0){
                vi[11]--;
                vi[1] += 2;
            }
            for(int j = 1; j <= 13; j++){
                if(vi[j] > 2){
                    vi[0] += vi[j]-2;
                    vi[j] = 2;
                }
            }
            chmin(rtn, vi[0]);

            bool b = 0;
            for(int i = 0; i <= 3; i++){
                if(pqk_loop_now[i] < pqk_loop_max[i]){
                    b = 1;
                    pqk_loop_now[i]++;
                    for(int j = 0; j < i; j++){
                        pqk_loop_now[j] = 0;
                    }
                    break;
                }
            }
            if(!b) break;
        }

        return rtn;
    }
};

bool operator<(const composite & x, const composite & y){
    return x.abs < y.abs;
}

//冪の桁数の組
vector<vector<vector<int>>> v_comb_pow_digit;
void calc_comb_pow_digit(int x){
    v_comb_pow_digit.resize(x+1);
    for(int i = 1; i <= x; i++){
        v_comb_pow_digit[i].push_back({i});
        for(int j = 1; j < i; j++){
            for(vector<int> v : v_comb_pow_digit[j]){
                if(v[v.size()-1] <= i-j){
                    v.push_back(i-j);
                    v_comb_pow_digit[i].push_back(v);
                }
            }
        }
    }
}

//冪の桁数の組を固定して合成数全列挙
vector<int> loop_now;
vector<int> loop_max;
vector<mpz_class> v_sub;
vector<power> p_fact_now;

vector<int> vec;
int sz;
int n, m;

int n_start;
vector<int> v_start;

bool calc_cmp1_update(int i){
    //cout << i << endl;
    if(i < 0) return false;
    if(loop_now[i] < loop_max[i]-1){
        loop_now[i]++;
        v_sub[i+1] = v_sub[i]*pow_list[vec[i]][loop_now[i]].abs;
        p_fact_now[i] = pow_list[vec[i]][loop_now[i]];
        for(int j = i+1; j < sz; j++){
            if(vec[j] == vec[j-1]) loop_now[j] = loop_now[j-1];
            else loop_now[j] = 0;
            
            v_sub[j+1] = v_sub[j]*pow_list[vec[j]][loop_now[j]].abs;
            p_fact_now[j] = pow_list[vec[j]][loop_now[j]];
        }
        return true;
    }
    else if(i != 0){
        return calc_cmp1_update(i-1);
    }
    return false;
}

composite MAX_CMP(0,{},0);

vector<vector<composite>> CMP_list_small;//素因数場n桁以下の合成数のうち、消費桁数72-2n-1桁以下のもの
void calc_cmp1(vector<int> v){
    vec = v;
    sz = v.size();
    if(v[sz-1] > n) return;
    int d = 0;
    for(int i : v){
        d += i;
    }
    MAX_N = pow_n((mpz_class)10,(mpz_class)(MAX_DIGIT-d));

    loop_now.clear();
    loop_max.clear();
    v_sub.clear();
    p_fact_now.clear();

    loop_now.resize(sz,0);
    loop_max.resize(sz,0);
    v_sub.resize(sz+1,1);
    p_fact_now.resize(sz);

    
    for(int i = 0; i < sz; i++){
        loop_max[i] = pow_list[v[i]].size();
        v_sub[i+1] = v_sub[i]*pow_list[v[i]][0].abs;
        p_fact_now[i] = pow_list[v[i]][0];
    }

    printTime();
    for(int i : v) cout << i << " "; cout << endl;
    //for(int i : loop_max) cout << i << " "; cout << endl;

    int update_i;
    do{
        update_i = sz-1;
        composite cmp(v_sub[sz], p_fact_now, digit(v_sub[sz])+d);
        if(printTime(time_interval)) {
            cout << "----";
            cmp.print_p_fact();
        }
        if(d <= n && cmp.digit <= MAX_DIGIT-1-2*n) {
            CMP_list_small[d].push_back(cmp);
        }
        if(cmp.digit > MAX_DIGIT) update_i = sz-2;
        if(cmp.abs < MAX_CMP.abs) continue;
        else if (MAX_CMP.abs <= cmp.abs && cmp.pqkable() <= 0){
            MAX_CMP = cmp;
            cmp.print();
        }
    }while(calc_cmp1_update(update_i));
}

void calc1(){
    bool b = false;
    for(int i = 1; i <= m; i++){
        for(auto j : v_comb_pow_digit[i]){
            //for(int k : j) cout << k << " "; cout << endl;
            for(int k : j) cout << k << " "; cout << endl;
            calc_cmp1(j);
        }
    }
    for(auto &i : CMP_list_small){
        sort(i.begin(), i.end());
    }

    /*for(auto i : CMP_list_small){
        for(auto j : i){
            j.print();
        }
        cout << endl;
    }*/
}

void calc2_sub(power pw){
    for(int i = 1; i <= m-pw.digit; i++){
        mpz_class cmp_upper_bound = pow_n((mpz_class)10,(mpz_class)(34-i-pw.digit));
        for(composite cmp : CMP_list_small[i]){
            cmp.abs *= pw.abs;
            if(cmp < MAX_CMP) continue;
            if(cmp.abs >= cmp_upper_bound) break;
            cmp.p_fact.push_back(pw);
            if (MAX_CMP.abs <= cmp.abs && cmp.pqkable() <= 0){
                MAX_CMP = cmp;
                cmp.print();
            }
        }
    }
}

void calc2(){
    //n桁以下の素数の大きい冪
    for(int i = n+1; i <= n+3; i++){
        for(power pw : pow_list[i]){
            if(printTime(time_interval)) {
                cout << "----" << endl;
                pw.print();
                cout << endl;
            }
            calc2_sub(pw);
            //cout << endl;
        }
    }
    //n+1桁以上の素数を順に探索
    MAX_N = pow_n((mpz_class)10,(mpz_class)(34-n-1));
    for(mpz_class p = pow_n((mpz_class)10,(mpz_class)n)+1; p < pow_n((mpz_class)10,(mpz_class)(m-1)); p += 2){
        if(!MR_test(p)) continue;
        {
            composite p_cmp = {p,{},0};
            if(p_cmp.pqkable() > 0) continue;
        }
        if(printTime(time_interval)) {
            cout << "----";
            cout << p << endl;
        }
        int p_digit = digit(p);
        vector<mpz_class> pow_p(1,1);//pの累乗
        for(int i = 1; i <= 256; i++){
            pow_p.push_back(pow_p[i-1]*p);
            if(pow_p[i] > MAX_N) break;
        }
        //cout << p << ":" << pow_p.size() << endl;
        for(int i = 1; i < pow_p.size(); i++){
            for(exponent ex : exp_list[i]){
                power pw(pow_p[i],p,ex,p_digit+ex.digit);
                if(i > 1){
                    composite cmp(pow_p[i], {pw}, p_digit+ex.digit);
                    
                    if(MAX_CMP.abs <= cmp.abs && cmp.pqkable() <= 0){
                        MAX_CMP = cmp;
                        cmp.print();
                    }
                }
                calc2_sub(pw);
            }
        }
    }
}

//素因数場

void input(){
    cin >> n;
    m = 2*n+1;
    //m = n;
    MAX_N = pow_n((mpz_class)10, (mpz_class)69);
    CMP_list_small.resize(n+1);

    time_interval = 1000*60*60;
    return;
}

//素因数場2n+1桁以下の合成数全列挙
int main(){
    input();
    time_start = calcTime();

    /*---------------- ----------------*/


    calc_prime_list(pow_n(10,n));
    calc_exp_list(256);
    calc_pow_list(n, MAX_N, MAX_DIGIT);
    calc_comb_pow_digit(m);
    calc1();
    calc2();
    MAX_CMP.print();

    /*---------------- ----------------*/

    printTime();
    return 0;
}