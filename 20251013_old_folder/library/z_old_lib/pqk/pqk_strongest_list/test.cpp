#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

#include "../pqk_lib/pqk_all.cpp"
#include "game_judge.cpp"

int main() {
    int n = 11;
    state st;
    st.build();
    st.game_start(n);

    st.print();
    while(st.get_t() >= 0) {
        string s; cin >> s;
        st.play(s);
        st.print();
        cout << string(32, '-') << endl;
    }
}
