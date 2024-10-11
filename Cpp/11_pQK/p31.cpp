#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

//x^y
int64_t power(int64_t x, int64_t y){
    if(y < 0) return 0;
    else{
        int64_t n = 1ll;
        for(int64_t i = 0; i < y; i++) n *= x;
        return n;
    }
}

//xのn^y位の数
int64_t digit(int64_t x, int64_t y, int64_t n){
  return x%power(n,y+1)/power(n,y);
}

//素数計算
vector<int64_t> ntrl;
vector<int64_t> prime;
int64_t maxn;
void prime_calculate(){
    rep(i,maxn){
        ntrl.push_back(i);
    }
    prime = {2,3};
    int64_t maxi = sqrt(maxn);
    rep(i,maxi){
        int64_t p = prime[i];
        int64_t q = prime[i+1];
        for(int64_t j = p*p; j < maxn; j += p) ntrl[j] = -1;
        for(int64_t k = p*p+1; k < q*q && k < maxn; k++){
            if(ntrl[k] > 0) prime.push_back(k);
        }
    }
    cout << "prime calculated" << endl;
}
bool pt(int64_t n,vector<int64_t>vec){
  int64_t s = vec.size();
  for(int64_t i = 0; i < s; i++){
    if(n%vec[i] == 0) return false;
    else if(vec[i]*vec[i] > n) return true;
  }
  return false;
  cout << "Insuficuent_Prime_List" << endl;
}

int main(){
    maxn = 1000000;
    prime_calculate();

    vector<int64_t> a = {
        0,
        127, 286, 389,
        425, 584, 625,
        761, 864, 943
    };
    int64_t c = power(9,4);
    rep(i,c){
        int64_t b0 = digit(i,0,9)+1;
        int64_t b1 = digit(i,1,9)+1;
        int64_t b2 = digit(i,2,9)+1;
        int64_t b3 = digit(i,3,9)+1;
        int64_t n = a[b0]*power(10,0)+a[b1]*power(10,3)+a[b2]*power(10,6)+a[b3]*power(10,9);

        if(pt(n,prime)){
            cout << b3 << b2 << b1 << b0 << "," << n << endl;
        }
    }
    //for(int64_t p : prime) cout << p << endl;
}