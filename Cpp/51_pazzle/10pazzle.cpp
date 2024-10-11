#include <bits/stdc++.h>
using namespace std;

struct quoz{
    int64_t num;
    int64_t den;
    bool error;

    quoz operator+(quoz p){
        if(error || p.error){
            return quoz(0,0);
        }
        int64_t d = lcm(den, p.den);
        int64_t n = d/den*num + d/p.den*p.num;
        quoz rtn(n,d);
        return rtn;
    }
    quoz operator-(quoz p){
        if(error || p.error){
            return quoz(0,0);
        }
        int64_t d = lcm(den, p.den);
        int64_t n = d/den*num - d/p.den*p.num;
        quoz rtn(n,d);
        return rtn;
    }
    quoz operator*(quoz p){
        if(error || p.error){
            return quoz(0,0);
        }
        int64_t d = den*p.den;
        int64_t n = num*p.num;
        quoz rtn(n,d);
        return rtn;
    }
    quoz operator/(quoz p){
        if(error || p.error){
            return quoz(0,0);
        }
        int64_t d = den*p.num;
        int64_t n = num*p.den;
        quoz rtn(n,d);
        return rtn;
    }
    bool operator<(quoz p){
        return num*p.den < den*p.num;
    }

    quoz(){
        error = false;
        num = 0;
        den = 1;
    }
    quoz(int64_t x){
        error = false;
        num = x;
        den = 1;
    }
    quoz(int64_t x, int64_t y){
        if(y == 0){
            error = true;
            x = 0;
            y = 0;
        }
        else{
            error = false;
            int64_t g = gcd(x,y);
            num = x/g;
            den = y/g;
        }
        
    }
};
bool operator<(quoz p, quoz q){
    return p.num*q.den < p.den*q.num;
}

double dec(quoz q){
    double rtn = (double)q.num/q.den;
    return rtn;
}
void print(quoz q){
    cout << q.num << "/" << q.den;
}

int main(){
    map<map<int,int>,map<quoz,int>> mp;
    int n = 10;
    int m = 3;
    for(int j = 0; j < n; j++){
        quoz r(j);
        map<int,int> mpj1;
        mpj1[j] = 1;
        map<quoz,int> mpj2;
        mpj2[r] = 1;
        mp[mpj1] = mpj2;
    }

    for(int i = 2; i <= m; i++){
        vector<int> loop_now(i,0);
        while(1){
            //for(int k : loop_now) cout << k << " "; cout << endl;
            map<int,int> mp1;
            map<quoz,int> mp2;
            for(int j : loop_now) mp1[j]++;
            
            
            bool b = false;
            for(int k = 0; k < i; k++){
                if(loop_now[k] == n-1) continue;
                loop_now[k]++;
                for(int l = 0; l < k; l++){
                    loop_now[l] = loop_now[k];
                }
                b = true;
                break;
            }
            if(!b) break;
        }
    }

    for(auto pr : mp){
        string s;
        for(auto pr1 : pr.first){
            for(int i = 0; i < pr1.second; i++){
                s.push_back('0'+pr1.first);
            }
        }
        cout << s << endl;
        for(auto pr2 : pr.second){
            print(pr2.first);
            cout << " " << pr2.second << endl;
        }
    }
}