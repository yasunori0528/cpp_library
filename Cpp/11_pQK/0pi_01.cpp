#include <bits/stdc++.h>
using namespace std;

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;
using Real = mp::number<mp::cpp_dec_float<1024>>;

string Bint_to_str(Bint n){
    if(n == 0) return "0";

    string rtn;
    while(n > 0){
        Bint k = n%10;
        rtn = (char)('0'+(int)k) + rtn;
        n /= 10;
    }
    return rtn;
}

Bint sqrt_(Bint n){
    Bint s = 0;
    Bint l = 1;
    while(l*l < n){
        s = l;
        l *= 2;
    }
    bool b = true;
    while(b){
        Bint m = (s+l)/2;
        Bint msq = m*m;
        Bint msq_ = (m+1)*(m+1);
        if(n < msq){
            l = m;
        }
        else if(n < msq_){
            return m;
        }
        else if(n == msq_) return m+1;
        else {
            s = m+1;
        }
    }
    return 0;
}
int main(){
    //for(int i = 1; i < 100; i++) cout << i << "," << sqrt_(i) << endl;
    int input; cin >> input;
    vector<tuple<Bint,Bint,Bint>> vec;
    for(int i = 1; i <= input; i++){
        for(int j = i-1; j > 0; j -= 2){
            int a, b, c;
            a = i*i-j*j;
            b = 2*i*j;
            c = i*i+j*j;
            if(a > b) swap(a,b);
            vec.push_back(make_tuple(a,b,c));
        }
    }
    Bint lcm_c = 1;
    for(tuple<Bint,Bint,Bint> t : vec){
        lcm_c = lcm(lcm_c, get<2>(t));
    }
    for(tuple<Bint,Bint,Bint> &t : vec){
        Bint k = lcm_c/get<2>(t);
        get<0>(t) *= k;
        get<1>(t) *= k;
        get<2>(t) *= k;
    }
    sort(vec.begin(), vec.end());
    
    int n = vec.size();
    Bint a_, b_;
    Bint l = 0;
    for(int i = 0; i < n; i++){
        Bint a, b;
        tie(a, b, ignore) = vec[i];
        if(i == n-1){
            l += sqrt_(2*(a-b)*(a-b));
        }
        if(i == 0){
            l += 2*sqrt_(a*a+(lcm_c-b)*(lcm_c-b));
        }
        else{
            l += 2*sqrt_((a_-a)*(a_-a)+(b_-b)*(b_-b));
        }
        a_ = a;
        b_ = b;
    }
    cout << 2*l << "\n/\n" << lcm_c << endl;
}