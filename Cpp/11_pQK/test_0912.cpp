#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)
int f(){
    int n = rand();
    return n;
}

int main(){
    srand(time(NULL));
    rep(i,100){
        int a = f();
        cout << a << endl;
    }
    
}