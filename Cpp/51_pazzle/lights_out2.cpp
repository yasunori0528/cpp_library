#include <bits/stdc++.h>
using namespace std;

template <typename T> using min_priority_queue = priority_queue<T,vector<T>,greater<T>>;

//!時間取得
double calcTime()
{
    struct::timespec getTime;
    clock_gettime(CLOCK_MONOTONIC, &getTime);
    return (getTime.tv_sec + getTime.tv_nsec*1e-9) *1000;
}

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

bool yn(bool b){
    if(b) cout << "Yes" << endl;
    else cout << "No" << endl;
    return b;
}

void input(){
    return;
}

void input_debug(){
    return;
}

void calc(){
    srand(time(NULL));
    vector<vector<int>> dir = {{0,0},{1,0},{1,1},{0,1},{-1,0},{-1,-1},{0,-1}};
    vector<int> a;
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if(abs(i-j) < 4){
                a.push_back(7*i+j);
            }
        }
    }

    int n = 49;
    vector<vector<int>> w(n,vector<int>(n,0));
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if(abs(i-j) > 3) continue;
            for(auto k : dir){
                if(i+k[0] < 0) continue;
                if(i+k[0] >= 7) continue;
                if(j+k[1] < 0) continue;
                if(j+k[1] >= 7) continue;
                if(abs(i+k[0]-j-k[1]) > 3) continue;
                /*if((i+k[0])*7+(j+k[1]) == 8) continue;
                if((i+k[0])*7+(j+k[1]) == 25) continue;
                if((i+k[0])*7+(j+k[1]) == 29) continue;
                if((i+k[0])*7+(j+k[1]) == 30) continue;
                if((i+k[0])*7+(j+k[1]) == 35) continue;*/
                w[i*7+j][(i+k[0])*7+(j+k[1])] = 1;
            }
        }
    }

    int m = 37;
    vector<vector<int>> v(m,vector<int>(m+1,0));
    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            v[i][j] = w[a[i]][a[j]];
        }
    }
    for(int i = 0; i < m; i++){
        int x; cin >> x;
        v[i][m] = (7-x)%6;
        //v[i][m] = rand()%6;
    }



    vector<vector<int>> v2 = v;
    for(auto &i : v2){
        for(auto &j : i){
            j %= 2;
        }
    }
    for(int i = 0; i < m; i++){
        sort(v2.begin(),v2.end());
        reverse(v2.begin(),v2.end());
        for(int j = i; j < m; j++){
            if(v2[j][i]){
                for(int k = 0; k < m; k++){
                    if(j != k && v2[k][i]){
                        for(int l = 0; l < m+1; l++){
                            v2[k][l] = (v2[k][l]-v2[j][l]+2)%2;
                        }
                    }
                }
            }
            break;
        }
    }
    /*for(auto i : v2){
        for(auto j : i){
            cout << j << " ";
        }
        cout << endl;
    }*/

    vector<int> ans(m);
    for(int i = 0; i < m; i++){
        ans[i] = (3*v2[i][m])%6;
    }

    vector<int> b(m);
    for(int i = 0; i < m; i++){
        b[i] = v[i][m];
        for(int j = 0; j < m; j++){
            b[i] -= v[i][j]*ans[j];
        }
        b[i] = (b[i]%6+6)%6;
    }
    /*for(int i : b){
        cout << i << " ";
    }
    cout << endl;*/

    vector<vector<int>> v3 = v;
    for(int i = 0; i < m; i++){
        v3[i][m] = b[i]%3;
    }
    for(auto &i : v3){
        for(auto &j : i){
            j %= 3;
        }
    }
    /*for(auto i : v3){
        for(auto j : i){
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;*/

    for(int i = 0; i < m; i++){
        sort(v3.begin(),v3.end());
        reverse(v3.begin(),v3.end());
        for(int j = i; j < m; j++){
            if(v3[j][i]){
                int v3ji = v3[j][i];
                for(int l = 0; l <= m; l++){
                    //cout << j << " " << l << endl;
                    //cout << v3[j][l] << "*" << v3[j][i] << endl;
                    v3[j][l] = (v3[j][l]*v3ji)%3;
                    //cout << v3[j][l] << endl;
                }
                for(int k = 0; k < m; k++){
                    if(j != k && v3[k][i]){
                        int d = 1;
                        if(v3[j][i] != v3[k][i]) d = 2;
                        for(int l = 0; l < m+1; l++){
                            v3[k][l] = (v3[k][l]-d*v3[j][l]+6)%3;
                        }
                    }
                }
            }
            break;
        }
        /*for(auto j : v3){
            for(auto k : j){
                cout << k << " ";
            }
            cout << endl;
        }
        cout << endl;*/
    }
    for(int i = 0; i < m; i++){
        ans[i] += v3[i][m]*4;
        ans[i] %= 6;
    }

    
    /*cout << endl;
    for(auto i : v3){
        for(auto j : i){
            cout << j << " ";
        }
        cout << endl;
    }*/

    
    set<int> s;
    s.insert(3);
    s.insert(8);
    s.insert(14);
    s.insert(21);
    s.insert(27);
    s.insert(32);
    s.insert(36);
    cout << "   ";
    int cnt = 2;
    for(int i = 0; i < m; i++){
        cout << ans[i] << " ";
        if(s.count(i)) {
            cout << endl;
            for(int j = 0; j < abs(cnt); j++){
                cout << " ";
            }
            cnt--;
        }
    }
    cout << endl;
}

int main(){
    //input_debug();
    input();
    calc();
    return 0;
}
