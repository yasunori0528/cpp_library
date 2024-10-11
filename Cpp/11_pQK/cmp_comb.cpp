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

//nの絵札枚数
int CARD(Bint n){
    int cnt = 0;
    while(n > 0){
        Bint n0 = n%10;
        n /= 10;
        if(n0 <= 3 && n%10 == 1){
            cnt++;
            n /= 10;
        }
    }
    return cnt;
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
bool pqkable(string s){
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

vector<char> card = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

//Xの必要枚数
int pqkable2(string s){
    int n = s.size();
    string t;
    rep(i,n) t.push_back('x');
    rep(i,n){
        char & c = s[i];
        if(c == '*' || c == '^' || c == '='){
            t[i] = c;
            c = 'x';
        }
        else if('4' <= c && c <= '9') {
            t[i] = c;
            c = 'y';
        }
        else if('0' <= c && c <= '3' && c != '1') {
            //絵札として使わない
            if(i == 0 || s[i-1] != '1') {
                t[i] = c;
                c = 'z';
            }
            //使う絵札が確定している
            else if(i == 1 || s[i-2] != '1'){
                string s_sub_i = s.substr(i-1,2);
                if(s_sub_i == "10"){
                    t[i-1] = '-';
                    t[i] = 'T';
                    s[i-1] = s[i] = 'w';
                }
                else if(s_sub_i == "11"){
                    t[i-1] = '-';
                    t[i] = 'J';
                    s[i-1] = s[i] = 'w';
                }
                else if(s_sub_i == "12"){
                    t[i-1] = '-';
                    t[i] = 'Q';
                    s[i-1] = s[i] = 'w';
                }  
                else if(s_sub_i == "13"){
                    t[i-1] = '-';
                    t[i] = 'K';
                    s[i-1] = s[i] = 'w';
                }  
            }
                
        }
    }
    int cnt = 0;
    rep(i,n){
        char & c = s[i];
        if(c == '1') cnt++;
        //cout << i << ":" << cnt << endl;
        char c_ = 'x';
        if(i < n-1) c_ = s[i+1];
        if(c_ == '1') continue;
        else{
            //if(20 <= i && i <= 22) cout << i << ":" << cnt << endl;
            if('0' <= c_ && c_ <= '3'){
                while(cnt >= 3){
                    s[i-cnt+1] = s[i-cnt+2] = 'z';
                    t[i-cnt+1] = '-';
                    t[i-cnt+2] = 'J';
                    cnt -= 2;
                }
                if(cnt == 1){
                    if(c_ == '0'){
                        s[i] = s[i+1] = 'z';
                        t[i] = '-';
                        t[i+1] = 'T';
                    }
                    if(c_ == '2'){
                        s[i] = s[i+1] = 'z';
                        t[i] = '-';
                        t[i+1] = 'Q';
                    }
                    if(c_ == '3'){
                        s[i] = s[i+1] = 'z';
                        t[i] = '-';
                        t[i+1] = 'K';
                    }
                }
                cnt = 0;
            }
            else{
                while(cnt > 0){
                    if(cnt == 1){
                        c = 'z';
                        t[i] = '1';
                        cnt--;
                    }
                    else{
                        s[i-cnt+1] = s[i-cnt+2] = 'z';
                        t[i-cnt+1] = '-';
                        t[i-cnt+2] = 'J';
                        cnt -= 2;
                    }
                }
            }
        }
    }
    //cout << t << endl;

    vector<int> AX(4,0);
    rep(i,n){
        char c = s[i];
        if('0' <= c && c <= '3' && c != '1'){
            AX[c-'0']++;
        }
    }
    //for(int i : AX) cout << i << endl;
    map<char,int> comb;
    for(char c : t){
        comb[c]++;
    }
    int AX0 = AX[0];
    int AX2 = AX[2];
    int AX3 = AX[3];
    int min_wild = s.size();
    rep(i,AX0+1){
        rep(j,AX2+1){
            rep(k,AX3+1){
                map<char,int> comb_ijk = comb;
                comb_ijk['0'] += i;
                comb_ijk['2'] += j;
                comb_ijk['3'] += k;
                comb_ijk['J'] += i+j+k;
                comb_ijk['T'] += AX0-i;
                comb_ijk['Q'] += AX2-j;
                comb_ijk['K'] += AX3-k;
                comb_ijk['1'] += AX0-i+AX2-j+AX3-k;
                int cntQ_ = max(0,min(comb_ijk['Q']-4,4-comb_ijk['2']));
                int cntK_ = max(0,min(comb_ijk['K']-4,4-comb_ijk['3']));
                int cntJ_ = max(0,(4-comb_ijk['1']-cntQ_-cntK_)/2);
                comb_ijk['1'] += 2*cntJ_+cntQ_+cntK_;
                comb_ijk['2'] += cntQ_;
                comb_ijk['3'] += cntK_;
                comb_ijk['J'] -= cntJ_;
                comb_ijk['Q'] -= cntQ_;
                comb_ijk['K'] -= cntK_;

                int wild = 0;
                for(char c : card){
                    if(c == '0') wild += comb_ijk['0'];
                    else wild += max(0,comb_ijk[c]-4);
                }
                min_wild = min(min_wild,wild);
            }
        }
    }
    return min_wild;
}

//deck_strでsが出せるかどうか
bool pqkable3(string s, string deck_str){
    int n = s.size();

    map<char,int> deck;
    for(char c : card) deck[c] = 0;
    deck['X'] = 0;
    for(char c : deck_str) deck[c]++;

    string t;
    rep(i,n) t.push_back('x');
    rep(i,n){
        char & c = s[i];
        if(c == '*' || c == '^' || c == '='){
            t[i] = c;
            c = 'x';
        }
        else if('4' <= c && c <= '9') {
            t[i] = c;
            c = 'y';
        }
        else if('0' <= c && c <= '3' && c != '1') {
            //絵札として使わない
            if(i == 0 || s[i-1] != '1') {
                t[i] = c;
                c = 'z';
            }
            //使う絵札が確定している
            else if(i == 1 || s[i-2] != '1'){
                string s_sub_i = s.substr(i-1,2);
                if(s_sub_i == "10"){
                    t[i-1] = '-';
                    t[i] = 'T';
                    s[i-1] = s[i] = 'w';
                }
                else if(s_sub_i == "11"){
                    t[i-1] = '-';
                    t[i] = 'J';
                    s[i-1] = s[i] = 'w';
                }
                else if(s_sub_i == "12"){
                    t[i-1] = '-';
                    t[i] = 'Q';
                    s[i-1] = s[i] = 'w';
                }  
                else if(s_sub_i == "13"){
                    t[i-1] = '-';
                    t[i] = 'K';
                    s[i-1] = s[i] = 'w';
                }  
            }
                
        }
    }
    int cnt = 0;
    rep(i,n){
        char & c = s[i];
        if(c == '1') cnt++;
        //cout << i << ":" << cnt << endl;
        char c_ = 'x';
        if(i < n-1) c_ = s[i+1];
        if(c_ == '1') continue;
        else{
            //if(20 <= i && i <= 22) cout << i << ":" << cnt << endl;
            if('0' <= c_ && c_ <= '3'){
                while(cnt >= 3){
                    s[i-cnt+1] = s[i-cnt+2] = 'z';
                    t[i-cnt+1] = '-';
                    t[i-cnt+2] = 'J';
                    cnt -= 2;
                }
                if(cnt == 1){
                    if(c_ == '0'){
                        s[i] = s[i+1] = 'z';
                        t[i] = '-';
                        t[i+1] = 'T';
                    }
                    if(c_ == '2'){
                        s[i] = s[i+1] = 'z';
                        t[i] = '-';
                        t[i+1] = 'Q';
                    }
                    if(c_ == '3'){
                        s[i] = s[i+1] = 'z';
                        t[i] = '-';
                        t[i+1] = 'K';
                    }
                }
                cnt = 0;
            }
            else{
                while(cnt > 0){
                    if(cnt == 1){
                        c = 'z';
                        t[i] = '1';
                        cnt--;
                    }
                    else{
                        s[i-cnt+1] = s[i-cnt+2] = 'z';
                        t[i-cnt+1] = '-';
                        t[i-cnt+2] = 'J';
                        cnt -= 2;
                    }
                }
            }
        }
    }
    //cout << t << endl;

    vector<int> AX(4,0);
    rep(i,n){
        char c = s[i];
        if('0' <= c && c <= '3' && c != '1'){
            AX[c-'0']++;
        }
    }
    //for(int i : AX) cout << i << endl;
    map<char,int> comb;
    for(char c : t){
        comb[c]++;
    }
    int AX0 = AX[0];
    int AX2 = AX[2];
    int AX3 = AX[3];
    int min_wild = s.size();
    rep(i,AX0+1){
        rep(j,AX2+1){
            rep(k,AX3+1){
                map<char,int> comb_ijk = comb;
                comb_ijk['0'] += i;
                comb_ijk['2'] += j;
                comb_ijk['3'] += k;
                comb_ijk['J'] += i+j+k;
                comb_ijk['T'] += AX0-i;
                comb_ijk['Q'] += AX2-j;
                comb_ijk['K'] += AX3-k;
                comb_ijk['1'] += AX0-i+AX2-j+AX3-k;
                int cntQ_ = max(0,min(comb_ijk['Q']-deck['Q'],deck['2']-comb_ijk['2']));
                int cntK_ = max(0,min(comb_ijk['K']-deck['K'],deck['3']-comb_ijk['3']));
                int cntJ_ = max(0,(deck['1']-comb_ijk['1']-cntQ_-cntK_)/2);
                comb_ijk['1'] += 2*cntJ_+cntQ_+cntK_;
                comb_ijk['2'] += cntQ_;
                comb_ijk['3'] += cntK_;
                comb_ijk['J'] -= cntJ_;
                comb_ijk['Q'] -= cntQ_;
                comb_ijk['K'] -= cntK_;

                int wild = 0;
                for(char c : card){
                    if(c == '0') wild += comb_ijk['0'];
                    else wild += max(0,comb_ijk[c]-deck[c]);
                }
                min_wild = min(min_wild,wild);

                //cout << cntJ_ << "," << cntQ_ << "," << cntK_ << "," << wild << endl;
            }
        }
    }
    if(min_wild <= deck['X']) return true;
    else return false;
}

//deck_strからsを出すときの絵札の使い方
string pqkable4(string s, string deck_str){
    int n = s.size();

    map<char,int> deck;
    for(char c : card) deck[c] = 0;
    deck['X'] = 0;
    for(char c : deck_str) deck[c]++;

    string t;
    rep(i,n) t.push_back('x');
    rep(i,n){
        char & c = s[i];
        if(c == '*' || c == '^' || c == '='){
            t[i] = c;
            c = 'x';
        }
        else if('4' <= c && c <= '9') {
            t[i] = c;
            c = 'y';
        }
        else if('0' <= c && c <= '3' && c != '1') {
            //絵札として使わない
            if(i == 0 || s[i-1] != '1') {
                t[i] = c;
                c = 'z';
            }
            //使う絵札が確定している
            else if(i == 1 || s[i-2] != '1'){
                string s_sub_i = s.substr(i-1,2);
                if(s_sub_i == "10"){
                    t[i-1] = '-';
                    t[i] = 'T';
                    s[i-1] = s[i] = 'w';
                }
                else if(s_sub_i == "11"){
                    t[i-1] = '-';
                    t[i] = 'J';
                    s[i-1] = s[i] = 'w';
                }
                else if(s_sub_i == "12"){
                    t[i-1] = '-';
                    t[i] = 'Q';
                    s[i-1] = s[i] = 'w';
                }  
                else if(s_sub_i == "13"){
                    t[i-1] = '-';
                    t[i] = 'K';
                    s[i-1] = s[i] = 'w';
                }  
            }
                
        }
    }
    int cnt = 0;
    rep(i,n){
        char & c = s[i];
        if(c == '1') cnt++;
        //cout << i << ":" << cnt << endl;
        char c_ = 'x';
        if(i < n-1) c_ = s[i+1];
        if(c_ == '1') continue;
        else{
            //if(20 <= i && i <= 22) cout << i << ":" << cnt << endl;
            if('0' <= c_ && c_ <= '3'){
                while(cnt >= 3){
                    s[i-cnt+1] = s[i-cnt+2] = 'z';
                    t[i-cnt+1] = '-';
                    t[i-cnt+2] = 'J';
                    cnt -= 2;
                }
                if(cnt == 1){
                    if(c_ == '0'){
                        s[i] = s[i+1] = 'z';
                        t[i] = '-';
                        t[i+1] = 'T';
                    }
                    if(c_ == '2'){
                        s[i] = s[i+1] = 'z';
                        t[i] = '-';
                        t[i+1] = 'Q';
                    }
                    if(c_ == '3'){
                        s[i] = s[i+1] = 'z';
                        t[i] = '-';
                        t[i+1] = 'K';
                    }
                }
                cnt = 0;
            }
            else{
                while(cnt > 0){
                    if(cnt == 1){
                        c = 'z';
                        t[i] = '1';
                        cnt--;
                    }
                    else{
                        s[i-cnt+1] = s[i-cnt+2] = 'z';
                        t[i-cnt+1] = '-';
                        t[i-cnt+2] = 'J';
                        cnt -= 2;
                    }
                }
            }
        }
    }
    //cout << t << endl;

    vector<int> AX(4,0);
    rep(i,n){
        char c = s[i];
        if('0' <= c && c <= '3' && c != '1'){
            AX[c-'0']++;
        }
    }
    //for(int i : AX) cout << i << endl;
    map<char,int> comb;
    for(char c : t){
        comb[c]++;
    }
    int AX0 = AX[0];
    int AX2 = AX[2];
    int AX3 = AX[3];
    string rtn;
    rep(i,AX0+1){
        rep(j,AX2+1){
            rep(k,AX3+1){
                map<char,int> comb_ijk = comb;
                comb_ijk['0'] += i;
                comb_ijk['2'] += j;
                comb_ijk['3'] += k;
                comb_ijk['J'] += i+j+k;
                comb_ijk['T'] += AX0-i;
                comb_ijk['Q'] += AX2-j;
                comb_ijk['K'] += AX3-k;
                comb_ijk['1'] += AX0-i+AX2-j+AX3-k;
                int cntQ_ = max(0,min(comb_ijk['Q']-deck['Q'],deck['2']-comb_ijk['2']));
                int cntK_ = max(0,min(comb_ijk['K']-deck['K'],deck['3']-comb_ijk['3']));
                int cntJ_ = max(0,(deck['1']-comb_ijk['1']-cntQ_-cntK_)/2);
                comb_ijk['1'] += 2*cntJ_+cntQ_+cntK_;
                comb_ijk['2'] += cntQ_;
                comb_ijk['3'] += cntK_;
                comb_ijk['J'] -= cntJ_;
                comb_ijk['Q'] -= cntQ_;
                comb_ijk['K'] -= cntK_;

                int wild = 0;
                for(char c : card){
                    if(c == '0') wild += comb_ijk['0'];
                    else wild += max(0,comb_ijk[c]-deck[c]);
                }
                if(wild <= deck['X']){
                    int cnt_AX0 = 0;
                    int cnt_AX2 = 0;
                    int cnt_AX3 = 0;
                    for(int l = 2; l < n; l++){
                        char c = s[l];
                        if(c == '0'){
                            if(cnt_AX0 < i){
                                t[l-2] = '-';
                                t[l-1] = 'J';
                                t[l] = '0';
                            }
                            else{
                                t[l-2] = '1';
                                t[l-1] = '-';
                                t[l] = 'T';
                            }
                            cnt_AX0++;
                        }
                        if(c == '2'){
                            if(cnt_AX2 < j){
                                t[l-2] = '-';
                                t[l-1] = 'J';
                                t[l] = '2';
                            }
                            else{
                                t[l-2] = '1';
                                t[l-1] = '-';
                                t[l] = 'Q';
                            }
                            cnt_AX2++;
                        }
                        if(c == '3'){
                            if(cnt_AX3 < k){
                                t[l-2] = '-';
                                t[l-1] = 'J';
                                t[l] = '3';
                            }
                            else{
                                t[l-2] = '1';
                                t[l-1] = '-';
                                t[l] = 'K';
                            }
                            cnt_AX3++;
                        }
                    }
                    for(char c : t){
                        if(c != '-') rtn.push_back(c);
                    }
                    rtn.push_back(',');
                }


                //cout << cntJ_ << "," << cntQ_ << "," << cntK_ << "," << wild << endl;
            }
        }
    }
    return rtn;
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
    string deck; cin >> deck;

    int TIME = time(NULL);//開始時刻
    int time_count = 0;
    int time_interval = 3600;

    int deck_d = 0;
    int wild = 0;
    for(char c : deck){
        if('0' <= c && c <= '9'){
            deck_d++;
        }
        else deck_d += 2;
        if(c == 'X') wild++;
    }
    int d = deck_d-1;
    while(deck_d < d+1+3*d/10) d--;
    //d = 10;
    int max_pd = d;
    //cout << d << endl;

    maxn = power(10,(max_pd+1)/2);//10^(d/2)
    prime_calculate();
    vector<string> vec_operator = {"", "*", "^"};//演算子
    Bint lower_bound_of_search_range = 1;
    //Bint ubosr = power(10,35)-1;
    vector<vector<string>> output_list(deck.size()+1,vector<string>(0));
    //vector<vector<pair<Bint,string>>> exp_list(d+1,vector<pair<Bint,string>>(0));
    for(int d_i = 2; d_i <= d; d_i++){
        {
            int Time = time(NULL);
            if(Time-TIME >= time_interval){
                time_count += Time-TIME;
                cout << "time:" << time_count << "///";
                TIME = Time;
            }
        }
        cout << "start:" << d_i << endl;
        Bint upper_bound_of_search_range =
        power(10,deck_d-d_i,100)-1;

        vector<vector<pair<Bint,string>>> exp_list(d_i+1,vector<pair<Bint,string>>(0));
        for(int i = 1; i <= d_i; i++){
            int64_t exp_pattern = power(2,i-1);//"^"の位置の個数
            int64_t num_pattern = power(10,i);
            unordered_set <string> calc_result;//計算結果が大きすぎる式の集合
            rep(j,exp_pattern){
                if((i == d_i || i >= deck_d-d_i) && j == 0) continue;
                //if(i == d-1 && j <= 0) continue;
                string s = "x";
                int64_t M = j;
                rep(k, i-1){
                    s = "x" + vec_operator[M%2*2] + s;
                    M /= 2;
                }
                int pd = 0;
                for(char c : s){
                    if(c == 'x') pd++;
                }
                if(pd > max_pd) continue;
                //cout << s << endl;
                {
                    Bint tmin;
                    int n = s.size();
                    string t = s;
                    int dd = 0;
                    rep(k,n){
                        char &c = t[k];
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
                            if(dd == 1 && (k == n-1 || t[k+1] == '*' || t[k+1] == '^')){
                                c = '2';
                            }
                            else if(dd == 1){
                                c = '1';
                            }
                            else c = '0';
                        }
                    }
                    tmin = calc(t,72-d_i);
                    if(tmin < 0 || upper_bound_of_search_range < tmin) continue;
                }
                //cout << s << endl;

                for(int64_t k = num_pattern/10; k < num_pattern; k++){
                    string r = to_string(k);
                    string t = s;
                    int l = 0;
                    for(char &c : t){
                        if(c == 'x'){
                            c = r[l];
                            l++;
                            if(l == i) break;
                        }
                    }
                    if(!pqkable3(t,deck)) continue;

                    {
                        int Time = time(NULL);
                        if(Time-TIME >= time_interval){
                            time_count += Time-TIME;
                            cout << "time:" << time_count << "///" << t << endl;
                            TIME = Time;
                        }
                    }

                    if(pt_p(t)){
                        if(calc_too_big(t,calc_result)) continue;
                        Bint exp_list_i_ = calc(t,72-d_i);
                        if(0 < exp_list_i_ && exp_list_i_ <= upper_bound_of_search_range) exp_list[i].push_back(make_pair(exp_list_i_,t));
                        else calc_result.insert(t);
                    }
                }
            }
        }
        rep(i,d_i+1) sort(exp_list[i].begin(), exp_list[i].end());
        /*rep(i,d_i+1) {
            cout << i << "," << exp_list[i].size() << endl;
        }*/
        cout << "exp_list_calculated\n";

        vector<int> exp_list_size(d_i+1);
        rep(i,d_i+1) exp_list_size[i] = exp_list[i].size();
        //rep(i,d) cout << exp_list_size[i] << ",";
        //cout << endl;

        int64_t product_pattern = power(2,d_i-1);//"*"の位置の個数
        
        for(int64_t i = 0; i < product_pattern; i++){
            string  s = "x";
            int64_t M = i;
            rep(j,d_i-1){
                int M2 = M%2;
                s = "x" + vec_operator [M2] + s;
                M /= 2;
            }
            bool multi_monotonicity = true;
            int d0_1 = d_i;
            int d0_2 = 0;
            for(char c : s){
                if(c == 'x') d0_2++;
                else if(d0_1 < d0_2){
                    multi_monotonicity = false;
                    break;
                }
                else{
                    d0_1 = d0_2;
                    d0_2 = 0;
                }
            }
            if(d0_1 < d0_2){
                multi_monotonicity = false;
            }
            if(!multi_monotonicity) continue;

            vector<int> vec_d(1,0);
            int vec_d_size = 1;
            for(char c : s){
                if(c == 'x') vec_d[vec_d_size-1]++;
                else {
                    vec_d.push_back(0);
                    vec_d_size++;
                }
            }
            //cout << s << endl;
            //for(int j : vec_d) cout << j << ",";
            //cout << vec_d_size << endl;

            vector<int> loop_max(vec_d_size);
            bool els0 = false;
            rep(j,vec_d_size){
                int elsvdj = exp_list_size[vec_d[j]];
                if(elsvdj == 0) {
                    els0 = true;
                    break;
                }
                loop_max[j] = elsvdj;
            }
            if(els0) continue;
            vector<int> loop_now(vec_d_size,0);

            /*cout << "---";
            for(int j : vec_d) cout << j << ",";
            cout << "---\n";*/

            bool bool_calc = true;
            while(bool_calc){
                bool break1 = false;
                string t;
                Bint calc_t = 1;
                rep(j,vec_d_size){
                    t += exp_list[vec_d[j]][loop_now[j]].second;
                    t += "*";
                    calc_t *= exp_list[vec_d[j]][loop_now[j]].first;
                }
                t.pop_back();
                if(lower_bound_of_search_range <= calc_t && calc_t < upper_bound_of_search_range){
                    string calc_t_str = to_string_Bint(calc_t)+"="+t;
                    if(pqkable3(calc_t_str,deck)){
                        string calc_t_op = pqkable4(calc_t_str,deck);
                        //cout << calc_t_op << endl;
                        int cnt_calc_t = 0;
                        for(char c : calc_t_op){
                            if(c == ',') break;
                            if(c != '=' && c != '*' && c != '^') cnt_calc_t++;
                        }
                        //if(to_string_Bint(calc_t).size()-CARD(calc_t) <= 2)
                        output_list[cnt_calc_t].push_back(calc_t_op);
                    }
                }
                else if(upper_bound_of_search_range <= calc_t || calc_t < 0){
                    break1 = true;//一次ループ抜ける
                }
                {
                    int Time = time(NULL);
                    if(Time-TIME >= time_interval){
                        time_count += Time-TIME;
                        cout << "time:" << time_count << "///" << t << endl;
                        TIME = Time;
                    }
                }

                //更新
                rep(j,vec_d_size){
                    if(!(break1 && j == 0) && loop_now[j]+1 < loop_max[j]){
                        loop_now[j]++;
                        for(int k = j-1; j >= 0; j--){
                            if(vec_d[k] == vec_d[k+1]) loop_now[k] = loop_now[k+1];
                            else loop_now[k] = 0;
                        }
                        break;
                    }
                    else if(j == vec_d_size-1) {
                        bool_calc = false;
                    }
                }
            }
        }
    }
    cout << endl;

    int cnt_all = 0;
    for(int i = 3; i <= deck.size(); i++){
        vector<string> vs = output_list[i];
        cout << i << endl;
        int vs_size = vs.size();
        cout << vs_size << endl;
        cnt_all += vs_size;
        for(string s : vs){
            cout << s << endl;
        }
        cout << endl;
    }
    cout << cnt_all << endl;
    

    int Time_end = time(NULL);
    time_count += Time_end-TIME;
    cout << "time:" << time_count << "///" << endl;
    
}                                                       