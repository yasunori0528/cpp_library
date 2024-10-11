#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;

//x^y
int64_t power(int64_t x, int64_t y){
    if(y < 0) return 0;
    else{
        int64_t n = 1ll;
        for(int64_t i = 0; i < y; i++) n *= x;
        return n;
    }
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

vector<char> card = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

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

int main(){
    int t_start = time(NULL);
    int t_0 = time(NULL);
    int t_interval = 3600;

    int a = 2;

    Bint maxp;
    int maxp_d = (a+70)/(a+1); //cout << maxp_d << endl;
    Bint maxp_up = power(10,maxp_d,72);
    Bint maxp_low = power(10,maxp_d-1,72);
    string maxn_str = "9999888877776666555544443333222213131313131312121212111111111";//61桁
    maxn_str = maxn_str.substr(0,71-maxp_d); //cout << maxn_str << endl;
    Bint maxn = str_int_Bint(maxn_str); //cout << maxn << endl;
    bool b = true;
    while(b){
        Bint maxp_mid = (maxp_up+maxp_low)>>1;
        Bint maxn_mid = power(maxp_mid,a,72);
        if(maxn_mid < maxn) maxp_low = maxp_mid;
        else maxp_up = maxp_mid;
        if(maxp_up - maxp_low == 1) b = false;
        //cout << maxp_low << "\n" << maxp_up << "\n\n";
    }
    maxp = maxp_low;
    if(!(maxp&1)) maxp--;
    cout << "maxp=" << maxp << endl;

    int p_size = maxp_d;
    //vector<Bint> skip_p(p_size,power(10,24,72));
    for(Bint p = maxp; p > 2; p -= 2){
        string p_str = to_string_Bint(p);
        rep(i,p_size-1){
            bool bi = false;
            if(p_str[i] != '1' && p_str[i+1] == '0'){
                for(int j = i; j >= 0; j--){
                    if(p_str[j] != '0'){
                        p_str[j]--;
                        for(int k = j+1; k < p_size; k++){
                            p_str[k] = '9'-(k-j-1)/4;
                        }
                        bi = true;
                        break;
                    }
                }
            }
            if(bi) break;
        }
        char & p_last = p_str[p_size-1];
        if(p_last == '5') p_last -= 2;
        else if (!((p_last-'0')&1)) p_last--;
        p = str_int_Bint(p_str);
        //cout << p << endl;

        Bint n = power(p,a,72);
        string n_str = to_string_Bint(n);

        //int i_start = 0;
        for(int i = 0; i < p_size-2; i++){
            //if(p >= skip_p[i]) continue;
            string p_i = p_str.substr(0,i+1);
            string p_i_min = p_i;
            if(p_str[i] == '1') {
                p_i_min += "01010101010111111111111";
                p_i_min = p_i_min.substr(0,p_size);
                if(p_i_min[p_size-1] == '0') p_i_min[p_size-1]++;
            }
            else{
                p_i_min += "10101010101011111111111";
                p_i_min = p_i_min.substr(0,p_size);
                if(p_i_min[p_size-1] == '0') p_i_min[p_size-1]++;
            }
            Bint p_i_min_Bint = str_int_Bint(p_i_min);
            Bint n_i_min_Bint = power(p_i_min_Bint,a,72);
            string n_i_min = to_string_Bint(n_i_min_Bint);
            string n_i_c;
            rep(j,p_size){
                if(n_str[j] == n_i_min[j]) n_i_c.push_back(n_str[j]);
            }
            string s_i = p_i + "^" + to_string(a) + "=" + n_i_c;
            if(pqkable2(s_i) > 2){
                //cout << i << "\n" << p << endl;
                //cout << p_i << endl;
                for(int j = i; j > 0; j--){
                    if(p_i[j] == '0'){
                        p_i[j] == '9';
                    }
                    else{
                        p_i[j]--;
                        break;
                    }
                }
                //cout << p_i << endl;
                p_str = p_i + "9999888877776666555544";
                p_str = p_str.substr(0,p_size);
                char & p_i_last = p_str[p_size-1];
                if (!((p_i_last-'0')&1)) p_i_last--;
                if(p_i_last == '5') p_i_last -= 2;
                Bint p_ = str_int_Bint(p_str);
                if(p_ < p) p = p_;
                n = power(p,a,72);
                n_str = to_string_Bint(n);
                //cout << p << endl;
                /*if(i < 7){
                    string sss; cin >> sss;
                }*/
                break;
            }
            /*else {
                skip_p[i] = p_i_min_Bint;
            }*/
        }
        
        string s = p_str + "^" + to_string(a) + "=" + n_str;
        if(pqkable2(s) <= 2) {
            cout << s << endl;
            //string sss; cin >> sss;
        }

        int t_1 = time(NULL);
        if(t_1 - t_0 >= t_interval){
            cout << "time:" << t_1-t_start << "///" << p << endl;
            t_0 = t_1;
        }
    }

    int t_end = time(NULL);
    cout << "///" << t_end-t_start << "[s]" << endl;
}