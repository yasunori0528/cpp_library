#include <bits/stdc++.h>
using namespace std;

struct UF {
    vector<int> par;
    vector<int> ran;
    vector<int> sz;

    UF(int n){
        par.resize(n);
        ran.resize(n);
        sz.resize(n,1);
        for(int i = 0; i < n; i++){
            par[i] = i;
        }
    }

    int find(int x){
        if(par[x] == x) return x;
        int rtn = find(par[x]);
        par[x] = rtn;
        return rtn;
    }

    void unite(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y) return;
        if(ran[x] < ran[y]){
            par[x] = y;
            sz[y] += sz[x];
        }
        else{
            par[y] = x;
            sz[x] += sz[y];
            if(ran[x] == ran[y]){
                ran[x]++;
            }
        }
    }

    bool same(int x, int y){
        return find(x) == find(y);
    }

    int siz(int x){
        return sz[find(x)];
    }
};
