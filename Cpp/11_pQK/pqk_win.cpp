#include <bits/stdc++.h>
using namespace std;

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;
// 仮数部が1024ビットの浮動小数点数型(TLEしたら小さくする)
using Real = mp::number<mp::cpp_dec_float<1024>>;

map<char,int> operator+(map<char,int> a, map<char,int> b) {
    map<char,int> rtn = a;
    for(auto bi : b){
        rtn[bi.first] += bi.second;
    }
    return rtn;
}

map<char,int> operator-(map<char,int> a, map<char,int> b) {
    map<char,int> rtn = a;
    for(auto bi : b){
        rtn[bi.first] -= bi.second;
    }
    for(auto ri : rtn){
        if(ri.second <= 0){
            rtn[ri.first] = 0;
        }
    }
    return rtn;
}

vector<char> card = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
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
    for(auto ri : rtn){
        bool b = false;
        for(char c : card){
            if(ri.first == c){
                b = true;
                break;
            }
        }
        if(!b) rtn[ri.first] = 0;
    }
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

vector<map<char,int>> vec;
string dfs(map<char,int> hand, int m){
    //cout << "m : " << m << endl;
    if(m == 0){
        bool b = false;
        for(auto mi : hand){
            if(mi.second > 0) {
                b = true;
                break;
            }
        }
        if (!b) {
            //cout << "_" << endl;
            return "";
        }
        else {
            //cout << "x" << endl;
            return "x";
        }
    }
    for(auto vi : vec){
        //cout << mtos(vi) << endl;
        bool b = false;
        for(auto mi : vi-hand){
            if(mi.second > 0) {
                b = true;
                break;
            }
        }
        if(b) continue;
        string rtn = dfs(hand-vi, m-1);
        if(rtn == "x") continue;
        else {
            rtn += ","+mtos(vi);
            //cout << "A" << endl;
            return rtn;
        }
    }
    //cout << "B" << endl;
    return "x";
}

int main(){
    calc_chartoint();
    prime_calc(pow(10,1));
    
    int n; cin >> n;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        map<char,int> s_map = stom(s);
        vec.push_back(s_map);
    }
    
    while(1){
        string hand;
        cin >> hand;
        map<char,int> hand_map = stom(hand);
        int m; cin >> m;
        cout << dfs(hand_map, m) << endl;
    }
}