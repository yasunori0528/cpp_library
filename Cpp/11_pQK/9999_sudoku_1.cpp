#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

int main(){
    vector<string> input(9);
    rep(i,9) cin >> input[i];
    vector<vector<int>> a(9,vector<int>(9));
    /*rep(i,9){
        rep(j,9){
            int aij; cin >> aij; aij--;
            a[i][j] = aij;
        }
    }*/
    rep(i,9){
        rep(j,9){
            if(input[i][j] == 'x') a[i][j] = -1;
            else a[i][j] = input[i][j] - '1';
        }
    }

    vector<vector<int>> b(9,vector<int>(9));
    rep(i,9) rep(j,9) b[i][j] = 0b111111111;

    bool solve = true;

    bool bl0 = true;
    while(bl0){
        int cnt0 = 0;
        bool bl = true;
        while(bl){
            int cnt = 0;
            rep(i,9){
                rep(j,9){
                    int &aij = a[i][j];
                    if(aij < 0) continue;
                    b[i][j] = 1<<aij;
                    rep(l,9) if(l != i) b[l][j] &= (0b111111111-(1<<aij));
                    rep(l,9) if(l != j) b[i][l] &= (0b111111111-(1<<aij));
                    int p = i/3; int q = j/3;
                    rep(k,3){
                        rep(l,3){
                            if(3*p+k != i || 3*q+l != j) b[3*p+k][3*q+l] &= (0b111111111-(1<<aij));
                        }
                    }
                }
            }
            rep(i,9){
                rep(j,9){
                    int aij = a[i][j];
                    if(aij >= 0) continue;
                    int bij = b[i][j];
                    int cntbij = __builtin_popcount(bij);
                    if(cntbij == 1){
                        a[i][j] = __builtin_ctz(bij);
                        cnt++;
                        cnt0++;
                    }
                    else if(cntbij == 0){
                        bl = false;
                        solve = false;
                    }
                }
            }
            if(cnt == 0) bl = false;
        }
        bool bk = false;
        rep(i,1<<9){
            int bpi = __builtin_popcount(i);
            if(bpi < 2 || 7 < bpi) continue;
            //行
            rep(j,9){
                int cnt = 0;
                int cmb = 0b111111111;
                rep(k,9){
                    if((b[j][k]&i) == 0){
                        cnt ++;
                        cmb -= (1<<k);
                    }
                }
                if(bpi+cnt == 9){
                    rep(k,9){
                        if(cmb>>k&1){
                            int &bjk = b[j][k];
                            if((bjk|i) != i){
                                cnt0++;
                                bjk &= i;
                            }
                        }
                    }
                }
                else if(bpi+cnt > 9){
                    solve = false;
                    bk = true;
                    bl0 = false;
                    break;
                }
            }
            if(bk) break;
            //列
            rep(j,9){
                int cnt = 0;
                int cmb = 0b111111111;
                rep(k,9){
                    if((b[k][j]&i) == 0){
                        cnt ++;
                        cmb -= 1<<k;
                    }
                }
                if(bpi+cnt == 9){
                    rep(k,9){
                        if(cmb>>k&1){
                            int &bjk = b[k][j];
                            if((bjk|i) != i){
                                cnt0++;
                                bjk &= i;
                            }
                        }
                    }
                }
                else if(bpi+cnt > 9){
                    solve = false;
                    bk = true;
                    bl0 = false;
                    break;
                }
            }
            if(bk) break;
            //ブロック
            rep(j,9){
                int cnt = 0;
                int cmb = 0b111111111;
                rep(k,9){
                    if((b[j/3*3+k/3][j%3*3+k%3]&i) == 0){
                        cnt ++;
                        cmb -= 1<<k;
                    }
                }
                if(bpi+cnt == 9){
                    rep(k,9){
                        if(cmb>>k&1){
                            int &bjk = b[j/3*3+k/3][j%3*3+k%3];
                            if((bjk|i) != i){
                                cnt0++;
                                bjk &= i;
                            }
                        }
                    }
                }
                else if(bpi+cnt > 9){
                    solve = false;
                    bk = true;
                    bl0 = false;
                    break;
                }
            }
            if(bk) break;
        }
        
        if(cnt0 == 0) bl0 = false;
    }

    if(solve){
        rep(i,9){
            rep(j,9){
                cout << a[i][j]+1 << " ";
            }
            cout << endl;
        }
    }
    else cout << "Impossible" << endl;
}