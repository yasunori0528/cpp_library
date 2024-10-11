#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

int main() {
    srand(time(NULL));
    string numeral = "123456789";
    string ans;
    rep(i,4){
        int a = rand()%(9-i);
        ans.push_back(numeral[a]);
        numeral = numeral.substr(0,a)+numeral.substr(a+1);
    }
    cout << ans << endl;

    bool game = true;
    while(game){
        string s; cin >> s;
        bool ip = true;
        if(s.size() != 4) ip = false;
        rep(i,4){
            if(s[i] < '1' || '9' < s[i]){
                ip = false;
            }
        }
        rep(i,4){
            for(int j = i+1; j < 4; j++){
                if(s[i] == s[j]) ip = false;
            }
        }
        if(!ip) cout << "wrong_input" << endl;
        else {
            int hit = 0;
            int blow = 0;
            rep(i,4){
                rep(j,4){
                    if(s[i] == ans[j]){
                        if(i == j) hit++;
                        else blow++;
                    }
                }
            }
            cout << "hit : " << hit << " blow : " << blow << endl;
            if(hit == 4) game = false;
        }
    }
}
