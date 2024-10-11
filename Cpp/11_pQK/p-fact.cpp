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
  int64_t s = vec.size();
  for(int64_t i = 0; i < s; i++){
    if(n%vec[i] == 0) return false;
    else if(vec[i]*vec[i] > n) return true;
  }
  return false;
  cout << "Insuficuent_Prime_List" << endl;
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
string p_fact_int(int64_t n, vector<int64_t> &prime){
    string s;
    for(int64_t p : prime){
        int a = 0;
        while(n%p == 0){
            n /= p;
            a++;
        }
        string q = to_string(p);
        if(a == 1) s = s + "*" + q;
        else if(a > 1){
            string b = to_string(a);
            s = s + "*" + q + "^" + b;
        }

        if(n == 1) break;
        if(n < p*p){
            string q = to_string(n);
            s = s + "*" + q;
            break;
        }
    }
    s = s.substr(1);
    return s;
}
string p_fact_(int64_t n, vector<int64_t> &prime){
    string s;
    for(int64_t p : prime){
        int a = 0;
        while(n%p == 0){
            n /= p;
            a++;
        }
        string q = int_str(p);
        if(a == 1) s = s + q;
        else if(a > 1){
            string b = int_str(a);
            s = s + q + b;
        }

        if(n == 1) break;
        if(n < p*p){
            string q = int_str(n);
            s = s + q;
            break;
        }
    }
    return s;
}
string p_fact_int_(int64_t n, vector<int64_t> &prime){
    string s;
    for(int64_t p : prime){
        int a = 0;
        while(n%p == 0){
            n /= p;
            a++;
        }
        string q = to_string(p);
        if(a == 1) s = s + q;
        else if(a > 1){
            string b = to_string(a);
            s = s + q + b;
        }

        if(n == 1) break;
        if(n < p*p){
            string q = to_string(n);
            s = s + q;
            break;
        }
    }
    return s;
}

//合成数出し最小消費枚数
int p_fact_comb(int64_t n, vector<int64_t> &prime){
    if(pt(n,prime)) return int_str(n).size();
    string s;
    int64_t m = n;
    for(int64_t p : prime){
        int a = 0;
        while(m%p == 0){
            m /= p;
            a++;
        }
        string q = int_str(p);
        if(a == 1) s = s + q;
        else if(a > 1){
            string b = int_str(a);
            s = s + q + b;
        }

        if(m == 1) break;
        if(m < p*p){
            string q = int_str(m);
            s = s + q;
            break;
        }
    }
    int c = s.size()+int_str(n).size();
    return c;
}
int p_fact_comb_int(int64_t n, vector<int64_t> &prime){
    if(pt(n,prime)) return to_string(n).size();
    string s;
    int64_t m = n;
    for(int64_t p : prime){
        int a = 0;
        while(m%p == 0){
            m /= p;
            a++;
        }
        string q = to_string(p);
        if(a == 1) s = s + q;
        else if(a > 1){
            string b = to_string(a);
            s = s + q + b;
        }

        if(m == 1) break;
        if(m < p*p){
            string q = to_string(m);
            s = s + q;
            break;
        }
    }
    int c = s.size()+to_string(n).size();
    return c;
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
    maxn = 10000;
    prime_calculate();
    vector<char> card_c = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K'};
    map<map<char,int>,string> comb;
    string pmin_s = "KJQJ";
    string pmax_s = "KKKK";
    int64_t pmin_i = str_int(pmin_s);
    int64_t pmax_i = str_int(pmax_s);
    for(int64_t i = pmax_i; i >= pmin_i; i -= 1){
        if(card(i) > 4) continue;
        string s = int_str(i);
        int64_t n = i;
        cout << s << "," << p_fact(n,prime) << endl;
    }
}