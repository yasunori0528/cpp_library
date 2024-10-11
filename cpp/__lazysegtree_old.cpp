#include <bits/stdc++.h>
using namespace std;

template <typename T>
bool chmax(T &a, const T& b) {
  if (a < b) {
    a = b;  // aをbで更新
    return true;
  }
  return false;
}

template <typename T>
bool chmin(T &a, const T& b) {
  if (a > b) {
    a = b;  // aをbで更新
    return true;
  }
  return false;
}

template <typename T>
struct lazySegtree{
    int sz;
    vector<T> dat;
    vector<T> lazy;
    T NUL;

    lazySegtree(int n){
        NUL = 0;

        sz = 1;
        while(sz <= n) sz *= 2;

        dat.resize(2*sz-1,NUL);
        lazy.resize(2*sz-1,NUL);
    }

    void eval(int k, int l, int r){
        if(lazy[k] != 0){
            dat[k] += lazy[k];
            if(r - l > 1){
                lazy[2*k+1] += lazy[k] / 2;
                lazy[2*k+2] += lazy[k] / 2;
            }
        }
        lazy[k] = 0;
        return;
    }

    void sub_add(int a, int b, T x, int k, int l, int r){
        eval(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b){
            lazy[k] += (r - l) * x;
            eval(k, l, r);
        }
        else{
            sub_add(a, b, x, 2*k+1, l, (l+r)/2);
            sub_add(a, b, x, 2*k+2, (l+r)/2, r);
            dat[k] = dat[2*k+1] + dat[2*k+2];
        }
        return;
    }
    void add(int a, int b, T x){
        sub_add(a, b, x, 0, 0, sz);
        return;
    }

    T sub_get(int a, int b, int k, int l, int r){
        if(b <= l || r <= a) return 0;
        eval(k, l, r);
        if(a <= l && r <= b) return dat[k];
        T vl = sub_get(a, b, 2*k+1, l, (l+r)/2);
        T vr = sub_get(a, b, 2*k+2, (l+r)/2, r);
        return vl + vr;
    }
    T get(int a, int b){
        return sub_get(a, b, 0, 0, sz);
    }
};

int main(){
    int N = 1000000;
    lazySegtree<int> S(N);
    while(1){
        int t, a, b;
        cin >> t >> a >> b;
        if(t == 1){
            int x; cin >> x;
            S.add(a, b, x);
        }
        else{
            cout << S.get(a, b) << endl;
        }
    }
}