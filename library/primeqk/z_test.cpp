#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

random_device seed_gen;
mt19937 engine(seed_gen());

#include "time.cpp"
#include "math.cpp"
#include "miller_rabin.cpp"
//#include "pollard_rho.cpp"
//#include "trial_divition.cpp"
#include "card.cpp"
#include "hand.cpp"
#include "max_prime.cpp"
#include "min_prime.cpp"

int main() {
    string s; cin >> s;
    int64_t t_start = get_time();

    cout << max_prime(hand(s)) << endl;
    cout << min_prime(hand(s)) << endl;

    int64_t t_end = get_time();
    cout << fixed << setprecision(6);
    cout << (t_end - t_start) / 1'000'000'000.0 << "[s]" << endl;
}
