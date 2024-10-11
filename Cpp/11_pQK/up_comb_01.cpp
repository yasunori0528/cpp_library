#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;

int main(){
    string deck; cin >> deck;
    vector<char> card = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K'};
    vector<int> comb_vec;
    int cnt_X = 0;
    int cnt_C = 0;
    for(char c : deck){
        if(c == 'X') {
            comb_vec.push_back(-1);
            cnt_X++;
        }
        else if('1' <= c && c <= '9') comb_vec.push_back(c - '0');
        for(int i = 10; i <= 13; i++){
            if(c == card[i]){
                comb_vec.push_back(i);
                cnt_C++;
            }
        }
    }
    int max_d = deck.size()+cnt_X+cnt_C;
    
    sort(comb_vec.begin(),comb_vec.end());
    int64_t max_p = 0;
    string max_p_str;
    do{
        if(cnt_X == 0){
            int64_t p = 0;
            string s;
            for(int i : comb_vec){
                s.push_back(card[i]);
                if(i < 10){
                    p = 10*p+i;
                }
                else p = 100*p+i;
            }

        }
        else {
            vector<int> loop_max(cnt_X,13);
            vector<int> loop_now(cnt_X,0);
        }
    }while(next_permutation(comb_vec.begin(),comb_vec.end()));
}