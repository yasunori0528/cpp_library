#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

int main() {
    int loop; cin >> loop;
    //n枚をm個のグループに分ける(i個目のグループの枚数はl_i個)
    //sum(l_i) == n
    srand(time(NULL));
    vector<char> card = {'1','2','3','4','5','6','7','8','9','T','J','Q','K','X'};
    int n;
    vector<int> l(2);
    rep(i,2) cin >> l[i];
    n = l[0]+l[1];
    int m; cin >> m;
    string cnd_f;
    cin >> cnd_f;
    vector<string> cnd_s(m);
    rep(i,m) cin >> cnd_s[i];
    map<char,int> first_hands_condition;
    vector<map<char,int>> second_hands_condition(m);

    for(char c : card){
        first_hands_condition[c] = 0;
    }
    for(char card_fi : cnd_f){
        card_fi;
        first_hands_condition[card_fi]++;
    }

    rep(i,m){
        for(char c : card){
            second_hands_condition[i][c] = 0;
        }
        for(char card_si : cnd_s[i]){
            card_si;
            second_hands_condition[i][card_si]++;
        }
    }
    
    vector<int> L;//0がl_0個,1がl_1個,,,と続く列
    rep(i,2){
        rep(j,l[i]){
            L.push_back(i);
        }
    }

    bool check_input = true;
    if(L.size() != n || n > 54){
        check_input = false;
        cout << "wrong_input" << endl;
    }
    else cout << "correct_input" << endl;
    if(check_input){
        int ok = 0;
        int ng = 0;
        rep(lp,loop){
            vector<int> h(n);
            vector<int> c(54,0);
            vector<vector<int>> b(0,vector<int>(2));
            map<char,int> first_hands;
            map<char,int> second_hands;
            for(char c : card){
                first_hands[c] = 0;
            }
            for(char c : card){
                second_hands[c] = 0;
            }
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
            rep(i,n){
                int player = b[i][0];
                int cdi = b[i][1];
                char cdc;
                if(cdi < 36) cdc = '0' + cdi/4+1;
                else if(cdi < 40) cdc = 'T';
                else if(cdi < 44) cdc = 'J';
                else if(cdi < 48) cdc = 'Q';
                else if(cdi < 52) cdc = 'K';
                else cdc = 'X';
                if(player == 0) first_hands[cdc]++;
                else second_hands[cdc]++;
            }

            int first_condition = 0;
            for(char cd : card){
                if(cd == 'X'){
                    first_condition += first_hands[cd];
                    break;
                }
                if(first_hands[cd] < first_hands_condition[cd]){
                    first_condition += first_hands[cd]-first_hands_condition[cd];
                }
            }
            if(first_condition < 0) continue;
            bool second_condition_bool = false;
            rep(i,m){
                int second_condition = 0;
                for(char cd : card){
                    if(cd == 'X'){
                        second_condition += second_hands[cd];
                        break;
                    }
                    if(second_hands[cd] < second_hands_condition[i][cd]){
                        second_condition += second_hands[cd]-second_hands_condition[i][cd];
                    }
                }
                if(second_condition >= 0) second_condition_bool = true;
            }
            if(second_condition_bool) ng++;
            else ok++;
        }
        cout << ok << " " << ng << endl;
        double probability = 1.0*ok/(ok+ng);
        cout << fixed << setprecision(10);
        cout << probability << endl;
    }
}
