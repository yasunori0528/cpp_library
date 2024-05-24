#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

#include "pqk_lib/pqk_all.cpp"

int num_card(bigint x){
    if(x < 10) return 1;
    bigint d2 = x % 100;
    if(10 <= d2  && d2 <= 13) return num_card(x / 100) + 1;
    return num_card(x / 10) + 1;
}

void f1(){
    vector<tuple<int,int64_t,int64_t>> V;
    for(int i = 1; i < 100000000; i++){
        string s = "4856" + to_string(i);
        int64_t p = stoll(s);
        int64_t n = p * 2;
        string t = to_string(n);
        if(miller_rabin(p)){
            V.push_back({num_card(n), p, n});
        }
    }

    cout << V.size() << endl;
    for(auto[d, p, n] : V){
        cout << p << " " << n << endl;
    }
}

void f2(){
    int N; cin >> N;
    vector<tuple<int,int64_t,int64_t>> V(N);
    for(auto &[d, p, n] : V) cin >> d >> p >> n;

    vector<tuple<int,int64_t,int64_t>> W;
    for(auto [d, p, n] : V){
        map<string,int> mp;
        mp["2"]++;
        string s = to_string(p);
        string t = to_string(n);
        string temp;
        for(char c : s){
            if(c == '1') temp.push_back(c);
            else{
                if(c <= '3'){
                    temp.push_back(c);
                    mp[temp]++;
                    temp.clear();
                }
                else{
                    if(temp.size()){
                        mp[temp]++;
                        temp.clear();
                    }
                    mp[string(1, c)]++;
                }
            }
        }
        if(temp.size()){
            mp[temp]++;
            temp.clear();
        }
        for(char c : t){
            if(c == '1') temp.push_back(c);
            else{
                if(c <= '3'){
                    temp.push_back(c);
                    mp[temp]++;
                    temp.clear();
                }
                else{
                    if(temp.size()){
                        mp[temp]++;
                        temp.clear();
                    }
                    mp[string(1, c)]++;
                }
            }
        }
        if(temp.size()){
            mp[temp]++;
            temp.clear();
        }

        bool b = true;
        for(auto[k, v] : mp){
            if(v >= 4) b = false;
            if(k == "0" && v >= 1) b = false;
            //if(k == "2" && v >= 2) b = false;
        }

        /*cout << s << endl;
        cout << t << endl;
        for(auto [k, v] : mp){
            cout << k << " " << v << endl;
        }
        cout << endl;*/

        if(b) W.push_back({d, p, n});
    }

    sort(W.begin(), W.end());
    cout << W.size() << endl;
    for(auto[d, p, n] : W){
        cout << d << " " << p << " " << n << endl;
    }
}

int main(){
    f1();
}
