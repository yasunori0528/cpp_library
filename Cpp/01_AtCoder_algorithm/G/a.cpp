#include <bits/stdc++.h>
using namespace std;
template <typename T> using min_priority_queue = priority_queue<T,vector<T>,greater<T>>;

random_device seed_gen;
mt19937 engine(seed_gen());

int64_t get_time(){
    struct::timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * int64_t(1'000'000'000) + t.tv_nsec;
}

template<typename T>
void invec(vector<T> &v){
    for(auto &i : v) cin >> i;
    return;
}

template<typename T>
void outvec(vector<T> &v, string s = " "){
    bool b = false;
    for(auto i : v){
        if(b) cout << s;
        else b = true;
        cout << i;
    }
    cout << endl;
    return;
}

template <typename T>
bool chmin(T &a, const T& b) {
    if (a > b) {
        a = b;  // aをbで更新
        return true;
    }
    return false;
}

template <typename T>
bool chmax(T &a, const T& b) {
    if (a < b) {
        a = b;  // aをbで更新
        return true;
    }
    return false;
}

bool yn(bool b){
    if(b) cout << "Yes" << endl;
    else cout << "No" << endl;
    return b;
}

bool check_with_simple_solution;
bool calc_time;
bool random_input;
bool debug_output;
int num_of_testcase;

using ans_type = int;

void input(){
    if(num_of_testcase > 1){
    }
    if(random_input){
    }   
    else{
    }
    return;
}

void output_input(){
    return;
}

void pre_solve(){
    return;
}

ans_type solve(){
    return ans_type();
}

ans_type solve_simple(){
    return ans_type();
}

void output(ans_type ans){
    return;
}

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    cout << fixed << setprecision(20);

    check_with_simple_solution = 0;
    calc_time = 0;
    random_input = 0;
    debug_output = 0;
    num_of_testcase = 1;
    
    if(num_of_testcase == 0) cin >> num_of_testcase;

    pre_solve();

    if(check_with_simple_solution){
        for(int i = 0; i < num_of_testcase; i++){
            if(debug_output) cout << "begin case " << i << " " << string(16, '=') << endl;
            input();
            ans_type ans = solve();
            if(debug_output) cout << string(16, '=') << endl;
            ans_type ans_simple = solve_simple();
            if(ans != ans_simple){
                cout << "input: " << endl;
                output_input();
                cout << "output: " << endl;
                output(ans);
                cout << "expected: " << endl;
                output(ans_simple);
            }
            if(debug_output) cout << "end case " << i << " " << string(16, '=') << endl;
        }
    }
    else{
        int64_t time_start = get_time();
        for(int i = 0; i < num_of_testcase; i++){
            input();
            output(solve());
        }
        int64_t time_end = get_time();

        if(calc_time){
            double time_per_case = (time_end - time_start) / (1e9 * num_of_testcase);
            cout << fixed << setprecision(3) << time_per_case << "[second/case]" << endl;
        }
    }

    return 0;
}
