#include <bits/stdc++.h>
using namespace std;

#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;

Bint gcd(Bint n, Bint m){
    if(n < 0 || m < 0) return gcd(abs(n), abs(m));
    if(n < m) return gcd(m, n);
    if(m == 0) return n;
    return gcd(m, n%m);
}

struct quo {
    Bint num;
    Bint den;
    quo() {
        num = 0;
        den = 1;
    }
    quo(Bint num_, Bint den_) {
        num = num_;
        den = den_;
    }
    quo operator+(const quo &q) {
        quo ret;
        ret.num = num*q.den+den*q.num;
        ret.den = den*q.den;
        Bint gcd_nd = gcd(ret.num, ret.den);
        ret.num /= gcd_nd;
        ret.den /= gcd_nd;
        return ret;
    }
    quo operator-(const quo &q) {
        quo ret;
        ret.num = num*q.den-den*q.num;
        ret.den = den*q.den;
        Bint gcd_nd = gcd(ret.num, ret.den);
        ret.num /= gcd_nd;
        ret.den /= gcd_nd;
        return ret;
    }
    quo operator*(const quo &q) {
        quo ret;
        ret.num = num*q.num;
        ret.den = den*q.den;
        Bint gcd_nd = gcd(ret.num, ret.den);
        ret.num /= gcd_nd;
        ret.den /= gcd_nd;
        return ret;
    }
    quo operator/(const quo &q) {
        quo ret;
        ret.num = num*q.den;
        ret.den = den*q.num;
        Bint gcd_nd = gcd(ret.num, ret.den);
        ret.num /= gcd_nd;
        ret.den /= gcd_nd;
        return ret;
    }
    void print(){
        cout << num << "/" << den;
    }
    quo make_quo(Bint n, Bint m){
        quo ret(n,m);
        return ret;
    }
};

bool operator==(quo q, Bint r){
    if(q.num == q.den*r) return true;
    return false;
}

bool operator==(quo q, quo r){
    if(q/r == 1) return true;
    return false;
}


struct p_nom {
    vector<quo> f;

    p_nom(){
        f.resize(1);
    }
    p_nom(int n){
        f.resize(n+1);
    }

    void print(){
        cout << "[ ";
        for(int i = 0; i < f.size(); i++){
            if(i != 0) cout << ", ";
            f.at(i).print();
        }
        cout << " ]";
    }
    int order(){
        return f.size()-1;
    }
    quo at(int n){
        return f[n];
    }
    void sbs(int n, quo q){
        f[n] = q;
    }
};
p_nom operator+(p_nom f, p_nom g){
    p_nom ret(max(f.order(),g.order()));
    for(int i = 0; i <= f.order(); i++){
        ret.sbs(i,f.at(i));
    }
    for(int i = 0; i <= g.order(); i++){
        ret.sbs(i, ret.at(i) + g.at(i) );
    }
    return ret;
}
p_nom operator-(p_nom f, p_nom g){
    p_nom ret(max(f.order(),g.order()));
    for(int i = 0; i <= f.order(); i++){
        ret.sbs(i,f.at(i));
    }
    for(int i = 0; i <= g.order(); i++){
        ret.sbs(i, ret.at(i) - g.at(i) );
    }
    return ret;
}
p_nom operator*(p_nom f, p_nom g){
    p_nom ret(f.order()+g.order());
    for(int i = 0; i <= f.order()+g.order(); i++){
        quo ret_i;
        for(int j = max(0, i-g.order()); j <= min(f.order(), i); j++){
            ret_i = ret_i + f.at(j)*g.at(i-j);
        }
        ret.sbs(i,ret_i);
    }
    return ret;
}


int main(){
    quo q(1,1);
    p_nom f(1);
    for(int i = 0; i <= 1; i++) f.sbs(i,q);
    f.print(); cout << endl;
    p_nom g = f;
    for(int i = 0; i < 10; i++){
        g = g*f;
    }
    g.print(); cout << endl;
}