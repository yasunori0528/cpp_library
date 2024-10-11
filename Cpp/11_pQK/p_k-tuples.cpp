#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

bool parity(int64_t n){
    n %= 10;
    if(n*n*n*n%10 == 1)
        return 1;
    else
        return 0;
}
bool parity(string s){
    int n = s.size();
    char c = s[n-1];
    if(c == '0' || c == '2' || c == '4' || c == '5'
        || c == '6' || c == '8' || c == 'T' || c == 'Q')
            return 0;
    else return 1;
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
}

//nの最上位桁
int64_t msd(int64_t n){
    string s = to_string(n);
    char c = s[0];
    int64_t i = c-'0';
    return i;
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

int main(){
    int64_t maxn = 3200000;
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

    int64_t cnt = 0;
    vector<char> cd = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K'};
    vector<char> ev = {'2','5','8'};
    vector<char> od = {'1','3','7','9'};
    int64_t amin = str_int("416");    int64_t amax = str_int("4169999");
    for(int64_t a = amin; a < amax; a += 3){
        if((to_string(a)).substr(0,3) != "416"){
            continue;
        }
        //int Ca = CARD(a); int ca = card(a);
        //if(ca > 6) continue;
        //if(ca != Ca && msd(a) == 1) continue;
        /*string b = int_str(a);
        map<char,int> combb;
        for(char c : cd){
            combb[c] = 0;
        }
        bool bl = false;
        int cnt2 = 0;
        /*for(char c : b){
            combb[c]++;
            /*if(combb[c] > 1 && cnt2 < 1){
                cnt2++;
            }
            else if(combb[c] > 1 && cnt2 >= 1){
                bl = true;
                break;
            }
            else if(combb[c] > 1){
                bl = true;
                break;
            }
        }
        if(combb['0'] > 0) continue;
        if(bl) continue;*/

        /*bool bol = false;
        int np = 0;
        for(char c : ev){
            for(char d : od){
                int64_t aeo = str_int(b+c+d);
                if(!pt(aeo,prime)){
                    np++;
                }
            }
        }
        if(np > 1) continue;
        cout << a << endl;
        cnt++;*/
        int64_t a1 = 10*a+1;
        int64_t a3 = 10*a+3;
        int64_t a7 = 10*a+7;
        int64_t a9 = 10*a+9;
        int64_t aJ = 100*a+11;
        int64_t aK = 100*a+13;
        //if(card(a1) > 6 || card(a3) > 6 || card(a7) > 6 || card(a9) > 6 || card(aK) > 6) continue;
        if(/*pt(a,prime) &&*/ pt(a1,prime) && pt(a3,prime) && pt(a7,prime) 
        && pt(a9,prime) /*&& !pt(aJ,prime) && pt(aK,prime)*/){
            cout << int_str(a) << endl;
            cnt++;
        }

        if(cnt >= 1024){
            cout << "output_1024" << endl;
            break;
        }
    }
}