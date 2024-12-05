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

int main() {
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

        for(action s : a.fu) {
            s.print();
        }
        cout << endl;
    }
}
