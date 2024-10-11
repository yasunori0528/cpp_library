#include <bits/stdc++.h>
using namespace std;
template <typename T> using min_priority_queue = priority_queue<T,vector<T>,greater<T>>;

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

struct monoid_max{
    int64_t val;
    int64_t e;
    monoid_max(){
        e = -0x7FFFFFFFFFFFFFFF;
        val = e;
    }
    monoid_max(int64_t a){
        e = -0x7FFFFFFFFFFFFFFF;
        val = a;
    }
    monoid_max operator+(monoid_max &other){
        monoid_max rtn(max(val, other.val));
        return rtn;
    }
    void operator+=(monoid_max &other){
        chmax(val, other.val);
        return;
    }
};

struct monoid_min{
    int64_t val;
    int64_t e;
    monoid_min(){
        e = 0x7FFFFFFFFFFFFFFF;
        val = e;
    }
    monoid_min(int64_t a){
        e = 0x7FFFFFFFFFFFFFFF;
        val = a;
    }
    monoid_min operator+(monoid_min &other){
        monoid_min rtn(min(val, other.val));
        return rtn;
    }
    void operator+=(monoid_min &other){
        chmin(val, other.val);
        return;
    }
};

struct monoid_plus{
    int64_t val;
    int64_t e;
    monoid_plus(){
        e = 0;
        val = e;
    }
    monoid_plus(int64_t a){
        e = 0;
        val = a;
    }
    monoid_plus operator+(monoid_plus &other){
        monoid_plus rtn(val + other.val);
        return rtn;
    }
    void operator+=(monoid_plus &other){
        val += other.val;
        return;
    }
};

template <typename T>
struct segtree{
    int sz;
    vector<T> dat;
    T NUL;

    segtree(int n){
        NUL = T();
        sz = 1;
        while(sz <= n) sz *= 2;

        dat.resize(2*sz-1, T());
    }

    void update(int k, T a){
        k += sz-1;
        dat[k] = a;
        while(k > 0){
            k = (k-1)/2;
            dat[k] = dat[2*k+1]+dat[2*k+2];
        }
    }

    //[a,b)
    T get(int a, int b){
        return sub_get(a, b, 0, 0, sz);
    }

    T sub_get(int a, int b, int k, int l, int r){
        if(r <= a || b <= l) return NUL;
        if(a <= l && r <= b) return dat[k];
        T vl = sub_get(a, b, 2*k+1, l, (l+r)/2);
        T vr = sub_get(a, b, 2*k+2, (l+r)/2, r);
        return vl + vr;
    }
};

/*
struct action{
    int64_t val;
    int64_t e;
    action(){
        e = 0;
        val = e;
    }
    action(int64_t a){
        e = 0;
        val = a;
    }

    action operator*(action &other){
        action rtn(val + other.val);
        return rtn;
    }
    void operator*=(action &other){
        val += other.val;
        return;
    }
};
*/

/*
monoid operator+(action x, monoid m){
    monoid rtn(x.val + m.val);
}
*/

/*
struct lazySegtree{
    int sz;
    vector<monoid> dat;
    vector<monoid> lazy;

    lazySegtree(int n){
        sz = 1;
        while(sz <= n) sz *= 2;

        dat.resize(2*sz-1,monoid());
        lazy.resize(2*sz-1,monoid());
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

    void sub_act(int a, int b, T x, int k, int l, int r){
        eval(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b){
            lazy[k] += (r - l) * x;
            eval(k, l, r);
        }
        else{
            sub_act(a, b, x, 2*k+1, l, (l+r)/2);
            sub_act(a, b, x, 2*k+2, (l+r)/2, r);
            dat[k] = dat[2*k+1] + dat[2*k+2];
        }
        return;
    }
    void act(int a, int b, T x){
        sub_act(a, b, x, 0, 0, sz);
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
*/

int main(){
    int N; cin >> N;
    segtree<monoid_max> S(N);

    while(1){
        int t; cin >> t;
        if(t == 1){
            int a;
            int64_t x;
            cin >> a >> x;
            S.update(a, monoid_max(x));
        }
        else{
            int l, r;
            cin >> l >> r;
            cout << S.get(l, r).val << endl;
        }
    }
    return 0;
}
