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
#include "search_composite.cpp"

int main() {
	int64_t t_start = get_time_ns();

	int n = 246;
	vector<pair<string,string>> v(n);
	for (auto& [s, t] : v) {
		cin >> s >> t;
	}

	for (auto& [s, t] : v) {
		bigint ans = max_prime(hand(s));
		bigint b = str_to_int(t);
		cout << ans << endl;
		// if (ans < 2 && b < 2) continue;
		// if (ans == b) continue;
		// cout << ans << " " << b << endl;
	}

	int64_t t_end = get_time_ns();
	cout << fixed << setprecision(6);
	cout << (t_end - t_start) / 1e9 << "[s]" << endl;
}
