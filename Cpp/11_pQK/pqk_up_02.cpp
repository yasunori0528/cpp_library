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

template <typename T> bool next_combination(const T first, const T last, int k) {
    const T subset = first + k;
    // empty container | k = 0 | k == n 
    if (first == last || first == subset || last == subset) {
        return false;
    }
    T src = subset;
    while (first != src) {
        src--;
        if (*src < *(last - 1)) {
            T dest = subset;
            while (*src >= *dest) {
                dest++;
            }
            iter_swap(src, dest);
            rotate(src + 1, dest + 1, last);
            rotate(subset, subset + (last - dest) - 1, last);
            return true;
        }
    }
    // restore
    rotate(first, subset, last);
    return false;
}

int main(){
    int n; cin >> n;

    int t_start = time(NULL);
    int t_0 = time(NULL);
    int t_interval = 10;

    prime_calculate(pow(10,n));

    vector<char> card = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K'};
    vector<int> vec;
    for(int i = 0; i <= 13; i++){
        if(i == 0) rep(j,2) vec.push_back(i);
        else rep(j,6) vec.push_back(i);
    }
    map<map<char,int>,pair<int64_t,string>> output_list_map;
    do{
        vector<int> vec_sub;
        rep(i,n) vec_sub.push_back(vec[i]);
        int64_t max_p = 0;
        string max_p_str;
        bool d2 = false;
        int d3;
        map<char,int> comb_i;
        for(char c : card) comb_i[c];
        for(int i : vec_sub){
            comb_i[card[i]]++;
            if(i%2 != 0 && i%5 != 0) d2 = true;
            d3 += i;
        }
        int cnt_X = 0;
        for(char c : card){
            if(c == '0') {
                cnt_X += comb_i[c];
                comb_i[c] = 0;
            }
            else if(comb_i[c] > 4){
                cnt_X += comb_i[c]-4;
                comb_i[c] = 4;
            }
        }
        comb_i['X'] = cnt_X;
        if(d3%3 != 0 && d2 && cnt_X <= 2){
            do{
                if(vec_sub[0] != 0){
                    int64_t p = 0;
                    string s;
                    for(int i : vec_sub){
                        s.push_back(card[i]);
                        if(i < 10) p = 10*p+i;
                        else p = 100*p+i;
                    }
                    if(max_p < p && pt(p,prime_list)) {
                        max_p = p;
                        max_p_str = s;
                    }
                    int t_1 = time(NULL);
                    if(t_1 - t_0 >= t_interval){
                        cout << "time:" << t_1-t_start << "///";
                        for(int i : vec_sub) cout << i << ",";
                        cout << endl;
                        t_0 = t_1;
                    }
                }
                
            }while(next_permutation(vec_sub.begin(),vec_sub.end()));
            if(max_p != 0 && max_p > output_list_map[comb_i].first) output_list_map[comb_i] = make_pair(max_p,max_p_str);
        }
        
    }while(next_combination(vec.begin(),vec.end(),n));

    vector<pair<int64_t,string>> output_list_vec;
    for(pair<map<char,int>,pair<int64_t,string>> pair_m_p : output_list_map){
        output_list_vec.push_back(pair_m_p.second);
    }
    sort(output_list_vec.begin(),output_list_vec.end());
    for(pair<int64_t,string> pr : output_list_vec){
        cout << pr.second << endl;
    }

    int t_end = time(NULL);
    cout << "///" << t_end - t_start << "[s]" << endl;
}