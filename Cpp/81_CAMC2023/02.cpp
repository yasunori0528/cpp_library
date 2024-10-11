#include <bits/stdc++.h>
using namespace std;

int main(){
    int m = 4;
    int n = pow(10,m);
    vector<int> g(9*m+1,0);
    for(int i = 1; i <= n; i++){
        int x = i;
        int s = 0;
        while(x > 0){
            s += x%10;
            x /= 10;
        }
        g[s]++;
    }
    for(int i = 1; i <= 9*m; i++){
        cout << i << " : " << g[i] << endl;
    }
}
//2(1)