#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

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
            if(ntrl[k] > 0) prime.push_back(k);
        }
    }
    cout << "prime calculated" << endl;
}
bool pt(int64_t n,vector<int64_t>vec){
    if(n <= 1) return false;
    int64_t s = vec.size();
    for(int64_t i = 0; i < s; i++){
        if(vec[i]*vec[i] > n) return true;
        else if(n%vec[i] == 0) return false;    
    }
    return false;
    cout << "Insuficuent_Prime_List" << endl;
}

vector<char> card = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K'};
//出せるかどうか
bool pqkable(string s){
    int n = s.size();
    map<char,int> m;
    for(char c : s){
        m[c]++;
    }
    int cnt = 0;
    rep(i,10){
        cnt += m[i+'0'];
    }
    if(cnt > 72) return false;
    int wild = 0;
    for(int i = 4; i <= 9; i++){
        wild += max(0,m[i+'0']-4);
        if(wild > 2) return false;
    }
    vector<int> Card(4,0);
    rep(i,n-1){
        char ci = s[i];
        char ci_ = s[i+1];
        if(ci == '1' && ('0' <= ci_ && ci_ <= '3')){
            Card[ci_-'0']++;
        }
    }
    for(int i = 2; i <= 3; i++){
        wild += max(0,m[i+'0']-Card[i]-4);
        if(wild > 2) return false;
    }
    {
        wild += max(0,m['1']-Card[0]-2*Card[1]-Card[2]-Card[3]);
        if(wild > 2) return false;
    }
    {
        wild += max(0,m['0']-Card[0]);
        if(wild > 2) return false;
    }
    return true;
}

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

int main(){
    /*string s = "125953451110922645881164536115863939107817141=101*3221^12";
    cout << pqkable2(s) << endl;*/

    int t_start = time(NULL);
    int t_0 = time(NULL);

    int max_p_d = 4;
    maxn = power(10,max_p_d);
    prime_calculate();
    int p_list_size = prime.size();

    Bint lower_bound_of_search_range =
    //3*power(5,38,72);//1
    //97*power(2,114,72);//2
    //541*power(11,37,72);//3,4

    //power(2,112,72);//1
    power(3,37,72)*power(13,21,72);//2,3

    Bint upper_bound_of_search_range = power(10,72-10,100);
    vector<pair<Bint,string>> exp_list;
    for(int64_t p : prime){
        Bint p_i = p;
        for(int i = 2; i <= 240; i++){
            p_i *= p;
            if(p_i >= upper_bound_of_search_range) break;
            string s = to_string(p)+'^'+to_string(i);
            exp_list.push_back(make_pair(p_i,s));
        }
    }
    cout << "exp_list_calculated" << endl;
    sort(exp_list.begin(),exp_list.end());
    cout << "sorted" << endl;
    int e_list_size = exp_list.size();
    rep(i,p_list_size){
        //auto pr1 = exp_list[i];
        int64_t n1 = prime[i];
        string s1 = to_string(n1);
        //if(n1*n1 > upper_bound_of_search_range) break;
        for(int j = 0; j < e_list_size; j++){
            auto pr2 = exp_list[j];
            string s2 = pr2.second;
            Bint n2 = pr2.first;
            //int d = to_string_Bint(n1).size()+to_string_Bint(n2).size();
            //if(d < 37 && 62 < d) continue;
            Bint N = n1*n2;
            string N_str = to_string_Bint(N);
            if(N >= upper_bound_of_search_range) break;
            string S = N_str+"="+s1+"*"+s2;
            if(N >= lower_bound_of_search_range && pqkable2(S) <= 2) cout << N << "\n=" << s1 << "*" << s2 << endl;

            int t_1 = time(NULL);
            if(t_1 - t_0 >= 60){
                cout << "///" << t_1-t_start << ":" << s1 << "*" << s2 << endl;
                t_0 = t_1;
            }
        }
    }
    int t_end = time(NULL);
    cout << "///" << t_end-t_start << "[s]" << endl;
}