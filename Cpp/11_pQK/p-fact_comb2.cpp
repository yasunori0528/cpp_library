#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

bool parity(int64_t n){
    n %= 10;
    if(n*n*n*n%10 == 1)
        return 1;
    else
        return 0;
}
bool parity(string s){
    int n = s.size();
    char c = s[n-1];
    if(c == '0' || c == '2' || c == '4' || c == '5'
        || c == '6' || c == '8' || c == 'T' || c == 'Q')
            return 0;
    else return 1;
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
//xのn^y位の数
int64_t digit(int64_t x, int64_t y, int64_t n){
  return x%power(n,y+1)/power(n,y);
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
int64_t pt(int64_t n, vector<int64_t> &prime){
    for(int64_t p : prime){
        if(n == 2) return 1;
        else if(n%p == 0)    return 0;
        else if(p*p > n) return 1;
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

int main(){
    maxn = 32000000;
    prime_calculate();
    vector<char> cd = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K'};
    map<char,int> card_condition;
    for(char c : cd){
        if(c == '0') card_condition[c] = 0;
        else card_condition[c] = 1;
    }
    map<char,int> card_condition2 = card_condition;
    card_condition2['Q']++;
    card_condition2['1']--;
    card_condition2['2']--;
    map<char,int> card_condition3 = card_condition;
    card_condition3['K']++;
    card_condition3['1']--;
    card_condition3['3']--;
    /*vector<int64_t> pwpw = {8,16,32,9,25,36,49};
    vector<int64_t> pwpw3 = {16,32,9,25,36,49};
    vector<int64_t> pwpw5 = {8,16,9,36,49};
    vector<int64_t> pwpw7 = {8,16,32,9,25,36};
    map<string,string> bpp2;
    bpp2["8"] = "23";
    bpp2["16"] = "24";
    bpp2["32"] = "25";
    bpp2["9"] = "32";
    bpp2["25"] = "52";
    bpp2["36"] = "62";
    bpp2["49"] = "72";*/
    for(int i = 9; i < 12; i++){
        cout << "i : " << i << endl;
        int jmin = power(13,3);
        int jmax = power(13,4);
        for(int j = jmin; j < jmax; j++){
            map<char,int> ncomb;
            for(char c : cd){
                ncomb[c] = 0;
            }
            string s;
            bool b1 = false;
            rep(k,13-j){
                char c = cd[digit(j,k,13)+1];
                if(ncomb[c] > 0){
                    b1 = true;
                    break;
                }
                s += c;
                ncomb[c]++;
            }
            if(b1) continue;
            int pw3 = power(3,13-j-1);
            if(i == 9) pw3--;
            rep(op,pw3){
                string t = s;
                rep(l,13-j-1){
                    int opl = digit(op,l,3);
                    if(opl == 2){
                        t = t.substr(0,13-j-1-l)+"^"+t.substr(13-j-1-l);
                    }
                    else if(opl == 1){
                        t = t.substr(0,13-j-1-l)+"*"+t.substr(13-j-1-l);
                    }
                }
                int64_t n = 0;
                rep(k,t.size()){
                    //ここで合成数場の計算をする
                }
                
            }
        }
    }
}