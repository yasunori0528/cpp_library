#include <bits/stdc++.h>
using namespace std;

int m = 60;
map<vector<int>,set<int>> mp;

void calc(vector<int> v){
    if(mp.count(v)) return;
    int sz = 0;
    for(int i : v) sz += i;
    if(sz == 0) {
        return;
    }
    if(sz == 1){
        int x;
        for(int i = 0; i < m; i++){
            if(v[i]) {
                x = i;
                break;
            }
        }
        mp[v].insert(x);
        mp[v].insert(-x);
        return;
    }

    for(int i = 0; i < m; i++){
        if(v[i]){
            vector<int> w = v;
            w[i]--;
            calc(w);
            for(int j : mp[w]){
                mp[v].insert(i+j);
                mp[v].insert(i-j);
                mp[v].insert(i*j);
                mp[v].insert(-(i+j));
                mp[v].insert(-(i-j));
                mp[v].insert(-(i*j));
            }
        }
    }
}

int main(){
    /*while(1){
        int n; cin >> n;
        vector<int> v(m,0);
        for(int i = 0; i < n; i++){
            int x; cin >> x;
            v[x]++;
        }
        calc(v);
        for(int i : mp[v]){
            cout << i << " ";
        }
        cout << endl;
    }*/
    for(int i = 1; i < m; i++){
        for(int j = i; j < m; j++){
            cout << i << " " << j << endl;
            for(int k = j; k < m; k++){
                for(int l = k; l < m; l++){
                    vector<int> v(m,0);
                    v[i]++;
                    v[j]++;
                    v[k]++;
                    v[l]++;
                    calc(v);
                }
            }
        }
    }

    for(auto pr : mp){
        int sz = 0;
        for(int i : pr.first){
            sz += i;
        }
        if(sz < 4) continue;
        bool b = true;
        for(int x : pr.second){
            if(x%m == 0) {
                b = false;
                break;
            }
        }
        if(b){
            for(int i = 0; i < m; i++){
                for(int j = 0; j < pr.first[i]; j++){
                    cout << i << " ";
                }
            }
            cout << endl;
        }
    }
}