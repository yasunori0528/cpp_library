#include <bits/stdc++.h>
using namespace std;

template <typename T>
bool chmax(T &a, const T& b) {
  if (a < b) {
    a = b;  // aをbで更新
    return true;
  }
  return false;
}

template <typename T>
bool chmin(T &a, const T& b) {
  if (a > b) {
    a = b;  // aをbで更新
    return true;
  }
  return false;
}

int main(){
    //72, 127, 157
    int K = 3;
    int N; cin >> N;
    vector<double> V(K);
    for(int i = 0; i < K; i++){
        double d;
        int a;
        cin >> d >> a;
        V[i] = log10(d)+a;
    }

    vector<int> Dcost;
    vector<int> Scost = {0};
    {
        int i = 0;
        while(Scost[Scost.size()-1] <= N){
            Dcost.push_back(i/2+1);
            Scost.push_back(Scost[i]+Dcost[i]);
            i++;
        }
    }

    int M = Scost.size();
    cout << M << endl;
    vector<tuple<double,int,int,int>> ans(N+1,{0.0,0,0,0});
    for(int i = 0; i < M; i++){
        int ci = Scost[i];
        if(ci > N) break;
        for(int j = 0; j < M; j++){
            int cj = Scost[j];
            if(ci+cj > N) break;
            for(int k = 0; k < M; k++){
                int ck = Scost[k];
                if(ci+cj+ck > N) break;
                chmax(ans[ci+cj+ck], {V[0]*i+V[1]*j+V[2]*k, i, j, k});
            }
        }
    }

    vector<int> L = {N-157, N-127, N-72};
    for(int l : L){
        auto [d, i, j, k] = ans[l];
        cout << l << " " << d << " " << i << " " << j << " " << k << endl;
    }
}