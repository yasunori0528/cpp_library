#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

//素数計算
vector<int> ntrl;
vector<int> prime;
int maxn;
void prime_calculate(){
    rep(i,maxn){
        ntrl.push_back(i);
    }
    prime = {2,3};
    for(int i = 0; i*i < maxn; i++){
        int p = prime[i];
        int q = prime[i+1];
        for(int j = p*p; j < maxn; j += p) ntrl[j] = -1;
        for(int k = p*p+1; k < q*q && k < maxn; k++){
            if(ntrl[k] > 0) prime.push_back(k);
        }
    }
}

int main(){
    maxn = 50;
    prime_calculate();

    for(int p : prime) cout << p << endl;
    //cout << endl;
    //for(int64_t n : ntrl) cout << n << endl;
}