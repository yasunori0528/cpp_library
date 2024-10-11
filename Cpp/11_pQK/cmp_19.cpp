#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;

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
Bint str_int_Bint(string s){
    Bint n = 0;
    for (char c : s){
        if (c == 'T') n = n * 100 + 10;
        else if (c == 'J') n = n * 100 + 11;
        else if (c == 'Q') n = n * 100 + 12;
        else if (c == 'K') n = n * 100 + 13;
        else n = n * 10 + (c - '0');
    }
    return n;
}

vector<char> card = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

int pqkable2(string s){
    int n = s.size();
    string t;
    rep(i,n) t.push_back('x');
    rep(i,n){
        char & c = s[i];
        if(c == '*' || c == '^' || c == '='){
            t[i] = c;
            c = 'x';
        }
        else if('4' <= c && c <= '9') {
            t[i] = c;
            c = 'y';
        }
        else if('0' <= c && c <= '3' && c != '1') {
            //絵札として使わない
            if(i == 0 || s[i-1] != '1') {
                t[i] = c;
                c = 'z';
            }
            //使う絵札が確定している
            else if(i == 1 || s[i-2] != '1'){
                string s_sub_i = s.substr(i-1,2);
                if(s_sub_i == "10"){
                    t[i-1] = '-';
                    t[i] = 'T';
                    s[i-1] = s[i] = 'w';
                }
                else if(s_sub_i == "11"){
                    t[i-1] = '-';
                    t[i] = 'J';
                    s[i-1] = s[i] = 'w';
                }
                else if(s_sub_i == "12"){
                    t[i-1] = '-';
                    t[i] = 'Q';
                    s[i-1] = s[i] = 'w';
                }  
                else if(s_sub_i == "13"){
                    t[i-1] = '-';
                    t[i] = 'K';
                    s[i-1] = s[i] = 'w';
                }  
            }
                
        }
    }
    int cnt = 0;
    rep(i,n){
        char & c = s[i];
        if(c == '1') cnt++;
        //cout << i << ":" << cnt << endl;
        char c_ = 'x';
        if(i < n-1) c_ = s[i+1];
        if(c_ == '1') continue;
        else{
            //if(20 <= i && i <= 22) cout << i << ":" << cnt << endl;
            if('0' <= c_ && c_ <= '3'){
                while(cnt >= 3){
                    s[i-cnt+1] = s[i-cnt+2] = 'z';
                    t[i-cnt+1] = '-';
                    t[i-cnt+2] = 'J';
                    cnt -= 2;
                }
                if(cnt == 1){
                    if(c_ == '0'){
                        s[i] = s[i+1] = 'z';
                        t[i] = '-';
                        t[i+1] = 'T';
                    }
                    if(c_ == '2'){
                        s[i] = s[i+1] = 'z';
                        t[i] = '-';
                        t[i+1] = 'Q';
                    }
                    if(c_ == '3'){
                        s[i] = s[i+1] = 'z';
                        t[i] = '-';
                        t[i+1] = 'K';
                    }
                }
                cnt = 0;
            }
            else{
                while(cnt > 0){
                    if(cnt == 1){
                        c = 'z';
                        t[i] = '1';
                        cnt--;
                    }
                    else{
                        s[i-cnt+1] = s[i-cnt+2] = 'z';
                        t[i-cnt+1] = '-';
                        t[i-cnt+2] = 'J';
                        cnt -= 2;
                    }
                }
            }
        }
    }
    //cout << t << endl;

    vector<int> AX(4,0);
    rep(i,n){
        char c = s[i];
        if('0' <= c && c <= '3' && c != '1'){
            AX[c-'0']++;
        }
    }
    //for(int i : AX) cout << i << endl;
    map<char,int> comb;
    for(char c : t){
        comb[c]++;
    }
    int AX0 = AX[0];
    int AX2 = AX[2];
    int AX3 = AX[3];
    int min_wild = s.size();
    rep(i,AX0+1){
        rep(j,AX2+1){
            rep(k,AX3+1){
                map<char,int> comb_ijk = comb;
                comb_ijk['0'] += i;
                comb_ijk['2'] += j;
                comb_ijk['3'] += k;
                comb_ijk['J'] += i+j+k;
                comb_ijk['T'] += AX0-i;
                comb_ijk['Q'] += AX2-j;
                comb_ijk['K'] += AX3-k;
                comb_ijk['1'] += AX0-i+AX2-j+AX3-k;
                int cntQ_ = max(0,min(comb_ijk['Q']-4,4-comb_ijk['2']));
                int cntK_ = max(0,min(comb_ijk['K']-4,4-comb_ijk['3']));
                int cntJ_ = max(0,(4-comb_ijk['1']-cntQ_-cntK_)/2);
                comb_ijk['1'] += 2*cntJ_+cntQ_+cntK_;
                comb_ijk['2'] += cntQ_;
                comb_ijk['3'] += cntK_;
                comb_ijk['J'] -= cntJ_;
                comb_ijk['Q'] -= cntQ_;
                comb_ijk['K'] -= cntK_;

                int wild = 0;
                for(char c : card){
                    if(c == '0') wild += comb_ijk['0'];
                    else wild += max(0,comb_ijk[c]-4);
                }
                min_wild = min(min_wild,wild);
            }
        }
    }
    return min_wild;
}

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

//deck_strからsを出すときの絵札の使い方
string pqkable4(string s, string deck_str){
    int n = s.size();

    map<char,int> deck;
    for(char c : card) deck[c] = 0;
    deck['X'] = 0;
    for(char c : deck_str) deck[c]++;

    string t;
    rep(i,n) t.push_back('x');
    rep(i,n){
        char & c = s[i];
        if(c == '*' || c == '^' || c == '='){
            t[i] = c;
            c = 'x';
        }
        else if('4' <= c && c <= '9') {
            t[i] = c;
            c = 'y';
        }
        else if('0' <= c && c <= '3' && c != '1') {
            //絵札として使わない
            if(i == 0 || s[i-1] != '1') {
                t[i] = c;
                c = 'z';
            }
            //使う絵札が確定している
            else if(i == 1 || s[i-2] != '1'){
                string s_sub_i = s.substr(i-1,2);
                if(s_sub_i == "10"){
                    t[i-1] = '-';
                    t[i] = 'T';
                    s[i-1] = s[i] = 'w';
                }
                else if(s_sub_i == "11"){
                    t[i-1] = '-';
                    t[i] = 'J';
                    s[i-1] = s[i] = 'w';
                }
                else if(s_sub_i == "12"){
                    t[i-1] = '-';
                    t[i] = 'Q';
                    s[i-1] = s[i] = 'w';
                }  
                else if(s_sub_i == "13"){
                    t[i-1] = '-';
                    t[i] = 'K';
                    s[i-1] = s[i] = 'w';
                }  
            }
                
        }
    }
    int cnt = 0;
    rep(i,n){
        char & c = s[i];
        if(c == '1') cnt++;
        //cout << i << ":" << cnt << endl;
        char c_ = 'x';
        if(i < n-1) c_ = s[i+1];
        if(c_ == '1') continue;
        else{
            //if(20 <= i && i <= 22) cout << i << ":" << cnt << endl;
            if('0' <= c_ && c_ <= '3'){
                while(cnt >= 3){
                    s[i-cnt+1] = s[i-cnt+2] = 'z';
                    t[i-cnt+1] = '-';
                    t[i-cnt+2] = 'J';
                    cnt -= 2;
                }
                if(cnt == 1){
                    if(c_ == '0'){
                        s[i] = s[i+1] = 'z';
                        t[i] = '-';
                        t[i+1] = 'T';
                    }
                    if(c_ == '2'){
                        s[i] = s[i+1] = 'z';
                        t[i] = '-';
                        t[i+1] = 'Q';
                    }
                    if(c_ == '3'){
                        s[i] = s[i+1] = 'z';
                        t[i] = '-';
                        t[i+1] = 'K';
                    }
                }
                cnt = 0;
            }
            else{
                while(cnt > 0){
                    if(cnt == 1){
                        c = 'z';
                        t[i] = '1';
                        cnt--;
                    }
                    else{
                        s[i-cnt+1] = s[i-cnt+2] = 'z';
                        t[i-cnt+1] = '-';
                        t[i-cnt+2] = 'J';
                        cnt -= 2;
                    }
                }
            }
        }
    }
    //cout << t << endl;

    vector<int> AX(4,0);
    rep(i,n){
        char c = s[i];
        if('0' <= c && c <= '3' && c != '1'){
            AX[c-'0']++;
        }
    }
    //for(int i : AX) cout << i << endl;
    map<char,int> comb;
    for(char c : t){
        comb[c]++;
    }
    int AX0 = AX[0];
    int AX2 = AX[2];
    int AX3 = AX[3];
    string rtn;
    rep(i,AX0+1){
        rep(j,AX2+1){
            rep(k,AX3+1){
                map<char,int> comb_ijk = comb;
                comb_ijk['0'] += i;
                comb_ijk['2'] += j;
                comb_ijk['3'] += k;
                comb_ijk['J'] += i+j+k;
                comb_ijk['T'] += AX0-i;
                comb_ijk['Q'] += AX2-j;
                comb_ijk['K'] += AX3-k;
                comb_ijk['1'] += AX0-i+AX2-j+AX3-k;
                int cntQ_ = max(0,min(comb_ijk['Q']-deck['Q'],deck['2']-comb_ijk['2']));
                int cntK_ = max(0,min(comb_ijk['K']-deck['K'],deck['3']-comb_ijk['3']));
                int cntJ_ = max(0,(deck['1']-comb_ijk['1']-cntQ_-cntK_)/2);
                comb_ijk['1'] += 2*cntJ_+cntQ_+cntK_;
                comb_ijk['2'] += cntQ_;
                comb_ijk['3'] += cntK_;
                comb_ijk['J'] -= cntJ_;
                comb_ijk['Q'] -= cntQ_;
                comb_ijk['K'] -= cntK_;

                int wild = 0;
                for(char c : card){
                    if(c == '0') wild += comb_ijk['0'];
                    else wild += max(0,comb_ijk[c]-deck[c]);
                }
                if(wild <= deck['X']){
                    int cnt_AX0 = 0;
                    int cnt_AX2 = 0;
                    int cnt_AX3 = 0;
                    for(int l = 2; l < n; l++){
                        char c = s[l];
                        if(c == '0'){
                            if(cnt_AX0 < i){
                                t[l-2] = '-';
                                t[l-1] = 'J';
                                t[l] = '0';
                            }
                            else{
                                t[l-2] = '1';
                                t[l-1] = '-';
                                t[l] = 'T';
                            }
                            cnt_AX0++;
                        }
                        if(c == '2'){
                            if(cnt_AX2 < j){
                                t[l-2] = '-';
                                t[l-1] = 'J';
                                t[l] = '2';
                            }
                            else{
                                t[l-2] = '1';
                                t[l-1] = '-';
                                t[l] = 'Q';
                            }
                            cnt_AX2++;
                        }
                        if(c == '3'){
                            if(cnt_AX3 < k){
                                t[l-2] = '-';
                                t[l-1] = 'J';
                                t[l] = '3';
                            }
                            else{
                                t[l-2] = '1';
                                t[l-1] = '-';
                                t[l] = 'K';
                            }
                            cnt_AX3++;
                        }
                    }
                    for(char c : t){
                        if(c != '-') rtn.push_back(c);
                    }
                    rtn.push_back(',');
                }


                //cout << cntJ_ << "," << cntQ_ << "," << cntK_ << "," << wild << endl;
            }
        }
    }
    return rtn;
}
bool pt(Bint n,vector<int64_t>vec){
    if(n <= 1) return false;
    int64_t s = vec.size();
    for(int64_t i = 0; i < s; i++){
        if(vec[i]*vec[i] > n) return true;
        else if(n%vec[i] == 0) return false;    
    }
    return false;
    cout << "Insuficuent_Prime_List" << endl;
}

int main(){
    int d; cin >> d;

    int t_start = time(NULL);
    int t_0 = time(NULL);
    int t_interval = 3600;

    string deck;
    for(int i = 1; i <= 13; i++){
        char c = card[i];
        rep(j,4) deck.push_back(c);
    }
    deck += "XX";
    int64_t maxp = pow((int64_t)10,(d-1)/2);
    //int64_t maxp = pow((int64_t)10,d-3);
    prime_calculate(maxp);
    Bint max_cmp = pow((Bint)10,72-d)-1;
    Bint min_cmp = 
    1;
    //pow((Bint)2,122);
    //953*pow((Bint)7,41);
    //541*pow((Bint)11,37);
    //pow((Bint)3,4)*pow((Bint)2,9)*pow((Bint)11,37);
    //pow((Bint)3,8)*pow((Bint)201389,8);
    int max_exp = (72-d-2)*10/3;
    vector<vector<string>> exp_pattern(max_exp+1,vector<string>(0));
    for(int i = 2; i <= max_exp; i++){
        string i_str = to_string(i);
        exp_pattern[i].push_back(i_str);
    }
    int sqrt_max_exp = sqrt(max_exp);
    int log2_max_exp = log2(max_exp);

    for(int i = 2; i <= sqrt_max_exp; i++){
        string i_str = to_string(i);
        for(int j = 2; j <= log2_max_exp; j++){
            string j_str = to_string(j);
            int pow_i_j = pow(i,j);
            if(pow_i_j > max_exp) break;
            string pow_i_j_str = i_str + "^" + j_str;
            exp_pattern[pow_i_j].push_back(pow_i_j_str);
        }
    }
    if(16 <= max_exp) exp_pattern[16].push_back("2^2^2");
    if(81 <= max_exp) exp_pattern[81].push_back("3^2^2");

    vector<vector<pair<Bint,string>>> exp_list(d+1,vector<pair<Bint,string>>(0,make_pair(0,"")));
    int max_exp_p = max_exp;
    int pd = (d-1)/2;
    for(int pd_i = 1; pd_i <= pd; pd_i++){
        for(int64_t id = 0; id < (1<<(pd_i*2)); id++){
            string p_str;
            int64_t id2 = id;
            rep(i,pd_i){
                p_str = to_string(id2%4+10) + p_str;
                id2 /= 4;
            }
            Bint p = str_int_Bint(p_str);
            if(!pt(p,prime_list)) continue;
            //cout << p << endl;
            int p_size = p_str.size();
            if(pqkable2(p_str) <= 2) exp_list[p_size].push_back(make_pair(p,p_str));
            else continue;
            Bint pow_p_i = p;
            for(int i = 2; i <= max_exp_p; i++){
                pow_p_i *= p;
                if(pow_p_i > max_cmp){
                    max_exp_p = i;
                    break;
                }
                for(string s : exp_pattern[i]){
                    string pow_p_i_str = p_str + "^" + s;
                    int pow_p_i_size = 0;
                    for(char c : pow_p_i_str){
                        if(c != '^') pow_p_i_size++;
                    }
                    if(pow_p_i_size <= d && pqkable2(pow_p_i_str) <= 2){
                        exp_list[pow_p_i_size].push_back(make_pair(pow_p_i,pow_p_i_str));
                    }

                    int t_1 = time(NULL);
                    if(t_1 - t_0 >= t_interval){
                        cout << "time:" << t_1-t_start << "///" << pow_p_i_str << endl;
                        t_0 = t_1;
                    }

                }
            }
        }
    }
    
    for(int i = 1; i <= d; i++){
        sort(exp_list[i].begin(),exp_list[i].end());
    }
    vector<int64_t> exp_list_size;
    for(int i = 0; i <= d; i++){
        exp_list_size.push_back(exp_list[i].size());
    }
    cout << "exp_list_calculated" << endl;

    /*for(vector<pair<Bint,string>> vpBs : exp_list){
        for(pair<Bint,string> pBs : vpBs){
            Bint n; string s;
            tie(n,s) = pBs;
            cout << n << "," << s << endl;
        }
        cout << endl;
    }
    cout << endl;*/

    //vector<int> cnt1(73,0);
    //vector<int> cnt2(73,0);

    int pro_pattern = pow(2,d-1);
    for(int i = 0; i < pro_pattern; i++){
        //cout << "i:" << i << endl;
        vector<int> d_vec(0);
        int i_bit = i;
        int d_j = 1;
        for(int j = 0; j < d-1; j++){
            if(i_bit%2){
                d_vec.push_back(d_j);
                d_j = 1;
            }
            else{
                d_j++;
            }
            i_bit /= 2;
        }
        d_vec.push_back(d_j);

        int d_vec_size = d_vec.size();
        bool pro_mono = true;
        for(int j = 0; j < d_vec_size-1; j++){
            if(d_vec[j] > d_vec[j+1]){
                pro_mono = false;
            }
        }
        if(!pro_mono) continue;
        vector<int64_t> loop_max(0);
        bool empty_list = false;
        for(int j : d_vec){
            int exp_list_size_j = exp_list_size[j];
            if(exp_list_size_j == 0){
                empty_list = true;
                break;
            }
            loop_max.push_back(exp_list_size_j-1);
        }
        if(empty_list) continue;
        Bint min_cmp_i = 1;
        Bint max_cmp_i = 1;
        for(int j : d_vec){
            min_cmp_i *= exp_list[j][0].first;
            max_cmp_i *= exp_list[j][exp_list_size[j]-1].first;
        }
        if(max_cmp_i < min_cmp || min_cmp_i > max_cmp) continue;

        cout << "///";
        for(int j : d_vec){
            cout << j << ",";
        }
        cout << endl;

        vector<int64_t> loop_now(d_vec_size,0);
        vector<Bint> calc_sub(d_vec_size,1);//j番目:前j個の部分積
        vector<string> calc_sub_str(d_vec_size,"=");
        bool calc_b = true;
        Bint cmp = 1;
        string p_fact_str = "=";
        int update_loop = 0;
        int update_loop_last = loop_max[d_vec_size-1];
        while(calc_b){
            //cout << "s" << ",";
            /*for(Bint i : calc_sub) cout << i << ",";
            cout << endl;
            for(string s : calc_sub_str) cout << s << ",";
            cout << endl;*/
            //for(int ln_i : loop_now) cout << ln_i << ",";
            int pre_update_loop = update_loop;
            update_loop = d_vec_size-1;
            cmp = calc_sub[pre_update_loop];
            p_fact_str = calc_sub_str[pre_update_loop];
            bool pqkable_bool = true;
            for(int j = pre_update_loop; j < d_vec_size; j++){
                pair<Bint,string> exp_d_j_now_pair = exp_list[d_vec[j]][loop_now[j]];
                Bint exp_d_j_now = exp_d_j_now_pair.first;
                string exp_d_j_now_str = exp_d_j_now_pair.second;
                if(j != 0) p_fact_str += "*";
                p_fact_str += exp_d_j_now_str;
                if(pqkable2(p_fact_str) > 2){
                    pqkable_bool = false;
                    update_loop = j;
                    break;
                }
                cmp *= exp_d_j_now;
                if(j < d_vec_size-1){
                    calc_sub[j+1] = cmp;
                    calc_sub_str[j+1] = p_fact_str;
                }
            }
            //cout << p_fact_str << ",";
            //cout << update_loop << ",";
            if(cmp < min_cmp){
                Bint calc_sub_d1 = calc_sub[d_vec_size-1];
                Bint min_exp_d_last = (min_cmp-1)/calc_sub_d1+1;
                int64_t low = loop_now[d_vec_size-1];
                int64_t up = loop_max[d_vec_size-1];
                vector<pair<Bint,string>> exp_d_last = exp_list[d_vec[d_vec_size-1]];
                if(calc_sub_d1*exp_d_last[up].first < min_cmp){
                    pqkable_bool = false;
                    update_loop = d_vec_size-2;
                }
                while(up-low > 1){
                    int64_t mid = (up+low)/2;
                    Bint mid_exp_d_last = exp_d_last[mid].first;
                    if(mid_exp_d_last < min_exp_d_last) low = mid;
                    else if(mid_exp_d_last > min_exp_d_last) up = mid;
                    else low = up = mid;
                }
                loop_now[d_vec_size-1] = low;
            }
            else if(pqkable_bool){
                if(cmp > max_cmp){
                    update_loop_last = loop_now[d_vec_size-1];
                    update_loop = d_vec_size-2;
                }
                else{
                    string cmp_str = Bint_to_string(cmp);
                    string s = cmp_str + p_fact_str;
                    //cnt2[cmp_str.size()]++;
                    if(pqkable2(s) <= 2){
                        cout << pqkable4(s,deck) << endl;
                        //cnt1[cmp_str.size()]++;
                        min_cmp = cmp;
                    }
                    update_loop = d_vec_size-1;
                    
                    int t_1 = time(NULL);
                    if(t_1 - t_0 >= t_interval){
                        cout << "time:" << t_1-t_start << "///" << s << endl;
                        t_0 = t_1;
                    }
                }
            }

            //更新
            //update_loop = d_vec_size-1;
            for(int j = update_loop; j >= 0; j--){
                //loop_now[j]を更新
                if((j == d_vec_size-1 && loop_now[j] < update_loop_last) || (loop_now[j] < loop_max[j])){
                    //cout << "j:" << j << ",d_vec_size:" << d_vec_size << "up_ll:" << update_loop_last << ",loopnow[j]:" << loop_now[j] << ",loopmax[j]:" << loop_max[j] << ",";
                    loop_now[j]++;
                    for(int k = j+1; k < d_vec_size; k++){
                        if(d_vec[k-1] == d_vec[k]) loop_now[k] = loop_now[k-1];
                        else loop_now[k] = 0;
                    }
                    update_loop = j;
                    if(j <= d_vec_size-3){
                        update_loop_last = loop_max[d_vec_size-1];
                    }
                    break;
                }
                //計算終了
                else if(j == 0){
                    calc_b = false;
                    break;
                }
            }
            if(update_loop < 0) calc_b = false;
            //cout << "e" << endl;
        }
    }

    /*for(int i = 1; i <= 72; i++){
        cout << cnt1[i] << endl;
    }
    cout << endl;
    for(int i = 1; i <= 72; i++){
        cout << cnt2[i] << endl;
    }*/

    int t_end = time(NULL);
    cout << "///" << t_end - t_start << "[s]" << endl;
}