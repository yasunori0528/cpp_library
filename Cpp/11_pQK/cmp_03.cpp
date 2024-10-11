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
    if(n < 2) return 0;
    if(n == 2) return 1;
    for(int64_t p : prime){
        if(n%p == 0)    return 0;
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
int pqkable(string s){
    map<int,int> comb_i;
    int k = s.size();
    if(k > 72) return 0;

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

// 素因数場の整合性
bool pt_p(string s){
    int n = s.size();
    int64_t m = 0;
    int b = 0;
    rep(i,n){
        char c = s[i];
        bool bol = false;
        if(c == '*'){
            m = 0;
            b = 0;
        }
        else if(c == '^'){
            m = 0;
            b = 1;
        }
        else{
            m = 10*m + (c - '0');
            bol = true;
        }
        
        char d;
        if(i != n-1) d = s[i+1];
        if(bol && b == 1 && (i == n-1 || d == '*' || d == '^')){
            if(m < 2) return false;
        }
        if(bol && b == 0 && (i == n-1 || d == '*' || d == '^')){
            if(!pt(m,prime)) {
                return false;
            }
        }
    }
    rep(i,n){
        char c = s[i];
        if(c == '0' && (i == 0 || s[i-1] == '*' || s[i-1] == '^')) return false;
    }
    return true;
}

//'0'~'9', '^', '*', で構成された文字列を計算
Bint calc(string s, int d){
    int n = s.size();
    Bint rtn;
    
    rep(i,n){
        if(s[i] == '*'){
            Bint x = calc(s.substr(0,i),d);
            Bint y = calc(s.substr(i+1),d);
            if(x < 0 || y < 0) return -1;
            rtn = x*y;
            return rtn;
        }
    }
    rep(i,n){
        if(s[i] == '^'){
            Bint x = calc(s.substr(0,i),d);
            Bint y = calc(s.substr(i+1),d);
            rtn = power(x,y,d);
            return rtn;
        }
    }
    rtn = stoi_Bint(s);
    return rtn;
}

//前の計算結果から明らかに大きいものを弾く
bool calc_too_big(string j, unordered_set<string> us){
    int n = j.size();
    for(string s : us){
        bool b = true;
        bool b2 = true;
        rep(i,n){
            char ji = j[i];
            char si = s[i];
            if(ji == '*' || ji == '^') b2 = true;
            else if(b2) {
                if(ji > si) b2 = false;
                else if(ji == si);
                else {
                    b = false;
                    break;
                }
            }
        }
        if(b) return true;
    }
    return false;
}

int main (){
    maxn = 10000;//10^((d-1)/2)
    prime_calculate();
    vector<string> vc = {"","*","^"};//演算子
    Bint maxcmp_ = 
    //power(5,43,72);
    power((Bint)2,122,72);
    //power(7,41,72)*953;
    //power((Bint)11,37,72)*541;
    //power(11,37,72)*power(2,9,72)*power(3,4,72);
    //power((Bint)13,11)*1013*power((Bint)1283,9);


    int TIME = time(NULL);//開始時刻
    int time_count = 0;
    //for(int d = 4; d <= 4; d++){
        int d = 6;
        int d_ub = 72-d;//合成数の桁数上限
        Bint power_10_d_bu = power(10,d_ub,100);
        int64_t N = power(3,d-1);//演算子の並びの個数
        int out_put_count = 0;
        //bool start_b1 = true;

        rep(i,N){
            /*if(start_b1) {
                i = 558;
                start_b1 = false;
            }*/
            string s = "x";
            int64_t M = i;
            rep(j,d-1){
                s = "x" + vc[M%3] + s;
                M /= 3;
            }

            int n = s.size();
            bool boool = false;
            /*int cnt = 0;
            for(char c : s){
                if(c == '*') cnt = 0;
                else if(c == '^') cnt++;
                if(cnt >= 2) boool = true;
            }
            if(boool) continue;*/

            /*int d0 = 0;
            int dmax = 0;
            for(char c : s){
                if(c == 'x') d0++;
                else {
                    dmax = max(dmax,d0);
                    if(c == '*') d0 = 0;
                    else d0 = -100;
                }
            }
            dmax = max(dmax,d0);
            if(dmax < 5) continue;*/

            int d1 = 0;
            int d2 = 0;
            rep(j,n){
                char c = s[j];
                if(c != '*') d2++;
                else {
                    if(d1 != 0 && d1 < d2){
                        boool = true;
                        break;
                    }
                    else if(d1 == d2){
                        string s_sub1 = s.substr(j-d1,d1);
                        string s_sub2 = s.substr(j-2*d1-1,d1);
                        if(s_sub1 < s_sub2){
                            boool = true;
                            break;
                        }
                        else {
                            d1 = d2;
                            d2 = 0;
                        }
                    }
                    else {
                        d1 = d2;
                        d2 = 0;
                    }
                }
            }
            if(d1 != 0 && d1 < d2){
                    boool = true;
            }
            else if(d1 == d2){
                string s_sub1 = s.substr(n-d1,d1);
                string s_sub2 = s.substr(n-2*d1-1,d1);
                if(s_sub1 < s_sub2){
                    boool = true;
                }
                else {
                    d1 = d2;
                    d2 = 0;
                }
            }
            else {
                d1 = d2;
                d2 = 0;
            }

            if(d1 != 0 && d1 < d2){
                boool = true;
            }
            if(boool) continue;

            Bint tmin, tmax;
            {
                string t = s;
                int dd = 0;
                rep(i,n){
                    char &c = t[i];
                    if(c == '*'){
                        dd = 0;
                        continue;
                    }
                    else if(c == '^'){
                        dd = 0;
                        continue;
                    }
                    else {
                        dd++;
                        if(dd == 1 && (i == n-1 || t[i+1] == '*' || t[i+1] == '^')){
                            c = '2';
                        }
                        else if(dd == 1){
                            c = '1';
                        }
                        else c = '0';
                    }
                }
                tmin = calc(t,d_ub);
                if(tmin < 0 || power_10_d_bu < tmin) continue;
                
            }

            {
                string t = s;
                int dd = 0;
                rep(i,n){
                    char &c = t[i];
                    if(c == '*' || c == '^'){
                        continue;
                    }
                    else {
                        c = '9';
                    }
                }
                tmax = calc(t,d_ub);
                if(tmax >= 0 && tmax < maxcmp_) continue;

            }
            
            
            int64_t D = power(10,d);//10^d
            unordered_set <string> calc_result;//計算結果が大きすぎる式の集合
            for(int64_t j = D/10; j < D; j++){
                string r = to_string(j);
                string t = s;
                int k = 0;
                for(char &c : t){
                    if(c == 'x'){
                        c = r[k];
                        k++;
                        if(k == d) break;
                    }
                }

                {
                    int Time = time(NULL);
                    if(Time-TIME >= 1){
                        time_count += Time-TIME;
                        cout << time_count << "///" << t << endl;
                        TIME = Time;
                    }
                }

                if(pt_p(t)){
                    if(calc_too_big(t,calc_result)) continue;
                    Bint calc_t = calc(t,d_ub);
                    if(maxcmp_ <= calc_t && calc_t < power_10_d_bu){
                        if(pqkable(t+"^"+to_string_Bint(calc_t))){
                            cout << t << "=\n" << calc_t << endl;
                        }
                    }
                    else if(calc_t >= power_10_d_bu || calc_t < 0){
                        calc_result.insert(t);
                    }
                }

            }

        }
    //}
}