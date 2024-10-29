#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

#include "../pqk_lib/pqk_all.cpp"

vector<string> listup_natural(int n, int m) {
    assert(n <= m && m <= n*2);
    int a = n * 2 - m;
    int b = m - n;

    vector<string> rtn;
    vector<int> loop1(a, 0);
    bool b1 = true;
    while(b1) {
        vector<int> loop2(b, 10);
        bool b2 = true;
        while(b2) {
            string s;
            for(int x : loop1) s.push_back(alphabet[x]);
            for(int x : loop2) s.push_back(alphabet[x]);
            sort(s.begin(), s.end());

            do{
                if(s[0] == '0') continue;
                rtn.push_back(s);
            }while(next_permutation(s.begin(), s.end()));

            b2 = false;
            for(int i = 0; i < b; i++) {
                if(loop2[i] < 13) {
                    loop2[i]++;
                    for(int j = i - 1; j >= 0; j--) {
                        loop2[j] = loop2[j + 1];
                    }
                    b2 = true;
                    break;
                }
            }
        }
        b1 = false;
        for(int i = 0; i < a; i++) {
            if(loop1[i] < 9) {
                loop1[i]++;
                for(int j = i - 1; j >= 0; j--) {
                    loop1[j] = loop1[j + 1];
                }
                b1 = true;
                break;
            }
        }
    }

    return rtn;
}

//x = [0-9+*=]*
pair<int,int> num_card_bound(string x) {
    int r = 0;
    for(char c : x) {
        if('0' <= c && c <= '9') r++;
    }
    int l = r - max_num_of_face(x);
    return {l, r};
}

//xをn枚出しする方法を全列挙 (x = [0-9+*=]*)
vector<string> way_to_use(string x, int n) {
    vector<string> rtn;
    auto[l, r] = num_card_bound(x);
    if(n < l || r < n) return rtn;

    vector<int> f;
    for(int i = 0; i < (int)x.size() - 1; i++) {
        if(x[i] == '1' && '0' <= x[i+1] && x[i+1] <= '3') f.push_back(i);
    }
    int m = f.size();

    //n-l個絵札にする
    if(m < r - n) return rtn;
    
    vector<int> loop(m, 0);
    for(int i = m - (r - n); i < m; i++) loop[i] = 1;

    do {
        string y = x;
        bool b = true;
        for(int i = 0; i < m; i++) {
            if(loop[i]) {
                if(y[f[i]] != '1') {
                    b = false;
                    break;
                }
                y[f[i]] = '_';
                y[f[i]+1] = alphabet[y[f[i]+1]-'0'+10];
            }
        }
        if(b) {
            string z;
            for(char c : y) {
                if(c == '_') continue;
                z.push_back(c);
            }
            rtn.push_back(z);
        }
    }while(next_permutation(loop.begin(), loop.end()));
    return rtn;
}

bool is_op(char c) {
    return c == '*' || c == '^' || c == '=';
}

string str_to_comb(string s) {
    string rtn;
    for(char c : s) {
        if(is_op(c)) continue;
        rtn.push_back(c);
    }
    sort(rtn.begin(), rtn.end());
    return rtn;
}

bigint flu_sub(vector<int> B) {
    if(B[14] > 2) return 0;

    bigint rtn = 1;
    for(int i = 1; i <= 13; i++) {
        if(B[i] == 1) rtn *= 4;
        if(B[i] == 2) rtn *= 6;
        if(B[i] == 3) rtn *= 4;
    }
    if(B[14] == 1) rtn *= 2;

    return rtn;
}

bigint flu(string s) {
    vector<int> B(15, 0);
    for(char c : s) {
        if(is_op(c)) continue;
        B[char_to_int(c)]++;
    }
    B[14] += B[0];
    B[0] = 0;
    for(int i = 1; i <= 13; i++) {
        int x = max(0, B[i] - 4);
        B[i] -= x;
        B[0] += x;
    }
    
    if(B[14] > 2) return 0;

    bigint rtn = 0;
    rtn += flu_sub(B);
    for(int i = 1; i <= 13; i++) {
        if(B[i] == 0) continue;
        B[i]--;
        B[14]++;
        rtn += flu_sub(B);
        for(int j = i; j <= 13; j++) {
            if(B[j] == 0) continue;
            B[j]--;
            B[14]++;
            rtn += flu_sub(B);
            B[j]++;
            B[14]--;
        }
        B[i]++;
        B[14]--;
    }

    return rtn;
}

void test() {
    while(1) {
        string x;
        int n;
        cin >> x >> n;
        vector<string> V = way_to_use(x, n);
        cout << V.size() << endl;
        for(string s : V) cout << s << endl;
        cout << endl;
    }
}

void test2() {
    int n; cin >> n;
    vector<string> V(n);
    for(auto &s : V) cin >> s;
    vector<string> W;
    for(auto s : V) {
        vector<string> A = way_to_use(s, 9);
        for(auto t : A) W.push_back(t);
    }

    for(auto s : W) {
        cout << s << ",";
    }
    cout << endl;
}

int main() {
    test2(); return 0;
    set<bigint> S;
    vector<tuple<int,int,int>> A = {
        {5, 4, 5},
        {6, 3, 6},
        {7, 4, 7},
        {8, 5, 6}
    };

    for(auto [x, y, z] : A) {
        for(int i = y; i <= z; i++) {
            //cout << i << " " << x << endl;
            vector<string> V = listup_natural(i, x);
            for(string s : V) {
                S.insert(str_to_int(s));
            }
        }
    }

    set<bigint> T;
    for(auto x : S) {
        auto [lp, rp] = num_card_bound(int_to_str(x));
        auto [ln, rn] = num_card_bound(int_to_str(x * 2));
        //[lp+ln, rp+rn] && [10, 11] != empty
        if(max(lp+ln, 10) > min(rp+rn, 11)) continue;
        if(miller_rabin(x)) T.insert(x);
        //if(gcd((bigint(x % 30030)).get_ui(), 30030) == 1) T.insert(x);
    }

    /*cout << T.size() << endl;
    for(bigint x : T) {
        cout << x << endl;
    }*/

    map<string, vector<string>> D;
    for(bigint x : T) {
        string s = int_to_str(x * 2) + "=2*" + int_to_str(x);
        for(int i = 11; i <= 12; i++) {
            vector<string> V = way_to_use(s, i);
            for(string t : V) D[str_to_comb(t)].push_back(t);
        }
    }

    bigint a11 = 0;
    bigint a12 = 0;
    vector<tuple<bigint,string,string>> E;
    for(auto [hand, ans] : D) {
        bigint a = flu(hand);
        if(hand.size() == 11) {
            a11 += a;
            a *= 43;
        }
        else {
            a12 += a;
            a *= 12;
        }
        string max_s;
        bigint max_n = 0;
        for(string s : ans) {
            string t;
            for(char c : s) {
                if(is_op(c)) break;
                t.push_back(c);
            }
            if(chmax(max_n, str_to_int(t))) max_s = s;
        }
        E.push_back({a, hand, max_s});
    }
    sort(E.begin(), E.end());
    reverse(E.begin(), E.end());

    for(auto [fl, hand, s] : E) {
        if(fl > 0) cout << fl << " " << hand << " " << s << endl;
    }

    cout << a11 << " " << a12 << endl;
}
