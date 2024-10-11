#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

bool pt(int64_t n){
    int s = 0; int64_t d = n-1;
    while(d%2 == 0){
        s++;
        d /= 2;
    }
    for(int i = 2; i < n-1; i++){
        
    }
}

int main(){
    int64_t n = 1000000;
    for(int64_t i = 3; i < n; i += 2){
        pt(i);
    }
}