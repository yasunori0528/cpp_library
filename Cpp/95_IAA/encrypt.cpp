#include <bits/stdc++.h>
using namespace std;

void PrintVec(vector<int> v){
    for(int i = 0; i < v.size(); i++){
        if(i) cout << " ";
        cout << v[i];
    }
    cout << endl;
}

int powmod(int a, int b, int mod){
    a %= mod;
    if(a == 0) return 0;
    if(b == 0) return 1;
    if(a == 1) return 1;
    if(b == 1) return a;
    int rtn = powmod(a, b/2, mod);
    rtn = rtn * rtn % mod * powmod(a, b%2, mod) % mod;
    return rtn;
}

int CharToInt(char c){
    if(c == ' ') return 0;
    else if('A' <= c && c <= 'Z') return c - 'A' + 1;
    return -1;
}

vector<int> StrToVec(string s){
    vector<int> rtn;
    int sz = s.size();
    for(int i = 0; i < sz; i += 2){
        int c = CharToInt(s[i]);
        int d = CharToInt(s[i+1]);
        rtn.push_back(100*c+d);
    }
    return rtn;
}

vector<int> encrypt_sub(vector<int> v, int e, int n){
    vector<int> rtn(v.size());
    for(int i = 0; i < v.size(); i++){
        rtn[i] = powmod(v[i], e, n);
    }
    return rtn;
}

vector<int> encrypt(string s, int e, int n){
    return encrypt_sub(StrToVec(s), e, n);
}

int main(){
    int e, n;
    string s;
    getline(cin, s);
    cin >> e >> n;
    vector<int> v = encrypt(s, e, n);
    PrintVec(v);
}
