#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

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

int64_t digit(int64_t x, int64_t y, int64_t n){
  return x%power(n,y+1)/power(n,y);
}

int main(){
    rep(i,1<<12){
        if(__builtin_popcount(i) != 4) continue;
        //if((i&7) != 3 || (i>>3&7) != 5) continue;
        int cnt = 0;
        for(int j = 0; j < 1000000; j++){
            int ab = j;
            rep(k,6){
                if(i>>k&1){
                    int abk = digit(ab,k,10);
                    ab = ab+(2-abk)*power(10,k);
                }
            }
            int a = ab/1000;
            int b = ab%1000;
            int c = a*b;
            if(a < 100 || b < 100 || c < 100000) continue;
            bool bl = true;
            for(int k = 6; k < 12; k++){
                if(i>>k&1){
                    if(digit(c,k-6,10) != 2){
                        bl = false;
                        break;
                    }
                }
            }
            if(bl) cnt++;
        }
        int d = 4-__builtin_popcount(i>>6);
        if(cnt/power(10,d) == 1){
            cout << bitset<12> (i) << endl;
        }
        if(cnt/power(10,d) == 2 && (i&7) == (i>>3&7)){
            cout << bitset<12> (i) << endl;
        }
    }
}