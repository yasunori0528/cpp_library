#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;

//素数計算
vector<int64_t> prime_list(1,2);
void prime_calculate(int64_t n){
    vector<int64_t> nutural_list(n+1);
    int64_t sqrt_n = sqrt(n);
    for(int64_t i = 3; i <= n; i += 2){
        nutural_list[i] = i;
    }
    bool b = true;
    int64_t p = 3;
    while(b){
        int64_t p2 = 2*p;
        for(int i = 3*p; i <= n; i += p2){
            nutural_list[i] = -1;
        }
        for(int i = p+2; i <= n; i += 2){
            if(nutural_list[i] > 0){
                p = i;
                break;
            }
        }
        if(p > sqrt_n) b = false;
    }
    for(int64_t i = 3; i <= n; i += 2){
        if(nutural_list[i] > 0){
            prime_list.push_back(i);
        }
    }
}
//素数判定
int64_t pt(int64_t n, vector<int64_t> &prime){
    if(n < 2) return 0;
    if(n == 2) return 1;
    for(int64_t p : prime){
        if(n%p == 0)    return 0;
        else if(p*p > n) return 1;
    }
    return 0;
    cout << "Insufficient_list" << endl;
}

int main(){
    int n; cin >> n;

    int t_start = time(NULL);
    int t_0 = time(NULL);
    int t_interval = 3600;

    prime_calculate(pow((int64_t)10,n));
    vector<char> card = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K'};
    vector<int> loopmax(n,13);
    vector<int> loopnow(n,0);
    loopnow[0] = 1;
    map<map<char,int>,tuple<int64_t,string,string>> output_list_map;
    bool calc = true;
    cout << "a" << endl;
    while(calc){
        string s;
        int64_t p = 0;
        map<char,int> cmb;
        for(char c : card) cmb[c];
        for(int i : loopnow){
            char c = card[i];
            s.push_back(c);
            cmb[c]++;
            if(i < 10) p = 10*p+i;
            else p = 100*p+i;
        }
        int cnt_X = 0;
        for(pair<char,int> pr : cmb){
            if(pr.first == '0') cnt_X += pr.second;
            else if(pr.second > 4){
                cnt_X += pr.second-4;
                cmb[pr.first] = 4;
            }
        }
        cmb['0'] = 0;
        cmb['X'] = cnt_X;
        //cout << p << "," << s;
        if(cnt_X <= 2 && pt(p,prime_list)){
            //cout << s << ",";
            //cout << endl;
            if(cnt_X <= 2){
                string cmb_str;
                for(char C : card){
                    rep(i,cmb[C]){
                        cmb_str.push_back(C);
                    }
                }
                //cout << cmb_str << ",";
                rep(i,cmb['X']){
                    cmb_str.push_back('X');
                }
                if(output_list_map.count(cmb)){
                    if(get<0>(output_list_map[cmb]) < p){
                        output_list_map[cmb] = make_tuple(p,s,cmb_str);
                    }
                }
                else output_list_map[cmb] = make_tuple(p,s,cmb_str);
            }
            if(cnt_X <= 1){
                for(char c : card){
                    if(cmb[c] > 0){
                        map<char,int> cmb_i = cmb;
                        cmb_i[c]--;
                        cmb_i['X']++;

                        string cmb_str;
                        for(char C : card){
                            rep(i,cmb_i[C]){
                                cmb_str.push_back(C);
                            }
                        }
                        rep(i,cmb_i['X']){
                            cmb_str.push_back('X');
                        }
                        //cout << cmb_str << ",";

                        if(output_list_map.count(cmb_i)){
                            if(get<0>(output_list_map[cmb_i]) < p){
                                output_list_map[cmb_i] = make_tuple(p,s,cmb_str);
                            }
                        }
                        else output_list_map[cmb_i] = make_tuple(p,s,cmb_str);
                    }
                }
            }
            if(cnt_X == 0){
                for(char c1 : card){
                    for(char c2 : card){
                        if(((c1 == c2) && cmb[c1] >= 2) || ((c1 != c2) && cmb[c1] >= 1 && cmb[c2] >= 1)){
                            map<char,int> cmb_i = cmb;
                            cmb_i[c1]--;
                            cmb_i[c2]--;
                            cmb_i['X'] += 2;
                            string cmb_str;
                            for(char C : card){
                                rep(i,cmb_i[C]){
                                    cmb_str.push_back(C);
                                }
                            }
                            rep(i,cmb_i['X']){
                                cmb_str.push_back('X');
                            }
                            //cout << cmb_str << ",";

                            if(output_list_map.count(cmb_i)){
                                if(get<0>(output_list_map[cmb_i]) < p){
                                    output_list_map[cmb_i] = make_tuple(p,s,cmb_str);
                                }
                            }
                            else output_list_map[cmb_i] = make_tuple(p,s,cmb_str);
                        }
                    }
                }
            }
            //cout << endl;
        }
        //cout << endl;

        int t_1 = time(NULL);
        if(t_1 - t_0 >= t_interval){
            cout << "time:" << t_1-t_start << "///" << s << endl;
            t_0 = t_1;
        }


        for(int i = n-1; i >= 0; i--){
            if(loopnow[i] < loopmax[i]){
                loopnow[i]++;
                for(int j = i+1; j < n; j++){
                    loopnow[j] = 0;
                }
                break;
            }
            else if(i == 0){
                calc = false;
            }
        }
    }
    cout << "b" << endl;
    /*for(pair<map<char,int>,tuple<int64_t,string,string>> pair_map_tuple : output_list_map){
        cout << get<0>(pair_map_tuple.second) << "," << get<1>(pair_map_tuple.second) << "," << get<2>(pair_map_tuple.second) << endl;
    }*/

    vector<tuple<int64_t,string,string>> output_list_vec;
    for(pair<map<char,int>,tuple<int64_t,string,string>> pair_map_tuple : output_list_map){
        output_list_vec.push_back(pair_map_tuple.second);
    }
    sort(output_list_vec.begin(), output_list_vec.end());
    cout << "c" << endl;

    int output_cnt = 0;
    int output_list_vec_size = output_list_vec.size();
    cout << output_list_vec.size() << endl;
    int t_end = time(NULL);
    for(int i = 0; i < output_list_vec_size; i++){
        if(i == 0 || get<1>(output_list_vec[i-1]) != get<1>(output_list_vec[i])){
            if(output_cnt >= 1000000){
                cout << "\noutput1000000\n";
                string sss; cin >> sss;
                output_cnt = 0;
            }
            cout << "\n" << get<1>(output_list_vec[i]);
            output_cnt++;
        }
        cout << "," << get<2>(output_list_vec[i]);
        
    }
    cout << endl;
    cout << output_list_vec.size() << endl;

    cout << "///" << t_end - t_start << "[s]" << endl;
}