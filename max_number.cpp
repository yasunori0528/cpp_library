#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using bigint = mpz_class;

#include "rand.cpp"
#include "time.cpp"
#include "math.cpp"
#include "miller_labin.cpp"
#include "card.cpp"

bool number_test(word x){
    return miller_rabin(x.val);
}

bool max_nutural_sub(word s, word t){
    return (s * t).val > (t * s).val;
}

word hand_upper_bound(vector<word> v){
    sort(v.begin(), v.end(), max_nutural_sub);
    word s;
    for(auto vi : v) s = s * vi;
    return s;
}

set<pair<uint64_t, bigint>> checked;

bool skip_calc(word w, vector<word> rest){
    if(checked.count({w.hash, w.val})) return true;
    if(rest.size() == 0) return false;

    bool include_X = false;
    for(auto i : rest){
        for(char c : i.str){
            if(c == 'X') include_X = true;
            break;
        }
        if(include_X) break;
    }

    if(!include_X){
        bigint mod3 = w.val;
        for(auto i : rest){
            mod3 += i.val;
        }
        mod3 %= 3;
        if(mod3 == 0) return true;
    }


    for(auto i : rest){
        if(i.val%2 != 0 && i.val%5 != 0) return false;
    }

    return true;
}

word max_number(vector<word> v){
    if(v.size() == 0) return word();
    if(v.size() == 1 && v[0].str == "X") return v[0];

    priority_queue<tuple<bigint, word, vector<word>>> q;
    q.push({hand_upper_bound(v).val, word(), v});

    word rtn;
    while(q.size()){
        auto[max_x, w, rest] = q.top();
        q.pop();

        if(max_x < rtn.val) break;

        if(rest.size() == 0){
            if(w.val > rtn.val && number_test(w)){
                rtn = w;
            }
            continue;
        }

        int rest_sz = rest.size();
        set<string> checked;
    }
}

int main(){
    ;
}