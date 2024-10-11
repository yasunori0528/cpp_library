#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    int cnt = 0;
    for(int a = 1; a < n; a++){
        cnt += (n-1)/a;
    }
    cout << cnt << endl;
}