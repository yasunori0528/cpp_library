#include <bits/stdc++.h>
using namespace std;

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;
using Real = mp::number<mp::cpp_dec_float<128>>;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

Real fact(Real n){
    if(n == 0) return 1;
    return n*fact(n-1);
}

Bint dtoB(double d){
    if(d < 1) return 0;
    int i;
    double f;
    f = frexp(d, &i);
    double d_ = d - pow(2,i-1);
    Bint rtn = pow((Bint)2,i-1)+dtoB(d_);
    return rtn;
}

string Bint_to_string(Bint n){
    if(n == 0) return "0";
    string s;
    while(n > 0){
        Bint k = n%10;
        char c = '0'+(int)k;
        s = c + s;
        n /= 10;
    }
    return s;
}

vector<int64_t> prime_list;
void prime_calc(int64_t MAX_N){
    for(int64_t i = 2; i <= MAX_N; i++){
        bool b = true;
        for(int64_t j = 2; j < i; j++){
            if(i%j == 0){
                b = false;
                break;
            }
            else if(j*j > i) break;
        }
        if(b) prime_list.push_back(i);
    }
}
bool pt(Bint n){
    if(n < 2) return false;
    for(int64_t i : prime_list){
        if(i*i > n) break;
        if(n%i == 0) return false;
    }
    return true;
}

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
    //個数を常用対数で 1/m 刻みで数える
    int m; cin >> m;
    //10^d_max_ex 以下の素数は全探索する
    int d_max_ex; cin >> d_max_ex;
    //素因数場の最大桁数 25,47
    int d_max; cin >> d_max;
    //素因数場の'*'を含まない部分の最大桁数
    int e_d_max = min(36,d_max);
    
    auto start = chrono::system_clock::now();

    srand(time(NULL));

    prime_calc(pow(10,d_max_ex));
    vector<vector<Real>> exp_list(d_max+1,vector<Real>(72*m,0));
    vector<vector<Real>> prm_list(d_max + 1, vector<Real>(72 * m, 0));

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
            //cout << exp_i << "," << exp_i_int << endl;


            int max_p_d = (exp_i_int - cnt_x +71)/(exp_i_int + 1);
            Bint max_p = pow((Bint)10,max_p_d);
            for(int64_t p : prime_list){
                if(p > max_p) break;
                Bint p_a = pow((Bint)p,exp_i_int);
                int d = to_string(p).size()+cnt_x;
                int D = Bint_to_string(p_a).size()+d;
                if(d > d_max) break;
                if(D > 72) break;
                double mlog_p_a = m*exp_i_int*log10(p);
                if(exp_i_int == 1){
                    prm_list[d][mlog_p_a]++;
                }
                exp_list[d][mlog_p_a]++;
                
                /*if(d == 2 || 1){
                    cout << d << "," << mlog_p_a << "," << p << "^" << exp_i_int << "=" << p_a << endl;
                }*/
            }

            for(int j = m*d_max_ex*exp_i_int; j < m*max_p_d*exp_i_int; j++){
                double dec_1_ma = pow(10,(double)1/m/exp_i_int);
                double dec_j_ma = pow(10,(double)j/m/exp_i_int);
                int d = j/m/exp_i_int+1+cnt_x;
                if(d > d_max) break;
                int d_p_a = j/m+1;
                double e_d_j = (m*exp_i_int*dec_j_ma*(j*dec_1_ma-(j+1)))/(log(10)*j*(j+1));
                if(exp_i_int == 1){
                    prm_list[d][j] += e_d_j;
                }
                exp_list[d][j] += e_d_j;
                /*if(d == 2 || 1){
                    cout << s << "," << d << "," << j << "," << dtoB(e_d_j) << endl;
                }*/
            }
        }
    }
    cout << "calc_exp_list" << endl;

    /*for(auto ei : exp_list){
        for(Real eij : ei){
            cout << eij << ",";
        }
        cout << endl;
    }
    cout << endl;

    for(auto ei : prm_list){
        for(Real eij : ei){
            cout << eij << ",";
        }
        cout << endl;
    }
    cout << endl;*/

    /*vector<vector<int>> exp_list_2(e_d_max+1,vector<int>(0));
    for(int i = 0; i <= e_d_max; i++){
        for(int j = 0; j < 72*m; j++){
            if(exp_list[i][j] > 0){
                exp_list_2[i].push_back(j);
            }
        }
    }*/

    //素因数場を'*'で分割したときの(分割の個数,桁数の組)
    vector<pair<int,vector<int>>> e_comb;
    {
        for(int d = 1; d <= e_d_max; d++){
            vector<int> v;
            v.push_back(d);
            vector<int> v_sum;
            v_sum.push_back(d);
            e_comb.push_back(make_pair(v.size(),v));

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

                e_comb.push_back(make_pair(v.size(),v));
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
    vector<int> e_comb_d(e_comb.size());
    for(int i = 0; i < e_comb.size(); i++){
        int ecd_i = 0;
        vector<int> eci = e_comb[i].second;
        for(int j : eci){
            ecd_i += j;
        }
        e_comb_d[i] = ecd_i;
    }

    /*for(auto ei : e_comb){
        cout << ei.first << ";";
        for(auto eij : ei.second){
            cout << eij << ",";
        }
        cout << endl;
    }*/

    map<vector<int>, int> map_e_comb;
    for(int i = 0; i < e_comb.size(); i++){
        map_e_comb[e_comb[i].second] = i;
    }

    //素因数場の桁の組と個数
    vector<vector<Real>> cmp_list(e_comb.size(),vector<Real>(72*m));
    int pre_eif = 0;
    for(int i = 0; i < e_comb.size(); i++){
        vector<Real> &cmp_list_i = cmp_list[i];
        auto ei = e_comb[i];
        int eif;
        vector<int> eis;
        tie(eif,eis) = ei;
        if(pre_eif != eif) {
            cout << eif << ",";
            auto end = chrono::system_clock::now();
            auto dur = end - start;
            auto msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
            cout << msec << "[ms]" << endl;
        }
        pre_eif = eif;
        /*for(int j : eis){
            cout << j << ",";
        }
        cout << endl;*/
        if(eif == 1){
            cmp_list_i = exp_list[ei.second[0]];
        }
        else{
            vector<int> e_comb_f;
            vector<int> e_comb_s;
            for(int j = 0; j < eis.size(); j++){
                if(j < eis.size()/2){
                    e_comb_f.push_back(eis[j]);
                }
                else{
                    e_comb_s.push_back(eis[j]);
                }
            }
            int i_f = map_e_comb[e_comb_f];
            int i_s = map_e_comb[e_comb_s];
            vector<Real> cmp_f = cmp_list[i_f];
            vector<Real> cmp_s = cmp_list[i_s];
            /*{
                for(int j : eis) cout << j << ","; cout << endl;
                for(int j : e_comb_f) cout << j << ","; cout << endl;
                for(int j : e_comb_s) cout << j << ","; cout << endl;
                cout << "i" << "," << "i_f" << "," << "i_s" << endl;
                cout << i << "," << i_f << "," << i_s << endl;
                for(Real j : cmp_f) cout << j << ","; cout << endl;
                for(Real j : cmp_s) cout << j << ","; cout << endl;
            }*/
            for(int j_f = 0; j_f < 72*m; j_f++){
                Real cmp_f_j = cmp_f[j_f];
                if(cmp_f_j == 0) continue;
                //cout << j_f << endl;
                for(int j_s = 0; j_s < 72*m; j_s++){
                    if(j_f + j_s >= 72*m) break;
                    Real cmp_s_j = cmp_s[j_s];
                    if(cmp_s_j == 0) continue;
                    //cout << "_" << j_s << endl;
                    Real cmp_fs_j = cmp_f_j*cmp_s_j;
                    cmp_list_i[j_f+j_s] += cmp_fs_j/2;
                    if(j_f+j_s != 72*m-1) cmp_list_i[j_f+j_s+1] = cmp_fs_j-cmp_fs_j/2;
                }
            }
        }

        /*for(int eisj : eis){
            cout << eisj << ",";
        }
        cout << endl;
        for(Real cij : cmp_list_i){
            cout << cij << ",";
        }
        cout << endl;*/
    }

    vector<vector<Real>> output_list(d_max+1,vector<Real>(72*m,0));
    for(int i = 0; i < e_comb.size(); i++){
        vector<Real> cmp_list_i = cmp_list[i];
        int d_i = e_comb_d[i];
        vector<Real> &output_list_d_i = output_list[d_i];
        vector<int> e_comb_i = e_comb[i].second;
        Real chohuku = 1;
        vector<int> ch_vec(d_max+1,0);
        for(int j : e_comb_i) ch_vec[j]++;
        for(int j : ch_vec) chohuku *= fact(j);

        for(int j = 0; j < 72*m; j++){
            output_list_d_i[j] += cmp_list_i[j]/chohuku;
        }
    }
    //N = p の形も含めて計算したので消す。
    for(int i = 0; i <= e_d_max; i++){
        vector<Real> &output_list_i = output_list[i];
        vector<Real> prm_list_i = prm_list[i];
        for(int j = 0; j < 72*m; j++){
            output_list_i[j] -= prm_list_i[j];
        }
    }

    /*for(auto oi : output_list){
        for(auto oij : oi){
            cout << oij << ",";
        }
        cout << endl;
    }
    cout << endl;*/

    cout << setprecision(22);
    for(auto oi : output_list){
        for(int j = 0; j < 72; j++){
            Real oij = 0;
            for(int k = m*j; k < m*(j+1); k++){
                oij += oi[k];
            }
            cout << oij << ",";
        }
        cout << endl;
    }

    auto end = chrono::system_clock::now();
    auto dur = end - start;
    auto msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
    cout << msec << "[ms]" << endl;
}