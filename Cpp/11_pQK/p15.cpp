#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;

int char_int(char c){
    if(c == 'K') return 13;
    if(c == 'Q') return 12;
    if(c == 'J') return 11;
    if(c == 'T') return 10;
    return c - '0';
}

char int_char(int i){
    if(i == 13) return 'K';
    if(i == 12) return 'Q';
    if(i == 11) return 'J';
    if(i == 10) return 'T';
    return '0'+i;
}

int64_t str_int(string s){
    int64_t n = 0;
    for(char c : s){
        if(c == 'T') n = n*100+10;
        else if(c == 'J') n = n*100+11;
        else if(c == 'Q') n = n*100+12;
        else if(c == 'K') n = n*100+13;
        else n = n*10+(c-'0');
    }
    return n;
}

Bint str_bint(string s){
    Bint n = 0;
    for(char c : s){
        if(c == 'T') n = n*100+10;
        else if(c == 'J') n = n*100+11;
        else if(c == 'Q') n = n*100+12;
        else if(c == 'K') n = n*100+13;
        else n = n*10+(c-'0');
    }
    return n;
}

int64_t power(int64_t x, int64_t y){
  if(y < 0)
    return 0;
  else{
    int64_t n = 1ll;
    for(int64_t i = 0; i < y; i++)
      n *= x;
    return n;
  }
}

Bint powermod(Bint x, Bint y, Bint p){
    if(y < 0) return 0;
    if(y == 0) return 1;
    else{
        Bint n = powermod(x,y/2,p);
        n = n*n%p;
        if(y%2 == 1) n = n*x%p;
        return n;
    }
}

bool MRpt(Bint n){
    if(n <= 1) return 0;
    if(n == 2) return 1;
    if(n%2 == 0) return 0;
    Bint s = 0;
    Bint d = n-1;
    while(d%2 == 0){
        d /= 2;
        s++;
    }
    //cout << n-1 << "= 2^" << s << "*" << d << endl;

    int k = 100;
    rep(looop,k){
        Bint a = rand()%(n-2)+1;
        Bint powmod_a_d_n = powermod(a,d,n);
        if(powmod_a_d_n == 1){
            //cout << n << "," << a << endl;
            continue;
        }
        bool bk = false;
        rep(i,s){
            if(powmod_a_d_n == n-1){
                //cout << n << "," << a << "," << i << endl;
                bk = true;
                break;
            }
            powmod_a_d_n = powmod_a_d_n*powmod_a_d_n%n;
        }
        if(bk) continue;
        return 0;
    }
    return 1;
}

bool even_odd(char c){
    if(c == '1' || c == '3' || c == '7' || c == '9' || c == 'J' || c == 'K') return 1;
    else return 0;
}

int64_t red_odd(vector<char> hand){
    int n = hand.size();
    int minodd_i = 99;
    for(char c : hand){
        if(even_odd(c)){
            int i = char_int(c);
            if(i < 10) i *= 10;
            if(i < minodd_i) minodd_i = i;
        }
    }
    char minodd_c;
    if(minodd_i%10 == 0) minodd_i /= 10;
    minodd_c = int_char(minodd_i);
}

int main(){
    vector<char> Card = {'9','8','7','6','5','4','3','2','1'};
    
}
