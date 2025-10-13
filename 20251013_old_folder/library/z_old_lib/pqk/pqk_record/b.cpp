#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

#include "../pqk_lib/pqk_all.cpp"

int main() {
    int n = 1000;
    vector<string> V(n);
    for(auto &s : V) cin >> s;

    map<string, int> A;
    for(auto &s : V) {
        A[s]++;
    }

    vector<tuple<int,int,bigint,string>> W;
    for(auto &[s, cnt] : A) {
        int a = s.size();
        W.push_back({-cnt, a, str_to_int(s), s});
    }

    sort(W.begin(), W.end());
    for(auto &[cnt, a, x, s] : W) {
        cout << -cnt << "," << a << "," << x << "," << s << endl;
    }
}
