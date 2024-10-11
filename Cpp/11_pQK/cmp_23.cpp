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

Bint strtoint(string s){
    int n = s.size();
    if(n == 1){
        return chartoint[s[0]];
    }
    Bint rtn = strtoint(s.substr(0,n-1));
    char i = chartoint[s[n-1]];
    if(i < 10) rtn = 10*rtn+i;
    else rtn = 100*rtn+i;
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

//n枚m桁^aを全探索
int main(){
    //11, 17, 3, 3
    int n, m, a;
    string a_s;
    cin >> n >> m >> a >> a_s;
    
    int t_start = time(NULL);
    int t_0 = time(NULL);
    int t_interval = 3600;

    calc_chartoint();
    string deck;
    for(int i = 1; i <= 13; i++){
        char c = card[i];
        rep(j,4) deck.push_back(c);
    }
    deck += "XX";
    /*{
        Bint nn = pow((Bint)2,122);
        string s = "2^122="+Bint_to_string(nn);
        cout << pqkable4(s, deck);
    }*/
    string max_cmp_str;
    Bint max_cmp_int = 0;
    vector<vector<char>> v1;
    {
        vector<int> v(11);
        for(int i = 0; i <= 9; i++){
            v[i] = i;
        }
        v[10] = 10+n-(m-n);
        cout << "A" << endl;
        while(1){
            vector<char> v1i;
            int cnt_w = 0;
            for(int i = 0; i < 10; i++){
                int j = v[i+1]-v[i]-1;
                if(i) cnt_w += max(j-4,0);
                else cnt_w += j;
                for(int k = 0; k < j; k++){
                    v1i.push_back(card[i]);
                }
            }
            if(cnt_w <= 2) v1.push_back(v1i);
            /*for(int vi : v){
                cout << vi << ",";
            }
            cout << endl;*/

            bool b = false;
            for(int i = 9; i > 0; i--){
                if(v[i] + 1 != v[i+1]){
                    v[i]++;
                    for(int j = i+1; j < 10; j++){
                        v[j] = v[j-1]+1;
                    }
                    b = true;
                    break;
                }
            }
            if(!b) break;
            /*for(int vi : v){
                cout << vi << ",";
            }
            cout << endl;*/
        }

        /*for(auto v1i : v1){
            for(auto v1ij : v1i){
                cout << v1ij;
            }
            cout << endl;
        }*/
    }

    vector<vector<char>> v2;
    {
        vector<int> v(5);
        for(int i = 0; i <= 3; i++){
            v[i] = i;
        }
        v[4] = 4+(m-n);
        cout << "A" << endl;
        while(1){
            vector<char> v2i;
            int cnt_w = 0;
            for(int i = 0; i < 4; i++){
                int j = v[i+1]-v[i]-1;
                cnt_w += max(j-4,0);
                for(int k = 0; k < j; k++){
                    v2i.push_back(card[i+10]);
                }
            }
            if(cnt_w <= 2) v2.push_back(v2i);
            /*for(int vi : v){
                cout << vi << ",";
            }
            cout << endl;*/

            bool b = false;
            for(int i = 3; i > 0; i--){
                if(v[i] + 1 != v[i+1]){
                    v[i]++;
                    for(int j = i+1; j < 4; j++){
                        v[j] = v[j-1]+1;
                    }
                    b = true;
                    break;
                }
            }
            if(!b) break;
            /*for(int vi : v){
                cout << vi << ",";
            }
            cout << endl;*/
        }

        /*for(auto v2i : v2){
            for(auto v2ij : v2i){
                cout << v2ij;
            }
            cout << endl;
        }*/
    }

    int v1_size = v1.size();
    int v2_size = v2.size();
    for(int i = 172; i < v1_size; i++){
        vector<char> v1i = v1[i];
        for(int j = 0; j < v2_size; j++){
            vector<char> v2j = v2[j];
            vector<char> v = v1i;
            for(char c : v2j) v.push_back(c);
            sort(v.begin(), v.end());
            do{
                if(v[0] == '0') continue;
                int vl = chartoint[v[v.size()-1]];
                if(vl%5 == 0 || vl%2 == 0) continue;
                string s;
                for(char c : v) s.push_back(c);
                Bint n = strtoint(s);
                if(n%3 == 0) break; 
                if(n < max_cmp_int) continue;
                if(MRpt(n)){
                    string s_c = Bint_to_string(pow(n,a));
                    s = s_c + '=' + Bint_to_string(n) + '^' + a_s;
                    if(pqkable2(s) <= 2){
                        max_cmp_int = n;
                        max_cmp_str = pqkable4(s, deck);
                        cout << max_cmp_str << endl;
                    }
                }

                int t_1 = time(NULL);
                if(t_1 - t_0 >= t_interval){
                    cout << "time:" << t_1-t_start << "///" << n << "[" << i+1 << "/" << v1_size << "," << j+1 << "/" << v2_size << "]" << endl;
                    t_0 = t_1;
                }
            }while(next_permutation(v.begin(), v.end()));
        }
    }

    cout << max_cmp_str << endl;

    int t_end = time(NULL);
    cout << "///" << t_end - t_start << "[s]" << endl;
}