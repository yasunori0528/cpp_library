#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;
#include "../pqk_lib/pqk_all.cpp"

int64_t root(int64_t p){
    auto v = pollard_rho(p - 1);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    
    for(int64_t i = 2; i < p; i++){
        bool b = true;
        for(auto j : v){
            if(pow_mod(i, (p - 1) / j, p) == 1){
                b = false;
                break;
            }
        }
        if(b) return i;
    }
    return 0;
}

int main(){
    map<int64_t,int64_t> mp;
    for(int64_t i = 3; i <= 100000000000; i += 2){
        if(miller_rabin(i)){
            int64_t a = root(i);
            if(mp.count(a)) continue;
            else{
                mp[a] = i;
                cout << i << " " << a << endl;
            }
        }
    }
}
