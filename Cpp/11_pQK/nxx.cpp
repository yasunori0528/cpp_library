#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

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
//nの枚数
int64_t card(int64_t n){
  int64_t cnt = 0;
  while(n > 0){
    int64_t n0 = n%10;
    n /= 10;
    cnt++;
    if(n0 <= 3 && n%10 == 1){
      n /= 10;
    }
  }
  return cnt;
}

//素数計算
vector<int64_t> ntrl;
vector<int64_t> prime;
int64_t maxn;
void prime_calculate(){
    rep(i,maxn){
        if(i <= 1) ntrl.push_back(-1);
        else ntrl.push_back(i);
    }
    prime = {2,3};
    int64_t maxi = sqrt(maxn);
    rep(i,maxi){
        int64_t p = prime[i];
        int64_t q = prime[i+1];
        for(int64_t j = p*p; j < maxn; j += p) ntrl[j] = -1;
        for(int64_t k = p*p+1; k < q*q && k < maxn; k++){
            if(ntrl.at(k) > 0) prime.push_back(k);
        }
    }
    cout << "prime calculated" << endl;
}
//素数判定
int64_t pt(int64_t n, vector<int64_t> &prime){
    if(n < 2) return 0;
    if(n == 2) return 1;
    for(int64_t p : prime){
        if(n%p == 0)    return 0;
        else if(p*p > n) return 1;
    }
    return 0;
    cout << "Insufficient_list" << endl;
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
        int64_t k_i1;
        if(i > 0) k_i1 = n%power(10,i)/power(10,i-1);
        if(k_i0 == 1 && k_i1 < 4 && i > 0){
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
int64_t str_int(string s){
    int64_t n = 0;
    for(char c : s){
        if(c == 'T') n = n*100+10;
        else if(c == 'J') n = n*100+11;
        else if(c == 'Q') n = n*100+12;
        else if(c == 'K') n = n*100+13;
        else n = n*10+(c-'0');
    }
    return n;
}

string card_id(int64_t n){
    string s;
    while(n > 0){
        char c;
        int64_t r = n%14;
        if(r < 10) c = '0'+r;
        else if(r == 10) c = 'T';
        else if(r == 11) c = 'J';
        else if(r == 12) c = 'Q';
        else c = 'K';
        s = c+s;
        n /= 14;
    }
    return s;
}
int64_t inv_card_id(string s){
    int64_t n = 0;
    for(char c : s){
        if('0' <= c && c <= '9') n = 14*n+(c-'0');
        else if(c == 'T') n = 14*n+10;
        else if(c == 'J') n = 14*n+11;
        else if(c == 'Q') n = 14*n+12;
        else n = 14*n+13;
    }
    return n;
}

int main(){
    maxn = 100000;
    prime_calculate();
    int64_t N = 3003*1048576ll;
    int TIME = time(NULL);
    int cnttime = 0;
    int64_t M;
    int cntcM = 169;
    int cntpM = 0;
    int cntcp = 0;
    int cntoutput = 0;
    for(int64_t i = 0; i < N; i++){
        int cntc = 0;
        int cntp = 0;
        bool b = false;
        for(int x = 1; x <= 13; x++){
            int64_t ix;
            if(x < 10) ix = 10*i+x;
            else ix = 100*i+x;

            for(int y = 1; y <= 13; y++){
                int64_t ixy;
                if(y < 10) ixy = 10*ix+y;
                else ixy = 100*ix+y;
                if(ixy%2 == 0 || ixy%3 == 0 || ixy%5 == 0 || ixy%7 == 0 || ixy%11 == 0 || ixy%13 == 0){
                    continue;
                }
                else if(!pt(ixy,prime)){
                    cntc++;
                    if(cntc > 21){
                        b = true;
                        break;
                    }
                }
                else cntp++;
                if(b) break;
            }
            if(b) break;
        }
        //cntcp = max(cntcp, cntc+cntp);
        
        /*if(cntp >= cntpM){
            cntpM = cntp;
            M = i;
            cout << cntc << "," << cntp << "," << i << endl;
        }*/

        if(cntp >= 23) {
            cout << cntc << "," << cntp << "," << i << endl;
            cntoutput++;
        }
        if(cntoutput == 1024){
            cout << "out_put_1024" << endl;
            break;
        }

        /*int Time = time(NULL);
        if(Time - TIME == 10){
            cnttime++;
            TIME = Time;
            cout << cnttime << "///" << i << endl;
        }*/
    }
    //cout << cntcp << endl;
}