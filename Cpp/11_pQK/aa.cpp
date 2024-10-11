#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main(){
    int n;
    int x, y;
    cin >> n >> x >> y;
    double p = (double)x/y;
    vector<vector<double>>a(1,vector<double>(n+1,0));
    a[0][0] = 1;
    for(int i = 1; i <= 1000000; i++){
        a.push_back(vector<double>(n+1));
        rep(j,n+1){
            if(j == 0){
                double sum_aij = 0;
                rep(j,n) sum_aij += a[i-1][j];
                a[i][j] = (1-p)*sum_aij;
            }
            else{
                a[i][j] = p*a[i-1][j-1];
            }
        }
    }

    double ans = 0;
    rep(i,1000001) ans += i*a[i][n];
    cout << ans << endl;
}