#include <bits/stdc++.h>
using namespace std;

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;

//n!
int64_t fact(int64_t n){
    if(n <= 1) return 1;
    return n*fact(n-1);
}

map<char,int> chartoint;
void calc_chartoint(){
    for(int i = 0; i < 10; i++){
        chartoint['0'+i] = i;
    }
    chartoint['T'] = 10;
    chartoint['J'] = 11;
    chartoint['Q'] = 12;
    chartoint['K'] = 13;
    chartoint['X'] = 14;
}
char inttochar(int n){
    if(0 <= n && n < 10) return (char)('0'+n);
    if(n == 10) return 'T';
    if(n == 11) return 'J';
    if(n == 12) return 'Q';
    if(n == 13) return 'K';
    return 'X';
}

int64_t strtoint(string s){
    int n = s.size();
    if(n == 1){
        return chartoint[s[0]];
    }
    int64_t rtn = strtoint(s.substr(0,n-1));
    char i = chartoint[s[n-1]];
    if(i < 10) rtn = 10*rtn+i;
    else rtn = 100*rtn+i;
    return rtn;
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

string max_prime(bool b, string s){
    Bint rtni = -1;
    vector<char> vec;
    for(char c : s) vec.push_back(c);
    sort(vec.begin(),vec.end());
    string rtn;
    bool b2 = true;
    for(char s : vec){
        if((int)pow(chartoint[s],4)%10 == 1) b2 = false;
        rtn += s;
    }
    if(b2) rtn = "0";
    else if(strtoint(rtn)%3 == 0) rtn = "0";
    else {
        rtn = "-1";
        do{
            string s;
            for(char t : vec){
                s += t;
            }
            Bint p = strtoint(s);
            //cout << s << "," << p << ",";
            if((rtni < 0 || ((b == (rtni < p)))) && pt(p)) {
                rtni = p;
                rtn = s;
            }
        }while(next_permutation(vec.begin(),vec.end()));
        //cout << endl;
    }
    return rtn;
}

int main(){
    calc_chartoint();
    prime_calc(pow(10,6));
    int n;
    cin >> n;
    vector<char> e = {'8','6','5','4','2','Q','T'};
    vector<char> o = {'1','3','7','9','J','K'};
    vector<tuple<int,int64_t,int64_t,string>> en;
    {
        vector<char> loop_now(7,0);
        vector<char> loop_max(7,4);
        bool b = true;
        while(b){
            int cnt = 0;
            for(int i : loop_now) cnt += i;
            if(cnt == n-1){
                string s;
                for(int i = 0; i < 7; i++){
                    char c = e[i];
                    int ln_i = loop_now[i];
                    for(int j = 0; j < ln_i; j++){
                        s.push_back(c);
                    }
                }
                int C = loop_now[5]+loop_now[6];
                int64_t d = 1;
                for(int i : loop_now){
                    d *= fact(i);
                }
                int64_t s_int = -strtoint(s);
                en.push_back(make_tuple(C,d,s_int,s));
            }

            bool calc = false;
            for(int i = 0; i < 7; i++){
                if(loop_now[i] == 4){
                    continue;
                }
                else{
                    loop_now[i]++;
                    for(int j = i-1; j >= 0; j--){
                        loop_now[j] = 0;
                    }
                    calc = true;
                    break;
                }
            }
            b = calc;
        }
        sort(en.begin(),en.end());
    }

    for(auto eni : en){
        string ei = get<3>(eni);
        cout << ei << ",";
        for(char oj : o){
            string eo = ei+oj;
            cout << max_prime(1,eo) << ",";
        }
        cout << endl;
    }
}