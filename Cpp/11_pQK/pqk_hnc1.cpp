#include <bits/stdc++.h>
using namespace std;

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;
// 仮数部が1024ビットの浮動小数点数型(TLEしたら小さくする)
using Real = mp::number<mp::cpp_dec_float<1024>>;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

vector<char> card = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
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

map<char,int> chartoint;
void calc_chartoint(){
    for(int i = 0; i < 10; i++){
        chartoint['0'+i] = i;
    }
    chartoint['T'] = 10;
    chartoint['J'] = 11;
    chartoint['Q'] = 12;
    chartoint['K'] = 13;
    chartoint['X'] = 14;
}
char inttochar(int n){
    if(0 <= n && n < 10) return (char)('0'+n);
    if(n == 10) return 'T';
    if(n == 11) return 'J';
    if(n == 12) return 'Q';
    if(n == 13) return 'K';
    return 'X';
}

vector<int> card_pri = {9,8,7,6,5,4,3,2,1,0,13,12,11,10,14};
string sort_91KT(string s){
    vector<pair<int,char>> vp;
    for(char c : s){
        vp.push_back(make_pair(card_pri[chartoint[c]],c));
    }
    sort(vp.begin(),vp.end());
    string rtn;
    for(auto vpi : vp){
        rtn.push_back(vpi.second);
    }
    return rtn;
}

string mtos(map<char,int> m){
    string s;
    for(auto mi : m){
        for(int i = 0; i < mi.second; i++){
            s.push_back(mi.first);
        }
    }
    sort_91KT(s);
    return s;
}

map<char,int> stom(string s){
    map<char,int> rtn;
    for(char c : s){
        rtn[c]++;
    }
    return rtn;
}

vector<int64_t> prime_list;
void prime_calc(int64_t MAX_N){
    for(int64_t i = 2; i <= MAX_N; i++){
        bool b = true;
        for(int64_t j = 2; j < i; j++){
            if(i%j == 0){
                b = false;
                break;
            }
            else if(j*j > i) break;
        }
        if(b) prime_list.push_back(i);
    }
}
bool pt(Bint n){
    if(n < 2) return false;
    for(int64_t i : prime_list){
        if(i*i > n) break;
        if(n%i == 0) return false;
    }
    return true;
}



int main(){
    //nとpの桁数の和
    int d;
    //絵札枚数
    int m;
    cin >> d;

    calc_chartoint();
    prime_calc(pow(10,3));
    string deck;
    for(int i = 1; i <= 13; i++){
        char c = card[i];
        rep(j,4) deck.push_back(c);
    }
    deck += "XX";

    int dp = d/2;
    int dn = d-dp;
    int64_t pmin, pmax;
    if(dn == dp) {
        pmin = 1*pow(10,dp-1);
        pmax = 5*pow(10,dp-1);
    }
    else{
        pmin = 5*pow(10,dp-1);
        pmax = 10*pow(10,dp-1);
    }
    //cout << "a" << endl;
    //hand -> p
    vector<map<map<char,int>,set<int64_t>>> output_list(d/2+1);
    for(int64_t p = pmin; p < pmax; p++){
        //cout << p << endl;
        //if(__gcd(p,30) != 1) continue;
        if(!pt(p)) continue;
        int64_t n = 2*p;
        string sp = to_string(p);
        string sn = to_string(n);
        string sp_ = pqkable4(sp,deck);
        string sn_ = pqkable4(sn,deck);
        //cout << sp_ << "_" << sn_ << endl;
        vector<string> vp(1);
        vector<string> vn(1);

        for(char c : sp_){
            if(c == ',') vp.push_back("");
            else vp[vp.size()-1].push_back(c);
        }
        vp.pop_back();
        for(char c : sn_){
            if(c == ',') vn.push_back("");
            else vn[vn.size()-1].push_back(c);
        }
        vn.pop_back();

        //for(string i : vp) cout << i << ",";
        //cout << endl;
        //for(string i : vn) cout << i << ",";
        //cout << endl;

        for(string vpi : vp){
            for(string vni : vn){
                string hand = vpi+vni;
                map<char,int> handm = stom(hand);
                output_list[d-hand.size()][handm].insert(p);
            }
        }
    }

    for(int i = d/2; i >= 0; i--){
        auto output_list_i = output_list[i];
        for(auto opi : output_list_i){
            map<char,int> opim;
            set<int64_t> opiv;
            tie(opim,opiv) = opi;
            vector<int> loop_max;
            for(int j = 10; j <= 13; j++){
                loop_max.push_back(opim[inttochar(j)]);
            }
            vector<int> loop_now(4,0);
            bool calc_start = true;
            while(1){
                if(calc_start) calc_start = false;
                else{
                    auto mj = opim;
                    int cp = 0;
                    for(int j = 0; j <= 3; j++){
                        mj[inttochar(j+10)] -= loop_now[j];
                        mj[inttochar(1)] += loop_now[j];
                        mj[inttochar(j)] += loop_now[j];
                        cp += mj[inttochar(j+10)];
                    }
                    set<int64_t> &opjv = output_list[cp][mj];
                    for(int64_t j : opiv){
                        opjv.insert(j);
                    }
                }

                int cc = -1;
                for(int j = 0; j <= 3; j++){
                    if(loop_now[j] != loop_max[j]){
                        cc = j;
                        break;
                    }
                }
                if(cc == -1) break;
                loop_now[cc]++;
                for(int j = cc-1; j >= 0; j--){
                    loop_now[j] = 0;
                }
            }
        }
    }

    for(int i = 0; i <= d/2; i++){
        auto output_list_i = output_list[i];
        int cnt_size = 0;
        for(pair<map<char,int>,set<int64_t>> opi : output_list_i){
            map<char,int> opim;
            set<int64_t> opiv;
            tie(opim,opiv) = opi;
            opim['2']++;
            int cntX = 0;
            for(auto j : opim){
                if(j.first == '0') cntX += j.second;
                else cntX += max(0,j.second-4);
            }
            if(cntX > 2) continue;
            cnt_size++;
            string opis = mtos(opim);
            cout << opis;
            for(int64_t opivj : opiv){
                cout << "," << opivj;
            }
            cout << endl;
        }
        cout << i << "," << cnt_size << "\n\n";
    }
    /*while(1){
        string s,t;
        cin >> s >> t;
        cout << pqkable4(s,t) << endl;
    }*/
}