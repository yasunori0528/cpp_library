#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
    //n枚をm個のグループに分ける(i個目のグループの枚数はl_i個)
    //sum(l_i) == n
    srand(time(NULL));
    int n; cin >> n;
    int m; cin >> m;
    vector<int> l(m);
    rep(i,m) cin >> l[i];
    vector<int> L;//0がl_0個,1がl_1個,,,と続く列
    rep(i,m){
        rep(j,l[i]){
            L.push_back(i);
        }
    }

    bool check_input = true;
    if(L.size() != n || n > 54){
        check_input = false;
        cout << "wrong_input" << endl;
    }

    if(check_input){
        rep(loop,1024){
            vector<int> h(n);
            vector<int> c(54,0);
            vector<vector<int>> b(0,vector<int>(2));
            int i = 0;
            while(i < n){
                int a = rand();
                if(a < 0x7fffffff/(54-i)*(54-i)){
                    a %= (54-i);
                    h[i] = a;
                    i++;
                }
            }

            rep(i,n){
                int cnt = 0;
                int g = h[i];
                rep(j,54){
                    int &d = c[j];
                    if(d == 0 && cnt == g){
                        d++;
                        b.push_back({L[i],j});
                        break;
                    }
                    if(d == 0) cnt++;
                }
            }
            sort(b.begin(),b.end());

            rep(i,n){
                if(i != 0){
                    int g0 = b[i-1][0];
                    int g1 = b[i][0];
                    if(g0 != g1) cout << ',';
                }
                int e = b[i][1];
                if(e < 36) cout << e/4+1;
                else if(e < 40) cout << 'T';
                else if(e < 44) cout << 'J';
                else if(e < 48) cout << 'Q';
                else if(e < 52) cout << 'K';
                else cout << 'X';
                cout << ',';
            }
            cout << endl;
        }
    }
}
