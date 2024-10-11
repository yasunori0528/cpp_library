#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

//時間計測

char print_time_option;
double time_start;
double time_now;
double time_end;
double time_1;
double time_interval;

//sec
double calcTime(){
    struct::timespec getTime;
    clock_gettime(CLOCK_MONOTONIC, &getTime);
    return getTime.tv_sec + getTime.tv_nsec*1e-9;
}

void printTime(){
    double t = calcTime() - time_start;
    if(print_time_option == 's'){
        printf("%010.3lf[s]\n", t);
        return;
    }
    else if(print_time_option == 'm'){
        t /= 60;
        printf("%09.1lf[m]\n", t);
    }
    else if(print_time_option == 'h'){
        t /= 3600;
        printf("%07.1lf[h]\n", t);
    }
    else if(print_time_option == 'd'){
        t /= 86400;
        printf("%06.1lf[d]\n", t);
    }
}

bool printTimeInterval(){
    time_now = calcTime();
    if(time_now - time_1 >= time_interval){
        time_1 = time_now;
        printTime();
        return true;
    }
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

vector<vector<int>> binomialCoefficientSmallList(33,vector<int>(33,-1));
int binomialCoefficientSmall(int x, int y){
    if(x < 0 || x > 32 || y < 0 || y > x) return 0;
    if(binomialCoefficientSmallList[x][y] >= 0) return binomialCoefficientSmallList[x][y];

    int rtn;
    if(y == 0) rtn = 1;
    else if(y == x) rtn = 1;
    else rtn = binomialCoefficientSmall(x-1,y-1)+binomialCoefficientSmall(x-1,y);

    binomialCoefficientSmallList[x][y] = rtn;
    return rtn;
}

int char_to_int(char c){
    if(c == 'X') return 14;
    if(c == 'K') return 13;
    else if(c == 'Q') return 12;
    else if(c == 'J') return 11;
    else if(c == 'T') return 10;
    return c-'0';
}

vector<char> int_to_char = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K','X'};
vector<char> card_92_KQJ1T = {'9','8','7','6','5','4','3','2','K','X','Q','J','1','T'};

int msd(char c){
    if('0' <= c && c <= '9') return c-'0';
    return 1;
}

mpz_class str_to_int(string s){
    if(s.size() == 0) return 0;
    string t = s;
    char c = s[s.size()-1];
    t.pop_back();
    int i = min(char_to_int(c), 13);
    mpz_class rtn;
    if(i < 10) rtn = str_to_int(t)*10+i;
    else rtn = str_to_int(t)*100+i;
    return rtn;
}

string max_prime(string s){
    int cntX = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == 'X') cntX++;
    }
    if(cntX){
        sort(s.begin(),s.end());
        vector<int> loop(cntX+1,1);
        loop[cntX] = 13;
        mpz_class maxPrimeInt = 0;
        string maxPrimeStr = "-1";
        while(1){
            string t = s;
            for(int i = 0; i < cntX; i++){
                t[t.size()-i-1] = int_to_char[loop[i]];
            }
            t = max_prime(t);

            if(t[0] != '-'){
                mpz_class tInt = str_to_int(t);
                if(chmax(maxPrimeInt, tInt)) maxPrimeStr = t;
            }
            
            bool b = false;
            for(int i = 0; i < cntX; i++){
                if(loop[i] < loop[i+1]){
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
        return maxPrimeStr;
    }

    vector<pair<int,char>> v;
    for(char c : s){
        v.push_back({msd(c),c});
    }
    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());
    mpz_class max_p = 0;
    string rtn = "-1";
    int j = -1;
    do{
        if(j >= 0 && v[j].first > 1) break;
        string t;
        for(auto pr : v){
            t.push_back(pr.second);
        }
        mpz_class n = str_to_int(t);
        if(n > 3 && n%3 == 0) return "-3";
        if(n > max_p && MR_test(n)){
            max_p = n;
            rtn = t;
            for(int i = 0; i < v.size(); i++){
                if(v[i].first == 1){
                    j = i;
                    break;
                }
            }
        }
    }while(prev_permutation(v.begin(),v.end()));
    return rtn;
}

string max_nutural(string s){
    vector<int> cnt(15,0);
    bool cntX = false;
    for(char c : s){
        if(c == 'X') {
            cntX = true;
        }
        cnt[char_to_int(c)]++;
    }
    string rtn;
    for(char c : card_92_KQJ1T){
        int i = cnt[char_to_int(c)];
        for(int j = 0; j < i; j++){
            rtn.push_back(c);
        }
    }
    if(!cntX && str_to_int(rtn)%3 == 0){
        return "-3";
    }
    if(cnt[1] || cnt[3] || cnt[7] || cnt[9] || cnt[11] || cnt[13] || cnt[14]){
        return rtn;
    }
    return "-1";
}

string comb_to_str(int64_t x){
    string rtn;
    for(int i = 0; i <= 14; i++){
        int64_t a = x>>(i*3)&7;
        for(int j = 0; j < a; j++){
            rtn.push_back(int_to_char[i]);
        }
    }
    return rtn;
}

bool in(int64_t x, int64_t y){
    int64_t num_X = (x>>42)-(y>>42);
    for(int i = 0; i <= 13; i++){
        int64_t a = x>>(i*3);
        int64_t b = y>>(i*3);
        if(a >= b) continue;
        if(num_X < b-a) return false;
        num_X -= b-a;
    }
    return true;
}

int64_t minus_comb(int64_t x, int64_t y){
    if(x < 0) return x;
    for(int i = 0; i <= 14; i++){
        int64_t a = x>>(i*3);
        int64_t b = y>>(i*3);
        if(a >= b) {
            x -= b<<(i*3);
            continue;
        }
        if(i == 14) return -1;
        if((x>>42) < b-a) return -1;
        x -= a<<(i*3);
        x -= (b-a)<<42;
    }
    return x;
}

int64_t random_hand(int x){
    set<int> s;
    while(s.size() < x){
        s.insert(rand()%54);
    }
    int64_t rtn = 0;
    for(int i : s){
        //cout << i << " " << ((int64_t)1<<((i/4+1)*3)) << endl;
        rtn += (int64_t)1<<((i/4+1)*3);
    }
    //cout << rtn << endl;
    return rtn;
}

vector<pair<int64_t,int>> handList;//{組, 数}
map<string, mpz_class> primeList;
int numHand;
int primeLength;//手札を2つに分けるときの小さい方の枚数
vector<vector<int>> combList;

map<string,double> primeUsabilityMap;
double r;

set<string> outputListSet;
vector<string> outputListVector;

double timeAll = 11491450;
double timeA = 1*60;
int interval = round(timeAll/timeA);

void calcHandList(){
    vector<int> handComb(numHand+1,1);
    handComb[numHand] // = 14;
    = 13;
    while(true){
        int64_t combInt = 0;
        bool b = true;
        for(int i = 0; i < numHand; i++){
            combInt += (int64_t)1<<(3*handComb[i]);
            int64_t x = combInt>>(3*handComb[i])&7;
            if(x == 5 || (x == 3 && handComb[i] == 14)){
                b = false;
                break;
            }
        }

        if(b){
            int x = 1;
            for(int i = 1; i <= 14; i++){
                int ai = combInt>>(3*i)&7;
                if(i < 14) {
                    x *= binomialCoefficientSmall(4,ai);
                    //cout << 4 << "C" << ai << "=" << binomialCoefficientSmall(4,ai) << endl;
                }
                else {
                    x *= binomialCoefficientSmall(2,ai);
                    //cout << 2 << "C" << ai << "=" << binomialCoefficientSmall(2,ai) << endl;
                }
                //cout << ai << " " << x << endl;
            }
            handList.push_back({combInt, x});
            //cout << x << " " << comb_to_str(combInt) << endl;
        }

        bool bk = false;
        for(int i = 0; i < numHand; i++){
            if(handComb[i] < handComb[i+1]){
                handComb[i]++;
                for(int j = 0; j < i; j++){
                    handComb[j] = 1;
                }
                bk = true;
                break;
            }
        }
        if(!bk) break;
    }
    cout << handList.size() << endl;
}

void calcPrimeList(int leng){
    vector<int> primeComb(leng+1,1);
    primeComb[leng] = 14;
    while(true){
        if(leng >= 2 && primeComb[leng-2] == 14) break;
        int64_t combInt = 0;
        bool b = true;
        bool bl = true;
        for(int i = 0; i < leng; i++){
            combInt += (int64_t)1<<(3*primeComb[i]);
            int64_t x = combInt>>(3*primeComb[i])&7;
            if(x == 5 || (x == 3 && primeComb[i] == 14)){
                b = false;
                break;
            }
        }

        if(b){
            string s0 = comb_to_str(combInt);
            string s = max_prime(s0);
            if(s[0] != '-') {
                primeList[s0] = str_to_int(s);
            }
        }

        bool bk = false;
        for(int i = 0; i < leng; i++){
            if(primeComb[i] < primeComb[i+1]){
                primeComb[i]++;
                for(int j = 0; j < i; j++){
                    primeComb[j] = 1;
                }
                bk = true;
                break;
            }
        }
        if(!bk) break;
    }
    cout << primeList.size() << endl;
}

void calcCombList(){
    vector<int> loop(primeLength+1);
    for(int i = 0; i < primeLength; i++) loop[i] = i;
    loop[primeLength] = numHand;
    while(1){
        loop.pop_back();
        combList.push_back(loop);
        //for(int i : loop) cout << i << " ";
        //cout << endl;
        loop.push_back(numHand);

        bool b = false;
        int iStart = 0;
        if(numHand == primeLength*2) iStart = 1;
        for(int i = iStart; i < primeLength; i++){
            if(loop[i] < loop[i+1]-1){
                loop[i]++;
                for(int j = 1; j < i; j++){
                    loop[j] = loop[j-1]+1;
                }
                b = true;
                break;
            }
        }
        if(!b) break;
    }
    cout << combList.size() << endl;
}

void input(){
    print_time_option = 's';
    time_interval = 3600;

    cin >> numHand >> primeLength >> r;
}  

void calc2(){
    primeUsabilityMap.clear();
    int cnt = 0;
    for(auto pr : handList){
        //if(rand()%10000) continue;
        cnt++;

        set<pair<pair<mpz_class, string>, pair<mpz_class, string>>> sepSet;
        vector<pair<pair<mpz_class, string>, pair<mpz_class, string>>> sepVec;
        int sepSz;
        bool thisHandSkip = false;

        string s = comb_to_str(pr.first);
        if(printTimeInterval()) cout << s << endl;
        //cout << s << endl;
        for(auto i : combList){
            string s1, s2;
            int j = 0;
            for(int k = 0; k < numHand; k++){
                if(i[j] == k){
                    s1.push_back(s[k]);
                    j++;
                }
                else{
                    s2.push_back(s[k]);
                }
            }
            //cout << s1 << " " << s2 << endl;

            mpz_class a1, a2;
            if(!primeList.count(s1)) continue;
            a1 = primeList[s1];
            if(numHand == primeLength*2){
                if(!primeList.count(s2)) continue;
                a2 = primeList[s2];
            }
            else{
                s2 = max_nutural(s2);
                if(s2[0] == '-') continue;
                a2 = str_to_int(s2);
            }
            //cout << s1 << " " << s2 << endl;

            if(a1 < a2) {
                swap(a1,a2);
                swap(s1,s2);
            }
            if(outputListSet.count(s1)) {
                thisHandSkip = true;
                break;
            }
            sepSet.insert({{a1,s1},{a2,s2}});

            if(a1 <= 0) cout << "WARN : " << s1 << " = " << a1 << endl;
            if(a2 <= 0) cout << "WARN : " << s2 << " = " << a2 << endl;
        } 

        if(thisHandSkip) continue;

        sepSz = sepSet.size();
        if(sepSz == 0) continue;

        for(auto i : sepSet){
            sepVec.push_back(i);
        }
        sort(sepVec.begin(), sepVec.end());
        reverse(sepVec.begin(), sepVec.end());

        double sc;
        if(r == 1.0) sc = pr.second/sepSz;
        else sc = pr.second*(1-r)/(1-pow(r,sepSz));
        for(int i = 0; i < sepSz; i++){
            primeUsabilityMap[sepVec[i].first.second] += sc;
            if(numHand == 2*primeLength) primeUsabilityMap[sepVec[i].second.second] += sc;
            sc *= r;
        }
    }
    //cout << cnt << endl;
}

void calc(){
    for(int i = 0; i < 100; i++){
        calc2();
        vector<pair<double, string>> outputList;
        for(auto pr : primeUsabilityMap){
            outputList.push_back({pr.second, pr.first});
        }
        sort(outputList.begin(), outputList.end());
        reverse(outputList.begin(), outputList.end());

        string s = outputList[0].second;
        outputListSet.insert(s);
        outputListVector.push_back(s);
        cout << s << endl;
        printTime();
    }
}

void output(){
    for(string s : outputListVector){
        cout << s << endl;
    }
}

int main(){
    input();
    time_start = calcTime();
    time_1 = time_start;
    srand(time(NULL));

    calcHandList();
    printTime();

    calcPrimeList(primeLength);
    printTime();

    calcCombList();
    printTime();

    calc();
    printTime();

    output();
    printTime();
}
