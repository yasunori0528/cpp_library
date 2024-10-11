#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
template <typename T> using min_priority_queue = priority_queue<T,vector<T>,greater<T>>;

//時間計測
char print_time_option = 's';
double time_start;
double time_now;
double time_end;
double time_1;
double time_interval;

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

//数学
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

vector<int> MR_list = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

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

mpz_class ALcgs = 98765432110111213;
mpz_class BLcgs = 3;
mpz_class MLcgs = (mpz_class)1 << 48;
mpz_class nextLcgs(mpz_class x){
    x = ( ALcgs * x + BLcgs ) % MLcgs;
    return x;
}

mpz_class PRC = 1;
mpz_class PRSub(mpz_class x, mpz_class n){
    return (x*x+PRC)%n;
}

mpz_class PRAlgo(mpz_class n){
    mpz_class x = 2;
    mpz_class y = 2;
    mpz_class d = 1;
    while(d == 1){
        x = PRSub(x, n);
        y = PRSub(PRSub(y, n), n);
        d = gcd(abs(x-y), n);
    }
    return d;
}

vector<mpz_class> primeFactorize(mpz_class n){
    //cout << "--" << n << endl;
    vector<mpz_class> rtn;
    while(n%2 == 0){
        rtn.push_back(2);
        n /= 2;
    }
    queue<mpz_class> q;
    q.push(n);
    while(!q.empty()){
        mpz_class pos = q.front();
        //cout << "--pop : " << pos << endl;
        q.pop();
        if(MR_test(pos)){
            rtn.push_back(pos);
            continue;
        }
        mpz_class d = PRAlgo(pos);
        mpz_class e = pos/d;
        if(d > 1) q.push(d);
        if(e > 1) q.push(e);
        if(d == 1 || e == 1) PRC++;
        //cout << "--push : " << d << endl;
        //cout << "--push : " << e << endl;
    }
    return rtn;
}

//素数大富豪
multiset<string> tmpPqkableVec;
string tmpPqkableStr;

bool pqkableSub(int i){
    ;
}

bool pqkable(string s, multiset<string> v){
    tmpPqkableVec = v;
    tmpPqkableStr = s;
}

void calc(){
    mpz_class x; cin >> x;
    time_start = calcTime();
    for(int i = 0; i < 10; i++){
        x = nextLcgs(x);
        mpz_class x; cin >> x;
        vector<mpz_class> v = primeFactorize(x);
        sort(v.begin(),v.end());
        bool b = false;
        cout << x << " = ";
        for(mpz_class p : v){
            if(b) cout << " * ";
            else b = true;
            cout << p;
        }
        cout << endl;
    }
}

int main(){
    calc();
    printTime();
}