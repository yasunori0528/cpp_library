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

int bigint_to_int(bigint x){
    //cout << "-L" << endl;
    //cout << x << " ";
    int sz = 31;
    vector<int> v;
    for(int i = 0; i < sz; i++){
        if(x % 2 == 0) v.push_back(0);
        else v.push_back(1);
        x /= 2;
    }

    int rtn = 0;
    for(int i = sz - 1; i >= 0; i--) rtn = rtn * 2 + v[i];
    //cout << rtn << endl;
    //for(auto i : v) cout << i << " ";
    //cout << endl;
    //cout << "-R" << endl;
    return rtn;
}

string bigint_to_string(bigint x){
    string s;
    while(x > 0){
        s.push_back('0' + bigint_to_int(x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

vector<int> int_to_comb(bigint x){
    //cout << x << " :";
    vector<int> rtn(18, 0);
    int temp = 0;//temp = 0, 1 or 11
    string s = bigint_to_string(x);
    for(char c : s){
        //cout << "L" << endl;
        int r = c - '0';
        x /= 10;
        if(r == 1){
            if(temp == 11){
                rtn[temp]++;
                temp = 1;
            }
            else temp = temp * 10 + 1;
        }
        else if(r < 4){
            temp = temp * 10 + r;
            if(temp < 14) rtn[temp]++;
            else{
                //110 : 14, ... , 113 : 17
                rtn[temp - 96]++;
            }
            temp = 0;
        }
        else{
            if(temp > 0) rtn[temp]++;
            rtn[r]++;
            temp = 0;
        }
        //cout << "R" << endl;
    }
    //for(auto i : rtn) cout << " " << i;
    //cout << endl;
    
    return rtn;
}

void f1(){
    //C = 7 * NM
    //7 * M は繰り上がらない
    vector<string> V;
    for(int d = 1; d <= 3; d++){
        vector<int> loop(d, 1);
        bool b = true;
        while(b){
            string s;
            for(int i = 0; i < d; i++) s.push_back(alphabet[loop[i]]);
            bigint n = str_to_int(s);
            if(n % 7 == 0) V.push_back(s);
            b = false;
            for(int i = 0; i < d; i++){
                if(loop[i] < 13){
                    loop[i]++;
                    for(int j = 0; j < i; j++) loop[j] = 1;
                    b = true;
                    break;
                }
            }
        }
    }

    vector<tuple<int,int,string,string,bigint,bigint,bigint,vector<int>>> output_list;
    for(string s : V){
        for(string t : V){
            bigint n = str_to_int(s + t);
            bigint p = n / 7;
            if(miller_rabin(p)){
                vector<int> nc = int_to_comb(n);
                vector<int> pc = int_to_comb(p);
                vector<int> comb(18);
                for(int i = 0; i < 18; i++) comb[i] = nc[i] + pc[i];
                bool b = true;
                for(int i = 0; i < 18; i++){
                    if(i == 0 && comb[i] > 0) b = false;
                    if(comb[i] > 4) b = false;
                }
                if(b) output_list.push_back({num_card(n), num_card(p), s, t, str_to_int(s), str_to_int(t), p, comb});
            }
        }
    }

    sort(output_list.begin(), output_list.end());
    int sz = output_list.size();
    cout << sz << endl;
    for(int i = 0; i < sz; i++){
        auto[nn, np, s, t, ss, tt, p, c] = output_list[i];
        cout << nn << " " << np << " " << s << " " << t << " " << ss << " " << tt << " " << p;
        for(auto j : c) cout << " " << j;
        cout << endl;
    }
}

void f2(){
    int N; cin >> N;
    vector<pair<string, string>> V(N);
    for(auto &[s, t] : V) cin >> s >> t;

    for(auto[s, t] : V){
        bigint n = str_to_int(s + t);
        bigint p = n / 7;
        vector<int> nc = int_to_comb(n);
        vector<int> pc = int_to_comb(p);
        vector<int> comb(18);
        for(int i = 0; i < 18; i++) comb[i] = nc[i] + pc[i];
    }
}

int main(){
    f1();
}
