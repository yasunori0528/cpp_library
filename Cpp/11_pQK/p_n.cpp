#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

//偶奇
bool parity(int64_t n){
    n %= 10;
    if(n*n*n*n%10 == 1) return 1;
    else return 0;
}
//x^y
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
//xのn^d位
int64_t digit(int64_t x, int64_t d, int64_t n){
  return x%power(n,d+1)/power(n,d);
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
        int64_t &p = prime[i];
        int64_t &q = prime[i+1];
        for(int64_t j = p*p; j < maxn; j += p) ntrl[j] = -1;
        for(int64_t k = p*p+1; k < q*q && k < maxn; k++){
            if(ntrl.at(k) > 0) prime.push_back(k);
        }
    }
    cout << "prime calculated" << endl;
}
//素数判定
int64_t pt(int64_t n, vector<int64_t> &prime){
    for(int64_t p : prime){
        if(n == 2) return 1;
        else if(n%p == 0)    return 0;
        else if(p*p > n) return 1;
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
//nの枚数
int64_t card(int64_t n){
  int64_t cnt = 0;
  while(n > 0){
    int64_t n0 = n%10;
    n /= 10;
    cnt++;
    if(n0 <= 3 && n%10 == 1){
      n /= 10;
    }
  }
  return cnt;
}
//nのa進法における下d桁
int64_t bnps(int64_t n, int64_t a, int64_t d){
  int64_t an = 0;
  for(int64_t i = 0; i < d; i++){
    an += a%power(n,i+1)/power(n,i)*power(10,i);
  }
  return an;
}
//nの上k桁
int64_t msd(int64_t n, int64_t k){
    string s = to_string(n);
    s = s.substr(0,k);
    int i = stoi(s);
    return i;
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
int64_t card_comb_str(string p){
    int64_t cmb = 0;
    while(p.size() > 0){
        int64_t q;
        char p0 = p[p.size()-1];
        if(p0 == 'K') q = 13;
        else if(p0 == 'Q') q = 12;
        else if(p0 == 'J') q = 11;
        else if(p0 == 'T') q = 10;
        else q = p0-'0';
        cmb += power(8,q);
        if(digit(cmb,q,8) == 7){
            p = "";
            cmb = -1;
        }
        else p.pop_back();
    }
    return cmb;
}
int64_t card_comb_int(int64_t q){
    string p = to_string(q);
    int64_t cmb = 0;
    while(p.size() > 0){
        int64_t q;
        char p0 = p[p.size()-1];
        if(p0 == 'K') q = 13;
        else if(p0 == 'Q') q = 12;
        else if(p0 == 'J') q = 11;
        else if(p0 == 'T') q = 10;
        else q = p0-'0';
        cmb += power(8,q);
        if(digit(cmb,q,8) == 7){
            p = "";
            cmb = -1;
        }
        else p.pop_back();
    }
    return cmb;
}
int main(){
    maxn = 10000;
    prime_calculate();
    vector<char> cd = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K'};
    int64_t amin = 1;
    int64_t amax = 9999;
    //int64_t range = amax-amin;
    //int64_t cntf = range/1024;
    map<map<char,int>,int64_t> card_comb;
    //int cnt = 0;
    //int cnt_ = 0;
    for(int64_t a = amax; a >= amin; a -= 2){
        int64_t m = 9530000+a;
        map<char,int> comba;
        string s = to_string(m);
        for(char c : s) comba[c] ++;
        if(comba['0'] > 0) continue;
        bool cont = false;
        for(char c : cd) if(comba[c] > 1) cont = true;
        if(cont) continue;
        if(pt(m,prime) && pt(a,prime)) cout << a << endl;
    }

    /*for(pair<map<char,int>,int64_t> cb : card_comb){
        cout << (cb.second) << endl;
    }*/
}