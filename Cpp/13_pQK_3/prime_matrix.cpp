#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

double time_start;
double time_1;
double time_now;
double time_interval;

double calcTime(){
    struct::timespec getTime;
    clock_gettime(CLOCK_MONOTONIC, &getTime);
    return (getTime.tv_sec + getTime.tv_nsec*1e-9) *1000;
}

void printTime(){
    time_now = calcTime();
    time_1 = calcTime();
    //cout << time_now - time_start << "[ms]" << endl;
    int64_t t =  (time_now - time_start)/1000;
    int64_t t_s, t_min, t_h, t_d;

    t_s = t%60;
    t /= 60;
    t_min = t%60;
    t /= 60;
    t_h = t%24;
    t /= 24;
    t_d = t;
    cout << t_d/10 << t_d%10 << "[day]" << t_h/10 << t_h%10 << "[hour]" << t_min/10 << t_min%10 << "[min]" << t_s/10 << t_s%10 << "[sec]";
    string s(32,'-');
    if(t_h == 0) cout << s;
    cout << endl;
}

bool printTime(double t){
    time_now = calcTime();
    if(time_now - time_1 >= t){
        printTime();
        return 1;
    }
    return 0;
}

int digit(mpz_class n){
    if(n < 10) return 1;
    else return digit(n/10)+1;
}

template <typename T>
T pow_n(T x, T y){
    if(x == 0) return 0;
    if(x == 1) return 1;
    if(y == 0) return 1;
    if(y == 1) return x;

    T rtn = pow_n(x,(T)(y/2));
    rtn *= rtn;
    if(y%2 == 1) rtn *= x;
    return rtn;
}

//x^y%p, 0^0 == 0
mpz_class pow_mod(mpz_class x, mpz_class y, mpz_class p){
    if(x >= p) x %= p;
    if(x == 0) return 0;
    if(x == 1) return 1;
    if(y == 0) return 1;
    if(y == 1) return x;
    mpz_class rtn = pow_mod(x, y/2, p);
    rtn = rtn*rtn%p;
    if(y%2 == 1) {
        rtn *= x;
        rtn %= p;
    }
    return rtn;
}

vector<int> MR_list = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

//a^(x-1)%x == 1, x-1 == 2^r*d;
bool MR_sub(int a, mpz_class x, int r, mpz_class d){
    mpz_class ad = pow_mod(a, d, x);
    if(ad == 1) return true;
    for(int i = 0; i < r; i++){
        if(ad == x-1) return true;
        ad = ad*ad%x;
    }
    return false;
}

bool MR_test(mpz_class x){
    if(x <= 1) return false;
    if(x == 2) return true;
    if(x%2 == 0) return false;

    int r = 0;
    mpz_class d = x-1;
    while(d%2 == 0){
        d /= 2;
        r++;
    }

    for(int a : MR_list){
        if(a >= x) break;
        if(MR_sub(a,x,r,d)) continue;
        return false;
    }
    return true;
}

int char_to_int(char c){
    if(c == 'K') return 13;
    else if(c == 'Q') return 12;
    else if(c == 'J') return 11;
    else if(c == 'T') return 10;
    return c-'0';
}

vector<char> int_to_char = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K'};
vector<char> card_92_KQJ1T = {'9','8','7','6','5','4','3','2','K','Q','J','1','T'};

int msd(char c){
    if('0' <= c && c <= '9') return c-'0';
    return 1;
}

mpz_class str_to_int(string s){
    if(s.size() == 0) return 0;
    string t = s;
    char c = s[s.size()-1];
    t.pop_back();
    int i = char_to_int(c);
    mpz_class rtn;
    if(i < 10) rtn = str_to_int(t)*10+i;
    else rtn = str_to_int(t)*100+i;
    return rtn;
}

string max_prime(string s){
    time_1 = calcTime();
    vector<pair<int,char>> v;
    for(char c : s){
        v.push_back({msd(c),c});
    }
    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());
    mpz_class max_p = 0;
    string rtn;
    int j = -1;
    do{
        if(j >= 0 && v[j].first > 1) break;
        string t;
        for(auto pr : v){
            t.push_back(pr.second);
        }
        mpz_class n = str_to_int(t);
        if(n%3 == 0) return "-1";
        if(n > max_p && MR_test(n)){
            max_p = n;
            rtn = t;
            for(int i = 0; i < v.size(); i++){
                if(v[i].first == 1){
                    j = i;
                    break;
                }
            }
            if(printTime(time_interval)){
                cout << rtn << endl;
            }
        }
    }while(prev_permutation(v.begin(),v.end()));
    return rtn;
}

string max_odd_prime(string s){
    map<char,int> mp;
    for(char c : s){
        mp[c]++;
    }
    char min_odd = '0';
    if(mp.count('1')) min_odd = '1';
    else if(mp.count('J')) min_odd = 'J';
    else if(mp.count('K')) min_odd = 'K';
    else if(mp.count('3')) min_odd = '3';
    else if(mp.count('7')) min_odd = '7';
    else if(mp.count('9')) min_odd = '9';
    string t;
    for(char c : card_92_KQJ1T){
        int k = mp[c];
        if(c == min_odd) k--;
        for(int i = 0; i < k; i++){
            t.push_back(c);
        }
    }
    if(min_odd != '0') t.push_back(min_odd);
    if(MR_test(str_to_int(t))){
        return t;
    }
    else{
        return "-1";
    }
}

int main(){
    srand(time(NULL));
    int n, m;
    n = 6;
    m = 4;
    set<string> P;
    vector<int> loop(n,1);
    while(1){
        string s;
        for(int i = 0; i < n; i++){
            s.push_back(int_to_char[loop[i]]);
        }
        mpz_class x = str_to_int(s);
        if(MR_test(x)) P.insert(s);
        bool b = false;
        for(int i = 0; i < n; i++){
            if(loop[i] < 13){
                loop[i]++;
                for(int j = 0; j < i; j++){
                    loop[j] = 1;
                }
                b = true;
                break;
            }
        }
        if(!b) break;
    }

    vector<string> NAT;
    vector<int> loop_nat(m,1);
    while(1){
        string s;
        for(int i = 0; i < m; i++){
            s.push_back(int_to_char[loop_nat[i]]);
        }
        mpz_class x = str_to_int(s);
        if(2 <= loop_nat[0]  && loop_nat[0] < 10) NAT.push_back(s);
        bool b = false;
        for(int i = 0; i < m; i++){
            if(loop_nat[i] < 13){
                loop_nat[i]++;
                for(int j = 0; j < i; j++){
                    loop_nat[j] = 1;
                }
                b = true;
                break;
            }
        }
        if(!b) break;
    }
    
    vector<string> ODD;
    vector<int> loop_odd(n-m,1);
    while(1){
        string s;
        for(int i = 0; i < n-m; i++){
            s.push_back(int_to_char[loop_odd[i]]);
        }
        mpz_class x = str_to_int(s);
        if(x%5 != 0 && x%2 != 0 && s != "J1") ODD.push_back(s);

        bool b = false;
        for(int i = 0; i < m; i++){
            if(loop_odd[i] < 13){
                loop_odd[i]++;
                for(int j = 0; j < i; j++){
                    loop_odd[j] = 1;
                }
                b = true;
                break;
            }
        }
        if(!b) break;
    }

    int nat_sz = NAT.size();
    int odd_sz = ODD.size();
    for(int i = 6; i < 100; i++){
        int max_sz = 10;
        for(int jj = 0; jj < 1000000000; jj++){
            if(jj%100000 == 0) cout << "--------" << jj << "--------" << endl;
            set<string> odd_i;
            while(odd_i.size() < i){
                string s = ODD[rand()%odd_sz];
                odd_i.insert(s);
            }
            set<string> nat_i;
            for(int j = 0; j < nat_sz; j++){
                string sn = NAT[j];
                bool b = true;
                for(string so : odd_i){
                    string s = sn+so;
                    if(!P.count(s)){
                        b = false;
                        break;
                    }
                }
                if(b) nat_i.insert(sn);
            }

            if(nat_i.size() >= max_sz){
                //max_sz = nat_i.size();
                cout << i << "*" << nat_i.size() << endl;
                for(string s : odd_i){
                    cout << s << endl;
                }
                cout << endl;
                for(string s : nat_i){
                    cout << s << endl;
                }
                cout << endl;
            }
        }
    }
}