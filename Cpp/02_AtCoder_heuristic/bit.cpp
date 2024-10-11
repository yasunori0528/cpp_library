#include <bits/stdc++.h>
using namespace std;

struct BIT {
    vector<int64_t> bit;
    int N;

    BIT(int size){
        N = size();
        bit.resize(N+1);
    }

    void add(int a, int w){
        for(int x = a; x <= N; x += x & -x){
            bit[x] += w;
        }
    }

    int64_t sum(int a){
        int rtn = 0;
        for(int x = a; x > 0; x -= x & -x){
            rtn += bit[x];
        }
        return rtn;
    }
};

int main(){

}