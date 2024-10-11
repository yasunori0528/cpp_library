#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;

int main(){
    rep(ii,3){
        map<map<int,int>,vector<int>> list;
        map<map<int,int>,bool> list_;
        cout << "3n+" << ii << endl;
        for(int i = 999; i >= 100; i--){
            int j = 3*i+ii;
            string s = to_string(i)+to_string(j);
            map<int,int> cmb;
            rep(k,10){
                cmb[k];
            }
            for(char c : s){
                cmb[c-'0']++;
            }
            if(cmb[0] > 0) continue;
            bool b = false;
            rep(k,10){
                if(cmb[k] >= 3){
                    b = true;
                    break;
                }
            }
            if(b) continue;
            if(cmb[1]+cmb[3]+cmb[7]+cmb[9] > 1) continue;
            if(list_.count(cmb)){
                continue;
            }
            list_[cmb] = true;
            for(pair<int,int> p : cmb){
                int p1 = p.first;
                map<int,int> cmbp = cmb;
                if(cmbp[p1] > 0){
                    cmbp[p1]--;
                    list[cmbp].push_back(i);
                }
                
            }
        }

        for(auto p : list){
            if(p.second.size() >= 3){
                vector<int> vec = p.second;
                vector<int> vec_mod3(3,0);
                for(int i : vec) {
                    vec_mod3[i%3]++;
                }
                int cnt = 0;
                for(int i : vec_mod3){
                    if(i == 3) cnt++;
                }
                if(cnt < 1) continue;
                /*for(auto p1i : p.first){
                    cout << p1i.first << "," << p1i.second << ",";
                }
                cout << endl;*/
                for(int i : vec) {
                    cout << i << ",(" << i%3 << "),";
                }
                cout << endl;
            }
        }

        /*for(auto p : list_){
            for(auto p1i : p.first){
                cout << p1i.first << "," << p1i.second << ",";
            }
            cout << endl;
        }*/
    }
}