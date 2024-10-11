#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

int digit(mpz_class n){
    if(n == 0) return 0;
    if(n < 10) return 1;
    else return digit(n/10)+1;
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

int main(){
    string S; cin >> S;
    int N = S.size();

    sort(S.begin(), S.end());
    do{
        for(int i = 1; i < N; i++){
            for(int j = i+1; j < N; j++){
                mpz_class x = str_to_int(S.substr(0, i));
                mpz_class y = str_to_int(S.substr(i, j - i));
                mpz_class z = str_to_int(S.substr(j));
                if(x == y * z) cout << x << " = " << y << " * " << z << endl;
            }
        }
    }while(next_permutation(S.begin(), S.end()));
    
}
//n倍メーカーソルバー
