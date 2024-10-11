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

//基本

template <typename T>
bool chmax(T &a, const T& b) {
  if (a < b) {
    a = b;  // aをbで更新
    return true;
  }
  return false;
}

template <typename T>
bool chmin(T &a, const T& b) {
  if (a > b) {
    a = b;  // aをbで更新
    return true;
  }
  return false;
}

template <typename T>
T floor(T x, T y){
    if(y < 0){
        x *= -1;
        y *= -1;
    }
    T r = x%y;
    r = (r+y)%y;
    return (x-r)/y;
}

template <typename T>
T ceil(T x, T y){
    if(y < 0){
        x *= -1;
        y *= -1;
    }
    T r = x%y;
    r = (r+y)%y;
    if(r) x += y-r;
    return x/y;
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


/*string max_prime_x(string s){
    vector<int> v;
    int n = s.size();
    for(int i = 0; i < n; i++){
        if(s[i] == 'X'){
            v.push_back(i);
        }
    }
    if(v.size() == 0){
        return max_prime(s);
    }

    string s;
    mpz_class p = -1;

}*/

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

    time_start = calcTime();
    time_1 = calcTime();
    time_interval = 1000*60;

    vector<int> loop_now(13,0);
    vector<int> loop_max(13,2);

    while(1){
        string s;
        for(int i = 0; i < 13; i++){
            for(int j = 0; j < loop_now[i]; j++){
                s.push_back(card_92_KQJ1T[i]);
            }
        }
        s = max_odd_prime(s);
        if(s != "-1") cout << s << endl;

        bool b = false;
        for(int i = 0; i < 13; i++){
            if(loop_now[i] == loop_max[i]) continue;
            loop_now[i]++;
            for(int j = i-1; j >= 0; j--){
                loop_now[j] = 0;
            }
            b = true;
            break;
        }
        if(!b) break;
    }

    printTime();
}