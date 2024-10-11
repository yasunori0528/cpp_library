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
string to_string_Bint(Bint n){
    if(n == 0) return "0";

    string rtn;
    while(n > 0){
        Bint k = n%10;
        rtn = (char)('0'+(int)k) + rtn;
        n /= 10;
    }
    return rtn;
}
Bint str_int_Bint(string s){
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

//combination(n,k)
int64_t com(int64_t n, int64_t k){
    if(n < k) return 0;
    if(n < 0 || k < 0) return 0;
    return com(n-1,k-1)+com(n-1,k);
}
//1,3,7,9:true; 2,4,5,6,8:false;
bool parity(int64_t n){
    if(n*n*n*n%10 == 1) return 1;
    else return 0;
}

//x^y,10^d未満, 0 <= x, 0 <= y, 大きすぎるものは-1を返す
Bint power(Bint x, Bint y, int d){
    if(y < 0 || x < 0) return -1;
    if(x == 0) return 0;
    if(x == 1 || y == 0) return 1;
    Bint rtn = 1;
    rep(i,y){
        rtn *= x;
        if(to_string_Bint(rtn).size() > d){
            rtn = -1;
            break;
        }
    }
    return rtn;
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
//nの最上位桁
int64_t msd(int64_t n){
    string s = to_string(n);
    char c = s[0];
    int64_t i = c-'0';
    return i;
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
//nの枚数
Bint card(Bint n){
    Bint cnt = 0;
    while(n > 0){
        Bint n0 = n%10;
        n /= 10;
        cnt++;
        if(n0 <= 3 && n%10 == 1){
            n /= 10;
        }
    }
    return cnt;
}
//素数計算
vector<int64_t> ntrl;
vector<int64_t> prime;
int64_t maxn;
void prime_calculate(){
    rep(i,maxn){
        if(i <= 1) ntrl.push_back(-1);
        else ntrl.push_back(i);
    }
    prime = {2,3};
    int64_t maxi = sqrt(maxn);
    rep(i,maxi){
        int64_t p = prime[i];
        int64_t q = prime[i+1];
        for(int64_t j = p*p; j < maxn; j += p) ntrl[j] = -1;
        for(int64_t k = p*p+1; k < q*q && k < maxn; k++){
            if(ntrl[k] > 0) prime.push_back(k);
        }
    }
    cout << "prime calculated" << endl;
}
bool pt(int64_t n,vector<int64_t>vec){
    if(n <= 1) return false;
    int64_t s = vec.size();
    for(int64_t i = 0; i < s; i++){
        if(vec[i]*vec[i] > n) return true;
        else if(n%vec[i] == 0) return false;    
    }
    return false;
    cout << "Insuficuent_Prime_List" << endl;
}

string card_id(int64_t n){
    string s;
    while(n > 0){
        char c;
        int64_t r = n%14;
        if(r < 10) c = '0'+r;
        else if(r == 10) c = 'T';
        else if(r == 11) c = 'J';
        else if(r == 12) c = 'Q';
        else c = 'K';
        s = c+s;
        n /= 14;
    }
    return s;
}
int64_t inv_card_id(string s){
    int64_t n = 0;
    for(char c : s){
        if('0' <= c && c <= '9') n = 14*n+(c-'0');
        else if(c == 'T') n = 14*n+10;
        else if(c == 'J') n = 14*n+11;
        else if(c == 'Q') n = 14*n+12;
        else n = 14*n+13;
    }
    return n;
}
string sort_card_91KT(string s){
    vector<int> v;
    for(char c : s){
        if('0' <= c && c <= '9') v.push_back((c-'0')+100);
        else if(c == 'T') v.push_back(10);
        else if(c == 'J') v.push_back(11);
        else if(c == 'Q') v.push_back(12);
        else v.push_back(13);
    }

    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());

    string t;
    for(int i : v){
        int j = i;
        if(j >= 100) j -= 100;

        if(j < 10) t.push_back('0'+j);
        else if(j == 10) t.push_back('T');
        else if(j == 11) t.push_back('J');
        else if(j == 12) t.push_back('Q');
        else t.push_back('K');
    }

    return t;
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
    cout << n-1 << "= 2^" << s << "*" << d << endl;

    int k = 10;
    rep(looop,k){
        Bint a = rand()+1;
        if(a >= n){
            a = a%(n-2)+1;
        }
        cout << a << endl;
        Bint powmod_a_d_n = powermod(a,d,n);
        cout << powmod_a_d_n << endl;
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
    srand(time(NULL));
    maxn = pow(10,5);
    prime_calculate();
    for(int64_t p : prime){
        Bint n = pow((Bint)2,p)-1;
        cout << p << "," << n << endl;
        if (MRpt(n)) cout << n << endl;
        else cout << n << endl;
    }
}