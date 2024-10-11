//4(2)
#include <bits/stdc++.h>
using namespace std;

//combinationの計算
vector<vector<int64_t>> v_comb;
int64_t comb(int64_t x, int64_t y){
    if(y < 0 || x < y) return 0;
    if(y == 0 || y == x) return 1;
    if(v_comb[x][y] > 0) return v_comb[x][y];
    int64_t rtn = comb(x-1, y-1) + comb(x-1, y);
    v_comb[x][y] = rtn;
    return rtn;
}

int main(){
    v_comb.resize(100,vector<int64_t>(100,0));

    int n = 42;
    vector<int64_t> v(n,0);//v[i] : i回目に初めて白を引く確率*5*(50-i)C9
    int64_t sum_v = 0;//Σv[i]
    for(int i = 1; i < n; i++){
        v[i] = comb(50-i, 9);
        sum_v += v[i];
    }
    //cout << sum_v << endl;

    //半全探索部
    int m = n/2;
    vector<int64_t> l(1<<m);
    vector<int64_t> r(1<<(n-m));
    vector<int64_t> unsorted_l;//最後解を求めるためにソート前の配列を保存する
    vector<int64_t> unsorted_r;//最後解を求めるためにソート前の配列を保存する
    //[0,n/2)を全探索
    for(int i = 0; i < (1<<m); i++){
        if(i == 0) l[i] = 0;
        else{
            for(int j = 0; j < m; j++){
                if(i>>j&1){
                    l[i] = l[i-(1<<j)] + v[j];
                    break;
                }
            }
        }
    }
    unsorted_l = l;
    sort(l.begin(), l.end());

    //[n/2,n)を全探索
    for(int i = 0; i < (1<<(n-m)); i++){
        if(i == 0) r[i] = 0;
        else{
            for(int j = 0; j < n-m; j++){
                if(i>>j&1){
                    r[i] = r[i-(1<<j)] + v[j+m];
                    break;
                }
            }
        }
    }
    unsorted_r = r;
    sort(r.begin(), r.end());

    int szl = l.size();
    int szr = r.size();
    //cout << szl << " " << szr << endl;
    int64_t al, ar;//差が最小のときの左右それぞれの確率
    int64_t min_d = sum_v;//最小の差
    {
        int i = 0;
        int j = szr-1;
        while(i < szl && j >= 0){
            int64_t d = 2*(l[i]+r[j]) - sum_v;
            if(abs(d) < min_d){
                min_d = abs(d);
                al = l[i];
                ar = r[j];
            }
            if(d < 0) {
                i++;
            }
            else if(d > 0){
                j--;
            }
            else{
                break;
            }
        }
    }

    cout << "min : " << min_d << endl;

    for(int i = 0; i < (1<<m); i++){
        if(unsorted_l[i] == al){
            for(int j = 0; j < m; j++){
                if(i>>j&1){
                    cout << j << " ";
                }
            }
            break;
        }
    }
    for(int i = 0; i < (1<<(n-m)); i++){
        if(unsorted_r[i] == ar){
            for(int j = 0; j < n-m; j++){
                if(i>>j&1){
                    cout << j+m << " ";
                }
            }
            break;
        }
    }
    cout << endl;

}