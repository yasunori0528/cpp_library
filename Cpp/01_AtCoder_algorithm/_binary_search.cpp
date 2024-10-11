#include <bits/stdc++.h>
using namespace std;

template<typename T, typename S, typename U, class fn>
T lower_bound(T l, T r, T eps, fn f, S x, U k){
    while(r - l > eps){
        T m = (l + r) / 2;
        if(f(m, x) < k) l = m;
        else r = m;
    }
    return r;
}

template<typename T, typename S, typename U, class fn>
T upper_bound(T l, T r, T eps, fn f, S x, U k){
    while(r - l > eps){
        T m = (l + r) / 2;
        if(f(m, x) <= k) l = m;
        else r = m;
    }
    return r;
}

int f(int x, int y){
    return x * y;
}

int main(){
    cout << fixed << setprecision(20);
    int l = 0;
    int r = 10000;
    auto[x, y] = binary_search(0, 10000, 1, f, 124);
    cout << x << " " << y << endl;
}
