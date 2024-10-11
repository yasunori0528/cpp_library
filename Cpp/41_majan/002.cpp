#include <bits/stdc++.h>
using namespace std;

double f(int i, double r, double r_ave){
    double rtn = r + 10.0 - 4*i + (r_ave-r)*3.0/800.0;
    //cout << i << "," << r << "," << 10.0 - 4*i + (r_ave-r)*3.0/800.0 << endl;
    return rtn;
}

int main(){
    srand(time(NULL));
    int m = 4;
    double r_ave = 1650.0;

    vector<int> a(m);
    double score = 0;
    for(int i = 0; i < m; i++){
        cin >> a[i];
        score += (i+1)*a[i];
    }

    int n;
    double r, l, u;
    cin >> n >> r >> l >> u;

    vector<int> b(m,0);
    for(int i = 0; i < m; i++){
        if(i) b[i] += b[i-1];
        b[i] += a[i];
    }
    score /= b[3];
    cout << score << endl;
    cout << r_ave + 3200*(2.5-score)/3 << endl;

    vector<int> v;
    for(int i = 0; i < n; i++){
        double r0 = r;
        int cnt = 0;
        while(l < r0 && r0 < u){
            int j = upper_bound(b.begin(),b.end(),rand()%b[3]) - b.begin() + 1;
            r0 = f(j, r0, r_ave);
            cnt++;
        }
        v.push_back(cnt);
    }
    
    int ans = v[n/2];
    cout << ans << endl;
}