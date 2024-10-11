#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

//combination(n,k)%p
const int64_t cmax = 1048576;
const int64_t mod = 1000000007;
vector<int64_t> fac(cmax), finv(cmax), inv(cmax);
void cominit(){
  fac.at(0) = fac.at(1) = 1;
  finv.at(0) = finv.at(1) = 1;
  inv.at(1) = 1;
  for(int64_t i = 2; i < cmax; i++){
    fac.at(i) = fac.at(i-1)*i%mod;
    inv.at(i) = mod - inv.at(mod%i) *(mod/i)%mod;
    finv.at(i) = finv.at(i-1)*inv.at(i)%mod;
  }
}
int64_t commod(int64_t n, int64_t k){
  if(n < k) return 0;
  if(n < 0 || k < 0) return 0;
  return fac.at(n)*(finv.at(k)*finv.at(n-k)%mod)%mod;
}
//combination(n,k)
int64_t com(int64_t n, int64_t k){
  if(n < k) return 0;
  if(n < 0 || k < 0) return 0;
  return com(n-1,k-1)+com(n-1,k);
}
//1,3,7,9:true; 2,4,5,6,8:false;
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
//x^y%p
int64_t powermod(int64_t x, int64_t y, int64_t p){
  if(y < 0)
    return 0;
  else{
    int64_t n = 1;
    x %= p;
    for(int64_t i = 0; i < y; i++){
      n = n*x%p;
    }
    return n;
  }
}
//xのn^y位の数
int64_t digit(int64_t x, int64_t y, int64_t n){
  return x%power(n,y+1)/power(n,y);
}
//nの絵札枚数
int64_t card(int64_t n){
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
int64_t card_comb(int64_t p){
  int64_t cmb = 0;
  while(p > 0){
    cmb += power(10,p%10);
    p /= 10;
  }
  return cmb;
}
//vecのk以上の要素のうち一番左のもの
int64_t left(vector<int64_t> vec, int64_t k){
  int64_t a = 0;
  int64_t b = vec.size()-1;
  if(vec.at(a) > k)
    return 0;
  else if(vec.at(a) == k)
    return a;
  else if(vec.at(b) < k)
    return -1;
  else{
    bool bk = true;
    while(bk){
      int64_t c = (a+b)/2;
      if(vec.at(c-1) < k && vec.at(c) == k){
        return c;
        bk = false;
      }
      else if(vec.at(c-1) >= k)
        b = c;
      else if(vec.at(c) < k)
        a = c;
      else{
        return c;
        bk = false;
      }
    }
  }
}
//vecのk以下の要素のうち一番右のもの
int64_t right(vector<int64_t> vec, int64_t k){
  int64_t a = 0;
  int64_t b = vec.size()-1;
  if(vec.at(a) > k)
    return -1;
  else if(vec.at(b) == k)
    return b;
  else if(vec.at(b) < k)
    return b;
  else{
    bool bk = true;
    while(bk){
      int64_t c = (a+b)/2;
      if(vec.at(c) == k && vec.at(c+1) > k){
        return c;
        bk = false;
      }
      else if(vec.at(c+1) <= k)
        a = c;
      else if(vec.at(c) > k)
        b = c;
      else{
        return c;
        bk = false;
      }
    }
  }
}
int64_t bnps(int64_t n, int64_t a, int64_t d){
  int64_t an = 0;
  for(int64_t i = 0; i < d; i++){
    an += a%power(n,i+1)/power(n,i)*power(10,i);
  }
  return an;
}
bool pt(int64_t n,vector<int64_t>vec){
  int64_t s = vec.size();
  for(int64_t i = 0; i < s; i++){
    if(n%vec.at(i) == 0)
      return 0;
    else if(vec.at(i+1)*vec.at(i+1) > n)
      return 1;
  }
  return 0;
}
int64_t pmax = 134217728;
vector<int64_t> ntrl(pmax);
vector<int64_t> prime ={2,3};
void vprime(){
  for(int64_t i = 0; i < pmax; i++){
    if(i <= 1)
      ntrl.at(i) = -1;
    else
      ntrl.at(i) = i;
  }
  int64_t imax = sqrt(pmax);
  for(int64_t i = 0; i < imax; i++){
    int64_t p = prime.at(i);
    int64_t q = prime.at(i+1);
    for(int64_t j = p*p; j < pmax; j += p)
      ntrl.at(j) = -1;
    for(int64_t k = p*p+1; k < q*q && k < pmax; k++)
      if(ntrl.at(k) > 0)
        prime.push_back(k);
  }
}
int64_t main() {
  
}