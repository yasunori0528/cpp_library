#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

int main(){
    int maxn = 100;
    vector<int> prime = {2,3};
    vector<int> ntrl;
    rep(i,maxn) ntrl.push_back(i);
    for(int i = 0; i*i < maxn; i++){
        int p = prime[i];
        int q = prime[i+1];
        for(int64_t j = p*p; j < maxn; j += p) ntrl[j] = -1;
        for(int64_t k = p*p+1; k < q*q && k < maxn; k++){
            if(ntrl[k] > 0) prime.push_back(k);
        }
    }
    for(int p : prime) cout << p << endl;
    //for(int n : ntrl) cout << n << endl;
}