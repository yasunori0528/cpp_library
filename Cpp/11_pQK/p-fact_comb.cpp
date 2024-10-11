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
        if(i <= 1) ntrl.push_back(-1);
        else ntrl.push_back(i);
    }
    prime = {2,3};
    int64_t maxi = sqrt(maxn);
    rep(i,maxi){
        int64_t &p = prime[i];
        int64_t &q = prime[i+1];
        for(int64_t j = p*p; j < maxn; j += p) ntrl[j] = -1;
        for(int64_t k = p*p+1; k < q*q && k < maxn; k++){
            if(ntrl.at(k) > 0) prime.push_back(k);
        }
    }
    cout << "prime calculated" << endl;
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
//素因数分解
string p_fact(int64_t n, vector<int64_t> &prime){
    string s;
    for(int64_t p : prime){
        int a = 0;
        while(n%p == 0){
            n /= p;
            a++;
        }
        string q = int_str(p);
        if(a == 1) s = s + "*" + q;
        else if(a > 1){
            string b = int_str(a);
            s = s + "*" + q + "^" + b;
        }

        if(n == 1) break;
        if(n < p*p){
            string q = int_str(n);
            s = s + "*" + q;
            break;
        }
    }
    s = s.substr(1);
    return s;
}
string p_fact_int(int64_t n, vector<int64_t> &prime){
    string s;
    for(int64_t p : prime){
        int a = 0;
        while(n%p == 0){
            n /= p;
            a++;
        }
        string q = to_string(p);
        if(a == 1) s = s + "*" + q;
        else if(a > 1){
            string b = to_string(a);
            s = s + "*" + q + "^" + b;
        }

        if(n == 1) break;
        if(n < p*p){
            string q = to_string(n);
            s = s + "*" + q;
            break;
        }
    }
    s = s.substr(1);
    return s;
}
string p_fact_(int64_t n, vector<int64_t> &prime){
    string s;
    for(int64_t p : prime){
        int a = 0;
        while(n%p == 0){
            n /= p;
            a++;
        }
        string q = int_str(p);
        if(a == 1) s = s + q;
        else if(a > 1){
            string b = int_str(a);
            s = s + q + b;
        }

        if(n == 1) break;
        if(n < p*p){
            string q = int_str(n);
            s = s + q;
            break;
        }
    }
    return s;
}
string p_fact_int_(int64_t n, vector<int64_t> &prime){
    string s;
    for(int64_t p : prime){
        int a = 0;
        while(n%p == 0){
            n /= p;
            a++;
        }
        string q = to_string(p);
        if(a == 1) s = s + q;
        else if(a > 1){
            string b = to_string(a);
            s = s + q + b;
        }

        if(n == 1) break;
        if(n < p*p){
            string q = to_string(n);
            s = s + q;
            break;
        }
    }
    return s;
}

//合成数出し最小消費枚数
int p_fact_comb(int64_t n, vector<int64_t> &prime){
    if(pt(n,prime)) return int_str(n).size();
    string s;
    int64_t m = n;
    for(int64_t p : prime){
        int a = 0;
        while(m%p == 0){
            m /= p;
            a++;
        }
        string q = int_str(p);
        if(a == 1) s = s + q;
        else if(a > 1){
            string b = int_str(a);
            s = s + q + b;
        }

        if(m == 1) break;
        if(m < p*p){
            string q = int_str(m);
            s = s + q;
            break;
        }
    }
    int c = s.size()+int_str(n).size();
    return c;
}
int p_fact_comb_int(int64_t n, vector<int64_t> &prime){
    if(pt(n,prime)) return to_string(n).size();
    string s;
    int64_t m = n;
    for(int64_t p : prime){
        int a = 0;
        while(m%p == 0){
            m /= p;
            a++;
        }
        string q = to_string(p);
        if(a == 1) s = s + q;
        else if(a > 1){
            string b = to_string(a);
            s = s + q + b;
        }

        if(m == 1) break;
        if(m < p*p){
            string q = to_string(m);
            s = s + q;
            break;
        }
    }
    int c = s.size()+to_string(n).size();
    return c;
}

int main(){
    maxn = 32000000;
    prime_calculate();
    vector<char> cd = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K'};
    map<char,int> card_condition;
    for(char c : cd){
        if(c == '0') card_condition[c] = 0;
        else card_condition[c] = 1;
    }
    map<char,int> card_condition2 = card_condition;
    card_condition2['Q']++;
    card_condition2['1']--;
    card_condition2['2']--;
    map<char,int> card_condition3 = card_condition;
    card_condition3['K']++;
    card_condition3['1']--;
    card_condition3['3']--;
    /*vector<int64_t> pwpw = {8,16,32,9,25,36,49};
    vector<int64_t> pwpw3 = {16,32,9,25,36,49};
    vector<int64_t> pwpw5 = {8,16,9,36,49};
    vector<int64_t> pwpw7 = {8,16,32,9,25,36};
    map<string,string> bpp2;
    bpp2["8"] = "23";
    bpp2["16"] = "24";
    bpp2["32"] = "25";
    bpp2["9"] = "32";
    bpp2["25"] = "52";
    bpp2["36"] = "62";
    bpp2["49"] = "72";*/
    int64_t cd_perm = power(14,11);
    for(int64_t i = 2140000000; i < cd_perm; i++){
        if(i%10000000 == 0) cout << i << endl;
        string s;
        map<char,int> ncomb;
        for(char c : cd){
            ncomb[c] = 0;
        }
        bool b0 = false;
        for(int j = 10; j >= 0; j--){
            int64_t ij = digit(i,j,14);
            if(ij == 0){
                if(s.size() > 0){
                    b0 = true;
                    break;
                }
                continue;
            }
            char cij = cd[ij];
            if(ncomb[cij] > 0){
                b0 = true;
                break;
            }
            s += cij;
            ncomb[cij]++;
        }
        if(b0) continue;

        //素因数分解
        int64_t n = str_int(s);
        if(pt(n,prime)) continue;
        //cout << "--" << s << "\n";
        vector<pair<int64_t,int>> nfact;
        int64_t nfsize = 0;
        for(int64_t p : prime){
            if(n%p == 0){
                nfact.push_back(make_pair(p,0));
                nfsize++;
                int nfp2 = 0;
                while(n%p == 0){
                    n /= p;
                    nfp2++;
                }
                nfact[nfsize-1].second = nfp2;
            }
            if(n == 1) break;
            if(p*p > n){
                nfact.push_back(make_pair(n,1));
                nfsize++;
                break;
            }
        }

        //素因数場指数部分(50未満なので1通り)
        //vector<int64_t> bpp; //p^a^b の形があるかどうか
        rep(j,nfsize){
            int64_t nfj1i = nfact[j].second;
            int64_t nfj0i = nfact[j].first;
            string nfj1s = int_str(nfj1i);
            if(nfj1s == "1") continue;
            for(char c : nfj1s){
                ncomb[c]++;
            }
            //p^a^b 確認
            /*if(nfj0i == 3){
                for(int64_t k : pwpw3){
                    if(k == nfj1i){
                        bpp.push_back(k);
                    }
                }
            }
            else if(nfj0i == 5){
                for(int64_t k : pwpw5){
                    if(k == nfj1i){
                        bpp.push_back(k);
                    }
                }
            }
            else if(nfj0i == 7){
                for(int64_t k : pwpw7){
                    if(k == nfj1i){
                        bpp.push_back(k);
                    }
                }
            }
            else if(nfj0i != 2){
                for(int64_t k : pwpw){
                    if(k == nfj1i){
                        bpp.push_back(k);
                    }
                }
            }*/
        }

        //素因数場素数部分"J2"と"1Q"等の重複に注意
        vector<int> dbl; //dbl[k]=112,113
        rep(j,nfsize){
            int64_t nfj0i = nfact[j].first;
            string nfj0s = int_str(nfj0i);
            int nfj0ss = nfj0s.size();
            for(char c : nfj0s){
                ncomb[c]++;
            }
            //重複確認
            rep(k,nfj0ss-1){
                if(nfj0s[k] == 'J'){
                    char nfj0sk_ = nfj0s[k+1];
                    //"J0"は不適なので"1T"に調節
                    if(nfj0sk_ == '0'){
                        ncomb['1']++;
                        ncomb['T']++;
                        ncomb['J']--;
                        ncomb['0']--;
                    }
                    //"J2","1Q"
                    else if(nfj0sk_ == '2'){
                        dbl.push_back(112);
                    }
                    //"J3","1K"
                    else if(nfj0sk_ == '3'){
                        dbl.push_back(113);
                    }
                }
            }
        }

        //出せるかどうか
        if(ncomb == card_condition || ncomb == card_condition2 || ncomb == card_condition3){
            cout << s << endl;
            continue;
        }

        int dbls = dbl.size();
        //int bpps = bpp.size();

        if(ncomb['T'] != 1){
            continue;
        }

        //dblのみ動かす
        bool b1 = false;
        if(dbls != 0){
            rep(j,14){
                char c = cd[j];
                if(j == 0){
                    if(ncomb[c] != 0){
                        b1 = true;
                        break;
                    }
                }
                else if(3 < j && j < 10){
                    if(ncomb[c] != 1){
                        b1 = true;
                        break;
                    }
                }
            }
            rep(j,1<<dbls){
                map<char,int> ncomb1 = ncomb;
                rep(k,dbls){
                    if(j>>k&1){
                        if(dbl[k] == 112){
                            ncomb1['1']++;
                            ncomb1['Q']++;
                            ncomb1['J']--;
                            ncomb1['2']--;
                        }
                        else{
                            ncomb1['1']++;
                            ncomb1['K']++;
                            ncomb1['J']--;
                            ncomb1['3']--;
                        }
                    }
                }
                if(ncomb1 == card_condition || ncomb1 == card_condition2 || ncomb1 == card_condition3){
                    cout << s << "\n";
                    b1 = true;
                    break;
                }
            }
        }
        if(b1) continue;
        /*
        //bppのみ動かす
        //p^a^bの形は複数存在しない(nの定義域より a == 2 || b == 2)
        bool b2 = false;
        if(bpps != 0){
            rep(j,bpps){
                map<char,int> ncomb2 = ncomb;
                int dblji = dbl[j];
                string dbljs = int_str(dblji);
                for(char c : dbljs){
                    ncomb2[c]--;
                }
                string dbljs_ = bpp2[dbljs];
                for(char c : dbljs_){
                    ncomb2[c]++;
                }
                if(ncomb2 == card_condition || ncomb2 == card_condition2 || ncomb2 == card_condition3){
                    cout << s << "\n";
                    b2 = true;
                    break;
                }
            }
        }
        if(b2) continue;

        //両方動かす(nの定義域より存在しない)
        /*bool b3 = false;
        if(dbls != 0 && bpps != 0){
            ;
        }
        if(b3) continue;*/
    }
}