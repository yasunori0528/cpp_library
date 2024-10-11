#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int64_t i = 0; i < (int64_t)(n); i++)

int main(){
    srand(time(NULL));
    rep(looop, 10){
        string s;
        rep(i,54){
            if(rand()%2){
                int n = i/4+1;
                char c;
                if(n < 10) c = '0'+n;
                else if(n == 10) c = 'T';
                else if(n == 11) c = 'J';
                else if(n == 12) c = 'Q';
                else if(n == 13) c = 'K';
                else c = 'X';
                s += c;
            }
        }
        if(s.size() <= 150) cout << s << endl;
    }    
}