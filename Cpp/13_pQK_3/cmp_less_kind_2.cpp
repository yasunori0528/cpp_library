#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
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

void out_time(int64_t &t_start){
    int64_t t_now = get_time();
    cout << (t_now - t_start)/1e9 << "[s]" << endl;
}

template <typename T>
bool chmax(T &a, const T& b) {
  if (a < b) {
    a = b;  // aをbで更新
    a.print();
    return true;
  }
  return false;
}

template <typename T>
bool chmin(T &a, const T& b) {
  if (a > b) {
    a = b;  // aをbで更新
    return true;
  }
  return false;
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

    //assert(x <= sqrt(numeric_limits<T>::max()));

    int s = 0;
    T d = x - 1;
    while(d % 2 == 0){
        d /= 2;
        s++;
    }

    T k = 1000;
    if(x - 1 < k) k = x - 1;

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

mpz_class to_int(string s){
    mpz_class rtn = 0;
    for(char c : s){
        if('0' <= c && c <= '9') rtn = rtn * 10 + (c - '0');
        else if(c == 'T') rtn = rtn * 100 + 10;
        else if(c == 'J') rtn = rtn * 100 + 11;
        else if(c == 'Q') rtn = rtn * 100 + 12;
        else if(c == 'K') rtn = rtn * 100 + 13;
    }
    return rtn;
}

int to_int(mpz_class x){
    for(int i = 0; ; i++){
        if(x == i) return i;
    }
    return 0;
}

string to_string(mpz_class x){
    string rtn;
    while(x){
        rtn.push_back('0' + to_int(x % 10));
        x /= 10;
    }
    reverse(rtn.begin(), rtn.end());
    return rtn;
}

string card = "0123456789TJQK";

int main(){
    int64_t t_start = get_time();

    int N = 14;
    vector V(N, vector(N, vector<mpz_class>(1, 1)));

    int M, K;
    cin >> M >> K;
    for(int i = 1; i <= M; i++){
        /*if(i == 1){
            vector<int> p = {2, 3, 5, 7, 11, 13};
            for(int pj : p){
                for(int k = 0; k < N; k++){
                    V[pj][k].push_back(pj);
                    if(pj != k) V[k][pj].push_back(pj);
                }
            }
        }*/
        if(miller_rabin(i)){
            string s(i, '1');
            mpz_class x = to_int(s);
            if(miller_rabin(x)){
                for(int k = 0; k < N; k++){
                    V[1][k].push_back(x);
                    if(k != 1) V[k][1].push_back(x);
                }
            }
        }

        /*for(int j = 0; j < N; j++)*/{
            int j = 0;
            /*for(int k = j+1; k < N; k++)*/{
                int k = 1;
                for(int l = 1; l < (1<<i)-1; l++){
                    string s;
                    for(int m = 0; m < i; m++){
                        if(l>>m&1) s.push_back(card[j]);
                        else s.push_back(card[k]);
                    }
                    if(s[0] == '0') continue;
                    mpz_class x = to_int(s);
                    if(miller_rabin(x)){
                        V[j][k].push_back(x);
                        V[k][j].push_back(x);
                    }
                }
            }
        }
    }
    cout << "A" << endl;
    out_time(t_start);
    
    vector<pair<mpz_class,string>> output_list;
    /*for(int j = 0; j < N; j++)*/{
        int j = 0;
        /*for(int k = j+1; k < N; k++)*/{
            int k = 1;
            int sz = V[j][k].size();
            cout << card[j] << " " << card[k] << " " << sz << endl;
            vector<int> loop(K + 1, 0);
            loop[K] = sz - 1;
            bool b = true;
            while(b){
                //for(auto l : loop) cout << l << " "; cout << endl;
                mpz_class x = 1;
                string s;
                int cnt_not_1 = 0;
                for(int l = 0; l < K; l++){
                    mpz_class a = V[j][k][loop[l]];
                    if(a == 1) continue;
                    cnt_not_1++;
                    x *= V[j][k][loop[l]];
                    s += to_string(V[j][k][loop[l]]);
                    s.push_back('*');
                }

                //cout << s << endl;

                if(cnt_not_1 > 1){
                    s.pop_back();
                    string t = to_string(x);
                    vector<bool> dp(t.size() + 1, false);
                    dp[0] = true;
                    for(int l = 0; l < t.size(); l++){
                        int a0 = -1;
                        if(l) a0 = t[l-1] - '0';
                        int a1 = t[l] - '0';

                        if(a1 == j) dp[l+1] = dp[l+1] || dp[l];
                        if(a1 == k) dp[l+1] = dp[l+1] || dp[l];
                        if(a0 == 1){
                            if(a0 * 10 + a1 == j) dp[l+1] = dp[l+1] || dp[l-1];
                            if(a0 * 10 + a1 == k) dp[l+1] = dp[l+1] || dp[l-1];
                        }
                    }
                    if(dp[t.size()]){
                        string t2;
                        int l = t.size()-1;
                        while(l >= 0){
                            if(dp[l+1] && dp[l]){
                                t2.push_back(t[l]);
                                l--;
                            }
                            else{
                                int a1 = (t[l-1]-'0')*10+(t[l]-'0');
                                t2.push_back(card[a1]);
                                l -= 2;
                            }
                        }
                        reverse(t2.begin(), t2.end());
                        string u = t2 + "=" + s;
                        output_list.push_back({x, u});
                    }
                }

                b = false;
                for(int l = 0; l < K; l++){
                    if(loop[l] < loop[l+1]){
                        loop[l]++;
                        for(int m = 0; m < l; m++) loop[m] = 0;
                        b = true;
                        break;
                    }
                }
            }
        }
    }

    sort(output_list.begin(), output_list.end());

    for(auto[x, s] : output_list) cout << s << endl;

    out_time(t_start);
    return 0;

    /*for(auto i : V){
        for(auto j : i){
            for(auto k : j){
                cout << k << " ";
            }
            cout << endl;
        }
    }*/
}