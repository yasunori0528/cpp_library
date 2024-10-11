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

template<typename T>
T pow_mod(T a, T b, T n){
    a %= n;
    if(a == 0) return 0;
    if(a == 1 || b == 0) return 1;
    if(b == 1) return a;
    T c = b/2;
    T d = b%2;
    T ac = pow_mod(a,c,n);
    T ad = pow_mod(a,d,n);
    return ac*ac%n*ad%n;
}

template<typename T>
bool miller_rabin(T x){
    if(x <= 1) return false;
    if(x == 2) return true;
    if(x % 2 == 0) return false;

    //assert(x <= sqrt(numeric_limits<T>::max()));

    int s = 0;
    T d = x - 1;
    while(d % 2 == 0){
        d /= 2;
        s++;
    }

    T k = 1000;
    if(x - 1 < k) k = x - 1;

    set<T> A;

    {
        T a_max = x - 1;
        while(A.size() < k){
            A.insert(engine() % a_max + 1);
        }
    }

    for(T a : A){
        T t = pow_mod(a, d, x);
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


mpz_class to_int(string s){
    mpz_class rtn = 0;
    for(char c : s){
        rtn = rtn * 10 + (c - '0');
    }
    return rtn;
}

int main(){

    int i = 1;
    while(i < 10){
        int j = 0;
        while(j <= i){
            int k = i - j;

            bool b = true;
            if(j == 0) b = false;
            if(k != 4) b = false;

            if(b){
                //cout << j << " " << k << endl;
                // /1(0{k,k+1}1)^{j}/
                for(uint64_t l = 0; l < (uint64_t(1)<<j); l++){
                    //cout << "l: " << l << endl;
                    string s = "1";
                    for(int m = 0; m < j; m++){
                        if((l>>m)&1) s += string(k + 1, '0');
                        else s += string(k, '0');
                        s.push_back('1');
                    }
                    mpz_class x = to_int(s);
                    if(miller_rabin(x)) cout << x << endl;
                }
            }
            
            j++;
        }
        i++;
    }
}