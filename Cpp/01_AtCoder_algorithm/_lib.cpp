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

//!時間取得
double calcTime()
{
    struct::timespec getTime;
    clock_gettime(CLOCK_MONOTONIC, &getTime);
    return (getTime.tv_sec + getTime.tv_nsec*1e-9) *1000;
}

//座標圧縮
template <typename T>
void compress(vector<T> &A){
    auto B = A;
    sort(B.begin(), B.end());
    B.erase(unique(B.begin(), B.end()), B.end());
    for(T &i : A){
        i = lower_bound(B.begin(), B.end(), i) - B.begin();
    }
    return;
}

//多次元配列
template <typename T>
struct box{
    vector<T> v;
    vector<int> size;
    vector<int> sub;
    int dim;
    box(){
        ;
    }
    box(vector<int> sz){
        size = sz;
        dim = sz.size();
        sub.resize(dim+1, 1);
        for(int i = dim-1; i >= 0; i--){
            sub[i] = sub[i+1]*size[i];
        }
        v.resize(sub[0]);
    }

    int pos(vector<int> a){
        int x = 0;
        for(int i = 0; i < dim; i++){
            x += a[i]*sub[i+1];
        }
        return x;
    }
    T at(vector<int> a){
        return v[pos(a)];
    }  
    void update(vector<int> a, T w){
        v[pos(a)] = w;
    }
};

int main(){
    int N = 3; int M = 4; int L = 5;
    box<int> B({N, M, L});
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            for(int k = 0; k < L; k++){
                B.update({i, j, k}, i+j+k);
            }
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            for(int k = 0; k < L; k++){
                cout << B.at({i, j, k}) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}