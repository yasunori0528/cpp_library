#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

#include "../pqk_lib/pqk_all.cpp"

bool number_test(bigint x){
    //return miller_rabin(x);
    if(gcd(x % 10, 10) != 1) return false; 
    x /= 10;
    x *= 10;
    return miller_rabin(x + 1) && miller_rabin(x + 3) && miller_rabin(x + 7) && miller_rabin(x + 9);
}

bigint solve(){
    string stem = "99998888777766665555444433332222KKKKK";//mod 3 = 1
    bigint stem_int = str_to_int(stem) * pow(bigint(10), 30);
    //TJQA*4+X(-A)
    //'10'*4+'12'*4+'1'*12+X(X=J) or '10'*4+'12'*4+'1'*11+X()
    vector<int> v;
    for(int i = 0; i < 4; i++) v.push_back(10);
    for(int i = 0; i < 12; i++) v.push_back(1);
    for(int i = 0; i < 4; i++) v.push_back(12);
    sort(v.begin(), v.end());
    int n = v.size();
    bigint max_val = 0;
    string max_str;
    int64_t loop_cnt = 0;
    int64_t loop_all =
    //5290740;
    8817900;
    set<bigint> S;
    do{
        string s;
        for(int i : v) s.push_back(alphabet[i]);

        loop_cnt++;
        if(floor((int64_t)1000 * (loop_cnt - 1), loop_all) < floor((int64_t)1000 * loop_cnt, loop_all)){
            int64_t a = 1000 * loop_cnt / loop_all;
            cout << to_string(a + 1000).substr(1) << " " << s << endl;
        }

        for(int i = 0; i <= n; i++){
            string t;
            if(i > 0) t += s.substr(0, i);
            t += "X";
            if(n - i > 0) t += s.substr(i);
            int cntJ = 0;
            {
                int temp = 0;
                for(char c : t){
                    if(c == '1') temp++;
                    else temp = 0;
                    if(temp >= 2){
                        cntJ++;
                        temp -= 2;
                    }
                }
            }
            if(cntJ < 4) continue;
            vector<int> X =
            //{12, 13};
            {12};
            //{10, 13};
            for(int x : X){
                t[i] = alphabet[x];
                bigint t_int = str_to_int(t);
                S.insert(t_int);
            }
        }
    }while(next_permutation(v.begin(), v.end()));

    int64_t s_cnt = 0;
    int64_t s_all = S.size();
    while(S.size()){
        bigint x = *(S.rbegin());
        S.erase(x);
        x += stem_int;

        if(floor((s_cnt - 1) * 1000, s_all) < floor(s_cnt * 1000, s_all)){
            cout << to_string(floor(s_cnt * 1000, s_all) + 1000).substr(1) << " " << x << endl;
        }
        s_cnt++;

        if(number_test(x)) return x;
    }
    return 0;
}

int main(){
    auto time_start = get_time();
    cout << solve() << endl;
    auto time_end = get_time();
    cout << (time_end - time_start) / 1e9 << "[s]" << endl;
}
