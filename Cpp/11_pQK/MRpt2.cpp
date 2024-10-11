#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;

Bint str_int_bint(string s){
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

Bint powermod(Bint x, Bint y, Bint p){
    if(y < 0) return 0;
    if(y == 0) return 1;
    else{
        Bint n = powermod(x,y/2,p);
        n = n*n%p;
        if(y%2 == 1) n = n*x%p;
        return n;
    }
}

bool MRpt(Bint n){
    if(n <= 1) return 0;
    if(n == 2) return 1;
    if(n%2 == 0) return 0;
    Bint s = 0;
    Bint d = n-1;
    while(d%2 == 0){
        d /= 2;
        s++;
    }
    //cout << n-1 << "= 2^" << s << "*" << d << endl;

    int k = 100;
    rep(looop,k){
        Bint a = rand()%(n-2)+1;
        Bint powmod_a_d_n = powermod(a,d,n);
        if(powmod_a_d_n == 1){
            //cout << n << "," << a << endl;
            continue;
        }
        bool bk = false;
        rep(i,s){
            if(powmod_a_d_n == n-1){
                //cout << n << "," << a << "," << i << endl;
                bk = true;
                break;
            }
            powmod_a_d_n = powmod_a_d_n*powmod_a_d_n%n;
        }
        if(bk) continue;
        return 0;
    }
    return 1;
}

/*bool pqkable_(string s){
    vector<int> vec(14,4);
    vec[0] = 2;
    int n = s.size();
    string t;
    rep(i,n){
        char c = s[i];
        bool b = true;
        if(i < n-1 && c == 1){
            char d = s[i+1];
            if(0 <= d && d <= 3) b = false;
        }

        t.push_back(c);
        if(b) t.push_back(',');
    }

    vector<string> vec2(1);
    for(char c : t){
        if('0' <= c && c <= '9'){
            vec2[vec2.size()-1] += c;
        }
        else vec2.push_back("");
    }

    for(string st : vec2){
        if(st.size() == 1){
            ;
        }
    }
    
}*/

int main(){
    int time_start = time(NULL);
    int time_ = time_start;
    srand(time(NULL));

    vector<char> Card = {'T','J','Q','K','X'};
    //d : 枚数
    for(int d = 9; d <= 9; d++){
        int64_t pow_4_d = power(4,d);
        map<map<char,int>,string> prime_list;
        for(int64_t i = pow_4_d-1; i >= 0; i--){
            string s;
            int64_t m = i;
            map<char,int> comb;
            for(char c : Card){
                comb[c];
            }
            rep(j,d){
                char c = Card[m%4];
                s = c+s;
                comb[c]++;
                m /= 4;
            }
            s = '9'+s;
            int cntX = 0;
            for(auto &p : comb){
                cntX += max(0,p.second-4);
                p.second = min(4,p.second);
            }

            int time_now = time(NULL);
            if(time_now-time_ >= 60){
                time_ = time_now;
                cout << "---" << time_now-time_start << ":" << s << "---" << endl;
            }

            if(cntX > 2) continue;
            comb['X'] = cntX;
            if(prime_list.count(comb)) continue;

            Bint n = str_int_bint(s);
            if(MRpt(n)){
                prime_list[comb] = s;
            }
        }

        vector<pair<Bint,string>> pl_d;
        for(pair<map<char,int>,string> p : prime_list){
            if(p.first['X'] == 1){
                bool b = false;
                rep(i,4){
                    if(p.first[Card[i]] == 4) continue;
                    map<char,int> p_i = p.first;
                    p_i['X'] = 0;
                    p_i[Card[i]]++;
                    if(prime_list.count(p_i) && str_int_bint(prime_list[p_i]) >= str_int_bint(p.second)){
                        b = true;
                        break;
                    }
                }
                if(b) continue;
            }
            else if(p.first['X'] == 2){
                bool b = false;
                rep(i,5){
                    rep(j,5){
                        if(i == 4 && j == 4) continue;
                        map<char,int> p_ij = p.first;
                        p_ij['X'] = 0;
                        p_ij[Card[i]]++;
                        p_ij[Card[j]]++;
                        if(p_ij[Card[i]] > 4) continue;
                        if(p_ij[Card[j]] > 4) continue;
                        if(prime_list.count(p_ij) && str_int_bint(prime_list[p_ij]) >= str_int_bint(p.second)){
                            b = true;
                            break;
                        }
                    }
                    if(b) break;
                }
                if(b) continue;
            }
            /*for(auto q : p.first){
                cout << q.first << ":" << q.second << ",";
            }*/
            //cout << p.second << endl;
            pl_d.push_back(make_pair(str_int_bint(p.second),p.second));
        }
        sort(pl_d.begin(),pl_d.end());
        reverse(pl_d.begin(), pl_d.end());
        cout << d << endl;
        for(auto p : pl_d){
            cout << p.second << endl;
        }
        cout << "time : " << time(NULL)-time_start << endl;
        cout << endl;
    }
    cout << "time : " << time(NULL)-time_start << endl;
}