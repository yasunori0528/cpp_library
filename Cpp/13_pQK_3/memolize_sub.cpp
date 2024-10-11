#include <bits/stdc++.h>
using namespace std;

vector<char> card = {'1','2','3','4','5','6','7','8','9','T','J','Q','K','X'};

int64_t str2int(string s){
    int64_t rtn = 0;
    for(char c : s){
        if('0' <= c && c <= '9') rtn = rtn*10+(c-'0');
        else if(c == 'T') rtn = rtn*100+10;
        else if(c == 'J') rtn = rtn*100+11;
        else if(c == 'Q') rtn = rtn*100+12;
        else if(c == 'K') rtn = rtn*100+13;
    }
    return rtn;
}

bool isPrime(int64_t n){
    if(n < 2) return false;
    for(int64_t i = 2; i*i <= n; i++){
        if(n%i == 0) return false;
    }
    return true;
}

bool obviousNotPrime(string s){
    bool b2 = true;
    for(char c : s){
        if(c == '1' || c == '3' || c == '7' || c == '9' || c == 'J' || c == 'K'){
            b2 = false;
            break;
        }
    }
    if(b2) return true;

    int n = str2int(s)%3;
    bool b3 = (n%3 == 0);
    if(b3) return true;

    bool b11 = (n%11 == 0);
    for(char c : s){
        if('0' <= c && c <= '9'){
            b11 = false;
            break;
        }
    }
    if(b11) return true;

    if(s.size() == 4){
        sort(s.begin(),s.end());
        if(s[0] == s[3]) return true;
        if((s[3] <= '9' || s[0] > '9') && s[0] == s[1] && s[2] == s[3]) return true;
    }

    return false;
}

int64_t maxPrime(string s){
    if(obviousNotPrime(s)) return -1;
    sort(s.begin(),s.end());
    int64_t rtn = 0;
    do{
        int64_t p = str2int(s);
        if(rtn < p && isPrime(p)) rtn = p;
    }while(next_permutation(s.begin(),s.end()));
    return rtn;
}

int main(){
    int n = 4;
    int m = 13;
    vector<int> loopNow;
    for(int i = 0; i < n; i++) loopNow.push_back(i);
    loopNow.push_back(n+m-1);

    vector<tuple<int64_t,string,int>> output;
    while(1){
        string s;
        for(int i = 0; i < n; i++){
            s.push_back(card[loopNow[i]-i]);
        }
        int64_t x = maxPrime(s);
        if(x >= 0) output.push_back({x, s, 0});

        bool b2 = false;
        for(int i = 0; i < n; i++){
            if(loopNow[i] < loopNow[i+1]-1){
                b2 = true;
                for(int j = 0; j < i; j++){
                    loopNow[j] = j;
                }
                loopNow[i]++;
                break;
            }
        }
        if(!b2) break;
    }

    sort(output.begin(),output.end());
    cout << output.size() << " 0" << endl;
    for(auto tp : output){
        string s;
        int64_t a, f;
        tie(a, s, f) = tp;
        cout << s << " " << a << " " << f << " 0 0 0" << endl;
    }
}