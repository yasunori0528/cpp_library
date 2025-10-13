#include <bits/stdc++.h>
using namespace std;

int64_t get_time() {
    struct::timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * int64_t(1'000'000'000) + t.tv_nsec;
}

int main() {
    int64_t mod; cin >> mod;
    int64_t sz = 1000;
    int64_t a = mod / sz;

    int64_t t_start = get_time();

    vector<int64_t> V;
    int64_t x = 1;
    for(int64_t i = 0; i < mod; i++) {
        if(i > 0) x = x * i % mod;
        if(i % a == 0) V.push_back(x);
    }

    //a = a;
    //factorial_a = {1, ...};
    cout << "a = " << a << ";" << endl;
    cout << "factorial_a = {";
    for(size_t i = 0; i < V.size(); i++) {
        if(i) cout << ",";
        cout << V[i];
    }
    cout << "};" << endl;

    int64_t t_end = get_time();
    cout << "//" << (t_end - t_start) / 1e9 << "[s]" << endl;
}
