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

map<mpz_class,char> int2char;
void calc_int2char(){
    for(int i = 0; i < 10; i++){
        int2char[(mpz_class)i] = '0'+i;
    }
}
string to_string(mpz_class x){
    string rtn;
    while(x > 0){
        rtn.push_back(int2char[x%10]);
        x /= 10;
    }
    reverse(rtn.begin(), rtn.end());
    return rtn;
}

vector<mpz_class> temp;

void prime_factorize(mpz_class x){
    temp.clear();
    temp.push_back(x);
    temp.push_back(-1);
    bool first_p = true;
    for(mpz_class i = 2; i*i <= x; i++){
        int cnti = 0;
        while(x%i == 0){
            x /= i;
            cnti++;
        }
        if(cnti > 0){
            if(!first_p) temp.push_back(-2);
            else first_p = false;
            temp.push_back(i);
            if(cnti > 1){
                temp.push_back(-3);
                temp.push_back(cnti);
            }
        }
    }   
    if(x > 1){
        if(!first_p) temp.push_back(-2);
        else first_p = false;
        temp.push_back(x);
    }

    /*for(mpz_class x : temp){
        cout << x << " ";
    }
    cout << endl;*/
}

string vec2str(){
    string rtn;
    for(mpz_class x : temp){
        if(x == -1) rtn.push_back('=');
        else if(x == -2) rtn.push_back('*');
        else if(x == -3) rtn.push_back('^');
        else rtn += to_string(x);
    }
    return rtn;
}

int main(){
    calc_int2char();
    
    while(true){
        mpz_class x; cin >> x;
        //cout << to_string(x) << endl;
        prime_factorize(x);
        cout << vec2str() << endl;
    }
}