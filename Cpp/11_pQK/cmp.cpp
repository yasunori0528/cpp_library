#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;
// 仮数部が1024ビットの浮動小数点数型(TLEしたら小さくする)
using Real = mp::number<mp::cpp_dec_float<1024>>;

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

Bint stoi_Bint(string s){
    Bint rtn = 0;
    for(char c : s){
        rtn = 10*rtn+(c-'0');
    }
    return rtn;
}

Bint power(Bint x, Bint y){
    if(y == -1) return 0;
    if(y > 255) return 0;
    Bint rtn = 1;
    rep(i,y){
        rtn *= x;
    }
    return rtn;
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
    return 0;
    cout << "Insufficient_list" << endl;
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

//出せるかどうか
int pqkable(Bint n){
    if(n < 1) return 2;

    map<int,int> comb_i;
    string s = to_string_Bint(n);
    int k = s.size();
    if(k > 72) return 2;

    int cntX = 0;

    for(char c : s){
        comb_i[c-'0']++;
    }

    for(int c = 4; c <= 9; c++){
        int cmb_i_c = comb_i[c];
        if(cmb_i_c > 6){
            return 0;
        }
        else if(cmb_i_c > 4){
            cntX += cmb_i_c-4;
        }
    }
    if(cntX > 2) return 0;

    map<int,int> comb_N;
    rep(i,k-1){
        if(s[i] == '1' && s[i+1] < '4'){
            int j = 10+(s[i+1]-'0');
            comb_N[j]++;
        }
    }
    /*map<int,int> comb_AN;
    rep(i,k-2){
        if(s[i] == '1' && s[i+1] == '1' && s[i+2] < '4'){
            int j = 110+(s[i+2]-'0');
            comb_N[j]++;
        }
    }*/

    int cnt0 = comb_i[0];
    int cnt1 = comb_i[1];
    int cnt2 = comb_i[2];
    int cnt3 = comb_i[3];

    int cntT = comb_N[10];
    int cntJ = comb_N[11];
    int cntQ = comb_N[12];
    int cntK = comb_N[13];

    /*int cntAT = comb_AN[110];
    int cntAQ = comb_AN[112];
    int cntAk = comb_AN[113];*/

    cntX += max(0,cnt0-cntT);
    cntX += max(0,cnt2-cntQ-4);
    cntX += max(0,cnt3-cntK-4);
    cntX += max(0,cnt1-(cntT+2*cntJ+cntQ+cntK)-4);
    if(cntX > 2) return 0;
    return 1;
}

int main(){
    maxn = 100000;
    prime_calculate();

    vector<int64_t> pr1;
    vector<int64_t> pr2;
    vector<int64_t> pr3;
    vector<int64_t> pr4;
    vector<int64_t> pr5;
    //vector<int64_t> pr6;
    for(int i = 2; i <= 1313; i++){
        int cmin = card(i);
        int cmax = cmin+CARD(i);
        if(cmin > 4) continue;
        if(pt(i,prime)){
            if(cmin <= 1 && 1 <= cmax) pr1.push_back(i);
            if(cmin <= 2 && 1 <= cmax) pr2.push_back(i);
            if(cmin <= 3 && 1 <= cmax) pr3.push_back(i);
            if(cmin <= 4 && 1 <= cmax) pr4.push_back(i);
            //if(cmin <= 5 && 1 <= cmax) pr5.push_back(i);
            //if(i <= power(13,6)) pr6.push_back(n);
        }
    }

    vector<int64_t> nt1;
    vector<int64_t> nt2;
    vector<int64_t> nt3;
    //vector<int64_t> nt4;
    //vector<int64_t> nt5;
    for(int i = 2; i <= 131313; i++){
        int cmin = card(i);
        int cmax = cmin + CARD(i);
        if(cmin <= 1 && 1 <= cmax) nt1.push_back(i);
        if(cmin <= 2 && 1 <= cmax) nt2.push_back(i);
        if(cmin <= 3 && 1 <= cmax) nt3.push_back(i);
        //if(i <= power(13,4)) nt4.push_back(n);
        //if(i <= power(13,4)) nt5.push_back(n);
    }

    cout << "aaa" << endl;
    Bint maxcmp = 0;
    for(int64_t a : pr1){
        for(int64_t b : nt1){
            for(int64_t c : nt1){
                //for(int64_t d : pr4){
                    //for(int64_t e : pr3){
                        Bint n = power(a,power(b,(Bint)c));
                        string s = to_string_Bint(n);
                        string abcdef = (to_string(a)+to_string(b)+to_string(c)/*+to_string(d)+to_string(e)+to_string(f)*/);
                        s += abcdef;
                        Bint m = stoi_Bint(s);
                        int boool = pqkable(m);
                        if(boool == 2) break;
                        if(boool && n > power((Bint)10,1)){
                            cout << a << "^" << b << "^" << c << "=\n" << n << endl;
                            maxcmp = max(n,maxcmp);
                        }
                    //}
                //}
            }
        }
    }
    cout << maxcmp << endl;
}