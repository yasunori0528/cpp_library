#include "../head.h"

random_device seed_gen;
mt19937 engine(seed_gen());

#include "../time.h"
#include "../math.h"
#include "../miller_rabin.h"
#include "../pollard_rho.h"
#include "../trial_divition.h"
#include "../card.h"
#include "../hand.h"
#include "../max_prime.h"
#include "../min_prime.h"
#include "../search_composite.h"

#define SKIP_MIN_PRIME 1
#define SKIP_SMALL_TEST 1

using ans_type = pair<bigint, bigint>;
string s;

void input(int n) {
	s.clear();
	for (int i = 0; i < n; i++) {
		s.push_back(ALPHABET[engine() % 27 / 2/* + 1*/]);
	}
}

void output_input() {
	cout << s << endl;
}

ans_type solve() {
	bigint ans_max = max_prime(hand(s));
	bigint ans_min;
#if not SKIP_MIN_PRIME
	ans_min = min_prime(hand(s));
#endif
	return { ans_max, ans_min };
}

ans_type simple_solve() {
	//cout << s << endl;
	string t;
	int cnt_x = 0;
	for (char c : s) {
		if (c == 'X') cnt_x++;
		else t.push_back(c);
	}

	vector<int> loop(cnt_x, 0);
	set<bigint> A;
	bool b = true;
	while (b) {
		string u = t;
		for (int i : loop) u.push_back(int_to_char(i));
		sort(u.begin(), u.end());

		do {
			if (u[0] == '0') continue;
			bigint p = str_to_int(u);
			A.insert(p);
		} while (next_permutation(u.begin(), u.end()));

		b = false;
		for (int i = 0; i < cnt_x; i++) {
			if (loop[i] < 13) {
				loop[i]++;
				for (int j = i - 1; j >= 0; j--) {
					loop[j] = loop[j + 1];
				}
				b = true;
				break;
			}
		}
	}

	bigint ans_max = 0;
	bigint ans_min = INF;

	{
		auto itr = A.rbegin();
		while (itr != A.rend()) {
			bigint p = *itr;
			if (miller_rabin(p)) {
				ans_max = p;
				break;
			}
			itr++;
		}
	}
	if (ans_max > 0) {
		auto itr = A.begin();
		while (itr != A.end()) {
			bigint p = *itr;
			if (miller_rabin(p)) {
				ans_min = p;
				break;
			}
			itr++;
		}
	}

	if (ans_min == INF) ans_min = 0;
	return { ans_max, ans_min };
}

void output(ans_type x) {
	auto [a, b] = x;
	cout << a << " " << b << endl;
}

void test() {
	input(5);
	ans_type ans = solve();
	ans_type ans_simple = simple_solve();

	cout << "input:    " << s << endl;
	cout << "output:   " << ans.first << endl;
	cout << "expected: " << ans_simple.first << endl;
}

void test_with_simple_solve() {
	for (int i = 0; i < 1024; i++) {
		input(engine() % 7 + 1);
		//output_input();
		ans_type ans = solve();
		ans_type ans_simple = simple_solve();
#if  SKIP_MIN_PRIME
		ans_simple.second = 0;
#endif

		if (ans != ans_simple) {
			cout << "input:" << endl;
			output_input();
			cout << "output:" << endl;
			output(ans);
			cout << "expected:" << endl;
			output(ans_simple);
		}
	}

	cout << "finish small test" << endl;
}

void calc_time_big_case(int n) {
	int m = 32;
	int64_t t_start = get_time_ns();
	for (int i = 0; i < m; i++) {
		input(n);
		ans_type ans = solve();
	}
	int64_t t_end = get_time_ns();

	cout << "n = " << n << ", " << (t_end - t_start) / 1e9 / m << "[s/case]" << endl;
}

int main() {
	cout << fixed << setprecision(6);
	test();
#if not SKIP_SMALL_TEST
	test_with_simple_solve();
#endif
	calc_time_big_case(80);
	calc_time_big_case(80);
	calc_time_big_case(80);
	calc_time_big_case(80);
	calc_time_big_case(80);
	calc_time_big_case(80);
	calc_time_big_case(80);
	calc_time_big_case(80);
}
//O(n^3)
//test : O(n!*n)
