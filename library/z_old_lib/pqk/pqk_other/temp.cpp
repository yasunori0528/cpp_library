#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

#include "../pqk_lib/pqk_all.cpp"

int num_card(bigint x){
    if(x < 10) return 1;
    bigint d2 = x % 100;
    if(10 <= d2  && d2 <= 13) return num_card(x / 100) + 1;
    return num_card(x / 10) + 1;
}

int bigint_to_int(bigint x){
    //cout << "-L" << endl;
    //cout << x << " ";
    int sz = 31;
    vector<int> v;
    for(int i = 0; i < sz; i++){
        if(x % 2 == 0) v.push_back(0);
        else v.push_back(1);
        x /= 2;
    }

    int rtn = 0;
    for(int i = sz - 1; i >= 0; i--) rtn = rtn * 2 + v[i];
    //cout << rtn << endl;
    //for(auto i : v) cout << i << " ";
    //cout << endl;
    //cout << "-R" << endl;
    return rtn;
}

string bigint_to_string(bigint x){
    string s;
    while(x > 0){
        s.push_back('0' + bigint_to_int(x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

uint64_t str_to_comb(string s){
    uint64_t rtn = 0;
    for(auto c : s){
        rtn += uint64_t(1) << (char_to_int(c) * 3);
    }
    return rtn;
}

void init_hand_list(int N, set<pair<string,int>> &H){
    vector<int> loop(N+1, 1);
    loop[N] = 14;
    bool b = true;
    while(b){
        vector<int> a(15, 0);
        for(int i = 0; i < N; i++) a[loop[i]]++;
        bool b2 = true;
        for(int i = 1; i <= 14; i++){
            if(a[i] > 4) b2 = false;
            if(a[i] > 2 && i == 14) b2 = false;
        }

        if(b2){
            string s;
            for(int i = 0; i < N; i++) s.push_back(alphabet[loop[i]]);
            int cnt = 1;
            for(int i = 1; i <= 14; i++){
                if(i < 14){
                    if(a[i] == 1) cnt *= 4;
                    else if(a[i] == 2) cnt *= 6;
                    else if(a[i] == 3) cnt *= 4;
                }
                if(i == 14){
                    if(a[i] == 1) cnt *= 2;
                }
            }
            H.insert({s, cnt});
        }

        b = false;
        for(int i = 0; i < N; i++){
            if(loop[i] < loop[i+1]){
                loop[i]++;
                for(int j = 0; j < i; j++){
                    loop[j] = 1;
                }
                b = true;
                break;
            }
        }
    }
}

double eps = 1e-9;
int main(){
    double time_start = get_time();
    set<pair<string, int>> H;
    vector<bigint> S;

    int M = 12;
    int K = 9;
    init_hand_list(M, H);

    {
        vector<pair<string,int>> erase_list;
        for(auto h : H) if(h.second <= 2359295) erase_list.push_back(h);
        for(auto h : erase_list) H.erase(h);
        cout << H.size() << endl;
    }

    map<vector<string>, string> str_to_p;
    map<string, set<bigint>> hand_sep;
    size_t N = 1000;
    int ccc = 0;
    while(S.size() < N){
        map<bigint, double> mp;
        for(auto [s, x] : H){
            if(!hand_sep.count(s)){
                if(ccc % 1 == 0){
                    cout << "--" << s << " " << x << endl;
                }
                ccc++;
                vector<int> loop(K+1);
                for(int i = 0; i < K; i++) loop[i] = i;
                loop[K] = M;

                set<bigint> p_set;

                bool b = true;
                while(b){
                    vector<bool> v(M, false);
                    for(int i = 0; i < K; i++) v[loop[i]] = true;
                    vector<string> t, u;
                    for(int i = 0; i < M; i++){
                        if(v[i]) t.push_back(string(1, s[i]));
                        else u.push_back(string(1, s[i]));
                    }

                    //for(auto tt : t) cout << tt << " "; cout << endl;
                    //for(auto uu : u) cout << uu << " "; cout << endl;

                    string p;
                    if(str_to_p.count(t)) p = str_to_p[t];
                    else p = max_number(t);
                    string q;
                    if(str_to_p.count(u)) q = str_to_p[u];
                    else q = max_number(u);
                    //cout << p << endl;
                    //cout << q << endl;
                    if(p[0] != '-' && q[0] != '-'){
                        p_set.insert(str_to_int(p));
                        //cout << "--" << p << " " << q << endl;
                    }

                    b = false;
                    for(int i = 0; i < K; i++){
                        if(loop[i] < loop[i+1] - 1){
                            loop[i]++;
                            for(int j = 0; j < i; j++) loop[j] = j;
                            b = true;
                            break;
                        }
                    }
                }
                hand_sep[s] = p_set;
            }

            {
                auto p_set = hand_sep[s];
                int i = 0;
                while(p_set.size()){
                    bigint p = *p_set.rbegin();
                    mp[p] += double(x) / (i + 1);
                    p_set.erase(p);
                    i++;
                }
            }
        }
        double best_val = 0;
        bigint best_p = 0;
        for(auto[p, x] : mp){
            if(x > best_val + eps){
                best_val = x;
                best_p = p;
            }
            else if(x > best_val - eps){
                chmax(best_val, x);
                chmax(best_p, p);
            }
        }
        S.push_back(best_p);

        {
            vector<string> clear_list;
            for(auto [h, s] : hand_sep){
                if(s.count(best_p)) clear_list.push_back(h);
            }
            for(auto h : clear_list) hand_sep[h].clear();
        }

        cout << best_p << endl;
        /*for(auto[p, x] : mp){
            cout << p << " " << x << endl;
        }
        cout << string(32, '-') << endl;*/
    }

    double time_end = get_time();
    cout << fixed << setprecision(3);
    cout << (time_end - time_start) / 1e9 << "[s]" << endl;
}
