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

// a + b = c
void addition_vec(vector<int64_t> a,vector<int64_t> b, vector<int64_t> &c){
    int g = 1000000000;
    for(int i = 9; i >= 0; i--){
        c[i] += a[i];
        c[i] += b[i];
        if(c[i] >= g){
            c[i] -= g;
            c[i-1]++;
        }
    }
}
// a - b = c
void subtraction_vec(vector<int64_t> a,vector<int64_t> b, vector<int64_t> &c){
    int g = 1000000000;
    for(int i = 9; i >= 0; i--){
        c[i] += a[i];
        c[i] -= b[i];
        if(c[i] < 0){
            c[i] += g;
            a[i-1]--;
        }
    }
}
// a * b = c
void multiplication_vec(vector<int64_t> a,vector<int64_t> b, vector<int64_t> &c){
    int g = 1000000000;
    rep(i,10){
        rep(j,10){
            if(9-(i+j) < 0) continue;
            int64_t aibj = a[9-i]*b[9-j];
            c[9-(i+j)] += aibj%g;
            if(9-(i+j+1) >= 0) c[9-(i+j+1)] += aibj/g;
            if(c[9-(i+j)] >= g){
                c[9-(i+j)] -= g;
                if(9-(i+j+1) >= 0) c[9-(i+j+1)]++;
            }
            if(c[9-(i+j+1)] >= g){
                if(9-(i+j+1) >= 0) c[9-(i+j+1)] -= g;
                if(9-(i+j+2) >= 0) c[9-(i+j+2)]++;
            }
        }
    }
}

string vec_str(vector<int64_t> a){
    int64_t g = 1000000000;
    string s;
    rep(i,10){
        string isai = int_str(a[i]);
        string ai = to_string(a[i]);
        if(i != 0 && ai.size() < 9){
            if(a[i-1] != 0){
                rep(j,9-ai.size()){
                    s += "0";
                }
            }
            
        }
        s += isai;
        if(i < 9 && s[s.size()-1] == '1'){
            s.pop_back();
            a[i+1] += g;
        }
    }
    return s;
}

int main(){
    vector<char> cd = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K','t','j','q','k'};
    vector<int64_t> a = {0,0,0,0,0,0,0,0,0,1};
    vector<int64_t> b(10);
    b[9] = 2;
    vector<int64_t> t(10);
    t[9] = 3;
    vector<int64_t> ansvec(10,0);
    int ansk;
    int ansi;
    rep(k,192){
        int imax = 0;
        string smax;
        a = {0,0,0,0,0,0,0,0,0,1};
        rep(l,k){
            vector<int64_t> d(10);
            multiplication_vec(a,t,d);
            a = d;
            d = {0,0,0,0,0,0,0,0,0,0};
        }
        //cout << vec_str(a) << endl;
        for(int i = 0; i < 256; i++){
            double dgt = 0.3011*i+0.4772*k;
            if(dgt >= 72) break;
            vector<int64_t> c(10);
            if(i != 0){
                multiplication_vec(a,b,c);
                a = c;
                c = {0,0,0,0,0,0,0,0,0,0};
            }
            string s = vec_str(a);
            if(i > 1) s += int_str(i);
            if(i > 0) s += "2";
            if(k > 1) s += int_str(k);
            if(k > 0) s += "3";
            map<char,int> scomb;
            int jk = 0;
            for(char c : cd){
                scomb[c] = 0;
            }
            rep(j,s.size()){
                char c = s[j];
                scomb[c]++;
                if(c == '0' && j > 0){
                    if(s[j-1] == 'J'){
                        scomb['J']--;
                        scomb['0']--;
                        scomb['1']++;
                        scomb['T']++;
                    }
                }
                if(c == 'J' && j < s.size()-1){
                    char d = s[j+1];
                    if(d == '2'){
                        scomb['q']++;
                    }
                    if(d == 3){
                        scomb['k']++;
                    }
                }

            }
            for(char c : cd){
                if(c == '0') jk += scomb[c];
                else if(scomb[c] > 4) jk += scomb[c]-4;
                if(c == 't' || c == 'j' || c == 'q' || c == 'k'){
                    if(scomb[c] > 0) jk--;
                }
            }
            if(jk > 2) continue;
            if(i > imax){
                imax = i;
                smax = vec_str(a);
                if(a > ansvec){
                    ansvec = a;
                    ansi = i;
                    ansk = k;
                }
            }
        }
        cout << "2^" << imax << "*" << "3^" << k << "=" << smax << endl;
    }
    cout << "2^" << ansi << "*" << "3^" << ansk << "=" << vec_str(ansvec) << endl;
}