#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

double time_start;
double time_1;
double time_now;
double time_interval;

double calcTime(){
    struct::timespec getTime;
    clock_gettime(CLOCK_MONOTONIC, &getTime);
    return (getTime.tv_sec + getTime.tv_nsec*1e-9) *1000;
}

void printTime(){
    time_now = calcTime();
    time_1 = calcTime();
    //cout << time_now - time_start << "[ms]" << endl;
    int t =  round((time_now - time_start)/1000);
    string s = to_string(t+1000000).substr(1);
    cout << s << "[s]" << endl;
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

int char_to_int(char c){
    if(c == 'K') return 13;
    else if(c == 'Q') return 12;
    else if(c == 'J') return 11;
    else if(c == 'T') return 10;
    return c-'0';
}

vector<char> int_to_char = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K'};

int msd(char c){
    if('0' <= c && c <= '9') return c-'0';
    return 1;
}

mpz_class str_to_int(string s){
    if(s.size() == 0) return 0;
    string t = s;
    char c = s[s.size()-1];
    t.pop_back();
    int i = char_to_int(c);
    mpz_class rtn;
    if(i < 10) rtn = str_to_int(t)*10+i;
    else rtn = str_to_int(t)*100+i;
    return rtn;
}

string max_prime(string s){
    vector<pair<int,char>> v;
    for(char c : s){
        v.push_back({msd(c),c});
    }
    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());
    mpz_class max_p = 0;
    string rtn;
    int j = -1;
    do{
        if(j >= 0 && v[j].first > 1) break;
        string t;
        for(auto pr : v){
            t.push_back(pr.second);
        }
        mpz_class n = str_to_int(t);
        if(n%3 == 0) return "-1";
        if(n > max_p && MR_test(n)){
            max_p = n;
            rtn = t;
            for(int i = 0; i < v.size(); i++){
                if(v[i].first == 1){
                    j = i;
                    break;
                }
            }
            cout << t << endl;
        }
    }while(prev_permutation(v.begin(),v.end()));
    return rtn;
}

int main(){
    srand(time(NULL));
    int n = 319;
    int m = 80;
    vector<tuple<int,string,vector<int>>> v;
    for(int i = 0; i < n; i++){
        string s;
        int x;
        cin >> s >> x;
        vector<int> vi;
        for(int j = 0; j < x; j++){
            int y; cin >> y;
            vi.push_back(y);
        }
        v.push_back({x,s,vi});
    }
    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());
    int a = 0;
    for(int i = 0; i < n; i++){
        int vi0;
        string vi1;
        vector<int> vi2;
        tie(vi0,vi1,vi2) = v[i];
        if(vi0 < a) break;
        for(int j = i+1; j < n; j++){
            int vj0;
            string vj1;
            vector<int> vj2;
            tie(vj0,vj1,vj2) = v[j];
            if(vi0+vj0 < m) continue;
            set<int> st;
            for(auto k : vi2) st.insert(k);
            for(auto k : vj2) st.insert(k);
            if(st.size() >= m){
                a = vi0;
                cout << vi1;
                //for(int k : vi2) cout << " " << k;
                //cout << endl;
                cout << " " << vj1;
                //for(int k : vj2) cout << " " << k;
                cout << endl;
            }
        }
    }
}