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
    maxn = 10000;
    prime_calculate();
    vector<char> card = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K'};
    map<map<char,int>,string> comb;
    string pmin_s = "10011";
    string pmax_s = "10299";
    int64_t pmin_i = inv_card_id(pmin_s);
    int64_t pmax_i = inv_card_id(pmax_s);
    for(int64_t i = pmax_i; i >= pmin_i; i -= 2){
        string s = card_id(i);
        int64_t n = str_int(s);
        map<char,int> combi;
        for(char c : card){
            combi[c];
        }
        for(char c : s){
            combi[c]++;
        }

        //if(combi['5'] == 0) continue;
        //if(combi['7'] == 0) continue;
        if(combi['1'] == 0) continue;
        if(combi['0'] == 0) continue;
        bool b = false;
        for(pair<char,int> pr : combi){
            char c = pr.first;
            int k = pr.second;
            if(c == '0'){
                if(k > 1){
                    b = true;
                    break;
                }                
            }
            else if('0' < c && c <= '9'){
                if(k > 1){
                    b = true;
                    break;
                }
            }
            else{
                if(k > 0){
                    b = true;
                    break;
                }
            }
        }
        if(b) continue;

        if(pt(n,prime)){
            if(comb.count(combi)){
                string t = comb[combi];
                int64_t m = str_int(t);
                if(n < m) comb[combi] = s;
            }
            else comb[combi] = s;
        }
    }

    for(auto p : comb){
        string s = p.second;
        cout << s << endl;
    }
}