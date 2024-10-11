#include <bits/stdc++.h>
using namespace std;

//初手語頭iのときの勝者
bool win_i(int i, int n, vector<vector<int>> vec){
    bool b = false;
    for(int j = 0; j < n; j++){
        //初手語頭i語尾j
        if(vec[i][j] > 0){
            vector<vector<int>> vec_ij = vec;
            vec_ij[i][j]--;
            if(!win_i(j,n,vec_ij)) b = true;
        }
    }
    return b;
}

bool win(int n, vector<vector<int>> vec){
    bool b = false;
    for(int i = 0; i < n; i++){
        if(win_i(i,n,vec)) b = true;
    }
    return b;
}

int main(){
    int n; cin >> n;
    vector<vector<int>> dictionary(n,vector<int>(n));
    int size = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int dij; cin >> dij;
            dictionary[i][j] = dij;
            size += dij;
        }
    }
    bool b;
    if(win(n,dictionary)) {
        cout << "first" << endl;
        b = true;
    }
    else {
        cout << "second" << endl;
        b = false;
    }

    int prej = 0;
    bool end = false;
    for(int k = 0; k < size; k++){
        if(k == 0){
            bool bk = false;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(dictionary[i][j] > 0){
                        vector<vector<int>> vec_ij = dictionary;
                        vec_ij[i][j]--;
                        if(win_i(j,n,vec_ij) == !b) {
                            cout << "(" << i << "," << j << ")," << endl;
                            dictionary = vec_ij;
                            prej = j;
                            b = !b;
                            bk = true;
                            break;
                        }
                    }
                }
                if(bk) break;
            }
        }
        else{
            for(int j = 0; j < n; j++){
                if(dictionary[prej][j] > 0){
                    vector<vector<int>> vec_ij = dictionary;
                    vec_ij[prej][j]--;
                    if(win_i(j,n,vec_ij) == !b) {
                        cout << "(" << prej << "," << j << ")," << endl;
                        dictionary = vec_ij;
                        prej = j;
                        b = !b;
                        break;
                    }
                }
                if(j == n-1) end = true;
            }
        }
        if(end) {
            cout << k << endl;
            break;
        }
    }
}