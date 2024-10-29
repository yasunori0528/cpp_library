#include <bits/stdc++.h>
using namespace std;

random_device seed_gen;
mt19937 engine(seed_gen());

uint64_t rand64(){
    uint64_t a = engine();
    uint64_t b = engine();
    return (a << 32) + b;
}

int64_t get_time(){
    struct::timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * int64_t(1'000'000'000) + t.tv_nsec;
}

template<typename T>
T pow_mod(T a, T b, T n){
    a %= n;
    if(a == 0) return 0;
    if(a == 1 || b == 0) return 1;
    if(b == 1) return a;
    T c = b/2;
    T d = b%2;
    T ac = pow_mod(a,c,n);
    T ad = pow_mod(a,d,n);
    return ac*ac%n*ad%n;
}

template<typename T>
bool miller_rabin(T x){
    if(x <= 1) return false;
    if(x == 2) return true;
    if(x % 2 == 0) return false;

    assert(x <= sqrt(numeric_limits<T>::max()));

    int s = 0;
    T d = x - 1;
    while(d % 2 == 0){
        d /= 2;
        s++;
    }

    T k = min(T(1000), x - 1);
    set<T> A;

    {
        T a_max = x - 1;
        while(A.size() < k){
            A.insert(engine() % a_max + 1);
        }
    }

    for(T a : A){
        T t = pow_mod(a, d, x);
        if(t == 1) continue;
        bool b = false;
        for(int i = 0; i < s; i++){
            if(t == x - 1){
                b = true;
                break;
            }
            t = t * t % x;
        }
        if(b) continue;
        return false;
    }
    return true;
}

template<typename T>
T next_pseudorand(T x, T p, T c){
    return (x * x + c) % p;
}

template<typename T>
T pollard_rho_sub(T x){
    for(T c = 1; c < x; c++){
        if(c == x - 2) continue;
        T r1 = 2;
        T r2 = 2;
        T d = 1;
        while(d == 1){
            r1 = next_pseudorand(r1, x, c);
            r2 = next_pseudorand(next_pseudorand(r2, x, c), x, c);
            d = gcd(abs(r1 - r2), x);
        }
        if(d == x) continue;
        return d;
    }
    return 1;
}

template<typename T>
vector<T> pollard_rho(T x){
    assert(x > 0);

    vector<T> rtn;
    queue<T> q;

    while(x % 2 == 0){
        rtn.push_back(2);
        x /= 2;
    }

    if(x == 1) return rtn;

    q.push(x);

    while(q.size()){
        T y = q.front();
        q.pop();

        if(miller_rabin(y)){
            rtn.push_back(y);
            continue;
        }

        T d = pollard_rho_sub(y);

        assert(1 < d && d < y && y % d == 0);
        q.push(d);
        q.push(y / d);
    }

    return rtn;
}

template<typename T>
void trial_division_sub(T &x, T p, vector<T> &rtn){
    while(x % p == 0){
        x /= p;
        rtn.push_back(p);
    }
}

template<typename T>
vector<T> trial_division(T x){
    vector<T> rtn;

    trial_division_sub(x, T(2), rtn);
    trial_division_sub(x, T(3), rtn);
    trial_division_sub(x, T(5), rtn);

    for(T i = 7; i*i <= x; ){
        trial_division_sub(x, i, rtn);
        i += 4;
        trial_division_sub(x, i, rtn);
        i += 2;
        trial_division_sub(x, i, rtn);
        i += 4;
        trial_division_sub(x, i, rtn);
        i += 2;
        trial_division_sub(x, i, rtn);
        i += 4;
        trial_division_sub(x, i, rtn);
        i += 6;
        trial_division_sub(x, i, rtn);
        i += 2;
        trial_division_sub(x, i, rtn);
        i += 6;
    }

    if(x > 1) rtn.push_back(x);

    return rtn;
}

template<typename T>
vector<T> prime_fact(T x){
    if(x < 300'000'000'000'000) return trial_division(x);
    return pollard_rho(x);
}

int main(){
    int64_t time_start = get_time();

    for(int64_t i = 101001; i < 102000; i += 2){
        if(miller_rabin(i)){
            string s = to_string(i);
            bool b = true;
            for(int j = 3; j < 5; j++){
                int c = s[j] - '0';
                if(c == 0 || gcd(c, 10) == 1){
                    b = false;
                    break;
                }
            }
            if(b) cout << i << endl;
        }
    }

    int64_t time_end = get_time();

    double time_per_case = double(time_end - time_start) / (1e9 * 1);
    cout << fixed << setprecision(6) << time_per_case << "[second]" << endl;
}
