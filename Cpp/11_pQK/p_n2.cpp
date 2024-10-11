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
//sの絵札枚数
int64_t CARD(string s){
    int64_t cnt = 0;
    for(char c : s){
        if(c < '0' || '9' < c) cnt++;
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
int main(){
    maxn = power(2,20);
    prime_calculate();
    vector<char> cd = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K'};
    int64_t amin = inv_card_id("111T");
    int64_t amax = inv_card_id("K999");
    map<map<char,int>,string> card_comb;
    for(int64_t a = amax; a >= amin; a -=1){
        string s = card_id(a);
        int64_t n = str_int(s);
        if(CARD(s) != 1) continue;
        map<char,int> ncomb;
        int cnt2 = 0;
        bool bl0 = false;
        for(char c : cd) ncomb[c] = 0;
        for(char c : s){
            if(c == '0'){
                bl0 = true;
                break;
            }
            int &ncc = ncomb[c];
            ncc++;
            /*if(ncc > 1){
                bl0 = true;
                break;
            }
            if(ncc > 2){
                bl0 = true;
                break;
            }*/
        }
        if(bl0) continue;
        if(!pt(n,prime)) continue;

        if(card_comb.count(ncomb)) {
            string t = card_comb[ncomb];
            int64_t m = str_int(t);
            if(m < n) card_comb[ncomb] = s;
        }
        else card_comb[ncomb] = s;
    }


    vector<vector<string>> table(1000,vector<string>(4,"N/A"));
    for(pair<map<char,int>,string> cb : card_comb){
        string s = cb.second;
        string t = sort_card_91KT(s);
        int64_t n = stoi(t.substr(0,3));
        char m = t[3];
        if(m == 'T') table[n][0] = s;
        else if(m == 'J') table[n][1] = s;
        else if(m == 'Q') table[n][2] = s;
        else table[n][3] = s;
    }
    for(int i = 999; i >= 0; i--){
        string rtn;
        rep(j,4){
            string s = table[i][j];
            if(s != "N/A") rtn += s;
            rtn += ",";
        }
        if(rtn != ",,,,") cout << rtn << endl;
    }
}