#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

//nの偶奇
bool parity(int64_t n){
  if(n%10 == 1 || n%10 == 3 || n%10 == 7 || n%10 == 9)
    return 1;
  else
    return 0;
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

//nの最上位桁
int64_t msd(int64_t n){
    string s = to_string(n);
    char c = s[0];
    int64_t i = c-'0';
    return i;
}

//数からカードの並びに変換
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

int64_t card_comb_str(string p){
    int64_t cmb = 0;
    while(p.size() > 0){
        char p0 = p[p.size()-1];
        if(p0 == 'K') cmb += 216;
        else if(p0 == 'Q') cmb += 36;
        else if(p0 == 'J') cmb += 6;
        else if(p0 == 'T') cmb += 1;
        else {
            int64_t q;
            q = p0-'0';
            cmb += q*1296;
        p.pop_back();
        }
    }
    return cmb;
}

//素因数分解
string p_fact_(int64_t n, vector<int64_t> &prime){
    string s;
    for(int64_t p : prime){
        while(n%p == 0){
            string q = int_str(p);
            s = s + "*" + q;
            n /= p;
        }
        if(p*p > n){
            if(n != 1){
                string q = int_str(n);
                s = s + "*" + q;
            }
            break;
        }
    }

    return s;
}

string p_fact(int64_t n, vector<int64_t> &prime){
    string s;
    for(int64_t p : prime){
        int a = 0;
        while(n%p == 0){
            n /= p;
            a++;
        }
        string q = int_str(p);
        if(a == 1) s = s + "*" + q;
        else if(a > 1){
            string b = int_str(a);
            s = s + "*" + q + "^" + b;
        }

        if(n == 1) break;
        if(n < p*p){
            string q = int_str(n);
            s = s + "*" + q;
            break;
        }
    }
    s = s.substr(1);
    return s;
}

int main(){
    int64_t maxn = 11000000;
    vector<int64_t> ntrl(maxn);
    for(int64_t i = 0; i < maxn; i++){
        if(i <= 1) ntrl.at(i) = -1;
        else ntrl.at(i) = i;
    }
    vector<int64_t> prime = {2ll,3ll};
    int64_t maxi = sqrt(maxn);
    for(int64_t i = 0; i < maxi; i++){
        int64_t p = prime.at(i);
        int64_t q = prime.at(i+1);
        for(int64_t j = p*p; j < maxn; j += p) ntrl.at(j) = -1;
        for(int64_t k = p*p+1; k < q*q && k < maxn; k++) if(ntrl.at(k) > 0) prime.push_back(k);
    }
    int64_t pmax = prime.at(prime.size()-1);

    vector<int>prm = {2,3,5,7,11,13/*,17,19,23,29,31,37,41,43,47,53*/};
    int cnt = 0;
    for(int64_t n = 2; n < 10101010101010; n++) {
        int m = n;
        for(int &p : prm){
            while(m%p == 0){
                m /= p;
            }
        }
        if(m == 1){
            cout << n << " = " << p_fact(n,prime) << endl;
            cnt++;
        }
        //if(cnt >= 1024) break;
    }
}