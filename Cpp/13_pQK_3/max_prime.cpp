#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

//時間計測

char print_time_option;
double time_start;
double time_now;
double time_end;
double time_1;
double time_interval;

//sec
double calcTime(){
    struct::timespec getTime;
    clock_gettime(CLOCK_MONOTONIC, &getTime);
    return getTime.tv_sec + getTime.tv_nsec*1e-9;
}

void printTime(){
    double t = calcTime() - time_start;
    if(print_time_option == 's'){
        printf("%010.3lf[s]\n", t);
        return;
    }
    else if(print_time_option == 'm'){
        t /= 60;
        printf("%09.1lf[m]\n", t);
    }
    else if(print_time_option == 'h'){
        t /= 3600;
        printf("%07.1lf[h]\n", t);
    }
    else if(print_time_option == 'd'){
        t /= 86400;
        printf("%06.1lf[d]\n", t);
    }
}

bool printTimeInterval(){
    time_now = calcTime();
    if(time_now - time_1 >= time_interval){
        time_1 = time_now;
        printTime();
        return true;
    }
    return false;
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

vector<vector<int>> binomialCoefficientSmallList(33,vector<int>(33,-1));
int binomialCoefficientSmall(int x, int y){
    if(x < 0 || x > 32 || y < 0 || y > x) return 0;
    if(binomialCoefficientSmallList[x][y] >= 0) return binomialCoefficientSmallList[x][y];

    int rtn;
    if(y == 0) rtn = 1;
    else if(y == x) rtn = 1;
    else rtn = binomialCoefficientSmall(x-1,y-1)+binomialCoefficientSmall(x-1,y);

    binomialCoefficientSmallList[x][y] = rtn;
    return rtn;
}

int char_to_int(char c){
    if(c == 'X') return 14;
    if(c == 'K') return 13;
    else if(c == 'Q') return 12;
    else if(c == 'J') return 11;
    else if(c == 'T') return 10;
    return c-'0';
}

vector<char> int_to_char = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K','X'};
vector<char> card_92_KQJ1T = {'9','8','7','6','5','4','3','2','K','X','Q','J','1','T'};

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

string max_prime(string s){
    int cntX = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == 'X') cntX++;
    }
    if(cntX){
        sort(s.begin(),s.end());
        vector<int> loop(cntX+1,1);
        loop[cntX] = 13;
        mpz_class maxPrimeInt = 0;
        string maxPrimeStr = "-1";
        while(1){
            string t = s;
            for(int i = 0; i < cntX; i++){
                t[t.size()-i-1] = int_to_char[loop[i]];
            }
            t = max_prime(t);

            if(t[0] != '-'){
                mpz_class tInt = str_to_int(t);
                if(chmax(maxPrimeInt, tInt)) maxPrimeStr = t;
            }
            
            bool b = false;
            for(int i = 0; i < cntX; i++){
                if(loop[i] < loop[i+1]){
                    loop[i]++;
                    for(int j = 0; j < i; j++){
                        loop[j] = 1;
                    }
                    b = true;
                    break;
                }
            }
            if(!b) break;
        }
        return maxPrimeStr;
    }

    vector<pair<int,char>> v;
    for(char c : s){
        v.push_back({msd(c),c});
    }
    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());
    mpz_class max_p = 0;
    string rtn = "-1";
    int j = -1;
    do{
        if(j >= 0 && v[j].first > 1) break;
        string t;
        for(auto pr : v){
            t.push_back(pr.second);
        }
        mpz_class n = str_to_int(t);
        if(n > 3 && n%3 == 0) return "-3";
        if(n > max_p && MR_test(n)){
            max_p = n;
            rtn = t;
            for(int i = 0; i < v.size(); i++){
                if(v[i].first == 1){
                    j = i;
                    break;
                }
            }
        }
    }while(prev_permutation(v.begin(),v.end()));
    return rtn;
}

int main(){
    string e = "8888888";
    int i = 0;
    while(1){
        string s = to_string(i);
        string p = e + s;;
    }
}