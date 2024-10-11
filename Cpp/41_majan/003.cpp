#include <bits/stdc++.h>
using namespace std;

double f(int i, double r, double r_ave){
    double rtn = r + 10.0 - 4*i + (r_ave-r)*3/160;
    return rtn;
}

int main(){
    srand(time(NULL));
    int m = 4;
    double r_ave = 1650.0;
    vector<int> a(m);
    for(int i = 0; i < m; i++){
        cin >> a[i];
    }
    vector<int> b(m,0);
    for(int i = 0; i < m; i++){
        if(i) b[i] += b[i-1];
        b[i] += a[i];
    }

    int n;
    double r;
    cin >> n >> r;
    map<int,int> mp;
    for(int i = 0; i < n; i++){
        int j = upper_bound(b.begin(),b.end(),rand()%b[3]) - b.begin() + 1;
        r = f(j, r, r_ave);
        mp[round(r*10)]++;
    }

    for(auto pr : mp){
        cout << pr.first << "," << pr.second << endl;
    }
}