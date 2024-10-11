//1(2)
#include <bits/stdc++.h>
using namespace std;

int n = 4;
int m = 5;
int ans = 0;

vector<pair<int,int>> v;//往路を保存するための配列

//vに応じた復路の探索((1)同様の帰納的な探索(DP))
void calc2(){
    vector<vector<int>> w(n,vector<int>(m,0));
    for(auto pr : v){
        w[pr.first][pr.second] = -1;
    }
    w[0][0] = 1;
    w[n-1][m-1] = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(w[i][j] == -1) continue;
            if(i != 0 && w[i-1][j] != -1) w[i][j] += w[i-1][j];
            if(j != 0 && w[i][j-1] != -1) w[i][j] += w[i][j-1];
            if(i != 0 && j != 0 && w[i-1][j-1] != -1) w[i][j] += w[i-1][j-1];
        }
    }

    ans += w[n-1][m-1];

    /*for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << w[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;*/
}

//往路の全探索(深さ優先)
void calc(int x, int y){
    /*cout << v.size() << " :";
    for(auto pr : v){
        cout << " (" << pr.first << "," << pr.second << ")";
    }
    cout << endl;*/

    if(x == n-1 && y == m-1){
        calc2();
    }

    if(x < n-1){
        v.push_back({x+1,y});
        calc(x+1,y);
        v.pop_back();
    }
    if(y < m-1){
        v.push_back({x,y+1});
        calc(x,y+1);
        v.pop_back();
    }
    if(x < n-1 && y < m-1){
        v.push_back({x+1,y+1});
        calc(x+1,y+1);
        v.pop_back();
    }
}

int main(){
    calc(0,0);
    cout << ans << endl;
}
//1(2)