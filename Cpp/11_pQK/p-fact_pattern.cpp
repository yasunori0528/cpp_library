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

int main(){
    int n = power(3,4);
    rep(i,n){
        string s = "a";
        rep(j,4){
            int k = i%power(3,j+1)/pow(3,j);
            if(k == 1){
                s += '*';
            }
            else if(k == 2){
                s += '^';
            }
            s += 'a'+j+1;
        }
        cout << s << endl;
    }
}