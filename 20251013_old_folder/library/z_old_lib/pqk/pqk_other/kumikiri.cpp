#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

#include "../pqk_lib/pqk_all.cpp"

bool is_op(char c) {
    return c == '*' || c == '^' || c == '=';
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

vector<int> A = {
    0, 4, 4, 4, 4,
    4, 4, 4, 4, 4,
    4, 4, 4, 4, 2
};

bool next_hand(vector<int> &v) {
    int cnt = 0;
    for(int i = 14; i > 0; i--) {
        if(cnt >= 1 && v[i] < A[i]) {
            v[i]++;
            int x = cnt-1;
            int j = 14;
            while(j > i) {
                int y = min(A[j], x);
                v[j] = y;
                x -= y;
                j--;
            }
            return true;
        }
        cnt += v[i];
    }
    return false;
}

vector<pair<bigint,string>> hand_list(int n) {
    vector<int> v(15, 0);
    {
        int x = n;
        int i = 14;
        while(x) {
            int y = min(A[i], x);
            v[i] = y;
            x -= y;
            i--;
        }
    }

    vector<pair<bigint,string>> X;
    do{
        string s;
        for(int i = 0; i <= 14; i++) {
            for(int j = 0; j < v[i]; j++) {
                s.push_back(alphabet[i]);
            }
        }
        bigint a = flu_sub(v);
        if(a > 0) X.push_back({a, s});
        if(engine()%10000 == 10001) cout << a << " " << s << endl;
    }while(next_hand(v));

    sort(X.begin(), X.end());
    reverse(X.begin(), X.end());
    return X;
}

bool easy_test(bigint x) {
    return gcd(bigint(x%9699690).get_ui(), 9699690) == 1;
}

vector<int> result_dictionary(4000, -1);
bool in(string x, string y) {
    vector<int> Bx(15, 0);
    for(char c : x) Bx[char_to_int(c)]++;
    vector<int> By(15, 0);
    for(char c : y) By[char_to_int(c)]++;
    for(int i = 1; i <= 13; i++) {
        int z = max(0, Bx[i]-By[i]);
        Bx[i] -= z;
        Bx[14] += z;
    }

    if(Bx[14] > By[14]) return false;

    string s;
    int a = 0;
    for(int i = 1; i <= 14; i++) {
        int z = By[i] - Bx[i];
        for(int j = 0; j < z; j++) {
            s.push_back(alphabet[i]);
            a = a * 15 + i;
        }
    }

    if(s.size() == 0) return true;
    if(result_dictionary[a] != -1) return result_dictionary[a];

    int rtn;
    if(s == "224" || s == "25T" || s == "339" || s == "357") rtn = true;
    s = max_number(s, miller_rabin);
    rtn = (s[0] != '-');
    result_dictionary[a] = rtn;
    return rtn;
}

string f(vector<pair<bigint,string>> &V, vector<tuple<bigint,bigint,string>> &W) {
    int n = W.size();
    bigint best = 0;
    bigint best_b;
    int id = 0;
    string s;
    bigint a_max = V[0].first;
    bigint b_max = get<0>(W[0]);
    for(int i = 0; i < n; i++) {
        auto &[b, ignore, x] = W[i];
        if(b * 2 < b_max) break;
        bigint temp = 0;
        for(int j = 0; j < (int)V.size(); j++) {
            auto [a, y] = V[j];
            if(a * 128 < a_max) {
                //if(i == 0) cout << "j : " << j << endl;
                break;
            }
            if(in(x, y)) {
                temp += a;
                //cout << x << " " << a << " " << y << endl;
            }
        }
        bigint old_b = b;
        b = temp;
        if(chmax(best, temp)) {
            best_b = old_b;
            s = x;
            id = i;
        }
    }

    //cout << "b_max / b_best = " << b_max << " / " << best_b << endl;

    if(best == 0) return "-1";

    for(auto &[a, y] : V) {
        if(in(s, y)) a = 0;
    }
    sort(V.begin(), V.end());
    reverse(V.begin(), V.end());
    while(V.size() && (V.rbegin()->first) == 0) {
        V.pop_back();
    }
    
    swap(W[id], W[n-1]);
    W.pop_back();
    sort(W.begin(), W.end());
    reverse(W.begin(), W.end());
    
    return s;
}

int main() {
    int n; cin >> n;
    int m; cin >> m;
    int k; cin >> k;
    vector<pair<bigint,string>> V = hand_list(n);
    vector<tuple<bigint,bigint,string>> W;
    {   
        A[14] = 0;
        vector<pair<bigint,string>> X = hand_list(m);
        vector<tuple<bigint,bigint,string>> Y;
        for(auto[a, s] : X) {
            //cout << s << endl;
            vector<string> v;
            for(char c : s) v.push_back(string(1, c));
            string p = max_number(s, easy_test);
            if(p[0] == '-') continue;
            Y.push_back({a, str_to_int(p), p});
        }
        sort(Y.begin(), Y.end());
        reverse(Y.begin(), Y.end());
        
        for(auto [a, b, p] : Y) {
            //cout << a << " " << p << endl;
            W.push_back({0, b, p});
        }

        //cout << X.size() << " " << W.size() << endl;
    }

    //while(V.size() > 100000) V.pop_back();
    //while(W.size() > 100000) W.pop_back();

    for(int i = 0; i < k && V.size() && W.size(); i++) {
        string s = f(V, W);
        s = max_number(s, miller_rabin);
        if(s[0] == '-') break;
        cout << s << "," << endl;
    }
}
