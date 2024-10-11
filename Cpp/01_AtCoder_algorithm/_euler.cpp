#include <bits/stdc++.h>
using namespace std;
template <typename T> using min_priority_queue = priority_queue<T,vector<T>,greater<T>>;

template<typename T>
void printv(vector<T> &v){
    bool b = false;
    for(auto i : v){
        if(b) cout << " ";
        else b = true;
        cout << i;
    }
    cout << endl;
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
bool chmax(T &a, const T& b) {
    if (a < b) {
        a = b;  // aをbで更新
        return true;
    }
    return false;
}

template <typename T>
struct segtree_min{
    int sz;
    vector<T> dat;
    T NUL;

    segtree_min(){
        ;
    }

    segtree_min(int n){
        NUL = 1;
        while(chmax(NUL,2*NUL));

        sz = 1;
        while(sz <= n) sz *= 2;

        dat.resize(2*sz-1,NUL);
    }

    void update(int k, T a){
        k += sz-1;
        dat[k] = a;
        while(k > 0){
            k = (k-1)/2;
            dat[k] = min(dat[2*k+1],dat[2*k+2]);
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
        return min(vl, vr);
    }
};

template <typename T>
struct segtree_plus{
    int sz;
    vector<T> dat;
    T NUL;

    segtree_plus(){
        ;
    }
    
    segtree_plus(int n){
        NUL = 0;

        sz = 1;
        while(sz <= n) sz *= 2;

        dat.resize(2*sz-1,NUL);
    }

    void update(int k, T a){
        k += sz-1;
        dat[k] = a;
        while(k > 0){
            k = (k-1)/2;
            dat[k] = dat[2*k+1] + dat[2*k+2];
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

struct euler{
    int n;
    vector<tuple<int,int,int64_t>> e;
    vector<vector<pair<int, int64_t>>> g;

    vector<int> in;
    vector<int> out;
    vector<int> parent;
    vector<int> edge;
    segtree_plus<int64_t> edge_weight;
    segtree_min<int> depth;

    euler(){
        ;
    }
    euler(int x){
        n = x;
        e.resize(n-1);
        g.resize(n);
        in.resize(n);
        out.resize(n);
        parent.resize(n);
        edge.resize(2*n);
        edge_weight  = segtree_plus<int64_t>(2*n);
        depth = segtree_min<int>(2*n);
    }

    void input(){
        for(int i = 0; i < n-1; i++){
            int u, v;
            int64_t w;
            cin >> u >> v >> w;
            u--; v--;
            e[i] = {u, v, w};
        }
    }

    void calc_g(){
        for(auto[u, v, w] : e){
            g[u].push_back(make_pair(v, w));
            g[v].push_back(make_pair(u, w));
        }
    }

    void init_sub(int v, int p, int &i, int64_t w_pv, int &d){
        parent[v] = p;
        in[v] = i;
        edge[i] = v;
        edge_weight.update(i, w_pv);
        depth.update(i, d);
        i++;

        d++;
        for(auto[u, w_vu] : g[v]){
            if(u == p) continue;
            init_sub(u, v, i, w_vu, d);
        }
        d--;

        out[v] = i;
        edge[i] = -v;
        edge_weight.update(i, -w_pv);
        depth.update(i, d-1);
        i++;
    }

    void init(){
        calc_g();
        int i = 0;
        int d = 0;
        init_sub(0, -1, i, 0, d);
    }

    void update(int i, int64_t w){
        auto[p, u, ignore] = e[i];
        if(parent[u] != p) swap(u, p);
        edge_weight.update(in[u], w);
        edge_weight.update(out[u], -w);
    }

    int lca(int u, int v){
        int i = in[u];
        int j = in[v];
        if(i > j) swap(i, j);
        j++;

        int min_d = depth.get(i, j);
        while(j-i > 1){
            int m = (i+j)/2;
            if(depth.get(i, m) == min_d) j = m;
            else i = m;
        }

        int x = edge[i];
        if(x < 0) x = parent[-x];
        return x;
    }

    int64_t dist(int u, int v){
        int a = lca(u, v);
        int64_t du = edge_weight.get(in[0], in[u]+1);
        int64_t dv = edge_weight.get(in[0], in[v]+1);
        int64_t da = edge_weight.get(in[0], in[a]+1);
        return du+dv-2*da;
    }
};

int main(){
    ;
}