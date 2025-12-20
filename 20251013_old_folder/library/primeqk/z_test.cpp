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

void print(multiset<int> S) {
	for (int i : S) cout << i << " ";
}

void eraseOne(multiset<int>& S, int x) {
	if (!S.count(x)) return;
	auto itr = S.lower_bound(x);
	S.erase(itr);
}

float score(multiset<int> S) {
	float rtn = 0;
	for (int i : S) {
		if (i < 10) {
			;
		} else if (i < 100) {
			rtn += log(2) ;
		} else if (i < 1000) {
			rtn += log(3);
		} else {
			assert(false);
		}
	}
	return rtn;
}

// 1,2,3,11,12,13 の multiset を 1,2,3,11,12,13,112,113 の multiset に変換する
multiset<int> f(multiset<int> S) {
	multiset<int> rtn = S;
	float maxScore = score(S);

	if (S.count(11) && S.count(2)) {
		multiset<int> T = S;
		eraseOne(T, 11);
		eraseOne(T, 2);
		T.insert(112);

		multiset<int> fT = f(T);
		float scoreFT = score(fT);
		if (chmax(maxScore, scoreFT)) rtn = fT;
	}
	if (S.count(11) && S.count(3)) {
		multiset<int> T = S;
		eraseOne(T, 11);
		eraseOne(T, 3);
		T.insert(113);

		multiset<int> fT = f(T);
		float scoreFT = score(fT);
		if (chmax(maxScore, scoreFT)) rtn = fT;
	}
	if (S.count(1) && S.count(2)) {
		multiset<int> T = S;
		eraseOne(T, 1);
		eraseOne(T, 2);
		T.insert(12);

		multiset<int> fT = f(T);
		float scoreFT = score(fT);
		if (chmax(maxScore, scoreFT)) rtn = fT;
	}
	if (S.count(1) && S.count(3)) {
		multiset<int> T = S;
		eraseOne(T, 1);
		eraseOne(T, 2);
		T.insert(12);

		multiset<int> fT = f(T);
		float scoreFT = score(fT);
		if (chmax(maxScore, scoreFT)) rtn = fT;
	}
	if (S.count(1) >= 2) {
		multiset<int> T = S;
		eraseOne(T, 1);
		eraseOne(T, 1);
		T.insert(11);

		multiset<int> fT = f(T);
		float scoreFT = score(fT);
		if (chmax(maxScore, scoreFT)) rtn = fT;
	}

	return rtn;
}

int main() {
	int64_t t_start = get_time_ns();

	// 123JQKX の組をグループ分けする
	// 1つの手札に対してジョーカーの値を2通り作る
	// "1112X" -> {11, 11, 12}(X = J), {112, 113}(X = K)

	map<vector<int>, vector<hand>> Grouping;

	{
		string s = "123JQK";
		vector<int> loop(6, 0);
		bool b = true;
		while(b) {
			hand h("X");
			multiset<int> a;
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < loop[i]; j++) {
					h.draw(s[i]);
					a.insert(char_to_int(s[i]));
				}
			}

			for (int x = 11; x <= 13; x++) {
				a.insert(x);
				multiset<int> c = f(a);
				// print(a);
				// cout << " -> ";
				// print(c);
				// cout << endl;
				vector<int> cVec;
				for (int ci : c) {
					cVec.push_back(ci);
				}
				Grouping[cVec].push_back(h);
				eraseOne(a, x);
			}

			b = false;
			for (int i = 0; i < 6; i++) {
				if (loop[i] < 4) {
					loop[i]++;
					for (int j = 0; j < i; j++) {
						loop[j] = 0;
					}
					b = true;
					break;
				}
			}
		}
	}

	// for (auto [v, H] : Grouping) {
	// 	for (int i : v) cout << i << " ";
	// 	cout << endl;
	// 	for (hand h : H) {
	// 		cout << "  ";
	// 		h.print();
	// 		cout << endl;
	// 	}
	// }

	cout << "Group Count : " << Grouping.size() << endl;
	cout << "Group Size Average : " << 15625.0*3 / Grouping.size() << endl;

	vector<pair<vector<int>, vector<int>>> needCheck;

	{
		for (auto& [v, h] : Grouping) {
			{
				int64_t tNow = get_time_ns();
				cout << (tNow - t_start) / 1e9 << "[s]:";
				
				for (int i : v) cout << " " << i;
				cout << endl;
			}

			string t = "456789T";
			vector<int> loop(7, 0);
			bool b = true;
			while(b) {
				vector<int> x;
				vector<int> a = v;
				for (int i = 0; i < 7; i++) {
					for (int j = 0; j < loop[i]; j++) {
						x.push_back(char_to_int(t[i]));
						a.push_back(char_to_int(t[i]));
					}
				}

				// for (int xi : x) cout << "  " << xi << " ";
				// cout << endl;

				int r = 0;
				for (int ai : a) {
					r += ai;
				}
				int countOdd = 0;
				for (int ai : a) {
					if (gcd(ai, 10) == 1) {
						countOdd++;
					}
				}

				if (r % 3 == 1) {
					bool existPrime = false;
					int n = a.size();

					if (countOdd) {
						for (int i = 0; i < 1000; i++) {
							do {
								shuffle(a.begin(), a.end(), engine);
							} while(gcd(a[n-1], 10) != 1);

							bigint p = 0;
							for (int ai : a) {
								if (ai < 10) p = p * 10 + ai;
								else if (ai < 100) p = p * 100 + ai;
								else if (ai < 1000) p = p * 1000 + ai;
								else assert(false);
							}
							if (miller_rabin(p)) {
								existPrime = true;
								break;
							}
						}
					}

					if (!existPrime) {
						needCheck.push_back({x, v});
						for (int xi : x) cout << xi << " ";
						cout << "| ";
						for (int vi : v) cout << vi << " ";
						cout << endl;
					}
				}

				b = false;
				for (int i = 0; i < 7; i++) {
					if (loop[i] < 4) {
						loop[i]++;
						for (int j = 0; j < i; j++) {
							loop[j] = 0;
						}
						b = true;
						break;
					}
				}
			}
		}
	}

	for (auto& [x, v] : needCheck) {
		for (hand h : Grouping[v]) {
			for (int i : x) {
				h.draw(i);
			}
			if (max_prime(h) < 1) {
				h.print();
			}
		}
	}

	int64_t t_end = get_time_ns();
	cout << fixed << setprecision(6);
	cout << (t_end - t_start) / 1e9 << "[s]" << endl;
}
