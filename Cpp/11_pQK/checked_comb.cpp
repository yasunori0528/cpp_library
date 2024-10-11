#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;

int64_t power(int64_t x, int64_t y){
  if(y < 0) return 0;
  else{
    int64_t n = 1ll;
    for(int64_t i = 0; i < y; i++) n *= x;
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

int main(){
    int d; cin >> d;

    int t0 = time(NULL);
    int t1 = time(NULL);

    vector<char> Card = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K'};

    map<map<char,int>,bool> primable_addX;
    int64_t maxcomb_id = power(14,d);
    for(int i = maxcomb_id/14; i < maxcomb_id; i++){
        string s = card_id(i);
        map<char,int> comb_s;
        for(char c : Card) comb_s[c];
        for(char c : s) comb_s[c]++;
        primable_addX[comb_s] = false;
    }

    int T = time(NULL);
    cout << T-t0 << "[s]" << endl;

    int64_t maxid = power(14,d+1);
    {
        maxn = sqrt(str_int(card_id(maxid-1)))+1;
        prime_calculate();
    }
    for(int i = maxid/14; i < maxid; i++){
        string s = card_id(i);
        int64_t n = str_int(s);

        {
            T = time(NULL);
            if(T - t1 >= 60){
                t1 = T;
                cout << "///" << T-t0 << "[s] : " << s << endl;
            }
        }

        int64_t pp = 2ll*3*5*7*11*13*17*19*23*29*31*37*41*43*47;
        int64_t gcd_n_pp = __gcd(n,pp);
        if(gcd_n_pp != 1) continue;

        map<char,int> comb_s;
        for(char c : Card) comb_s[c];
        for(char c : s) comb_s[c]++;

        
        bool b = true;
        for(char c : Card){
            if(comb_s[c] > 0){
                map<char,int> comb_s_c = comb_s;
                comb_s_c[c]--;
                if(!primable_addX[comb_s_c]){
                    b = false;
                    break;
                }
            }
        }
        if(b) continue;

        if(!pt(n,prime)) continue;
        for(char c : Card){
            if(comb_s[c] > 0){
                map<char,int> comb_s_c = comb_s;
                comb_s_c[c]--;
                primable_addX[comb_s_c] = true;
            }
        }        
    }

    for(pair<map<char,int>,bool> pr : primable_addX){
        if(!pr.second){
            map<char,int> mp = pr.first;
            if(mp['0'] > 0) continue;
            bool b = false;
            for(char c : Card){
                if(mp[c] > 4){
                    b = true;
                    break;
                }
            }
            if(b) continue;
            for(char c : Card){
                int m = mp[c];
                rep(i,m) cout << c;
            }
            cout << endl;
        }
    }

    T = time(NULL);
    cout << "///" << T-t0 << "[s]" << endl;
}