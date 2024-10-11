#include <bits/stdc++.h>
using namespace std;

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;
// 仮数部が1024ビットの浮動小数点数型(TLEしたら小さくする)
using Real = mp::number<mp::cpp_dec_float<1024>>;

template <typename T> bool next_combination(const T first, const T last, int k) {
    const T subset = first + k;
    // empty container | k = 0 | k == n 
    if (first == last || first == subset || last == subset) {
        return false;
    }
    T src = subset;
    while (first != src) {
        src--;
        if (*src < *(last - 1)) {
            T dest = subset;
            while (*src >= *dest) {
                dest++;
            }
            iter_swap(src, dest);
            rotate(src + 1, dest + 1, last);
            rotate(subset, subset + (last - dest) - 1, last);
            return true;
        }
    }
    // restore
    rotate(first, subset, last);
    return false;
}

vector<vector<int64_t>> v_comb(100,vector<int64_t>(100));
int64_t comb(int64_t x, int64_t y){
    if(x < 0 || y < 0 || x < y) return 0;
    if(y == 0 || x == y) return 1;
    if(v_comb[x][y] != 0) return v_comb[x][y];
    int64_t rtn = comb(x-1,y-1)+comb(x-1,y);
    v_comb[x][y] = rtn;
    return rtn;
}

//m in n
bool include_map (map<char,int> m, map<char,int> n){
    bool rtn = true;
    for(auto mi : m){
        if(n[mi.first] < mi.second){
            rtn = false;
            break;
        }
    }
    return rtn;
}
// m\n
map<char,int> map_difference(map<char,int> m, map<char,int> n){
    map<char,int> rtn = m;
    for(auto mi : m){
        rtn[mi.first] = max(0,mi.second-n[mi.first]);
    }
    return rtn;
}

map<char,int> chartoint;
void calc_chartoint(){
    for(int i = 0; i < 10; i++){
        chartoint['0'+i] = i;
    }
    chartoint['T'] = 10;
    chartoint['J'] = 11;
    chartoint['Q'] = 12;
    chartoint['K'] = 13;
    chartoint['X'] = 14;
}
char inttochar(int n){
    if(0 <= n && n < 10) return (char)('0'+n);
    if(n == 10) return 'T';
    if(n == 11) return 'J';
    if(n == 12) return 'Q';
    if(n == 13) return 'K';
    return 'X';
}

Bint strtoint(string s){
    int n = s.size();
    if(n == 1){
        return chartoint[s[0]];
    }
    Bint rtn = strtoint(s.substr(0,n-1));
    char i = chartoint[s[n-1]];
    if(i < 10) rtn = 10*rtn+i;
    else rtn = 100*rtn+i;
    return rtn;
}

vector<int64_t> prime_list;
void prime_calc(int64_t MAX_N){
    for(int64_t i = 2; i <= MAX_N; i++){
        bool b = true;
        for(int64_t j = 2; j < i; j++){
            if(i%j == 0){
                b = false;
                break;
            }
            else if(j*j > i) break;
        }
        if(b) prime_list.push_back(i);
    }
}
bool pt(Bint n){
    if(n < 2) return false;
    for(int64_t i : prime_list){
        if(i*i > n) break;
        if(n%i == 0) return false;
    }
    return true;
}

string max_prime(bool b, vector<char> vec){
    Bint rtni = -1;
    string rtn;
    bool b2 = true;
    for(char s : vec){
        if((int)pow(chartoint[s],4)%10 == 1) b2 = false;
        rtn += s;
    }
    if(b2) rtn = "x2";
    else if(strtoint(rtn)%3 == 0) rtn = "x3";
    else {
        rtn = '-'+rtn;
        do{
            string s;
            for(char t : vec){
                s += t;
            }
            Bint p = strtoint(s);
            //cout << s << "," << p << ",";
            if((rtni < 0 || ((b == (rtni < p)))) && pt(p)) {
                rtni = p;
                rtn = s;
            }
        }while(next_permutation(vec.begin(),vec.end()));
        //cout << endl;
    }
    return rtn;
}

string max_prime(bool b, string s){
    Bint rtni = -1;
    vector<char> vec;
    for(char c : s) vec.push_back(c);
    sort(vec.begin(),vec.end());
    string rtn;
    bool b2 = true;
    for(char s : vec){
        if((int)pow(chartoint[s],4)%10 == 1) b2 = false;
        rtn += s;
    }
    if(b2) rtn = "x2";
    else if(strtoint(rtn)%3 == 0) rtn = "x3";
    else {
        rtn = '-'+rtn;
        do{
            string s;
            for(char t : vec){
                s += t;
            }
            Bint p = strtoint(s);
            //cout << s << "," << p << ",";
            if((rtni < 0 || ((b == (rtni < p)))) && pt(p)) {
                rtni = p;
                rtn = s;
            }
        }while(next_permutation(vec.begin(),vec.end()));
        //cout << endl;
    }
    return rtn;
}

vector<int> card_pri = {9,8,7,6,5,4,3,2,1,0,13,12,11,10,14};
string sort_91KT(string s){
    vector<pair<int,char>> vp;
    for(char c : s){
        vp.push_back(make_pair(card_pri[chartoint[c]],c));
    }
    sort(vp.begin(),vp.end());
    string rtn;
    for(auto vpi : vp){
        rtn.push_back(vpi.second);
    }
    return rtn;
}

string mtos(map<char,int> m){
    string s;
    for(auto mi : m){
        for(int i = 0; i < mi.second; i++){
            s.push_back(mi.first);
        }
    }
    sort_91KT(s);
    return s;
}

map<char,int> stom(string s){
    map<char,int> rtn;
    for(char c : s){
        rtn[c]++;
    }
    return rtn;
}

string rand_hand(int n){
    string rtn;
    vector<char> vec;
    for(int i = 0; i < 54; i++) {
        char c;
        c = inttochar((i/4+1));
        vec.push_back(c);
    }
    for(int i = 0; i < n; i++){
        int j = rand()%(54-i);
        rtn.push_back(vec[j]);
        for(int k = j; k < 54-i; k++){
            vec[k] = vec[k+1];
        }
        vec.pop_back();
    }
    rtn = sort_91KT(rtn);
    return rtn;
}

int log_(int64_t n, int64_t m){
    if(m < n) return 0;
    else{
        return 1+log_(n,m/n);
    }
}

int main(){
    calc_chartoint();
    prime_calc(pow(10,6));
    
    int n, k;
    cin >> n >> k;
    vector<int> v(n,0);
    v[n-2] = 1;
    vector<int> loop_max(n,k+1);

    vector<int> ansv;
    int maxcntp = 0;
    double pc = 0;

    while(1){
        //for(int vi : v) cout << vi << ","; cout << endl;
        int mm = 0;
        for(int vi : v) mm = max(mm,vi);
        vector<vector<int64_t>> b(mm+1,vector<int64_t>(n));
        if(mm > 2){
            for(int i = 2; i <= mm; i++){
                vector<int64_t> bi = b[i];
                bi[0] = v[0];
                for(int j = 1; j < n; j++){
                    bi[j] = bi[j-1]*(int)pow(i,log_(i,v[j])+1)+v[j];
                }
                b[i] = bi;
                //cout << i << ":" << bi[n-1] << endl;
            }

            int cntp = 0;
            int cntc = 0;
            for(int i = 2; i <= mm; i++){
                int64_t bi = b[i][n-1];
                if(pt(bi)) {
                    cntp++;
                }
                else {
                    cntc++;
                }
            }
            double pci = (double)cntp/(cntp+cntc);
            /*if(cntp > maxcntp){
                ansv = v;
                maxcntp = cntp;
            }*/
            if(pci >= 4.0/5.0){
                if(mm == k || 1){
                    for(int vi : v) cout << vi << " ";
                    cout << endl;
                }
            }
            else if(pci > pc){
                ansv = v;
                pc = pci;
            }
        }

        int cc = -1;
        for(int i = n-1; i >= 0; i--){
            if(v[i] != loop_max[i]-1) {
                cc = i;
                break;
            }
        }
        if(cc == -1) break;
        if(cc == 0) cout << "___" << v[0] << endl;
        v[cc]++;
        for(int i = cc+1; i < n; i++){
            v[i] = 0;
        }        
    }

    for(int vi : ansv) cout << vi << " ";
    cout << endl;
    cout << pc << endl;
}