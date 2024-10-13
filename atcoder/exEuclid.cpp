#include <bits/stdc++.h>
using namespace std;
template <typename T> using min_priority_queue = priority_queue<T,vector<T>,greater<T>>;

//ax+by=d
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

//a^-1 mod p
template <typename T>
T modinv(T a, T p){
    T x, y;
    T d = exEuclid(a, p, x, y);
    if(d != 1) return -1;
    if(x <= -p || p <= x) x %= p;
    if(x < 0) x += p;
    return x;
}

//min{ a | a >= x && a%n == r }
template <typename T>
T floor(T x, T r, T n){
    T rtn = x + (r - x) % n;
    if(rtn < x) rtn += n;
    return rtn;
}

//max{ a | a <= x && a%n == r }
template <typename T>
T ceil(T x, T r, T n){
    T rtn = x - (x - r) % n;
    if(rtn > x) rtn -= n;
    return rtn;
}

int main(){
    while(1){
        int64_t x, p;
        cin >> x >> p;
        int64_t y = modinv(x, p);
        cout << x << " * " << y << " mod " << p << " = " << x*y%p << endl;
    }
}