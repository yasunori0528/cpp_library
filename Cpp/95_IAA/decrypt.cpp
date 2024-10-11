#include <bits/stdc++.h>
using namespace std;

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

template <typename T>
T exEuclid(T a, T b, T &x, T &y){
    T d = a;
    if(b != 0){
        d = exEuclid(b, a%b, y, x);
        y -= (a/b)*x;
    }
    else{
        x = 1;
        y = 0;
    }
    //cout << a << " * " << x << " + " << b << " * " << y << " = " << d << endl;
    return d;
}

int CalcPrivateKey(int e, int p, int q){
    int d, y;
    int f = (p-1)*(q-1);
    exEuclid(e, f, d, y);
    d = (d%f+f)%f;
    return d;
}

vector<int> sub_decrypt(vector<int> v, int e, int p, int q){
    int d = CalcPrivateKey(e, p, q);
    cout << "Private Key is " << d << endl;
    int sz = v.size();
    vector<int> rtn(sz);
    for(int i = 0; i < sz; i++){
        rtn[i] = powmod(v[i], d, p*q);
    }
    return rtn;
}

char IntToChar(int x){
    if(x == 0) return ' ';
    else if(1 <= x && x <= 26) return 'A'+x-1;
    return '?';
}

string VecToStr(vector<int> v){
    string rtn;
    for(int i : v){
        char a = IntToChar(i/100);
        char b = IntToChar(i%100);
        rtn.push_back(a);
        rtn.push_back(b);
    }
    return rtn;
}

string decrypt(vector<int> v, int e, int p, int q){
    return VecToStr(sub_decrypt(v, e, p, q));
}

int main(){
    int e, p, q;
    cin >> e >> p >> q;
    int n; cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];

    /*
    vector<int> d = sub_decrypt(v, e, p, q);
    for(auto i : d) cout << i << " "; cout << endl;
    */

    string s = decrypt(v, e, p, q);
    cout << "\"" << s << "\"" << endl;
}
