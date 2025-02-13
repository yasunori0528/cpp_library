#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

random_device seed_gen;
mt19937 engine(seed_gen());

#include "../time.cpp"
#include "../math.cpp"
#include "../miller_rabin.cpp"
#include "../pollard_rho.cpp"
#include "../trial_divition.cpp"
#include "../card.cpp"
#include "../hand.cpp"
#include "../max_prime.cpp"
#include "../min_prime.cpp"
#include "../search_composite.cpp"
#include "../sufu.cpp"

void test_action() {
    string s; cin >> s;
    action a(s);
    a.print();
}

void f(vector<sufu> &A) {
    map<string,vector<int>> mp;
    for(sufu &a : A) for(action &b : a.fu) mp[b.n] = vector<int>(13, 0);

    for(sufu &a : A) {
        int len = a.fu.size() - 2;
        //a.fu[0].print();
        for(int i = 0; i < len; i++) {
            action &b = a.fu[i+2];
            //b.print();
            if(b.w == "W") {
                //b.print();
                
                for(string pl : a.player) {
                    if(pl == b.n) {
                        if(b.k == "C") {
                            mp[pl][0]++;
                            mp[pl][1] += len;
                        }
                        else {
                            mp[pl][2]++;
                            mp[pl][3] += len;
                        }
                    }
                    else {
                        mp[pl][4]++;
                        mp[pl][5] += len;
                    }
                }
            }
            
            //cout << b.k << "," << b.b << endl;
            if(b.k == "C" && b.b == "T") mp[b.n][6]++;
            else if(b.k == "P" && b.b == "T") mp[b.n][7]++;
            else if(b.k == "IN") mp[b.n][8]++;
            else if(b.k == "GC") mp[b.n][9]++;
            else if(b.k == "C" || b.k == "P") mp[b.n][10]++;
            else if(b.k == "%") mp[b.n][11]++;
            else if(b.k == "%%") mp[b.n][12]++;
            else {
                b.print();
                assert(false);
            }
        }
    }

    for(auto [pl, v] : mp) {
        cout << pl;
        for(int i : v) {
            cout << "," << i;
        }
        cout << endl;
    }
}

bigint assign(string s) {
    string x;
    while(1) {
        if(s.size()-4 >= 0 && s[s.size()-4] == '|') {
            x.push_back(s[s.size()-1]);
            for(int i = 0; i < 4; i++) s.pop_back();
        }
        else break;
    }
    reverse(x.begin(), x.end());

    int n = s.size();
    int m = x.size();
    int i = 0;
    int j = 0;
    while(i < n && j < m) {
        if(s[i] == 'X') {
            s[i] = x[j];
            i++;
            j++;
        }
        else i++;
    }

    for(int k = 0; k < (int)s.size(); k++) {
        if(s[k] == 'A') s[k] = '1';
        if(s[k] == '=') {
            s = s.substr(0, k);
            break;
        }
    }
    //cout << s << endl;
    return str_to_int(s);
}

void test_assign() {
    string s; cin >> s;
    cout << assign(s) << endl;
}

void g(vector<sufu> &A) {
    map<bigint,int> C, P;
    for(sufu a : A) {
        //cout << "(" << a.fu[0].d << ")" << endl;
        for(action b : a.fu) {
            if(b.k == "C" && b.b == "T") {
                C[assign(b.a)]++;
            }
            else if(b.b == "T") {
                P[assign(b.a)]++;
            }
        }
    }

    vector<pair<int,bigint>> CC, PP;
    for(auto [s, k] : C) {
        CC.push_back({k, s});
    }
    for(auto [s, k] : P) {
        PP.push_back({k, s});
    }
    sort(CC.begin(), CC.end());
    reverse(CC.begin(), CC.end());
    sort(PP.begin(), PP.end());
    reverse(PP.begin(), PP.end());

    for(auto [k, s] : CC) cout << k << " " << s << endl;
    for(auto [k, s] : PP) cout << k << " " << s << endl;
}

int main() {
    //test_action();
    //test_assign();

    int n; cin >> n;
    vector<string> V(n);
    for(auto &s : V) cin >> s;

    vector<string> temp;
    vector<sufu> A;
    for(int i = 0; i < n; i++) {
        string s = V[i];
        temp.push_back(s);
        if(s[s.size()-1] == '#') {
            A.push_back(sufu(temp));
            temp.clear();
        }
    }

    for(sufu &a : A) {
        a.build();
    }

    //f(A);
    g(A);
}
