#include <bits/stdc++.h>
using namespace std;

int64_t pow_mod(int64_t a, int64_t b, int64_t n){
    a %= n;
    if(a == 0) return 0;
    if(a == 1 || b == 0) return 1;
    if(b == 1) return a;
    int64_t c = b/2;
    int64_t d = b%2;
    int64_t ac = pow_mod(a,c,n);
    int64_t ad = pow_mod(a,d,n);
    return ac*ac%n*ad%n;
}

//k^-1 mod n, gcd(n,k) == 1
int64_t inv(int64_t k, int64_t n){
    if(gcd(n,k) != 1) return 0;
    k %= n;
    if(k == 1) return 1;
    vector<vector<int64_t>> v;
    v.push_back({n,k,n/k,n%k});
    int sz = 1;
    if(n%k != 1){
        while(1){
            int64_t a = v[sz-1][1];
            int64_t b = v[sz-1][3];
            v.push_back({a,b,a/b,a%b});
            sz++;
            if(a%b == 1) break;
        }
    }
    vector<int64_t> w(sz+2,0);
    w[0] = 1;
    for(int i = 0; i < sz; i++){
        int64_t wi = w[i];
        w[i] -= wi;
        w[i+1] -= v[sz-1-i][2]*wi;
        w[i+2] += wi;
    }
    //w[sz+1]*n+w[sz]*k==1
    int64_t rtn = w[sz]%n;
    rtn = (rtn+n)%n;
    return rtn;
}

pair<int64_t,int64_t> perm(int64_t n, int64_t m, int64_t p){
    int64_t rtn = 1;
    int64_t a = 0;
    for(int64_t i = n; i > n-m; i--){
        int64_t j = i;
        int64_t b = 0;
        while(j%p == 0){
            j /= p;
            b++;
        }
        rtn *= j%p;
        rtn %= p;
        a += b;
    }
    return {rtn,a};
}

int64_t comb_mod(int64_t n, int64_t m, int64_t p){
    auto pr1 = perm(n,m,p);
    auto pr2 = perm(m,m,p);
    if(pr1.second > pr2.second) return 0;
    int64_t rtn = pr1.first*inv(pr2.first,p)%p;
    return rtn;
}

int main(){
    int64_t mod = 97;
    for(int i = 0; i < 100; i++){
        int64_t n, m;
        cin >> n >> m;
        cout << comb_mod(n, m, mod) << endl;
    }
}