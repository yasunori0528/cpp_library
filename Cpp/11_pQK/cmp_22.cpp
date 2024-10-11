#include <bits/stdc++.h>
using namespace std;

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

string Bint_to_string(Bint n){
    if(n == 0) return "0";
    string s;
    while(n > 0){
        Bint k = n%10;
        char c = '0'+(int)k;
        s = c + s;
        n /= 10;
    }
    return s;
}

int calc (string s){
    int n = s.size();
    if(n == 0) return 1;
    int rtn = -1;
    for(int i = 0 ; i < n; i++){
        if(s[i] == '^'){
            //cout << s.substr(0,i) << "," << s.substr(i+1) << endl;
            if(calc(s.substr(i+1)) == -2 || calc(s.substr(i+1))*log2(stoll(s.substr(0,i))) > 8){
                rtn = -2;
                break;
            }
            rtn = pow(stoll(s.substr(0,i)), calc(s.substr(i+1)));
            break;
        }
    }
    if(rtn == -1){
        rtn = stoll(s);
    }

    return rtn;
}

//n^a%p
Bint powmod(Bint n, Bint a, Bint p){
    if(a == 0) return 1;
    n %= p;
    Bint b = a/2;
    Bint c = a%2;
    Bint nb = powmod(n, b, p);
    Bint rtn = 1;
    if(c) rtn = n;
    rtn = (rtn*nb*nb)%p;
    return rtn;
}

bool MRpt(Bint n){
    //cout << n << endl;
    if(n < 2) return false;
    if(n == 2 || n == 3) return true;
    if(n%2 == 0) return false;

    int k = 10;

    Bint s = n-1;
    int e = 0;
    //n-1 = s*2^e
    while(s%2 == 0){
        s /= 2;
        e++;
    }
    //cout << n << "=" << s << "*2^" << e << endl;

    for(int i = 0; i < k; i++){
        Bint a = rand()%(n-3)+2;
        //cout << "ai : " << a << endl;
        Bint as = powmod(a,s,n);
        bool c = false;
        if(as == 1 || as == n-1) c = true;
        Bint asj = as;
        for(int j = 1; j < e; j++){
            asj = asj*asj%n;
            if(asj == n-1) c = true;
        }
        if(!c) return false;
    }
    return true;
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

//'*'を含まない形を全探索
int main(){
    int t_start = time(NULL);
    int t_0 = time(NULL);
    int t_interval = 3600;

    string deck;
    for(int i = 1; i <= 13; i++){
        char c = card[i];
        rep(j,4) deck.push_back(c);
    }
    deck += "XX";

    vector<tuple<int,int,string>> pow_list;
    for(int pow_x = 0; pow_x < 8; pow_x++){
        string s = "xxx";
        int pow_x_ = pow_x;
        for(int i = 2; i >= 0; i--){
            if(pow_x_%2) s = s.substr(0,i) + "^" + s.substr(i);
            pow_x_ /= 2;
        }
        while(1){
            if(s[0] == 'x') s = s.substr(1);
            else break;
        }
        if(s.size()) s = s.substr(1);
        //cout << s << ",";

        int cnt_x = 0;
        for(char c : s){
            if(c == 'x') cnt_x++;
        }
        //cout << cnt_x << endl;

        int looop = pow(10,cnt_x);
        for(int i = 0; i < looop; i++){
            int i_ = i;
            string exp_i = s;
            for(int j = 0; j < cnt_x; j++){
                for(int k = exp_i.size()-1; k >= 0; k--){
                    if(exp_i[k] == 'x'){
                        exp_i[k] = '0'+i_%10;
                        i_ /= 10;
                        break;
                    }
                }
            }
            bool b_exp_i = true;
            for(int j = 0; j < exp_i.size(); j++){
                if(exp_i[j] == '^') continue;
                if((j == 0 || exp_i[j-1] == '^') && exp_i[j] == '0'){
                    b_exp_i = false;
                    break;
                }
                if((j == 0 || exp_i[j-1] == '^') && (j == exp_i.size()-1 || exp_i[j+1] == '^') && exp_i[j] == '1'){
                    b_exp_i = false;
                    break;
                }
            }
            if(!b_exp_i) continue;
            int exp_i_int = calc(exp_i);
            if(exp_i_int == -2 || exp_i_int > 229) continue;
            pow_list.push_back(make_tuple(cnt_x,exp_i_int,exp_i));
            //cout << cnt_x << "," << exp_i_int << "," << exp_i << endl;
        }
    }

    sort(pow_list.begin(),pow_list.end());
    /*for(auto i : pow_list){
        int x, y;
        string s;
        tie(x, y, s) = i;
        cout << x << "," << y << "," << s << endl;
    }*/
    //cout << "A" << endl;

    vector<vector<string>> pow_list_2(230);
    for(auto i : pow_list){
        int x, y;
        string s;
        tie(x, y, s) = i;
        pow_list_2[y].push_back(s);
    }
    //cout << "B" << endl;

    Bint MAX_C = pow((Bint)42521771,6);
    Bint Max_C_2 = pow((Bint)10,36);
    vector<pair<Bint,string>> max_cmp(230,make_pair(0,""));
    int max_a = 229;
    for(Bint p = 47211505469; p < pow((Bint)10,47); p += 2){
        //if(p == 4) p--;
        if(!MRpt(p)) continue;
        string p_s = Bint_to_string(p);
        Bint p_a = p*p;
        for(int a = 2; a <= max_a; a++){
            vector<string> pl2a = pow_list_2[a];
            string p_a_s = Bint_to_string(p_a);
            if(p_s.size()+p_a_s.size() >= 72) {
                for(int i = max_a; i >= a; i--){
                    cout << max_cmp[i].second << endl;
                }
                max_a = a-1;
                break;
            }
            for(string a_s : pl2a){
                string s = p_a_s + "=" + p_s + "^" + a_s;
                if(pqkable2(s) <= 2){
                    if(max_cmp[a].first <= p_a){
                        max_cmp[a] = make_pair(p_a, s);
                        if(p_a >= Max_C_2) cout << ">>>" << pqkable4(s, deck) << endl;
                        if(p_a >= MAX_C) {
                            MAX_C = p_a;
                        }
                    }

                    
                }
            }
            p_a *= p;
        }

        int t_1 = time(NULL);
        if(t_1 - t_0 >= t_interval){
            cout << "time:" << (t_1-t_start)/3600 << "///" << p << endl;
            t_0 = t_1;
        }
    }

    int t_end = time(NULL);
    cout << "///" << t_end - t_start << "[s]" << endl;
}