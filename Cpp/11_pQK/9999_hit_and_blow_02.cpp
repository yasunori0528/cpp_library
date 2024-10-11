#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
    bool game = true;
    vector<vector<int>> res(0, vector<int>(3));
    vector<bool> oplog(10000,false);
    srand(time(NULL));

    while(game){
        bool op_option = false;
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
            op_option = true;
            cout << i << endl;
            int hit, blow;
            bool ip = false;
            while(!ip){
                cin >> hit >> blow;
                if(hit < 0 || blow < 0 || (hit+blow) > 4 || (hit == 3 && blow == 1)){
                    cout << "wrong_input" << endl;
                }
                else ip = true;
            }
            if(hit == 4 && blow == 0) {
                game = false;
            }
            res.push_back({i,hit,blow});
            oplog[i] = true;
        }
        if(!op_option){
            cout << "No_option" << endl;
            game = false;
        }
    }
}
