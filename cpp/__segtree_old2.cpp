#include <bits/stdc++.h>
using namespace std;

random_device seed_gen;
mt19937 engine(seed_gen());

template <typename T>
struct monoid_min{
    T val;

    monoid_min(){
        val = numeric_limits<T>::max();
    }

    monoid_min(T x){
        val = x;
    }

    monoid_min e(){
        return monoid_min();
    }

    monoid_min operator*(monoid_min other){
        if(val < other.val) return monoid_min(val);
        return other;
    }
};

template <typename T>
struct monoid_max{
    T val;

    monoid_max(){
        val = numeric_limits<T>::min();
    }

    monoid_max(T x){
        val = x;
    }

    monoid_max e(){
        return monoid_max();
    }

    monoid_max operator*(monoid_max other){
        if(val > other.val) return monoid_max(val);
        return other;
    }
};

//モノイドのひな型
template <typename T>
struct monoid{
    T val;

    monoid(){
        ;
    }

    monoid(T x){
        val = x;
    }

    monoid e(){
        return monoid();
    }

    monoid operator*(monoid other){
        return monoid();
    }
};

template <typename T>
struct group_plus{
    T val;

    group_plus(){
        val = 0;
    }

    group_plus(T x){
        val = x;
    }

    group_plus e(){
        return group_plus();
    }

    group_plus operator*(group_plus other){
        return group_plus(val + other.val);
    }

    group_plus inv(){
        return group_plus(-val);
    }

    string monoid_to_string(){
        string rtn = to_string(val);
        return rtn;
    }

    bool operator==(group_plus other){
        return val == other.val;
    }
    bool operator!=(group_plus other){
        return val != other.val;
    }
};

//作用のひな型
//(元 : TからTへの写像, 演算 : 写像の合成) によって構成されるモノイド. Mと準同型
template <typename M, typename T>
struct monoid_mapping{
    M val;

    monoid_mapping(){
        val = val.e();
    }

    monoid_mapping(M f){
        val = f;
    }

    monoid_mapping e(){
        return monoid_mapping();
    }

    T map(T x){
        return T();
    }

    //写像 other*self
    monoid_mapping composition(monoid_mapping other){
        return this * other;
    }

    bool operator==(monoid_mapping other){
        return val == other.val;
    }
    bool operator!=(monoid_mapping other){
        return val != other.val;
    }
};

template <typename monoid>
struct mapping_add{
    monoid val;

    mapping_add(){
        val = val.e();
    }

    mapping_add(monoid x){
        val = x;
    }

    mapping_add id(){
        return mapping_add();
    }

    //f(s)
    monoid map(monoid s){
        return monoid(val * s);
    }

    //f^x(s)
    monoid map(monoid s, int x){
        return monoid(monoid(val.val * x) * s);
    }

    //写像 other*self
    mapping_add composition(mapping_add other){
        return mapping_add(other.val * val);
    }

    bool operator==(mapping_add other){
        return val == other.val;
    }
    bool operator!=(mapping_add other){
        return val != other.val;
    }
};

template <typename monoid>
struct segtree{
    int sz;
    vector<monoid> dat;

    segtree(){
        ;
    }
    
    segtree(int n){
        sz = 1;
        while(sz < n) sz *= 2;

        dat.resize(2*sz-1, monoid().e());
    }

    void update(int k, monoid a){
        k += sz-1;
        dat[k] = a;
        while(k > 0){
            k = (k-1)/2;
            dat[k] = dat[2*k+1]*dat[2*k+2];
        }
    }

    void plus(int k, monoid a){
        update(k, get(k, k+1)*a);
    }

    //[a,b)
    monoid get(int a, int b){
        return sub_get(a, b, 0, 0, sz);
    }

    monoid sub_get(int a, int b, int k, int l, int r){
        if(r <= a || b <= l) return monoid().e();
        if(a <= l && r <= b) return dat[k];
        monoid vl = sub_get(a, b, 2*k+1, l, (l+r)/2);
        monoid vr = sub_get(a, b, 2*k+2, (l+r)/2, r);
        return vl*vr;
    }

    void print(int a = 8){
        int len = sz;
        int i = 0;
        while(len){
            for(int j = 0; j < sz; j += len){
                //dat[i] : [j, j+len)
                string s(a * len - 1, ' ');
                string t = dat[i].monoid_to_string();
                int l = (a * len - t.size()) / 2;
                for(int k = 0; k < t.size(); k++){
                    s[l+k] = t[k];
                }
                cout << '|' << s;
                i++;
            }
            cout << "|\n";
            len /= 2;
        }
    }
};

template <typename monoid, typename mapping>
struct lazy_segtree{
    int sz;
    vector<monoid> dat;
    vector<mapping> lazy;

    lazy_segtree(int n){
        sz = 1;
        while(sz < n) sz *= 2;

        dat.resize(2*sz-1, monoid().e());
        lazy.resize(2*sz-1, mapping().id());
    }

    void eval(int k, int l, int r){
        if(lazy[k] != mapping().id()){
            dat[k] = lazy[k].map(dat[k], r - l);
            if(r - l > 1){
                lazy[2*k+1] = lazy[2*k+1].composition(lazy[k]);
                lazy[2*k+2] = lazy[2*k+2].composition(lazy[k]);
            }
        }
        lazy[k] = mapping().id();
        return;
    }

    void sub_apply(int a, int b, mapping f, int k, int l, int r){
        eval(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b){
            lazy[k] = lazy[k].composition(f);
            eval(k, l, r);
        }
        else{
            sub_apply(a, b, f, 2*k+1, l, (l+r)/2);
            sub_apply(a, b, f, 2*k+2, (l+r)/2, r);
            dat[k] = dat[2*k+1]*dat[2*k+2];
        }
        return;
    }

    void apply(int a, int b, mapping f){
        sub_apply(a, b, f, 0, 0, sz);
        return;
    }

    monoid sub_get(int a, int b, int k, int l, int r){
        if(b <= l || r <= a) return monoid().e();
        eval(k, l, r);
        if(a <= l && r <= b) return dat[k];
        monoid vl = sub_get(a, b, 2*k+1, l, (l+r)/2);
        monoid vr = sub_get(a, b, 2*k+2, (l+r)/2, r);
        return vl * vr;
    }
    
    monoid get(int a, int b){
        return sub_get(a, b, 0, 0, sz);
    }

    void print(int a = 16){
        int len = sz;
        int i = 0;
        while(len){
            for(int j = 0; j < sz; j += len){
                //dat[i] : [j, j+len)
                string s(a * len - 1, ' ');
                string t = dat[i].monoid_to_string();
                string u = lazy[i].val.monoid_to_string();
                string v = t + "(" + u + ")";
                int l = (a * len - v.size()) / 2;
                for(int k = 0; k < v.size(); k++){
                    s[l+k] = v[k];
                }
                cout << '|' << s;
                i++;
            }
            cout << "|\n";
            len /= 2;
        }
    }
};



int main(){
    int N = 8;
    lazy_segtree<group_plus<int>, mapping_add<group_plus<int>>> seg(N);

    for(int i = 0; i < 10; i++){
        int l = engine()%N;
        int r = engine()%N;
        if(l > r) swap(l, r);
        int x = engine()%100;

        cin >> l >> r >> x;
        seg.apply(l, r, mapping_add<group_plus<int>>(group_plus<int>(x)));
        seg.print();
        cout << endl;
    }
}
