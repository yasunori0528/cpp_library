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
//x^y,10^d未満, 0 <= x, 0 <= y, 大きすぎるものは-1を返す
int64_t power_small(int64_t x, int64_t y, int d){
    if(y < 0 || x < 0) return -1;
    if(x == 0) return 0;
    if(x == 1 || y == 0) return 1;
    int64_t rtn = 1;
    rep(i,y){
        rtn *= x;
        if(to_string(rtn).size() > d){
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

bool include_0_int(int64_t n){
    string s = to_string(n);
    int m = s.size();
    rep(i,m-1){
        if(s[i+1] == '0' && s[i] != '1'){
            return false;
        }
    }
    return true;
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
//'0'~'9', '^', '*', で構成された文字列を計算
int64_t calc_small(string s, int d){
    int n = s.size();
    int64_t rtn;
    
    rep(i,n){
        if(s[i] == '*'){
            int64_t x = calc_small(s.substr(0,i),d);
            int64_t y = calc_small(s.substr(i+1),d);
            if(x < 0 || y < 0) return -1;
            rtn = x*y;
            return rtn;
        }
    }
    rep(i,n){
        if(s[i] == '^'){
            int64_t x = calc_small(s.substr(0,i),d);
            int64_t y = calc_small(s.substr(i+1),d);
            rtn = power_small(x,y,d);
            return rtn;
        }
    }
    rtn = stoi(s);
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

int main(){
    int d = 7;

    maxn = 100000000;
    prime_calculate();
    vector<string> vec_operator = {"", "*", "^"};//演算子
    int64_t lower_bound_of_search_range = 2;
    //power(5,43,72);//3
    //power((Bint)2,122,72);//4

    //power((Bint)7,41,72)*953;//6
    //power((Bint)11,37,72)*541;//7
    //power((Bint)11,37,72)*power(2,9,72)*power(3,4,72);//8
    //power((Bint)201389,8,72)*power((Bint)3,8,72);//9
    

    int TIME = time(NULL);//開始時刻
    int time_count = 0;
    int time_interval = 60;

    int64_t upper_bound_of_search_range =
    98765432131211110;
    //power((Bint)201389,8,72)*power((Bint)3,8,72);//9
    vector<vector<pair<int64_t,string>>> exp_list(d+1,vector<pair<int64_t,string>>(0));
    rep(i,d+1){
        int64_t exp_pattern = power(2,i-1);//"^"の位置の個数
        int64_t num_pattern = power(10,i);
        unordered_set <string> calc_result;//計算結果が大きすぎる式の集合
        rep(j,exp_pattern){
            if(i == d && j == 0) j++;
            string s = "x";
            int64_t M = j;
            rep(k, i-1){
                s = "x" + vec_operator[M%2*2] + s;
                M /= 2;
            }
            //cout << s << endl;
            {
                int64_t tmin;
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
                tmin = calc_small(t,19);
                if(tmin < 0 || power(10,17-i) < tmin) continue;
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
                    int64_t exp_list_i_ = calc_small(t,19);
                    if(0 < exp_list_i_ && exp_list_i_ < power(10,17-i)) exp_list[i].push_back(make_pair(exp_list_i_,t));
                    else calc_result.insert(t);
                }
            }
        }
    }
    rep(i,d+1) sort(exp_list[i].begin(), exp_list[i].end());
    /*rep(i,d+1) {
        for(auto j : exp_list[i]){
            cout << "," << j.first << "," << j.second << "," << "\n";
        }
        cout << endl;
    }*/
    cout << "exp_list_calculated\n\n";

    vector<int> exp_list_size(d+1);
    rep(i,d+1) exp_list_size[i] = exp_list[i].size();
    //rep(i,d) cout << exp_list_size[i] << ",";
    //cout << endl;

    map<map<int,int>,vector<int64_t>> comb_cmp;

    for(int ii = 1; ii <= d; ii++){
        int64_t product_pattern = power(2,ii-1);//"*"の位置の個数

        for(int64_t i = 0; i < product_pattern; i++){
            string  s = "x";
            int64_t M = i;
            rep(j,ii-1){
                int M2 = M%2;
                s = "x" + vec_operator [M2] + s;
                M /= 2;
            }
            bool multi_monotonicity = true;
            int d0_1 = ii;
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
            rep(j,vec_d_size){
                loop_max[j] = exp_list_size[vec_d[j]];
            }
            vector<int> loop_now(vec_d_size,0);

            cout << "---";
            for(int j : vec_d) cout << j << ",";
            cout << "---\n";

            bool bool_calc = true;
            while(bool_calc){
                bool break1 = false;
                string t;
                int64_t calc_t = 1;

                rep(j,vec_d_size){
                    t += exp_list[vec_d[j]][loop_now[j]].second;
                    t += "*";
                    calc_t *= exp_list[vec_d[j]][loop_now[j]].first;
                }
                t.pop_back();

                if(lower_bound_of_search_range <= calc_t && calc_t < power(10,17-ii)){
                    map<int,int> comb;
                    string r = t;
                    
                    bool op_bool = false;
                    for(char c : to_string(calc_t)+t){
                        if(c != '*' && c != '^'){
                            comb[c-'0']++;
                        }
                        else op_bool = true;
                    }
                    if(op_bool) comb_cmp[comb].push_back(calc_t);
                }
                else if(power(10,17-ii) <= calc_t || calc_t < 0){
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
    
    /*for(auto comb : comb_cmp){
        if(comb.second.size() >= 2){
            vector<int64_t> comb1 = comb.second;
            vector<int64_t> comb2;
            for(int64_t n : comb1){
                if(CARD(n) > 0 && include_0_int(n)) comb2.push_back(n);
            }
            if(comb2.size() < 2) continue;

            sort(comb2.begin(),comb2.end());

            vector<string> out_put;
            int combsize = comb2.size();
            int cnt = 0;
            string pre_s_str = to_string(comb1[0]);
            rep(i,combsize){
                int64_t s = comb2[i];
                if(to_string(s).size() > pre_s_str.size()){
                    out_put.push_back(pre_s_str);
                    cnt++;
                }
                pre_s_str = to_string(s);
            }
            if(pre_s_str.size() > to_string(comb2[combsize-2]).size()){
                out_put.push_back(pre_s_str);
                cnt++;
            }
            if(pre_s_str.size() > 5) continue;

            //if(out_put[0].size() > 6) continue;
            if(cnt >= 2){
                for(string s : out_put){
                    cout << s << ",";
                }
                cout << endl;
            }
        }
    }*/

    map<int,int> comb_12345678910111213;
    string str_12345678910111213 = "12345678910111213";
    for(char c : str_12345678910111213){
        if(c != '*' && c != '^'){
            comb_12345678910111213[c-'0']++;
        }
    }
    vector<int64_t> comb_cmp_12345678910111213 = comb_cmp[comb_12345678910111213];
    for(int64_t p : comb_cmp_12345678910111213){
        cout << p << endl;
    }
    int Time_end = time(NULL);
    time_count += Time_end-TIME;
    cout << "time:" << time_count << "///" << endl;
}