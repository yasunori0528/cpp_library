#include <bits/stdc++.h>
using namespace std;

int main(){
    srand(time(NULL));
    vector<int> p = {
        17,19,23,29,
        31,37,41,43,
        47,53,59,61,
        67,71,73,79
    };
    int n = p.size();

    int m; cin >> m;
    vector<int> v(m);
    for(int i = 0; i < m; i++){
        cin >> v[i];
    }

    vector<int> a;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(v[i] <= p[j]){
                a.push_back(v[i]*p[j]);
            }
        }
    }
    int sz = a.size();

    while(1){
        int x = rand()%sz;
        cout << a[x] << endl;
        while(1){
            int y; cin >> y;
            if(a[x]%y == 0) break;
        }        
    }
}