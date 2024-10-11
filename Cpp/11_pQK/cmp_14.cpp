#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;

//x^y
int64_t power(int64_t x, int64_t y){
    if(y < 0) return 0;
    else{
        int64_t n = 1ll;
        for(int64_t i = 0; i < y; i++) n *= x;
        return n;
    }
}

string int_str(int64_t n){
    int64_t d = 0;
    int64_t m = n;
    string s;
    while(m > 0){
        m /= 10;
        d++;
    }
    int64_t i = d-1;
    while(i >= 0){
        int64_t k_i0 = n%power(10,i+1)/power(10,i);
        int64_t k_i1;
        if(i > 0) k_i1 = n%power(10,i)/power(10,i-1);
        if(k_i0 == 1 && k_i1 < 4 && i > 0){
            if(k_i1 == 0) s.push_back('T');
            else if(k_i1 == 1) s.push_back('J');
            else if(k_i1 == 2) s.push_back('Q');
            else if(k_i1 == 3) s.push_back('K');
            i -= 2;
        }
        else{
            char c = '0'+k_i0;
            s.push_back(c);
            i--;
        }
    }
    return s;
}
int64_t str_int(string s){
    int64_t n = 0;
    for(char c : s){
        if(c == 'T') n = n*100+10;
        else if(c == 'J') n = n*100+11;
        else if(c == 'Q') n = n*100+12;
        else if(c == 'K') n = n*100+13;
        else n = n*10+(c-'0');
    }
    return n;
}
string to_string_Bint(Bint n){
    if(n == 0) return "0";

    string rtn;
    while(n > 0){
        Bint k = n%10;
        rtn = (char)('0'+(int)k) + rtn;
        n /= 10;
    }
    return rtn;
}
Bint str_int_Bint(string s){
    Bint n = 0;
    for(char c : s){
        if(c == 'T') n = n*100+10;
        else if(c == 'J') n = n*100+11;
        else if(c == 'Q') n = n*100+12;
        else if(c == 'K') n = n*100+13;
        else n = n*10+(c-'0');
    }
    return n;
}

//x^y,10^d未満, 0 <= x, 0 <= y, 大きすぎるものは-1を返す
Bint power(Bint x, Bint y, int d){
    if(y < 0 || x < 0) return -1;
    if(x == 0) return 0;
    if(x == 1 || y == 0) return 1;
    Bint rtn = 1;
    rep(i,y){
        rtn *= x;
        if(to_string_Bint(rtn).size() > d){
            rtn = -1;
            break;
        }
    }
    return rtn;
}
//x^y%p
Bint powermod(Bint x, Bint y, Bint p){
    if(y < 0) return 0;
    else{
        Bint n = 1;
        x %= p;
        for(int64_t i = 0; i < y; i++){
            n = n*x%p;
        }
        return n;
    }
}
//素数計算
vector<int64_t> ntrl;
vector<int64_t> prime;
int64_t maxn;
void prime_calculate(){
    rep(i,maxn){
        if(i <= 1) ntrl.push_back(-1);
        else ntrl.push_back(i);
    }
    prime = {2,3};
    int64_t maxi = sqrt(maxn);
    rep(i,maxi){
        int64_t p = prime[i];
        int64_t q = prime[i+1];
        for(int64_t j = p*p; j < maxn; j += p) ntrl[j] = -1;
        for(int64_t k = p*p+1; k < q*q && k < maxn; k++){
            if(ntrl[k] > 0) prime.push_back(k);
        }
    }
    cout << "prime calculated" << endl;
}
bool pt(int64_t n,vector<int64_t>vec){
    if(n <= 1) return false;
    int64_t s = vec.size();
    for(int64_t i = 0; i < s; i++){
        if(vec[i]*vec[i] > n) return true;
        else if(n%vec[i] == 0) return false;    
    }
    return false;
    cout << "Insuficuent_Prime_List" << endl;
}

vector<char> card = {'0','1','2','3','4','5','6','7','8','9','T','J','Q','K'};
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

bool MRpt(Bint n){
    if(n <= 1) return 0;
    if(n == 2) return 1;
    if(n%2 == 0) return 0;
    Bint s = 0;
    Bint d = n-1;
    while(d&1 == 0){
        d = d >> 1;
        s++;
    }
    //cout << n-1 << "= 2^" << s << "*" << d << endl;

    int k = 10;
    rep(looop,k){
        Bint a = rand()+1;
        if(a >= n){
            a = a%(n-2)+1;
        }
        Bint powmod_a_d_n = powermod(a,d,n);
        if(powmod_a_d_n == 1){
            //cout << n << "," << a << endl;
            continue;
        }
        bool bk = false;
        rep(i,s){
            if(powmod_a_d_n == n-1){
                //cout << n << "," << a << "," << i << endl;
                bk = true;
                break;
            }
            powmod_a_d_n = powmod_a_d_n*powmod_a_d_n%n;
        }
        if(bk) continue;
        return 0;
    }
    return 1;
}

// N = 2^a*P(n,2n)
int main(){
    int TIME = time(NULL);//開始時刻
    int time_count = 0;
    int time_interval = 60;
    srand(time(NULL));

    //maxn = power(10,8);
    //prime_calculate();

    Bint lower_bound_of_search_range =
    //power(2,122,72)*131613121;
    //power(2,93,72)*131010111311;
    power(2,70,72)*str_int_Bint("JKTJQQTTJK");

    Bint upper_bound_of_search_range = power(10,72-33,100);

    vector<Bint> power2(1,1);
    Bint power2i = 1;
    rep(i,256){
        power2i *= 2;
        power2.push_back(power2i);
    }

    vector<char> Card = {'T','J','Q','K'};
    int amin = 43-4;
    int amax = 46-3;
    for(int d = 15; d <= 15; d++){
        int64_t maxi = 1<<(2*d);
        for(int64_t i = 1; i < maxi; i+=2){
            string s;
            int64_t j = i;
            rep(looop,d){
                s = Card[j%4] + s;
                j /= 4;
            }
            Bint s_int = str_int_Bint(s);
            //if(!pt(s_int,prime)) continue;
            if(__gcd((int)(s_int%210),210) != 1) continue;
            string s_ = to_string_Bint(s_int);
            if(pqkable2(s_) > 2) continue;
            Bint n = power2[amin-1]*s_int;
            for(int a = amin; a <= amax; a++){
                n *= 2;
                if(n < lower_bound_of_search_range) continue;
                if(n >= upper_bound_of_search_range){
                    amax = a-1;
                    break;
                }
                if(a == amin){
                    amin--;
                    cout << "amin--;" << endl;
                }
                string s1 = "2^"+to_string(a)+"*"+s_+"=";
                string s2 = to_string_Bint(n);
                string s3 = s1+s2;
                if(pqkable2(s3) <= 2){
                    //lower_bound_of_search_range = n;
                    //amin = a;
                    cout << s1 << "\n" << s2 << endl;
                    cout << "a_in_[" << amin << "," << amax << "]" << endl;
                    //string sss; cin >> sss;
                }

                {
                    int Time = time(NULL);
                    if(Time-TIME >= time_interval){
                        time_count += Time-TIME;
                        cout << "time:" << time_count << "///" << s1 << endl;
                        cout << "a_in_[" << amin << "," << amax << "]" << endl;
                        TIME = Time;
                    }
                }
            }
            if(amin > amax) break;
        }

        {
            int Time = time(NULL);
            time_count += Time-TIME;
            cout << "time:" << time_count << "///end:d:" << d << ",a_in_[" << amin << "," << amax << "]" << endl;
            TIME = Time;
        }

        amin -= 4;
        amax -= 3;
    }
        
    

    int Time_end = time(NULL);
    time_count += Time_end-TIME;
    cout << "time:" << time_count << "///" << endl;
}