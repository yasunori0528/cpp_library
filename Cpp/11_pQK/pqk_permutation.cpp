#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;
// 仮数部が1024ビットの浮動小数点数型(TLEしたら小さくする)
using Real = mp::number<mp::cpp_dec_float<1024>>;

vector<vector<Bint>> comb_vec(55,vector<Bint>(55,0));
Bint comb(int n, int m){
    if(n < 0 || m < 0 || m > n) return 0;
    if(n == 0 || n == 1) return 1;
    Bint c_nm = comb_vec[n][m];
    if(c_nm > 0){
        return c_nm;
    }
    Bint rtn;
    if(m == 0 || m == n) {
        rtn = 1;
    }
    else{
        rtn = comb(n-1,m-1)+comb(n-1,m);
    }
    comb_vec[n][m] = rtn;
    return rtn;
}

int main(){
    int t_start = time(NULL);
    int t_0 = time(NULL);
    int t_interval = 3600;

    int x = 13;
    int y = 4;

    vector<Bint> fact(x*y+3);
    fact[0] = 1;
    for(int i = 1; i < x*y+3; i++){
        fact[i] = i*fact[i-1];
        //cout << fact[i] << endl;
    }

    vector<vector<Bint>> cnt(x*y+3,vector<Bint>((x+max(x-9,0))*y+5,0));
    for(int wild1 = -1; wild1 <= x; wild1++){
        for(int wild2 = wild1; wild2 <= x; wild2++){
            vector<int> loop_max(x+1,y);
            loop_max[0] = 0;
            if(wild1 >= 0) loop_max[wild1]++;
            if(wild2 >= 0) loop_max[wild2]++;

            vector<int> loop_now(x+1,0);
            if(wild1 >= 0) loop_now[wild1] = loop_max[wild1];
            if(wild2 >= 0) loop_now[wild2] = loop_max[wild2];

            while(true){
                int t_1 = time(NULL);
                if(t_1 - t_0 >= t_interval){
                    cout << "time:" << t_1-t_start << "///";
                    for(int i = 0; i <= x; i++){
                        for(int j = 0; j < loop_now[i]; j++){
                            cout << i << ",";
                        }
                    }
                    cout << endl;
                    t_0 = t_1;
                }

                int n = 0;
                int m = 0;
                Bint cnt_nm = 1;
                for(int i = 0; i <= x; i++){
                    int ln_i = loop_now[i];
                    n += 1*ln_i;
                    if(i < 10){
                        m += 1*ln_i;
                    }
                    else{
                        m += 2*ln_i;
                    }
                }
                int n_ = n;
                for(int i = 0; i <= x; i++){
                    int ln_i = loop_now[i];
                    if(i == 0) cnt_nm *= comb(n_-1, ln_i);
                    else cnt_nm *= comb(n_, ln_i);
                    n_ -= ln_i;
                }
                cnt[n][m] += cnt_nm;
                /*for(int i = 0; i <= x; i++){
                    for(int j = 0; j < loop_now[i]; j++){
                        cout << i << ",";
                    }
                }
                cout << endl;*/

                //vector update
                bool b = true;
                for(int i = x; i >= 0; i--){
                    if(i == wild1 || i == wild2){
                        continue;
                    }
                    if(loop_now[i] < loop_max[i]){
                        loop_now[i]++;
                        for(int j = i+1; j <= x; j++){
                            if(j != wild1 && j != wild2){
                                loop_now[j] = 0;
                            }
                        }
                        b = false;
                        break;
                    }
                }
                if(b) break;
            }
        }
    }

    for(vector<Bint> cnti : cnt){
        for(Bint cntij : cnti){
            cout << cntij << ",";
        }
        cout << endl;
    }

    int t_end = time(NULL);
    cout << "///" << t_end - t_start << "[s]" << endl;
}