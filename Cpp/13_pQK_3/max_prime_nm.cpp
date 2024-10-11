#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
template <typename T> using min_priority_queue = priority_queue<T,vector<T>,greater<T>>;
ofstream outputfile("output.txt");

//時間計測

char print_time_option = 's';
double time_start;
double time_now;
double time_end;
double time_1;
double time_interval;

double calcTime(){
    struct::timespec getTime;
    clock_gettime(CLOCK_MONOTONIC, &getTime);
    return getTime.tv_sec + getTime.tv_nsec*1e-9;
}

void printTime(){
    double t = calcTime() - time_start;
    time_now = t;
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

vector<int> MR_list = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

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
    if('0' <= c && c <= '9') return c - '0';
    else if(c == 'T') return 10;
    else if(c == 'J') return 11;
    else if(c == 'Q') return 12;
    else if(c == 'K') return 13;
    else if(c == 'X') return 14;
    else return c - 'a';
}

vector<char> int_to_char = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K','X','a','b','c','d','e','f','g','h','i','j','k','l','m','n'};
vector<int> card_92_KQJ1T = {9,8,7,6,5,4,3,2,14,13,12,11,1,10};

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

/*string max_prime(string s){
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
*/

struct hand{
    uint64_t comb;
    int sz;
    hand(){
        comb = 0;
        sz = 0;
    }
    hand(uint64_t c){
        comb = c;
        sz = 0;
        while(c){
            sz += c&7;
            c >>= 3;
        }
    }
    hand(string s){
        sz = s.size();
        comb = 0;
        for(char c : s){
            comb += ((uint64_t)1)<<(3*char_to_int(c));
        }
    }

    int count(int x){
        return comb>>(3*x)&7;
    }
    void insert(int x){
        if((comb>>(3*x)&7) == 7) {
            cout << "! could not insert" << endl;
            return;
        }
        comb += ((uint64_t)1)<<(3*x);
        sz++;
    }
    void erase(int x){
        if(comb>>(3*x)&7 == 0) return;
        comb -= ((uint64_t)1)<<(3*x);
        sz--;
    }

    hand operator+(hand other){
        uint64_t c1 = comb;
        uint64_t c2 = other.comb;
        uint64_t c = 0;
        int i = 0;
        while(c1 || c2){
            c += min((uint64_t)7,(c1&7)+(c2&7))<<i;
            c1 >>= 3;
            c2 >>= 3;
            i += 3;
        }
        return hand(c);
    }
    hand operator-(hand other){
        uint64_t c1 = comb;
        uint64_t c2 = other.comb;
        uint64_t c = 0;
        int i = 0;
        while(c1 || c2){
            c += max((uint64_t)0,(c1&7)-(c2&7))<<i;
            c1 >>= 3;
            c2 >>= 3;
            i += 3;
        }
        return hand(c);
    }
    hand operator&(hand other){
        uint64_t c1 = comb;
        uint64_t c2 = other.comb;
        uint64_t c = 0;
        int i = 0;
        while(c1 || c2){
            c += min((c1&7),(c2&7))<<i;
            c1 >>= 3;
            c2 >>= 3;
            i += 3;
        }
        return hand(c);
    }
    hand operator|(hand other){
        uint64_t c1 = comb;
        uint64_t c2 = other.comb;
        uint64_t c = 0;
        int i = 0;
        while(c1 || c2){
            c += max((c1&7),(c2&7))<<i;
            c1 >>= 3;
            c2 >>= 3;
            i += 3;
        }
        return hand(c);
    }
    hand operator^(hand other){
        uint64_t c1 = comb;
        uint64_t c2 = other.comb;
        uint64_t c = 0;
        int i = 0;
        while(c1 || c2){
            uint64_t x;
            if((c1&7) > (c2&7)) x = (c1&7)-(c2&7);
            else x = (c2&7)-(c1&7);
            c += x<<i;
            c1 >>= 3;
            c2 >>= 3;
            i += 3;
        }
        return hand(c);
    }
    hand operator<(hand other){
        return comb < other.comb;
    }

    void print(){
        for(int i = 0; i <= 14; i++){
            char c = int_to_char[i];
            for(int j = 0; j < count(i); j++){
                cout << c;
            }
        }
        cout << endl;
    }

    string max_str(){
        string s;
        for(int i : card_92_KQJ1T){
            char c = int_to_char[i];
            int a = count(i);
            if(c == 'X') c = 'K';
            for(int j = 0; j < a; j++){
                s.push_back(c);
            }
        }
        return s;
    }
};

struct max_prime_state{
    mpz_class max_value;
    string s;
    mpz_class n;
    hand h;
    max_prime_state(){
        ;
    }
    max_prime_state(string t, hand g){
        s = t;
        h = g;
        n = str_to_int(s);
        string max_str = h.max_str();
        max_value = str_to_int(s+max_str);
    }

    void print(){
        //cout << "max_value : " << max_value << endl;
        cout << "s : " << s << endl;
        //cout << "n : " << n << endl;
        //cout << "h : ";
        //h.print();
    }
    void push_back(int i){
        int x = 0;
        if(i > 13){
            x = 15;
            i -= 15;
        }
        h.erase(min(14,i+x));
        s.push_back(int_to_char[i+x]);
        if(i < 10){
            n = n*10+i;
        }
        else{
            n = n*100+i;
        }
        max_value = str_to_int(s+h.max_str());
    }
    void pop_back(){
        char c = s[s.size()-1];
        int i = char_to_int(c);
        int x = 0;
        if('a' <= c && c <= 'z'){
            x = 15;
        }
        //cout << "----" << c << " " << i << " " << x << endl;
        s.pop_back();
        if(i < 10){
            n /= 10;
        }
        else{
            n /= 100;
        }
        //cout << "----" << h.comb << endl;
        h.insert(min(14,i+x));
        //cout << "----" << h.comb << endl;
        max_value = str_to_int(s+h.max_str());        
    }
};

bool operator<(max_prime_state st1, max_prime_state st2){
    return st1.max_value < st2.max_value;
}
bool operator>(max_prime_state st1, max_prime_state st2){
    return st1.max_value > st2.max_value;
}

vector<int> max_prime_sub_odd = {1,3,7,9,11,13,14};

bool max_prime_sub(max_prime_state st){
    if(st.h.sz == 0) return true;
    char c1 = '_';
    char c2 = st.s[st.s.size()-1];
    if(st.h.count(14) == 0){
        bool b = false;
        for(int i : max_prime_sub_odd){
            if(st.h.count(i)){
                b = true;
                break;
            }
        }
        if(!b) return false;
        if(st.max_value%3 == 0) return false;

        b = false;
        for(int i = 1; i <= 9; i++){
            if(st.h.count(i)){
                b = true;
                break;
            }
        }
        if(!b && st.max_value%11 == 0) return false;
    }
    if('a' <= c2 && c2 <= 'z'){
        if(st.h.count(c2-'a')) return false;
        if(c2 == 'a' && st.s.size() == 1) return false;
    }
    if(st.s.size() == 1) return true;

    c1 = st.s[st.s.size()-2];
    if(char_to_int(c1) == 1){
        if(char_to_int(c2) == 11) return false;
        if(st.h.count(10+char_to_int(c2))) return false;
    }
    return true;
}

string max_prime(hand h){
    if(h.sz == 0) return "-1";
    if(h.sz == 1) {
        for(int i = 0; i <= 14; i++){
            if(h.comb>>(i*3)&7){
                string s;
                if(i == 14){
                    s = "X";
                }
                else if(i < 14 && MR_test(i)){
                    s.push_back(int_to_char[i]);
                }
                else{
                    s = "-1";
                }
                return s;
            }
        }
    }

    priority_queue<max_prime_state> q;
    q.push(max_prime_state("",h));
    while(!q.empty()){
        //cout << string(16,'-') << endl;
        max_prime_state st = q.top();
        //st.print();
        q.pop();
        if(st.h.sz == 0){
            if(MR_test(st.n)) {
                string rtn = st.s;
                for(char &c : rtn){
                    if('a' <= c && c <= 'z'){
                        c = int_to_char[char_to_int(c)];
                    }
                }
                return rtn;
            }
            continue;
        }
        for(int i = 0; i <= 28; i++){
            if(i == 14) continue;
            if(st.h.count(min(14,i)) == 0) continue;
            st.push_back(i);
            if(max_prime_sub(st)){
                q.push(st);
                //st.print();
            }
            st.pop_back();
            //st.print();
        }
        //cout << string(16,'-') << endl;
    }
    return "-1";
}

void calc(){
    while(1){
        string s; cin >> s;
        hand h(s);
        cout << max_prime(h) << endl;
    }
}

vector<hand> V1;
vector<hand> V2;
int cnt = 0;
bool bl = true;
void calc1(int N, int M){
    int N1 = 2*N-M;
    int N2 = M-N;
    V1.clear();
    V2.clear();

    int numMax = 4;
    int XMax = 2;
    bool b1 = true;
    vector<int> loop1(9,0);
    for(int i = 0; i < N1/numMax; i++){
        loop1[i] = numMax;
    }
    loop1[N1/numMax] = N1%numMax;
    while(b1){
        //for(int i : loop1) cout << i;
        //cout << endl;
        hand h(0);
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < loop1[i]; j++){
                h.insert(i+1);
            }
        }
        V1.push_back(h);
        b1 = false;
        bool zero = true;
        for(int i = 0; i < 9; i++){
            b1 = true;
            if(zero) b1 = false;
            if(loop1[i] != 0) zero = false;
            if(!b1) continue;
            b1 = false;
            if(loop1[i] == numMax) continue;
            b1 = true;
            loop1[i]++;
            int s = -1;
            for(int j = 0; j < i; j++){
                s += loop1[j];
            }
            //cout << s << endl;
            for(int j = 0; j < i; j++){
                loop1[j] = 0;
            }
            for(int j = 0; j < s/numMax; j++){
                loop1[j] = numMax;
            }
            loop1[s/numMax] = s%numMax;
            break;
        }
    }

    bool b2 = true;
    vector<int> loop2(5,0);
    for(int i = 0; i < N2/numMax; i++){
        loop2[i] = numMax;
    }
    loop2[N2/numMax] = N2%numMax;
    while(b2){
        //for(int i : loop2) cout << i;
        //cout << endl;
        hand h(0);
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < loop2[i]; j++){
                h.insert(i+10);
            }
        }
        V2.push_back(h);
        b2 = false;
        bool zero = true;
        for(int i = 0; i < 5; i++){
            b2 = true;
            if(zero) b2 = false;
            if(loop2[i] != 0) zero = false;
            if(!b2) continue;
            b2 = false;
            if(loop2[i] == numMax) continue;
            if(i == 4 && loop2[i] == XMax) continue;
            b2 = true;
            loop2[i]++;
            int s = -1;
            for(int j = 0; j < i; j++){
                s += loop2[j];
            }
            //cout << s << endl;
            for(int j = 0; j < i; j++){
                loop2[j] = 0;
            }
            for(int j = 0; j < s/numMax; j++){
                loop2[j] = numMax;
            }
            loop2[s/numMax] = s%numMax;
            break;
        }
    }
    //return;

    set<pair<mpz_class,string>> outputList;
    for(hand g : V1){
        for(hand h : V2){
            string s = max_prime(g+h);
            if(s[0] == '-') continue;
            mpz_class n = str_to_int(s);
            outputList.insert({n,s});
        }
    }
    /*cnt += 2+outputList.size();
    if(cnt > 1000000){
        bl = false;
        return;
    }*/
    outputfile << N << " " << M << "\n";
    for(auto [n,s] : outputList){
        outputfile << s << "," << n << "\n";
    }

}

void calc2(){
    /*for(int i = 1; i <= 13; i++){
        for(int j = i+max(0,i-9); j <= i+min(i,4); j++){
            cout << i << " " << j << endl;
            calc1(i,j);
        }
    }*/
    /*for(int n = 3; n <= 3; n++){
        for(int i = n; i <= n+18; i++){
            cout << i << " " << 2*i-n << endl;
            calc1(i,2*i-n);
        }
    }*/
    for(int j = 1; j <= 1; j++){
        for(int i = 0; i <= 36; i++){
            if(i+j == 0) continue;
            cout << i+j << " " << i+j*2 << endl;
            calc1(i+j, i+j*2);
        }
    }
}

void calc3(){
    set<tuple<int,mpz_class,string>> outputList;
    int N = 15;
    int K; cin >> K;
    for(int i = 0; i < K; i++){
        string s; cin >> s;
        vector<int> loopMax(N,0);
        for(char c : s){
            loopMax[char_to_int(c)]++;
        }
        vector<int> loopNow(N,0);
        bool b = true;
        while(b){
            hand h;
            for(int i = 0; i < N; i++){
                for(int j = 0; j < loopNow[i]; j++){
                    h.insert(i);
                }
            }
            string t = max_prime(h);
            outputList.insert({t.size(), str_to_int(t), t});
            b = false;
            for(int i = 0; i < N; i++){
                if(loopNow[i] == loopMax[i]) continue;
                b = true;
                loopNow[i]++;
                for(int j = 0; j < i; j++){
                    loopNow[j] = 0;
                }
                break;
            }
        }
    }

    for(auto [a, n, t] : outputList){
        if(n > 0) outputfile << t << "," << n << endl;
    }
}

int main(){
    calc3();
}
