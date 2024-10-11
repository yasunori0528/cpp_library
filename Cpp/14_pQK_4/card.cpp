#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

random_device seed_gen;
mt19937 engine(seed_gen());

bigint pow(bigint x, bigint y){
    assert(y >= 0);
    assert(!(x == 0 && y == 0));

    if(x == 0) return 0;
    if(y == 0) return 1;
    if(x == 1) return 1;
    if(y == 1) return x;

    vector<pair<bigint, bigint>> a = {{y, y}};
    while(1){
        auto [l, r] = *a.rbegin();
        if(l == 0) break;
        a.push_back({l / 2, (r + 1) / 2});
    }

    int n = a.size();
    vector<pair<bigint, bigint>> pow_list(n);
    for(int i = n - 1; i >= 0; i--){
        auto [l, r] = a[i];
        auto &[pl, pr] = pow_list[i];

        if(l == 0) pl = 1;
        else if(l == 1) pl = x;
        else if(l % 2 == 0) pl = pow_list[i + 1].first * pow_list[i + 1].first;
        else pl = pow_list[i + 1].first * pow_list[i + 1].second;

        if(r == l) pr = pl;
        else if(r == 0) pr = 1;
        else if(r == 1) pr = x;
        else if(r % 2 == 0) pr = pow_list[i + 1].second * pow_list[i + 1].second;
        else pr = pow_list[i + 1].first * pow_list[i + 1].second;
    }

    return pow_list[0].first;
}

const string alphabet = "0123456789TJQKXabcdefghijklmn";

struct word {
    int len;
    string str;
    int digit;
    bigint val;

    word(){
        len = 0;
        str = "";
        digit = 0;
        val = 0;
    }

    word(char c){
        if('0' <= c && c <= '9') val = c - '0';
        else if('a' <= c && c <= 'n') val = c - 'a';
        else if(c == 'T') val = 10;
        else if(c == 'J') val = 11;
        else if(c == 'Q') val = 12;
        else if(c == 'K') val = 13;
        else {
            cout << "!Wrong Argument" << endl;
            assert(false);
        }

        digit = (val < 10) ? 1 : 2;
        len = 1;
        str = string(1, c);
    }

    word operator*(word other){
        word rtn;
        rtn.len = len + other.len;
        rtn.str = str + other.str;
        rtn.digit = digit + other.digit;
        rtn.val = val * pow(bigint(10), other.digit) + other.val;
        return rtn;
    }
};

int main(){
    string s; cin >> s;
    word w;
    for(char c : s){
        w = w * word(c);
    }
    cout << w.str << endl;
    cout << w.val << endl;
}