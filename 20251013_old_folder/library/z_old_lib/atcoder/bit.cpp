#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct BIT {
    vector<T> bit;
    int N;

    BIT(int size){
        N = size;
        bit.resize(N+1);
    }

    void add(int a, T w){
        for(int x = a; x <= N; x += x & -x){
            bit[x] += w;
        }
    }

    T sum(int a){
        if(a == 0) return 0;
        T rtn = 0;
        for(int x = a; x > 0; x -= x & -x){
            rtn += bit[x];
        }
        return rtn;
    }

    void update(int a, T w){
        add(a, w - sum(a) + sum(a-1));
    }
};

int main(){

}