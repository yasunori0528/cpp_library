#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

bool parity(int64_t n){
  if(n*n*n*n%10 == 1)
    return 1;
  else
    return 0;
}

//x^y
int64_t power(int64_t x, int64_t y){
  if(y < 0)
    return 0;
  else{
    int64_t n = 1ll;
    for(int64_t i = 0; i < y; i++)
      n *= x;
    return n;
  }
}

int64_t pt(int64_t n, vector<int64_t> &prime){
    for(int64_t p : prime){
        if(n == 2) return 1;
        else if(n%p == 0)    return 0;
        else if(p*p > n) return 1;
    }
    return 0;
}
//nの絵札枚数
int64_t CARD(int64_t n){
  int64_t cnt = 0;
  while(n > 0){
    int64_t n0 = n%10;
    n /= 10;
    if(n0 <= 3 && n%10 == 1){
      cnt++;
      n /= 10;
    }
  }
  return cnt;
}

string int_str(int64_t n){
    int64_t d = 0;
    int64_t m = n;
    string s;
    while(m > 0){
        m /= 10;
        d++;
    }
    int64_t i = d-1;
    while(i >= 0){
        int64_t k_i0 = n%power(10,i+1)/power(10,i);
        int64_t k_i1, k_i2;
        if(i > 0) k_i1 = n%power(10,i)/power(10,i-1);
        if(i > 1) k_i2 = n%power(10,i-1)/power(10,i-2);
        if(k_i0 == 1 && k_i1 == 1 && k_i2 == 0){
            s += "1T";
            i -= 3;
        }
        else if(k_i0 == 1 && k_i1 < 4 && i > 0){
            if(k_i1 == 0) s.push_back('T');
            else if(k_i1 == 1) s.push_back('J');
            else if(k_i1 == 2) s.push_back('Q');
            else if(k_i1 == 3) s.push_back('K');
            i -= 2;
        }
        else{
            char c = '0'+k_i0;
            s.push_back(c);
            i--;
        }
    }
    return s;
}

int main(){
    int64_t maxn = 11000000000;
    vector<int64_t> ntrl(maxn);
    for(int64_t i = 0; i < maxn; i++){
        if(i <= 1)
        ntrl.at(i) = -1;
        else
        ntrl.at(i) = i;
    }
    vector<int64_t> prime = {2ll,3ll};
    int64_t maxi = sqrt(maxn);
    for(int64_t i = 0; i < maxi; i++){
        int64_t p = prime.at(i);
        int64_t q = prime.at(i+1);
        for(int64_t j = p*p; j < maxn; j += p)
        ntrl.at(j) = -1;
        for(int64_t k = p*p+1; k < q*q && k < maxn; k++)
        if(ntrl.at(k) > 0)
            prime.push_back(k);
    }
    cout << "prime calculated" << endl;
    int64_t pmax = prime.at(prime.size()-1);
    vector<int64_t> cmb(power(18,4),0);

    int64_t n = 10;
    int64_t m = power(4,n);
    rep(i,m){
        int64_t q = 0;
        for(int64_t j = n-1; j >= 0; j--){
            int64_t k = i%power(4,j+1)/power(4,j);
            q = 100*q+10+k;
        }
        if(pt(q,prime)){
            int64_t cmbq = 0;
            rep(i,n){
                int64_t q_i = q%power(10,2*i+1)/power(10,2*i);
                cmbq += power(18,q_i);
            }
            cmb[cmbq] = q;
        }
    }
    sort(cmb.begin(),cmb.end());
    reverse(cmb.begin(),cmb.end());
    for(int64_t p : cmb) if(p > 0) cout << int_str(p) << endl;
}