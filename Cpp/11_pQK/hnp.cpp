#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

int main(){
    vector<int> ans(6,0);
    vector<int> ansa(6,0);
    vector<int> ansb(6,0);
    rep(i,32){
        vector<int> a;
        a.push_back(i%2);

        rep(j,4){
            if(i>>(j+1)&1) a.push_back(j+2);
            else a.push_back(a[j]);
        }
        //for(int j : a) cout << j;
        //cout << endl;

        vector<vector<int>> b(6,vector<int>(2,0));
        rep(j,6) b[j][1] = j;
        for(int j : a) b[j][0]++;
        sort(b.begin(),b.end());

        int w = a[4];
        int v = b[5][1];
        int u = b[4][1];

        int x = w;
        int y = v;
        if(v == w) y = u;
        ans[x]++; ansa[x]++;
        ans[y]++; ansb[y]++;
    }
    for(int i : ans) cout << i << " ";
    cout << endl;
    for(int i : ansa) cout << i << " ";
    cout << endl;
    for(int i : ansb) cout << i << " ";
    cout << endl;
}