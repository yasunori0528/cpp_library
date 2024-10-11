#include <bits/stdc++.h>
using namespace std;

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;
// 仮数部が1024ビットの浮動小数点数型(TLEしたら小さくする)
using Real = mp::number<mp::cpp_dec_float<1024>>;

//n^a%p
Bint powmod(Bint n, Bint a, Bint p){
    if(a == 0) return 1;
    n %= p;
    Bint b = a/2;
    Bint c = a%2;
    Bint nb = powmod(n, b, p);
    Bint rtn = 1;
    if(c) rtn = n;
    rtn = (rtn*nb*nb)%p;
    return rtn;
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
vector<char> card;
void calc_card(){
    for(int i = 0; i < 10; i++){
        card.push_back('0'+i);
    }
    card.push_back('T');
    card.push_back('J');
    card.push_back('Q');
    card.push_back('K');
    card.push_back('X');
}
map<char,int> str_to_map(string s){
    map<char,int> x;
    for(char c : s){
        for(char cd : card){
            if(c == cd){
                x[c]++;
            }
        }
    }
    return x;
}

vector<int64_t> prime_list = {2, 3};
void prime_calc(int64_t n){
    vector<bool> natural_number(n+1,true);
    int64_t i = 0;
    bool b = true;
    while(b){
        int64_t pi = prime_list[i];
        for(int64_t kpi = 2*pi; kpi <= n; kpi += pi){
            natural_number[kpi] = false;
        }
        int64_t pi_;
        for(int64_t j = pi+1; j <= n; j++){
            if(natural_number[j]){
                pi_ = j;
                break;
            }
        }
        int64_t maxj = min(pi_*pi_-1, n);
        if(maxj == n) b = false;
        for(int64_t j = pi*pi+1; j <= maxj ; j++){
            if(natural_number[j]) prime_list.push_back(j);
        }
        i++;
    }
}

bool is_prime(int64_t n){
    for(int64_t i = 0; i < prime_list.size()-1; i++){
        int64_t p = prime_list[i]; 
        if(n%p == 0) return false;
        int64_t p_ = prime_list[i+1];
        if(p_*p_ > n) return true;
    }
    return false;
}

bool MRpt(Bint n){
    //cout << n << endl;
    if(n < 2) return false;
    if(n == 2) return true;
    if(n%2 == 0) return false;

    int k = 10;

    Bint s = n-1;
    int e = 0;
    //n-1 = s*2^e
    while(s%2 == 0){
        s /= 2;
        e++;
    }
    //cout << n << "=" << s << "*2^" << e << endl;

    for(int i = 0; i < k; i++){
        Bint a = rand()%(n-3)+2;
        //cout << "ai : " << a << endl;
        Bint as = powmod(a,s,n);
        bool c = false;
        if(as == 1 || as == n-1) c = true;
        Bint asj = as;
        for(int j = 1; j < e; j++){
            asj = asj*asj%n;
            if(asj == n-1) c = true;
        }
        if(!c) return false;
    }
    return true;
}

bool tumi(string s){
    if(strtoint(s)%3 == 0) return true;
    else{
        for(char c : s){
            if(c == '1' || c == '3' || c == '7' || c == '9' || c == 'J' || c == 'K') return false;
        }
    }
    return true;
}

int main() {
    auto start = chrono::system_clock::now();

    Bint a = 1;

    while(1){
        a *= 10;
        Bint b = a+1;
        Bint c = b;
        Bint d = 1;
        for(Bint i = 7; i*i <= c; i++){
            if(c%(i*i) == 0){
                d *= i;
            }
            else if(c%i == 0){
                c /= i;
            }
        }
        if(d > 1){
            Bint e = b/d/d;
            cout << b << "=" << d << "^2*" << e << endl;
            for(Bint i = d/4; i < d; i++){
                Bint f = e*i*i;
                if((b-1)/10 <= f){
                    cout << f*b << endl;
                }
            }
        }
    }

    auto end = chrono::system_clock::now();
    auto dur = end-start;
    auto msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
    cout << msec << "[ms]" << endl;

}