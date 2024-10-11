#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<vector<T>> operator+(vector<vector<T>> a, vector<vector<T>> b){
    int n = a.size();
    int m = a[0].size();
    vector<vector<T>> rtn(n,vector<T>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            rtn[i][j] = a[i][j]+b[i][j];
        }
    }
    return rtn;
}


template <typename T>
vector<vector<T>> operator*(vector<vector<T>> a, vector<vector<T>> b){
    int n = a.size();
    int m = a[0].size();
    int l = b[0].size();
    vector<vector<T>> rtn(n,vector<T>(m,0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            for(int k = 0; k < l; k++){
                rtn[i][k] += a[i][j]*b[j][k];
            }
        }
    }
    return rtn;
}

template <typename T>
void print(vector<vector<T>> v){
    for(auto i : v){
        bool b = 0;
        for(auto j : i){
            if(b) cout << " ";
            else b = 1;
            cout << j;
        }
        cout << endl;
    }
}

template<typename T>
vector<vector<T>> det(vector<vector<T>> a){
    ;
}

template <typename T>
vector<vector<T>> inv(vector<vector<T>> a){
    ;
}

int main(){
    int n, m, l;
    cin >> n >> m >> l;
    vector<vector<int>> a(n,vector<int>(m));
    vector<vector<int>> b(m,vector<int>(l));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    for(int j = 0; j < m; j++){
        for(int k = 0; k < l; k++){
            cin >> b[j][k];
        }
    }

    vector<vector<int>> v = a*b;
    print(v);
}