#include <bits/stdc++.h>
using namespace std;

int main(){
    const int N = 0b1111;
    const int M = 0b1000;    
    vector<int> H(N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            H[i] += (__builtin_popcount(i-j+1) == 1)<<j;
        }
    }

    vector<vector<int>> outputlist;
    for(int k = 1; k < (1<<N); k++){
        int s = 0;
        vector<int> v;
        for(int i = 0; i < N; i++){
            if(k>>i&1) {
                s ^= H[i];
                v.push_back(i+1);
            }
        }
        if(s == 0 && v.size() <= 5){
            outputlist.push_back(v);
        }
    }

    for(auto h : H){
        cout << bitset<M>(h) << endl;
    }

    sort(outputlist.begin(), outputlist.end());
    for(auto i : outputlist){
        for(auto j : i){
            cout << j << " ";
        }
        cout << endl;
    }
}