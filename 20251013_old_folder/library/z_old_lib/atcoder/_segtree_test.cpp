#include <bits/stdc++.h>
using namespace std;
#include "segtree.cpp"

random_device seed_gen;
mt19937 engine(seed_gen());

int64_t get_time(){
    struct::timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * int64_t(1'000'000'000) + t.tv_nsec;
}

using value_type = int64_t;
using ans_type = vector<value_type>;

int n, m;
vector<value_type> A;
vector<tuple<int,int,int,value_type>> V;

value_type id;

void init_id() {
    id = 0;
}

value_type f(value_type x, value_type y) {
    return x + y;
}

value_type rand_value() {
    return engine() & 0x3FF;
}

void output_value(value_type x) {
    cout << x;
}

void input() {
    //n = engine() % 100000 + 1;
    //m = engine() % 100000 + 1;
    A.resize(n);
    for(auto &a : A) {
        a = rand_value();
    }
    V.resize(m);
    for(auto &[x, y, z, w] : V) {
        x = engine() % 2;
        if(x == 0) {
            y = engine() % n;
            w = rand_value();
        }
        else {
            y = engine() % n;
            z = engine() % n;
            if(y > z) swap(y, z);
            z++;
        }
    }
}

void output_input() {
    cout << n << " " << m << endl;
    for(auto a : A) cout << a << " ";
    cout << endl;
    for(auto [x, y, z, w] : V) {
        if(x == 0) {
            cout << x << " " << y << " ";
            output_value(w);
            cout << endl;
        }
        else {
            cout << x << " " << y << " " << z << endl;
        }
    }
}

void output(ans_type ans) {
    for(auto x : ans) {
        output_value(x);
        cout << endl;
    }
}

ans_type solve() {
    segtree<value_type> S(n, f, id);
    S.build(A);
    vector<value_type> ans;
    for(auto [x, y, z, w] : V) {
        if(x == 0) {
            S[y] = w;
        }
        else {
            auto a = S.query(y, z);
            ans.push_back(a);
        }
    }
    return ans;
}

ans_type solve_simple() {
    vector<value_type> S = A;
    vector<value_type> ans;
    for(auto [x, y, z, w] : V) {
        if(x == 0) {
            S[y] = w;
        }
        else {
            value_type a = id;
            for(int i = y; i < z; i++) {
                a = f(a, S[i]);
            }
            ans.push_back(a);
        }
    }
    return ans;
}

int main() {
    int check_with_simple_solution;
    int calc_time;
    int num_of_testcase;

    cin >> check_with_simple_solution;
    calc_time = !check_with_simple_solution;
    cin >> num_of_testcase;
    cin >> n >> m;
    init_id();

    if(check_with_simple_solution) {
        for(int i = 0; i < num_of_testcase; i++) {
            input();
            auto ans = solve();
            auto ans_simple = solve_simple();
            if(ans != ans_simple) {
                cout << "input:" << endl;
                output_input();
                cout << "output:" << endl;
                output(ans);
                cout << "expected:" << endl;
                output(ans_simple);
            }
        }
    }
    else {
        int64_t time_start = get_time();
        for(int i = 0; i < num_of_testcase; i++) {
            input();
            auto ans = solve();
            //output(ans);
        }
        int64_t time_end = get_time();

        if(calc_time){
            double time_per_case = (time_end - time_start) / (1e9 * num_of_testcase);
            cout << fixed << setprecision(3) << time_per_case << "[second/case]" << endl;
        }
    }
}
