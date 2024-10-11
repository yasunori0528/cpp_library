#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;

//x^y
int64_t power(int64_t x, int64_t y){
    if(y < 0) return 0;
    else{
        int64_t n = 1ll;
        for(int64_t i = 0; i < y; i++) n *= x;
        return n;
    }
}
//x^y%p
Bint powermod(Bint x, Bint y, Bint p){
    if(y < 0) return 0;
    else{
        Bint n = 1;
        x %= p;
        for(int64_t i = 0; i < y; i++){
        n = n*x%p;
        }
        return n;
    }
}
//nの絵札枚数
int64_t CARD(int64_t n){
    int64_t cnt = 0;
    while(n > 0){
        int64_t n0 = n%10;
        n /= 10;
        if(n0 <= 3 && n%10 == 1){
            cnt++;
            n /= 10;
        }
    }
    return cnt;
}
string int_str(int64_t n){
    int64_t d = 0;
    int64_t m = n;
    string s;
    while(m > 0){
        m /= 10;
        d++;
    }
    int64_t i = d-1;
    while(i >= 0){
        int64_t k_i0 = n%power(10,i+1)/power(10,i);
        int64_t k_i1;
        if(i > 0) k_i1 = n%power(10,i)/power(10,i-1);
        if(k_i0 == 1 && k_i1 < 4 && i > 0){
            if(k_i1 == 0) s.push_back('T');
            else if(k_i1 == 1) s.push_back('J');
            else if(k_i1 == 2) s.push_back('Q');
            else if(k_i1 == 3) s.push_back('K');
            i -= 2;
        }
        else{
            char c = '0'+k_i0;
            s.push_back(c);
            i--;
        }
    }
    return s;
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

    int k = 10;
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

int main() {
    int64_t amax = 131313;
    int64_t amin = 101010;
    cout << amax << endl;
    cout << amin << endl;
    for(int64_t n = amax; n >= amin; n -= 2){
        if(CARD(n) == 3) cout << int_str(n) << endl;
    }
}