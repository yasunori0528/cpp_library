#include <bits/stdc++.h>
using namespace std;

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;

int calc (string s){
    int n = s.size();
    if(n == 0) return 1;
    int rtn = -1;
    for(int i = 0 ; i < n; i++){
        if(s[i] == '^'){
            //cout << s.substr(0,i) << "," << s.substr(i+1) << endl;
            if(calc(s.substr(i+1)) == -2 || calc(s.substr(i+1))*log2(stoll(s.substr(0,i))) > 8){
                rtn = -2;
                break;
            }
            rtn = pow(stoll(s.substr(0,i)), calc(s.substr(i+1)));
            break;
        }
    }
    if(rtn == -1){
        rtn = stoll(s);
    }

    return rtn;
}

int main(){
    //min_cmp_d桁以上のpqk-cmpを全探索
    int min_cmp_d;
    cin >> min_cmp_d;

    vector<pair<int,string>> pow_list;
    for(int pow_x = 0; pow_x < 8; pow_x++){
        string s = "xxx";
        int pow_x_ = pow_x;
        for(int i = 2; i >= 0; i--){
            if(pow_x_%2) s = s.substr(0,i) + "^" + s.substr(i);
            pow_x_ /= 2;
        }
        while(1){
            if(s[0] == 'x') s = s.substr(1);
            else break;
        }
        if(s.size()) s = s.substr(1);
        //cout << s << ",";

        int cnt_x = 0;
        for(char c : s){
            if(c == 'x') cnt_x++;
        }
        //cout << cnt_x << endl;

        int looop = pow(10,cnt_x);
        for(int i = 0; i < looop; i++){
            int i_ = i;
            string exp_i = s;
            for(int j = 0; j < cnt_x; j++){
                for(int k = exp_i.size()-1; k >= 0; k--){
                    if(exp_i[k] == 'x'){
                        exp_i[k] = '0'+i_%10;
                        i_ /= 10;
                        break;
                    }
                }
            }
            bool b_exp_i = true;
            for(int j = 0; j < exp_i.size(); j++){
                if(exp_i[j] == '^') continue;
                if((j == 0 || exp_i[j-1] == '^') && exp_i[j] == '0'){
                    b_exp_i = false;
                    break;
                }
                if((j == 0 || exp_i[j-1] == '^') && (j == exp_i.size()-1 || exp_i[j+1] == '^') && exp_i[j] == '1'){
                    b_exp_i = false;
                    break;
                }
            }
            if(!b_exp_i) continue;
            int exp_i_int = calc(exp_i);
            if(exp_i_int == -2 || exp_i_int > 229) continue;
            pow_list.push_back(make_pair(exp_i_int,exp_i));
            //cout << exp_i << "," << exp_i_int << endl;
        }
    }

    //素因数場を'*'で分割したときの(桁数,分割の個数,桁数の組)
    vector<tuple<int,int,vector<int>>> e_comb;
    {
        for(int d = 1; d <= 72-min_cmp_d; d++){
            vector<int> v;
            v.push_back(d);
            vector<int> v_sum;
            v_sum.push_back(d);
            e_comb.push_back(make_tuple(d,v.size(),v));

            int cnt = 0;
            while(v[0] > 1){
                int v_size = v.size();
                for(int i = v_size-1; i >= 0; i--){
                    if(v[i] == 1) {
                        v.pop_back();
                        v_sum.pop_back();
                    }
                    else{
                        v[i]--;
                        v_sum[i]--;
                        int d_ = d-v_sum[i];
                        while(d_ > 0){
                            int min_d_vi = min(d_,v[i]);
                            v.push_back(min_d_vi);
                            v_sum.push_back(v_sum[v_sum.size()-1]+min_d_vi);
                            d_ -= v[i];
                        }
                        break;
                    }
                }
                int ecd_i = 0;
                for(int j : v){
                    ecd_i += j;
                }

                e_comb.push_back(make_tuple(ecd_i, v.size(), v));

                /*for(int vj : v){
                    cout << vj << ",";
                }
                cout << endl;*/
                /*for(int vj : v_sum){
                    cout << vj << ",";
                }
                cout << endl;*/
            }
        }
        
    }
    sort(e_comb.begin(), e_comb.end());
    /*for(auto i : e_comb){
        int x, y;
        vector<int> v;
        tie(x,y,v) = i;
        cout << x << "," << y << ";";
        for(int vi : v) cout << vi << ","; cout << endl;
    }*/

    for(auto i : e_comb){
        int x, y;
        vector<int> v;
        tie(x, y, v) = i;
        
    }
}