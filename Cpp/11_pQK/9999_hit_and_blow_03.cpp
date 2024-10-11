#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
    rep(ans,10000){
        string sans = to_string(ans);
        if(sans.size() != 4) continue;
        bool bans = true;
        rep(i,4){
            if(sans[i] == '0'){
                bans = false;
                break;
            }
        }
        if(!bans) continue;
        rep(i,4){
            for(int j = i+1; j < 4; j++){
                if(sans[i] == sans[j]){
                    bans = false;
                    break;
                }
            }
            if(!bans) break;
        }
        if(!bans) continue;

        bool game = true;
        vector<vector<int>> res(0, vector<int>(3));
        vector<bool> oplog(10000,false);
        int cnt = 0;
        while(game){
            rep(i,10000){
                string s = to_string(i);
                if(s.size() != 4) continue;
                bool b = false;
                rep(j,4) {
                    if(s[j] == '0'){
                        b = true;
                        break;
                    }
                }
                if(b) continue;
                rep(j,4){
                    for(int k = j+1; k < 4; k++){
                        if(s[j] == s[k]) {
                            b = true;
                            break;
                        }
                    }
                    if(b) break;
                }
                if(b) continue;
                if(oplog[i]) continue;
                for(auto resi : res){
                    int ni = resi[0];
                    int hi = resi[1];
                    int bi = resi[2];
                    string si = to_string(ni);

                    int hi_ = 0;
                    int bi_ = 0;
                    rep(j,4){
                        rep(k,4){
                            if (s[j] == si[k]) {
                                if (j == k) hi_++;
                                else bi_++;
                            }
                        }
                    }
                    if(hi != hi_ || bi != bi_){
                        b = true;
                        break;
                    }
                }
                if(b) continue;
                s = to_string(i);
                if(cnt == 1){
                    i = 5678;
                    s = "5678";
                }
                //cout << cnt << "," << i << endl;
                cnt++;
                int hit = 0;
                int blow = 0;
                rep(j,4){
                    rep(k,4){
                        if(sans[j] == s[k]){
                            if(j == k) hit++;
                            else blow++;
                        }
                    }
                }
                if(hit == 4 && blow == 0) {
                    game = false;
                }
                res.push_back({i,hit,blow});
                oplog[i] = true;
                break;
            }
        }
        if(cnt >= 8){
            cout << ans << " : " << cnt << endl;
        }
    }
}
